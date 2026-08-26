#define _DEFAULT_SOURCE
#define _BSD_SOURCE

#include "./ui.h"
#include "pthreadpool.h"
#include "xiangqi_arr.h"
#include <arpa/inet.h>
#include <fcntl.h>
#include <linux/input.h> // 输入子系统头文件
#include <netinet/in.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <unistd.h>

// 弹窗相关外部声明
extern lv_obj_t *ui_gamewinCon;
extern lv_obj_t *ui_gamelowCon;
extern lv_obj_t *ui_showWin;
extern lv_obj_t *ui_showLow;

// 弹窗类型枚举
typedef enum {
  DUISHOU_HUIHE, // 不是我的回合（对方回合）
  MY_HUIHE,      // 不是我的棋子（我的回合但不能点对方棋子）
  EAT,           // 吃子提示
  DUISHOU_EAT,   // 被吃子提示（对方吃我）
  WIN,           // 胜利
  LOSE           // 失败
} popup_type_t;

// 弹窗定时器关闭回调函数
static void popup_timer_close_cb(lv_timer_t *timer)
{
    lv_obj_t *win_con = (lv_obj_t *)timer->user_data;
    lv_obj_add_flag(win_con, LV_OBJ_FLAG_HIDDEN);
    lv_timer_del(timer);
}

// 隐藏对象（确保隐藏成功）
static void hide_object_safe(lv_obj_t *obj)
{
    if (!lv_obj_has_flag(obj, LV_OBJ_FLAG_HIDDEN)) {
        printf("警告：对象未隐藏，重新设置隐藏\n");
        lv_obj_add_flag(obj, LV_OBJ_FLAG_HIDDEN);
    }
}

// 显示对象（确保显示成功）
static void show_object_safe(lv_obj_t *obj)
{
    if (lv_obj_has_flag(obj, LV_OBJ_FLAG_HIDDEN)) {
        printf("警告：对象仍处于隐藏状态，重新取消隐藏\n");
        lv_obj_clear_flag(obj, LV_OBJ_FLAG_HIDDEN);
    }
}

// 显示提示弹窗
static void show_popup_message(popup_type_t type, const char *message) {
  // 先隐藏所有弹窗（使用安全函数）
  hide_object_safe(ui_gamewinCon);
  hide_object_safe(ui_gamelowCon);

  // 根据类型显示不同的弹窗（使用安全函数）
  switch (type) {
  case DUISHOU_HUIHE:
    // 不是我的回合 - 使用失败弹窗显示
    show_object_safe(ui_gamelowCon);
    break;

  case MY_HUIHE:
    // 不是我的棋子 - 使用失败弹窗显示
    show_object_safe(ui_gamelowCon);
    break;

  case EAT:
    // 吃子提示 - 使用胜利弹窗显示
    // show_object_safe(ui_gamewinCon);
    break;

  case DUISHOU_EAT:
    // 被吃子提示 - 不显示弹窗，只显示日志
    // （只有将/帅被吃才显示失败弹窗，在单独的地方处理）
    printf("【被吃】%s\n", message);
    return;  // 直接返回，不显示弹窗，不启动定时器

  case WIN:
    // 胜利
    show_object_safe(ui_gamewinCon);
    break;

  case LOSE:
    // 失败
    show_object_safe(ui_gamelowCon);
    break;
  }

  // 2 秒后自动关闭弹窗
  lv_obj_t *target_con =
      (type == WIN || type == EAT) ? ui_gamewinCon : ui_gamelowCon;
  lv_timer_t *timer = lv_timer_create(popup_timer_close_cb, 2000, target_con);
  lv_timer_set_repeat_count(timer, 1);
}

// 蜂鸣器鸣笛函数
// frequency: 频率（Hz），duration_ms: 持续时间（毫秒）
static void beep_buzzer(int set_hz, int set_ms) {
  // 通过路径打开驱动
  int fd = open("/dev/input/event0", O_WRONLY);
  if (fd < 0) {
    perror("open event0 failed");
    return;
  }

  // 输入子系统结构体 设置频率
  struct input_event event;
  event.type = EV_SND;   // 事件的类型 - 声音
  event.code = SND_TONE; // 事件的编码 - 音调
  event.value = set_hz;  // 事件的值 - 频率

  // 写入状态 - 开始鸣叫
  if (write(fd, &event, sizeof(event)) < 0) {
    perror("write beep failed");
    close(fd);
    return;
  }

  // 持续指定时间
  usleep(set_ms * 1000);

  // 归零 - 停止鸣叫
  event.value = 0;
  if (write(fd, &event, sizeof(event)) < 0) {
    perror("write stop failed");
  }

  close(fd);
}

// 强制停止蜂鸣器（用于异常情况下关闭蜂鸣器）
static void stop_buzzer_force(void) {
  int fd = open("/dev/input/event0", O_WRONLY);
  if (fd < 0) {
    return;
  }

  struct input_event event;
  event.type = EV_SND;
  event.code = SND_TONE;
  event.value = 0; // 停止鸣叫

  write(fd, &event, sizeof(event));
  close(fd);
}

// my_zhenyin: 0=红方，1=黑方
static void set_mycolors(int my_zhenyin) {
  lv_color_t my_color, duishou_color;

  if (my_zhenyin == 0) // 红方
  {
    my_color = lv_color_hex(0xFF0000);      // 红色
    duishou_color = lv_color_hex(0x000000); // 黑色

    // 设置标签文本
    lv_label_set_text(ui_myWin, "我方红棋");
    lv_label_set_text(ui_duishouWin, "敌方黑棋");
  } else // 黑方
  {
    my_color = lv_color_hex(0x000000);      // 黑色
    duishou_color = lv_color_hex(0xFF0000); // 红色

    // 设置标签文本
    lv_label_set_text(ui_myWin, "我方黑棋");
    lv_label_set_text(ui_duishouWin, "敌方红棋");
  }

  // 设置我方标签颜色（红色或黑色）
  lv_obj_set_style_text_color(ui_mytimecount, my_color,
                              LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_text_color(ui_mytimedanwei, my_color,
                              LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_text_color(ui_myWin, my_color,
                              LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_text_color(ui_myshengyu, my_color,
                              LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_text_color(ui_myqiziCount, my_color,
                              LV_PART_MAIN | LV_STATE_DEFAULT);

  // 设置敌方标签颜色（相反颜色）
  lv_obj_set_style_text_color(ui_duishoutimecount, duishou_color,
                              LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_text_color(ui_duishoutimedanwei, duishou_color,
                              LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_text_color(ui_duishouWin, duishou_color,
                              LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_text_color(ui_duishoushengyu, duishou_color,
                              LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_text_color(ui_duishouqiziCount, duishou_color,
                              LV_PART_MAIN | LV_STATE_DEFAULT);

  printf("UI 颜色已设置：我方=%s，敌方=%s\n", my_zhenyin == 0 ? "红色" : "黑色",
         my_zhenyin == 0 ? "黑色" : "红色");
}

// 函数声明
static void printArr_qipan(void);
static void re_qipan(void);
static void rule_ma(int row, int col, const char *piece);
static void rule_che(int row, int col, const char *piece);
static void rule_xiang(int row, int col, const char *piece);
static void rule_shi(int row, int col, const char *piece);
static void rule_jiang(int row, int col, const char *piece);
static void rule_pao(int row, int col, const char *piece);
static void rule_bing(int row, int col, const char *piece);
static void nextip_by_qizitype(int row, int col, const char *piece);
static int init_bemfa_connection(void);
static void start_bemfa_threads(int tcpfd);
static void stop_bemfa_threads(void);
static void send_moveinfo(int from_row, int from_col, int to_row, int to_col,
                          const char *piece);
static void daojishi(lv_timer_t *timer);
void daojishi_start(void);
void daojishi_stop(void);
void daojishi_reset(void);

void ui_event_regame(lv_event_t *e);
void ui_event_change_zhenyin(lv_event_t *e);

// 颜色选择按钮的通用事件处理函数实现
void ui_event_change_zhenyin(lv_event_t *e) {
  lv_event_code_t event_code = lv_event_get_code(e);
  void *user_data = lv_event_get_user_data(e);

  if (event_code == LV_EVENT_CLICKED) {
    char selected_color = (char)(intptr_t)user_data;

    printf("\n========== 选择棋子 ==========\n");

    if (selected_color == 'r') {
      printf("用户选择红棋\n");
      set_zhenyin(0); // 红方
      zhenyin_selected = 1;
      xiaqi = 1; // 红方先手，设置可以下棋

      // 根据颜色设置 UI 标签的字体颜色
      set_mycolors(0); // 红方

      printf("发送消息到云端，通知对方选择黑方...\n");
      send_duishou_yourcolor(0); // 我选红方，通知对方选黑方
    } else if (selected_color == 'b') {
      printf("用户选择黑棋\n");
      set_zhenyin(1); // 黑方
      zhenyin_selected = 1;
      xiaqi = 0; // 黑方后手，等待对方

      // 根据颜色设置 UI 标签的字体颜色
      set_mycolors(1); // 黑方

      printf("发送消息到云端，通知对方选择红方...\n");
      send_duishou_yourcolor(1); // 我选黑方，通知对方选红方
    }

    printf("================================\n\n");
  }
}
void ui_event_regame(lv_event_t *e) {
  lv_event_code_t event_code = lv_event_get_code(e);
  if (event_code == LV_EVENT_CLICKED) {


    printf("准备重新开始游戏...\n");



    // 强制关闭蜂鸣器
    stop_buzzer_force();

    // 强制关闭双方倒计时
    daojishi_stop();

    onlysend();

    char history_cmd_red[150];
    sprintf(history_cmd_red, "cmd=2&uid=3f2d5feab40ea3844d23321f165ab2db&topic="
                             "QtDQMfr0E002&msg=move:-1,-1,-1,-1,null\r\n");
    send(bemfa_tcpfd, history_cmd_red, strlen(history_cmd_red), 0);
    printf("已发送重置消息到 红方 QtDQMfr0E002\n");
    usleep(100000);

    char history_cmd_black[150];
    sprintf(history_cmd_black,
            "cmd=2&uid=3f2d5feab40ea3844d23321f165ab2db&topic=cvM3doRhm002&msg="
            "move:-1,-1,-1,-1,null\r\n");
    send(bemfa_tcpfd, history_cmd_black, strlen(history_cmd_black), 0);
    printf("已发送重置消息到 黑方 cvM3doRhm002\n");
    usleep(100000);

    onlyrecv();
 
 
    lv_label_set_text(ui_duishouqiziCount, "17");
    lv_label_set_text(ui_myqiziCount, "17");
 
    hide_object_safe(ui_gamewinCon);
    hide_object_safe(ui_gamelowCon);
 
    show_object_safe(ui_QiPan);
    show_object_safe(ui_duishou);
    show_object_safe(ui_myself);
 
     lv_obj_set_x(ui_Button1, 353);
    lv_obj_set_y(ui_Button1, 256);

    zhenyin_selected = 0;
    xiaqi = 0;

    // 初始化象棋棋子位置
    init_xiangqi_ui_arr();
printf("---------------------------------------重新开始新游戏...\n");printf("---------------------------------------重新开始新游戏...\n");printf("---------------------------------------重新开始新游戏...\n");
    printf("---------------------------------------重新开始新游戏...\n");
    lv_disp_load_scr(ui_changeWin);
  }
}

static int selected_row = -1;
static int selected_col = -1;
static char selected_qizi[PIECE_NAME_LEN] = ""; // 存储选中的棋子名称

int bemfa_tcpfd = -1;
static thread_pool_t *comm_thread_pool = NULL;
static int recv_task_running = 0;
static int send_task_running = 0;
static pthread_mutex_t thread_mutex = PTHREAD_MUTEX_INITIALIZER; // 线程互斥锁

#define TOPIC_RED "cvM3doRhm002"   // 红方发送的 topic
#define TOPIC_BLACK "QtDQMfr0E002" // 黑方发送的 topic

// 0 红方    1 黑方
static int current_zhenyin = 0; // 默认红方

static char recv_oldmsg[200] = {0}; // 初始化为空

static int lunxun_r_b = 1;

static long long my_zhenyin_timestamp = 0;
static long long duishou_zhenyin_timestamp = 0;

// 定时器
static lv_timer_t *daojishi_time = NULL;
static int my_daojishi_cur = 30;
static int duishou_daojishi_cur = 30;

// 待发送的消息队列
typedef struct {
  int from_row;
  int from_col;
  int to_row;
  int to_col;
  char qizi[PIECE_NAME_LEN];
  int valid; // 消息是否有效
} send_msging;

static send_msging msg_is_send; // 待发送消息

// 初始化巴法云连接
static int init_bemfa_connection(void) {
  if (bemfa_tcpfd != -1) {
    // 已经有连接，直接使用
    return bemfa_tcpfd;
  }

  // 配置巴法云服务器地址
  struct sockaddr_in server_addr;
  memset(&server_addr, 0, sizeof(server_addr));
  server_addr.sin_family = AF_INET;
  server_addr.sin_port = htons(8344);
  server_addr.sin_addr.s_addr = inet_addr("119.91.109.180");

  // 创建 TCP 套接字
  int tcpfd = socket(AF_INET, SOCK_STREAM, 0);
  if (tcpfd == -1) {
    perror("创建巴法云套接字失败");
    return -1;
  }

  // 连接服务器
  if (connect(tcpfd, (struct sockaddr *)&server_addr, sizeof(server_addr)) ==
      -1) {
    perror("连接巴法云失败");
    close(tcpfd);
    return -1;
  }

  printf("巴法云连接成功，套接字=%d\n", tcpfd);
  bemfa_tcpfd = tcpfd;
  return tcpfd;
}

// 接收巴法云消息的任务函数（用于线程池）
static void *recv_bemfa_msg_task(void *arg) {

  
  int tcpfd = (int)(intptr_t)arg; // 直接转换，不取地址
  int recv_count = 0;             // 接收次数计数
  const int MAX_RECV_COUNT = 30;  // 最大接收 30 次

  printf("接收任务已启动，tcpfd=%d，最大接收次数=%d...\n", tcpfd,
         MAX_RECV_COUNT);

  while (recv_task_running) {

    sleep(1);
    char buffer[1024];
    memset(buffer, 0, sizeof(buffer));

    char getmsg_cmd[150];
    if (!zhenyin_selected) {
      if (lunxun_r_b) {
        sprintf(getmsg_cmd, "cmd=9&uid=3f2d5feab40ea3844d23321f165ab2db&topic="
                            "QtDQMfr0E002\r\n");
        printf(" 查询红方 topic: QtDQMfr0E002\n");
      } else {
        sprintf(getmsg_cmd, "cmd=9&uid=3f2d5feab40ea3844d23321f165ab2db&topic="
                            "cvM3doRhm002\r\n");
        printf("查询黑方 topic: cvM3doRhm002\n");
      }
      lunxun_r_b = !lunxun_r_b;
    } else if (current_zhenyin == 0) // 我方是红方
    {
      // 接收黑方topic 的消息
      sprintf(
          getmsg_cmd,
          "cmd=9&uid=3f2d5feab40ea3844d23321f165ab2db&topic=QtDQMfr0E002\r\n");
      printf(" 接收对方 (黑方) topic: QtDQMfr0E002\n");
    } else // 我方是黑方
    {
      // 接收红方topic 的消息
      sprintf(
          getmsg_cmd,
          "cmd=9&uid=3f2d5feab40ea3844d23321f165ab2db&topic=cvM3doRhm002\r\n");
      printf(" 接收对方 (红方) topic: cvM3doRhm002\n");
    }

    int ret = send(tcpfd, getmsg_cmd, strlen(getmsg_cmd), 0);
    if (ret == -1) {
      perror("发送历史消息请求失败");
    } else {
      printf("已发送获取历史消息请求：%s\n", getmsg_cmd);
    }

    memset(buffer, 0, 1024);
    recv(tcpfd, buffer, sizeof(buffer), 0);

    printf("收到消息 buffer: %s\n", buffer);

    if (strlen(buffer) > 0) {
      char *msg_start = strstr(buffer, "&msg=");
      if (msg_start != NULL) {
        msg_start += 5;
        printf("提取到 msg_start: %s\n", msg_start);

        char *end = strstr(msg_start, "\r\n");
        if (end != NULL) {
          *end = '\0';
        }

        if (strcmp(msg_start, recv_oldmsg) == 0) {
          continue;
        }

        printf("\n检测到新消息：%s\n", recv_count, MAX_RECV_COUNT, msg_start);

        strncpy(recv_oldmsg, msg_start, sizeof(recv_oldmsg) - 1);
        recv_oldmsg[sizeof(recv_oldmsg) - 1] = '\0';

        int from_row, from_col, to_row, to_col;
        char qizi[PIECE_NAME_LEN];

        int parse_result = sscanf(msg_start, "move:%d,%d,%d,%d,%9s", &from_row,
                                  &from_col, &to_row, &to_col, qizi);

        if (parse_result == 5) {
          printf("解析成功：从 (%d,%d) 到 (%d,%d), %s\n", from_row, from_col,
                 to_row, to_col, qizi);

          // 检查是否是选择阵营的颜色选择消息
          if (from_row == -1 && from_col == -1 && to_row == -1 &&
              to_col == -1) {

            if (strcmp(qizi, "null") == 0) {
              continue;
            } else {
              char color_str[20] = {0};
              long long timestamp = 0;
              
              if (sscanf(qizi, "%[^_]_%lld", color_str, &timestamp) == 2) {
                 printf("收到带时间戳的消息：%s_%lld\n", color_str, timestamp);
                 duishou_zhenyin_timestamp = timestamp;
                 
                 if (zhenyin_selected == 1) {
                   printf("我也选了阵营，比较时间戳\n");
                   if (my_zhenyin_timestamp < duishou_zhenyin_timestamp) {
                     printf("我早\n");
                     if (current_zhenyin == 0) {
                       printf("保持红方，进游戏\n");
                       xiaqi = 1;
                       set_mycolors(0);
                       printf("开始游戏...\n");
                       lv_disp_load_scr(ui_gamePage);
                       usleep(600000);
                       daojishi_reset();
                       daojishi_start();
                       return NULL;
                     } else {
                       printf("保持黑方，进游戏\n");
                       xiaqi = 0;
                       set_mycolors(1);
                       printf("开始游戏...\n");
                       lv_disp_load_scr(ui_gamePage);
                       usleep(600000);
                       daojishi_reset();
                       daojishi_start();
                       return NULL;
                     }
                   } else {
                     printf("他早！听他的\n");
                   }
                 }
                 
                 if (strcmp(color_str, "red") == 0) {
                  printf("对方选择红方，我为黑方\n");
                  set_zhenyin(1);
                  zhenyin_selected = 1;
                  xiaqi = 0;

                  set_mycolors(1);

                  printf("开始游戏...\n");
                  lv_disp_load_scr(ui_gamePage);
                  usleep(600000);
                  daojishi_reset();
                  daojishi_start();

                  return NULL;
                } else if (strcmp(color_str, "black") == 0) {
                  printf("对方选择黑方，我为红方\n");
                  set_zhenyin(0);
                  zhenyin_selected = 1;
                  xiaqi = 1;

                  set_mycolors(0);

                  printf("开始游戏...\n");
                  lv_disp_load_scr(ui_gamePage);
                  usleep(600000);
                  daojishi_reset();
                  daojishi_start();

                  return NULL;
                }
              } else {
                if (strcmp(qizi, "red") == 0) {
                  printf("对方选择红方，我为黑方\n");
                  set_zhenyin(1);
                  zhenyin_selected = 1;
                  xiaqi = 0;

                  set_mycolors(1);

                  printf("开始游戏...\n");
                  lv_disp_load_scr(ui_gamePage);
                  usleep(600000);
                  daojishi_reset();
                  daojishi_start();

                  return NULL;
                } else if (strcmp(qizi, "black") == 0) {
                  printf("对方选择黑方，我为红方\n");
                  set_zhenyin(0);
                  zhenyin_selected = 1;
                  xiaqi = 1;

                  set_mycolors(0);

                  printf("开始游戏...\n");
                  lv_disp_load_scr(ui_gamePage);
                  usleep(600000);
                  daojishi_reset();
                  daojishi_start();

                  return NULL;
                }
              }
            }
          } else {
            printf("检测到对方移动消息：从 (%d,%d) 到 (%d,%d), 棋子 %s\n",
                   from_row, from_col, to_row, to_col, qizi);
          }

          // 先检查目标位置是否有己方棋子（被吃了）- 在更新棋盘之前
          const char *have_myqizi = get_qizi_by_qipanarr(to_row, to_col);
          int is_beichi = (have_myqizi[0] != '\0' &&
                           get_qizi_color(have_myqizi) == current_zhenyin);

          // 更新棋盘数组
          set_qipanarr(to_row, to_col, qizi);

          if (is_beichi) {
            // 显示被吃子提示
            char duishou_chi_zi_msg[100];
            sprintf(duishou_chi_zi_msg, "对方吃掉你的棋子：%s", have_myqizi);
            show_popup_message(DUISHOU_EAT, duishou_chi_zi_msg);

            // 被吃的是己方棋子，我的棋子数量 -1
            const char *count_str = lv_label_get_text(ui_myqiziCount);
            int count = atoi(count_str);

            if (count > 0) {
              count--;
              char new_count[8];
              sprintf(new_count, "%d", count);
              lv_label_set_text(ui_myqiziCount, new_count);
              printf("我的棋子剩余：%d\n", count);
            }

            // 检查被吃的是否是将或帅
            char is_over_qizi[PIECE_NAME_LEN];
            get_qizi_value(have_myqizi, is_over_qizi);

            if (strcmp(is_over_qizi, "将") == 0 ||
                strcmp(is_over_qizi, "帅") == 0 ||
                strcmp(is_over_qizi, "將") == 0 ||
                strcmp(is_over_qizi, "帥") == 0) {
              printf("将/帅被吃，你输了！\n");

              // 显示失败弹窗
              show_popup_message(LOSE, "五一怎么过？下局一定过！！！");

              lv_obj_add_flag(ui_QiPan, LV_OBJ_FLAG_HIDDEN);
              lv_obj_add_flag(ui_duishou, LV_OBJ_FLAG_HIDDEN);
              lv_obj_add_flag(ui_myself, LV_OBJ_FLAG_HIDDEN);

              lv_obj_set_x(ui_Button1, 1);
              lv_obj_set_y(ui_Button1, 154);
            }
          } else {
            printf("is_beichi：    %d\n", is_beichi);
          }

          clear_old_qizi(from_row, from_col);

          xiaqi = 1;
          printf("对方已落子，轮到我方下棋，启动倒计时...\n");
          daojishi_reset();
          daojishi_start();

          lv_obj_t *src_label = get_label_by_zuobiao(from_row, from_col);
          lv_obj_t *dst_label = get_label_by_zuobiao(to_row, to_col);
          lv_obj_t *src_button = get_button_by_zuobiao(from_row, from_col);
          lv_obj_t *dst_button = get_button_by_zuobiao(to_row, to_col);

          char piece_type[PIECE_NAME_LEN];
          get_qizi_value(qizi, piece_type);

          if (src_label && dst_label && src_button && dst_button) {
            lv_label_set_text(dst_label, piece_type);
            lv_label_set_text(src_label, " ");

            // 使用安全函数隐藏/显示按钮
            show_object_safe(dst_button);
            hide_object_safe(src_button);

            int color = get_qizi_color(qizi);
            if (color == 0) // 红方
            {
              lv_obj_set_style_bg_color(
                  dst_button, lv_color_hex(CHESS_RED_COLOR), LV_PART_MAIN);
            } else if (color == 1) // 黑方
            {
              lv_obj_set_style_bg_color(
                  dst_button, lv_color_hex(CHESS_BLACK_COLOR), LV_PART_MAIN);
            }

            printf("对方棋子移动从 (%d,%d) 到 (%d,%d)\n", from_row, from_col,
                   to_row, to_col);
          }

          recv_task_running = 0;
          return NULL;
        } else {
          printf("消息解析失败： (%d,%d) 到 (%d,%d), 棋子 %s\n", from_row,
                 from_col, to_row, to_col, qizi);
        }
      }
    }
    

  }

  printf("接收任务已退出\n");
  return NULL;
}

static void *send_bemfa_msg_task(void *arg) {
  int tcpfd = (int)(intptr_t)arg;

  printf("发送任务已启动，tcpfd=%d...\n", tcpfd);

  while (1) {
    if (send_task_running && msg_is_send.valid) {
      pthread_mutex_lock(&thread_mutex);

      // 我方是红方 (current_zhenyin==0)，发送消息到红方 topic (QtDQMfr0E002)
      // 我方是黑方 (current_zhenyin==1)，发送消息到黑方 topic (cvM3doRhm002)
      // 对方订阅我们的 topic，所以我们发送到自己的 topic
      const char *topic = (current_zhenyin == 0) ? TOPIC_RED : TOPIC_BLACK;

      printf("发送棋子移动：%s, 我方阵营=%s, 发送到 topic=%s\n",
             msg_is_send.qizi, (current_zhenyin == 0) ? "红方" : "黑方", topic);

      // 构建发送消息
      char msg[200];
      char cmd[150];
      sprintf(cmd, "cmd=2&uid=3f2d5feab40ea3844d23321f165ab2db&topic=%s",
              topic);

      char move_info[100];
      sprintf(move_info, "move:%d,%d,%d,%d,%s", msg_is_send.from_row,
              msg_is_send.from_col, msg_is_send.to_row, msg_is_send.to_col,
              msg_is_send.qizi);

      sprintf(msg, "%s&msg=%s\r\n", cmd, move_info);

      int send_len = send(tcpfd, msg, strlen(msg), 0);
      if (send_len == -1) {
        perror("发送巴法云失败");
        bemfa_tcpfd = -1;
      } else {
        printf("巴法云发送成功：%s\n", msg);
      }

      msg_is_send.valid = 0;

      pthread_mutex_unlock(&thread_mutex);
    }
 
  }

  printf("发送任务已退出\n");
  return NULL;
}

static void start_bemfa_tasks(int tcpfd) {
  pthread_mutex_lock(&thread_mutex);

  printf("准备启动巴法云任务，tcpfd=%d\n", tcpfd);

  if (!recv_task_running && comm_thread_pool != NULL) {
    recv_task_running = 1;
    int ret = thread_pool_add_task(comm_thread_pool, recv_bemfa_msg_task,
                                   (void *)(intptr_t)tcpfd);
    if (ret != 0) {
      perror("添加接收任务失败");
      recv_task_running = 0;
    } else {
      printf("接收任务已添加到线程池\n");
    }
  }

  if (!send_task_running && comm_thread_pool != NULL) {
    send_task_running = 1;
    int ret = thread_pool_add_task(comm_thread_pool, send_bemfa_msg_task,
                                   (void *)(intptr_t)tcpfd);
    if (ret != 0) {
      perror("添加发送任务失败");
      send_task_running = 0;
    } else {
      printf("发送任务已添加到线程池\n");
    }
  }

  pthread_mutex_unlock(&thread_mutex);
}

static void stop_bemfa_tasks(void) {
  pthread_mutex_lock(&thread_mutex);

  if (recv_task_running) {
    recv_task_running = 0;
    printf("已停止接收任务\n");
  }

  if (send_task_running) {
    send_task_running = 0;
    printf("已停止发送任务\n");
  }

  pthread_mutex_unlock(&thread_mutex);
}

void onlyrecv(void) {
  pthread_mutex_lock(&thread_mutex);
  send_task_running = 0;

  if (!recv_task_running && comm_thread_pool != NULL && bemfa_tcpfd != -1) {
    recv_task_running = 1;
    int ret = thread_pool_add_task(comm_thread_pool, recv_bemfa_msg_task,
                                   (void *)(intptr_t)bemfa_tcpfd);
    if (ret != 0) {
      perror("重新启动接收任务失败");
      recv_task_running = 0;
    } else {
      printf("接收任务已重新启动\n");
    }
  } else if (recv_task_running) {
    printf("接收任务已在运行\n");
  }

  if (current_zhenyin == 0) // 接收黑方 topic
  {
    printf("已启用接收模式：接收 cvM3doRhm002的消息\n");
  } else // 接收红方 topic
  {
    printf("已启用接收模式：接收 QtDQMfr0E002的消息\n");
  }
  pthread_mutex_unlock(&thread_mutex);
}

// 启用发送任务，禁用接收任务（根据棋子颜色发送到对应 topic）
void onlysend(void) {
  pthread_mutex_lock(&thread_mutex);
  recv_task_running = 0;
  send_task_running = 1;
  printf("已启用发送模式：根据棋子颜色发送到对应 topic\n");
  pthread_mutex_unlock(&thread_mutex);
}

// 0 红    1 黑
void set_zhenyin(int zhenyin) {
  pthread_mutex_lock(&thread_mutex);
  current_zhenyin = zhenyin;
  pthread_mutex_unlock(&thread_mutex);

  if (zhenyin == 0) {
    printf("已设置为红方模式：发送 QtDQMfr0E002，接收 cvM3doRhm002\n");
  } else {
    printf("已设置为黑方模式：发送 cvM3doRhm002，接收 QtDQMfr0E002\n");
  }
}

void bemfainfo_init() {
  printf("开始初始化巴法云信息\n");
  onlysend();

  pthread_mutex_lock(&thread_mutex);
  msg_is_send.from_row = -1;
  msg_is_send.from_col = -1;
  msg_is_send.to_row = -1;
  msg_is_send.to_col = -1;
  strncpy(msg_is_send.qizi, "null", PIECE_NAME_LEN - 1);
  msg_is_send.qizi[PIECE_NAME_LEN - 1] = '\0';
  msg_is_send.valid = 1;
  pthread_mutex_unlock(&thread_mutex);

  usleep(500000); // 500ms

  onlyrecv();
  printf("初始化巴法云信息结束\n");
}

void send_duishou_yourcolor(int my_color) {
  onlysend();

  const char *duishou_color = (my_color == 0) ? "black" : "red";
  
  struct timeval tv;
  gettimeofday(&tv, NULL);
  my_zhenyin_timestamp = (long long)tv.tv_sec * 1000000LL + tv.tv_usec;

  char msg_content[50];
  snprintf(msg_content, sizeof(msg_content), "%s_%lld", duishou_color, my_zhenyin_timestamp);

  printf("已添加待发送消息：通知对方选择%s (时间戳：%lld)\n", duishou_color, my_zhenyin_timestamp);
  
  // 直接发送到两个 topic，确保对方无论选什么颜色都能收到
  char *topics[] = {TOPIC_RED, TOPIC_BLACK};
  
  for (int i = 0; i < 2; i++) {
    const char *topic = topics[i];
    
    char msg[200];
    char cmd[150];
    sprintf(cmd, "cmd=2&uid=3f2d5feab40ea3844d23321f165ab2db&topic=%s", topic);
    
    char move_info[100];
    sprintf(move_info, "move:%d,%d,%d,%d,%s", -1, -1, -1, -1, msg_content);
    
    sprintf(msg, "%s&msg=%s\r\n", cmd, move_info);
    
    int send_len = send(bemfa_tcpfd, msg, strlen(msg), 0);
    if (send_len == -1) {
      perror("发送巴法云失败");
    } else {
      printf("巴法云发送成功到 topic=%s: %s\n", topic, msg);
    }
    
    usleep(100000);
  }
  
  printf("发送完成，切换到接收模式\n");

  onlyrecv();
  
  printf("等待对方响应...\n");
  
  int wait_count = 0;
  while (wait_count < 20) {
    usleep(100000);
    wait_count++;
    
    if (duishou_zhenyin_timestamp != 0) {
      printf("===================================收到对方响应，时间戳：%lld\n", duishou_zhenyin_timestamp);
      return;
    }
  }
  
  printf("===================================对方没抢！直接进游戏\n");
  
  if (my_color == 0) {
    printf("保持红方，进游戏\n");
    xiaqi = 1;
    set_mycolors(0);
    printf("开始游戏...\n");
    lv_disp_load_scr(ui_gamePage);
    usleep(600000);
    daojishi_reset();
    daojishi_start();
  } else {
    printf("保持黑方，进游戏\n");
    xiaqi = 0;
    set_mycolors(1);
    printf("开始游戏...\n");
    lv_disp_load_scr(ui_gamePage);
    usleep(600000);
    daojishi_reset();
    daojishi_start();
  }
}

int init_bemfa_communication(void) {
  if (bemfa_tcpfd != -1) {
    return bemfa_tcpfd;
  }

  struct sockaddr_in server_addr;
  memset(&server_addr, 0, sizeof(server_addr));
  server_addr.sin_family = AF_INET;
  server_addr.sin_port = htons(8344);
  server_addr.sin_addr.s_addr = inet_addr("119.91.109.180");

  int tcpfd = socket(AF_INET, SOCK_STREAM, 0);
  if (tcpfd == -1) {
    perror("创建巴法云套接字失败");
    return -1;
  }

  if (connect(tcpfd, (struct sockaddr *)&server_addr, sizeof(server_addr)) ==
      -1) {
    perror("连接巴法云失败");
    close(tcpfd);
    return -1;
  }

  printf("巴法云连接成功，套接字=%d\n", tcpfd);
  bemfa_tcpfd = tcpfd;

  memset(&msg_is_send, 0, sizeof(msg_is_send));

  msg_is_send.valid = 0;

  start_bemfa_tasks(tcpfd);

  return tcpfd;
}

void close_bemfa_communication(void) {
  stop_bemfa_tasks();

  if (bemfa_tcpfd != -1) {
    close(bemfa_tcpfd);
    bemfa_tcpfd = -1;
  }

  printf("巴法云通信已关闭\n");
}

int init_comm_thread_pool(int pool_size) {
  if (comm_thread_pool != NULL) {
    printf("线程池已存在\n");
    return 0;
  }

  comm_thread_pool = thread_pool_create(pool_size);
  if (comm_thread_pool == NULL) {
    printf("创建通信线程池失败\n");
    return -1;
  }

  printf("通信线程池初始化成功\n");
  return 0;
}

void destroy_comm_thread_pool(void) {
  if (comm_thread_pool != NULL) {
    thread_pool_destroy(comm_thread_pool);
    comm_thread_pool = NULL;
    printf("通信线程池已销毁\n");
  }
}

static void send_moveinfo(int from_row, int from_col, int to_row, int to_col,
                          const char *piece) {
  onlysend();

  pthread_mutex_lock(&thread_mutex);
  msg_is_send.from_row = from_row;
  msg_is_send.from_col = from_col;
  msg_is_send.to_row = to_row;
  msg_is_send.to_col = to_col;
  strncpy(msg_is_send.qizi, piece, PIECE_NAME_LEN - 1);
  msg_is_send.qizi[PIECE_NAME_LEN - 1] = '\0';
  msg_is_send.valid = 1;
  pthread_mutex_unlock(&thread_mutex);

  printf("已添加待发送消息：从 (%d,%d) 到 (%d,%d), 棋子=%s\n", from_row,
         from_col, to_row, to_col, piece);

  usleep(500000);

  onlyrecv();
}

static void daojishi(lv_timer_t *timer) {
  if (xiaqi) {
    if (my_daojishi_cur > 0) {
      my_daojishi_cur--;
      char time_str[8];
      sprintf(time_str, "%d", my_daojishi_cur);
      lv_label_set_text(ui_mytimecount, time_str);
      printf("我的倒计时：%d\n", my_daojishi_cur);

      if (my_daojishi_cur < 5) {
        lv_obj_set_style_text_font(ui_mytimecount, &lv_font_montserrat_48,
                                   LV_PART_MAIN | LV_STATE_DEFAULT);

        beep_buzzer(1500, 200);
      }

    } else {
      lv_obj_clear_flag(ui_gamelowCon, LV_OBJ_FLAG_HIDDEN);
      lv_obj_add_flag(ui_gamewinCon, LV_OBJ_FLAG_HIDDEN);

      lv_obj_add_flag(ui_QiPan, LV_OBJ_FLAG_HIDDEN);
      lv_obj_add_flag(ui_duishou, LV_OBJ_FLAG_HIDDEN);
      lv_obj_add_flag(ui_myself, LV_OBJ_FLAG_HIDDEN);

      lv_obj_set_x(ui_Button1, 1);
      lv_obj_set_y(ui_Button1, 154);
    }
  } else // 对手的回合
  {
    if (duishou_daojishi_cur > 0) {
      duishou_daojishi_cur--;
      char time_str[8];
      sprintf(time_str, "%d", duishou_daojishi_cur);
      lv_label_set_text(ui_duishoutimecount, time_str);
      printf("对手倒计时：%d\n", duishou_daojishi_cur);

      if (duishou_daojishi_cur < 5) {
        lv_obj_set_style_text_font(ui_duishoutimecount, &lv_font_montserrat_48,
                                   LV_PART_MAIN | LV_STATE_DEFAULT);

        beep_buzzer(1500, 200);
      }

    } else {
      lv_obj_clear_flag(ui_gamewinCon, LV_OBJ_FLAG_HIDDEN);
      lv_obj_add_flag(ui_gamelowCon, LV_OBJ_FLAG_HIDDEN);

      lv_obj_add_flag(ui_QiPan, LV_OBJ_FLAG_HIDDEN);
      lv_obj_add_flag(ui_duishou, LV_OBJ_FLAG_HIDDEN);
      lv_obj_add_flag(ui_myself, LV_OBJ_FLAG_HIDDEN);

      lv_obj_set_x(ui_Button1, 1);
      lv_obj_set_y(ui_Button1, 154);
    }
  }
}

void daojishi_start(void) {
  if (daojishi_time == NULL) {
    daojishi_time = lv_timer_create(daojishi, 1000, NULL); // 1 秒间隔
    printf("倒计时定时器已启动\n");
  }
}

void daojishi_stop(void) {
  if (daojishi_time != NULL) {
    lv_timer_del(daojishi_time);
    daojishi_time = NULL;
    printf("倒计时定时器已停止\n");
  }
}

void daojishi_reset(void) {
  if (xiaqi) // 我的回合
  {
    my_daojishi_cur = 30;
    lv_label_set_text(ui_mytimecount, "30");
    duishou_daojishi_cur = 30;
    lv_label_set_text(ui_duishoutimecount, "30");
    printf("我的回合：我的时间=30，对手时间=30\n");
  } else // 对手回合
  {
    duishou_daojishi_cur = 30;
    lv_label_set_text(ui_duishoutimecount, "30");
    my_daojishi_cur = 30;
    lv_label_set_text(ui_mytimecount, "30");
    printf("对手回合：对手时间=30，我的时间=30\n");
  }
}

// 打印棋盘数组内容
static void printArr_qipan(void) {
  printf("\n========== 当前棋盘状态 ==========\n");
  printf("   0    1    2    3    4    5    6    7    8\n");
  printf("┌────┬────┬────┬────┬────┬────┬────┬────┬────┐\n");

  for (int row = 0; row < BOARD_ROWS; row++) {
    printf("│");
    for (int col = 0; col < BOARD_COLS; col++) {
      const char *piece = get_qizi_by_qipanarr(row, col);
      if (piece[0] == '\0') {
        printf("    │");
      } else {
        printf("%-4s│", piece);
      }
    }
    printf(" %d\n", row);

    if (row < BOARD_ROWS - 1) {
      printf("├────┼────┼────┼────┼────┼────┼────┼────┼────┤\n");
    }
  }
  printf("└────┴────┴────┴────┴────┴────┴────┴────┴────┘\n");
  printf("====================================\n\n");
}
static void re_qipan(void);

// 显示可走位置提示的函数声明
static void rule_ma(int row, int col, const char *piece);
static void rule_che(int row, int col, const char *piece);
static void rule_xiang(int row, int col, const char *piece);
static void rule_shi(int row, int col, const char *piece);
static void rule_jiang(int row, int col, const char *piece);
static void rule_pao(int row, int col, const char *piece);
static void rule_bing(int row, int col, const char *piece);

// 根据棋子类型显示可走位置
static void nextip_by_qizitype(int row, int col, const char *qizi) {

  printArr_qipan();

  char qizi_value[PIECE_NAME_LEN];
  printf("%d行%d列  棋子=%s   类型=%s\n", row, col, qizi, qizi_value);

  if (strcmp(qizi, "馬_r") == 0 || strcmp(qizi, "馬_b") == 0 ||
      strcmp(qizi, "马_r") == 0 || strcmp(qizi, "马_b") == 0) {
    rule_ma(row, col, qizi);
  } else if (strcmp(qizi, "車_r") == 0 || strcmp(qizi, "車_b") == 0 ||
             strcmp(qizi, "车_r") == 0 || strcmp(qizi, "车_b") == 0) {
    rule_che(row, col, qizi);
  } else if (strcmp(qizi, "相_r") == 0 || strcmp(qizi, "相_b") == 0 ||
             strcmp(qizi, "象_r") == 0 || strcmp(qizi, "象_b") == 0) {
    rule_xiang(row, col, qizi);
  } else if (strcmp(qizi, "士_r") == 0 || strcmp(qizi, "士_b") == 0 ||
             strcmp(qizi, "仕_r") == 0 || strcmp(qizi, "仕_b") == 0) {
    rule_shi(row, col, qizi);
  } else if (strcmp(qizi, "將_r") == 0 || strcmp(qizi, "將_b") == 0 ||
             strcmp(qizi, "将_r") == 0 || strcmp(qizi, "将_b") == 0 ||
             strcmp(qizi, "帥_r") == 0 || strcmp(qizi, "帥_b") == 0 ||
             strcmp(qizi, "帅_r") == 0 || strcmp(qizi, "帅_b") == 0) {
    rule_jiang(row, col, qizi);
  } else if (strcmp(qizi, "炮_r") == 0 || strcmp(qizi, "炮_b") == 0 ||
             strcmp(qizi, "砲_r") == 0 || strcmp(qizi, "砲_b") == 0) {
    rule_pao(row, col, qizi);
  } else if (strcmp(qizi, "兵_r") == 0 || strcmp(qizi, "兵_b") == 0 ||
             strcmp(qizi, "卒_r") == 0 || strcmp(qizi, "卒_b") == 0) {
    rule_bing(row, col, qizi);
  } else {
    printf("  未识别的棋子类型：%s\n", qizi);
  }
}

static void re_qipan(void) {
  printf("还原棋盘显示...\n");

  // 遍历保存的坐标数组
  for (int i = 0; i < save_zuobiao_count; i++) {
    int row = save_zuobiao[i][0];
    int col = save_zuobiao[i][1];

    if (row < 0 || row >= BOARD_ROWS || col < 0 || col >= BOARD_COLS)
      continue;

    lv_obj_t *button = get_button_by_zuobiao(row, col);
    if (button == NULL)
      continue;

    const char *piece = get_qizi_by_qipanarr(row, col);

    if (piece[0] == '\0') {
      lv_obj_add_flag(button, LV_OBJ_FLAG_HIDDEN);
      printf("  隐藏空位置 (%d,%d)\n", row, col);
    } else {
      int color = get_qizi_color(piece);
      if (color == 0) // 红方
      {
        lv_obj_set_style_bg_color(button, lv_color_hex(CHESS_RED_COLOR),
                                  LV_PART_MAIN);
      } else if (color == 1) // 黑方
      {
        lv_obj_set_style_bg_color(button, lv_color_hex(CHESS_BLACK_COLOR),
                                  LV_PART_MAIN);
      }
      printf("  还原位置 (%d,%d) 背景色，棋子=%s\n", row, col, piece);
    }
  }

  clear_saved_zuobiaos();
}

// 马走日
static void rule_ma(int row, int col, const char *qizi) {
  printf("显示马的移动提示：%d行%d列，棋子=%s\n", row, col, qizi);

  int ma_moves[8][2] = {{row - 2, col - 1}, {row - 2, col + 1},
                        {row - 1, col - 2}, {row - 1, col + 2},
                        {row + 1, col - 2}, {row + 1, col + 2},
                        {row + 2, col - 1}, {row + 2, col + 1}};

  int my_color = get_qizi_color(qizi);

  clear_saved_zuobiaos();

  for (int i = 0; i < 8; i++) {
    int next_row = ma_moves[i][0];
    int next_col = ma_moves[i][1];

    if (!is_bianjie(next_row, next_col)) {
      printf("  位置 (%d,%d) 超出范围，跳过\n", next_row, next_col);
      continue;
    }

    // 检查是否蹩马腿
    int row_diff = next_row - row;
    int col_diff = next_col - col;
    int leg_row = row, leg_col = col;

    if (abs(row_diff) == 2 && abs(col_diff) == 1) {
      leg_row = row + (row_diff > 0 ? 1 : -1);
    } else if (abs(row_diff) == 1 && abs(col_diff) == 2) {
      leg_col = col + (col_diff > 0 ? 1 : -1);
    }

    const char *leg_piece = get_qizi_by_qipanarr(leg_row, leg_col);
    if (leg_piece[0] != '\0') {
      printf("  位置 (%d,%d) 蹩马腿，跳过\n", next_row, next_col);
      continue;
    }

    // 获取目标位置的棋子
    const char *target_piece = get_qizi_by_qipanarr(next_row, next_col);
    lv_obj_t *nextqizi_button = get_button_by_zuobiao(next_row, next_col);

    if (nextqizi_button == NULL)
      continue;

    // 保存坐标
    save_zuobiaoarr(next_row, next_col);

    // 判断目标位置是否有棋子
    if (target_piece[0] == '\0') {
      lv_obj_clear_flag(nextqizi_button, LV_OBJ_FLAG_HIDDEN);
      lv_obj_set_style_bg_color(nextqizi_button, lv_color_hex(0x808080),
                                LV_PART_MAIN);
      printf("位置 (%d,%d) 为空\n", next_row, next_col);
    } else {
      // 有棋子，判断是否可以吃子
      int nextqizi_color = get_qizi_color(target_piece);

      if (nextqizi_color != my_color && nextqizi_color != -1) {
        // 敌方棋子
        lv_obj_clear_flag(nextqizi_button, LV_OBJ_FLAG_HIDDEN);
        lv_obj_set_style_bg_color(nextqizi_button, lv_color_hex(0x808080),
                                  LV_PART_MAIN);
        printf("  位置 (%d,%d) 可吃子：%s灰色\n", next_row, next_col,
               target_piece);
      } else {
        // 己方棋子
        printf("  位置 (%d,%d) 是己方棋子：%s，不能吃\n", next_row, next_col,
               target_piece);
      }
    }
  }

  printf("  共保存 %d 个可走位置\n", save_zuobiao_count);
}

// 车走直线
static void rule_che(int row, int col, const char *piece) {
  printf("显示車的移动提示：%d行%d列，棋子=%s\n", row, col, piece);

  int my_color = get_qizi_color(piece);
  clear_saved_zuobiaos();

  // 四个方向：上、下、左、右
  int che_move[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

  for (int d = 0; d < 4; d++) {
    int dr = che_move[d][0];
    int dc = che_move[d][1];

    for (int step = 1; step < 9; step++) {
      int next_row = row + dr * step;
      int next_col = col + dc * step;

      if (!is_bianjie(next_row, next_col))
        break;

      const char *next_piece = get_qizi_by_qipanarr(next_row, next_col);
      lv_obj_t *nextqizi_button = get_button_by_zuobiao(next_row, next_col);

      if (nextqizi_button == NULL)
        break;

      if (next_piece[0] == '\0') {
        // 空位，可以走
        save_zuobiaoarr(next_row, next_col);
        lv_obj_clear_flag(nextqizi_button, LV_OBJ_FLAG_HIDDEN);
        lv_obj_set_style_bg_color(nextqizi_button, lv_color_hex(0x808080),
                                  LV_PART_MAIN);
        printf("  位置 (%d,%d) 为空，灰色\n", next_row, next_col);
      } else {
        // 有棋子
        int nextqizi_color = get_qizi_color(next_piece);
        if (nextqizi_color != my_color && nextqizi_color != -1) {
          // 敌方棋子，可以吃
          save_zuobiaoarr(next_row, next_col);
          lv_obj_clear_flag(nextqizi_button, LV_OBJ_FLAG_HIDDEN);
          lv_obj_set_style_bg_color(nextqizi_button, lv_color_hex(0x808080),
                                    LV_PART_MAIN);
          printf("  位置 (%d,%d) 可吃子%s\n", next_row, next_col, next_piece);
        }
        break; // 遇到棋子停止
      }
    }
  }

  printf("  共保存 %d 个可走位置\n", save_zuobiao_count);
}

// 象走田，不能过河
static void rule_xiang(int row, int col, const char *qizi) {
  printf("显示相/象的移动提示：%d行%d列，棋子=%s\n", row, col, qizi);

  int my_color = get_qizi_color(qizi);
  clear_saved_zuobiaos();

  // 象走田的 4 个可能位置
  int xiang_moves[4][2] = {{row - 2, col - 2},
                           {row - 2, col + 2},
                           {row + 2, col - 2},
                           {row + 2, col + 2}};

  for (int i = 0; i < 4; i++) {
    int next_row = xiang_moves[i][0];
    int next_col = xiang_moves[i][1];

    if (!is_bianjie(next_row, next_col))
      continue;

    if (my_color == 0 && next_row > 4) // 红方相不能到 5-9 行
    {
      printf("  位置 (%d,%d) 过河，跳过\n", next_row, next_col);
      continue;
    }
    if (my_color == 1 && next_row < 5) // 黑方象不能到 0-4 行
    {
      printf("  位置 (%d,%d) 过河，跳过\n", next_row, next_col);
      continue;
    }

    // 检查象眼是否被塞
    int eye_row = (row + next_row) / 2;
    int eye_col = (col + next_col) / 2;
    const char *eye_piece = get_qizi_by_qipanarr(eye_row, eye_col);

    if (eye_piece[0] != '\0') {
      printf("  位置 (%d,%d) 塞象眼，跳过\n", next_row, next_col);
      continue;
    }

    const char *next_qizi = get_qizi_by_qipanarr(next_row, next_col);
    lv_obj_t *nextqizi_button = get_button_by_zuobiao(next_row, next_col);

    if (nextqizi_button == NULL)
      continue;

    save_zuobiaoarr(next_row, next_col);

    if (next_qizi[0] == '\0') {
      lv_obj_clear_flag(nextqizi_button, LV_OBJ_FLAG_HIDDEN);
      lv_obj_set_style_bg_color(nextqizi_button, lv_color_hex(0x808080),
                                LV_PART_MAIN);
      printf("  位置 (%d,%d) 为空，灰色\n", next_row, next_col);
    } else {
      int target_color = get_qizi_color(next_qizi);
      if (target_color != my_color && target_color != -1) {
        lv_obj_clear_flag(nextqizi_button, LV_OBJ_FLAG_HIDDEN);
        lv_obj_set_style_bg_color(nextqizi_button, lv_color_hex(0x808080),
                                  LV_PART_MAIN);
        printf("  位置 (%d,%d) 可吃子：%s\n", next_row, next_col, next_qizi);
      } else {
        printf("  位置 (%d,%d) 是己方棋子\n", next_row, next_col, next_qizi);
      }
    }
  }

  printf("  共保存 %d 个可走位置\n", save_zuobiao_count);
}

// 显示士/仕的可走位置（九宫格内斜线）
static void rule_shi(int row, int col, const char *qizi) {
  printf("显示士/仕的移动提示：%d行%d列，棋子=%s\n", row, col, qizi);

  int my_color = get_qizi_color(qizi);
  clear_saved_zuobiaos();

  // 士走斜线的 4 个可能位置
  int shi_moves[4][2] = {{row - 1, col - 1},
                         {row - 1, col + 1},
                         {row + 1, col - 1},
                         {row + 1, col + 1}};

  for (int i = 0; i < 4; i++) {
    int next_row = shi_moves[i][0];
    int next_col = shi_moves[i][1];

    // 检查是否在棋盘范围内
    if (!is_bianjie(next_row, next_col))
      continue;

    // 检查是否在九宫格内
    if (my_color == 0) // 红方仕
    {
      if (next_row < 0 || next_row > 2 || next_col < 3 || next_col > 5) {
        printf("  位置 (%d,%d) 不在九宫格，跳过\n", next_row, next_col);
        continue;
      }
    } else // 黑方士
    {
      if (next_row < 7 || next_row > 9 || next_col < 3 || next_col > 5) {
        printf("  位置 (%d,%d) 不在九宫格，跳过\n", next_row, next_col);
        continue;
      }
    }

    const char *next_qizi = get_qizi_by_qipanarr(next_row, next_col);
    lv_obj_t *next_button = get_button_by_zuobiao(next_row, next_col);

    if (next_button == NULL)
      continue;

    save_zuobiaoarr(next_row, next_col);

    if (next_qizi[0] == '\0') {
      lv_obj_clear_flag(next_button, LV_OBJ_FLAG_HIDDEN);
      lv_obj_set_style_bg_color(next_button, lv_color_hex(0x808080),
                                LV_PART_MAIN);
      printf("  位置 (%d,%d) 为空，灰色\n", next_row, next_col);
    } else {
      int nextqizi_color = get_qizi_color(next_qizi);
      if (nextqizi_color != my_color && nextqizi_color != -1) {
        lv_obj_clear_flag(next_button, LV_OBJ_FLAG_HIDDEN);
        lv_obj_set_style_bg_color(next_button, lv_color_hex(0x808080),
                                  LV_PART_MAIN);
        printf("  位置 (%d,%d) 可吃子：%s\n", next_row, next_col, next_qizi);
      } else {
        printf("  位置 (%d,%d) 是己方棋子：%s\n", next_row, next_col,
               next_qizi);
      }
    }
  }

  printf("  共保存 %d 个可走位置\n", save_zuobiao_count);
}

// 将/帅
static void rule_jiang(int row, int col, const char *qizi) {
  printf("显示将/帅的移动提示：%d行%d列，棋子=%s\n", row, col, qizi);

  int my_color = get_qizi_color(qizi);
  clear_saved_zuobiaos();

  // 将/帅走直线的 4 个可能位置
  int jiang_moves[4][2] = {
      {row - 1, col}, {row + 1, col}, {row, col - 1}, {row, col + 1}};

  for (int i = 0; i < 4; i++) {
    int next_row = jiang_moves[i][0];
    int next_col = jiang_moves[i][1];

    // 检查是否在棋盘范围内
    if (!is_bianjie(next_row, next_col))
      continue;

    // 检查是否在九宫格内
    if (my_color == 0) // 红方帅
    {
      if (next_row < 0 || next_row > 2 || next_col < 3 || next_col > 5) {
        printf("  位置 (%d,%d) 不在九宫格，跳过\n", next_row, next_col);
        continue;
      }
    } else // 黑方将
    {
      if (next_row < 7 || next_row > 9 || next_col < 3 || next_col > 5) {
        printf("  位置 (%d,%d) 不在九宫格，跳过\n", next_row, next_col);
        continue;
      }
    }

    const char *next_qizi = get_qizi_by_qipanarr(next_row, next_col);
    lv_obj_t *next_button = get_button_by_zuobiao(next_row, next_col);

    if (next_button == NULL)
      continue;

    save_zuobiaoarr(next_row, next_col);

    if (next_qizi[0] == '\0') {
      lv_obj_clear_flag(next_button, LV_OBJ_FLAG_HIDDEN);
      lv_obj_set_style_bg_color(next_button, lv_color_hex(0x808080),
                                LV_PART_MAIN);
      printf("  位置 (%d,%d) 为空,灰色\n", next_row, next_col);
    } else {
      int target_color = get_qizi_color(next_qizi);
      if (target_color != my_color && target_color != -1) {
        lv_obj_clear_flag(next_button, LV_OBJ_FLAG_HIDDEN);
        lv_obj_set_style_bg_color(next_button, lv_color_hex(0x808080),
                                  LV_PART_MAIN);
        printf("  位置 (%d,%d) 可吃子\n", next_row, next_col, next_qizi);
      } else {
        printf("  位置 (%d,%d) 是己方棋子\n", next_row, next_col, next_qizi);
      }
    }
  }

  printf("  共保存 %d 个可走位置\n", save_zuobiao_count);
}

// 炮走直线，吃子需要跳
static void rule_pao(int row, int col, const char *qizi) {
  printf("显示炮的移动提示：%d行%d列，棋子=%s\n", row, col, qizi);

  int my_color = get_qizi_color(qizi);
  clear_saved_zuobiaos();

  // 四个方向：上、下、左、右
  int pao_moves[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

  for (int d = 0; d < 4; d++) {
    int dr = pao_moves[d][0];
    int dc = pao_moves[d][1];
    int tiaozi_count = 0; // 炮架计数

    for (int step = 1; step < 9; step++) {
      int next_row = row + dr * step;
      int next_col = col + dc * step;

      if (!is_bianjie(next_row, next_col))
        break;

      const char *next_qizi = get_qizi_by_qipanarr(next_row, next_col);
      lv_obj_t *nextqizi_button = get_button_by_zuobiao(next_row, next_col);

      if (nextqizi_button == NULL)
        break;

      if (tiaozi_count == 0) {
        // 炮架前
        if (next_qizi[0] == '\0') {
          // 空位，可以走
          save_zuobiaoarr(next_row, next_col);
          lv_obj_clear_flag(nextqizi_button, LV_OBJ_FLAG_HIDDEN);
          lv_obj_set_style_bg_color(nextqizi_button, lv_color_hex(0x808080),
                                    LV_PART_MAIN);
          printf("  位置 (%d,%d) 为空，显示提示（灰色）\n", next_row, next_col);
        } else {
          // 遇到第一个棋子，作为炮架
          tiaozi_count = 1;
        }
      } else {
        // 炮架后
        if (next_qizi[0] == '\0') {
          // 空位不能吃
          continue;
        } else {
          // 有棋子，判断是否可以吃
          int nextqizi_color = get_qizi_color(next_qizi);
          if (nextqizi_color != my_color && nextqizi_color != -1) {
            // 敌方棋子，可以吃
            save_zuobiaoarr(next_row, next_col);
            lv_obj_clear_flag(nextqizi_button, LV_OBJ_FLAG_HIDDEN);
            lv_obj_set_style_bg_color(nextqizi_button, lv_color_hex(0x808080),
                                      LV_PART_MAIN);
            printf("  位置 (%d,%d) 可吃子：%s（灰色）\n", next_row, next_col,
                   next_qizi);
          }
          break; // 遇到第二个棋子停止
        }
      }
    }
  }

  printf("  共保存 %d 个可走位置\n", save_zuobiao_count);
}

// 兵/卒
static void rule_bing(int row, int col, const char *qizi) {
  printf("显示兵/卒的移动提示：%d行%d列，棋子=%s\n", row, col, qizi);

  int my_color = get_qizi_color(qizi);
  clear_saved_zuobiaos();

  // 判断前进方向
  int bing_moves = (my_color == 0) ? 1 : -1; // 红方向下（+），黑方往上（-）

  // 判断是否过河
  int is_guohe = (my_color == 0) ? (row >= 5) : (row <= 4);

  // 前进
  int next_row = row + bing_moves;
  int next_col = col;

  if (is_bianjie(next_row, next_col)) {
    const char *next_qizi = get_qizi_by_qipanarr(next_row, next_col);
    lv_obj_t *nextqizi_button = get_button_by_zuobiao(next_row, next_col);

    if (nextqizi_button != NULL) {
      save_zuobiaoarr(next_row, next_col);

      if (next_qizi[0] == '\0') {
        lv_obj_clear_flag(nextqizi_button, LV_OBJ_FLAG_HIDDEN);
        lv_obj_set_style_bg_color(nextqizi_button, lv_color_hex(0x808080),
                                  LV_PART_MAIN);
        printf("  位置 (%d,%d) 为空\n", next_row, next_col);
      } else {
        int target_color = get_qizi_color(next_qizi);
        if (target_color != my_color && target_color != -1) {
          lv_obj_clear_flag(nextqizi_button, LV_OBJ_FLAG_HIDDEN);
          lv_obj_set_style_bg_color(nextqizi_button, lv_color_hex(0x808080),
                                    LV_PART_MAIN);
          printf("  位置 (%d,%d) 可吃子\n", next_row, next_col, next_qizi);
        } else {
          printf("  位置 (%d,%d) 是己方棋子\n", next_row, next_col, next_qizi);
        }
      }
    }
  }

  // 过河后可以横走
  if (is_guohe) {
    // 左
    next_row = row;
    next_col = col - 1;
    if (is_bianjie(next_row, next_col)) {
      const char *next_qizi = get_qizi_by_qipanarr(next_row, next_col);
      lv_obj_t *nextqizi_button = get_button_by_zuobiao(next_row, next_col);

      if (nextqizi_button != NULL) {
        save_zuobiaoarr(next_row, next_col);

        if (next_qizi[0] == '\0') {
          lv_obj_clear_flag(nextqizi_button, LV_OBJ_FLAG_HIDDEN);
          lv_obj_set_style_bg_color(nextqizi_button, lv_color_hex(0x808080),
                                    LV_PART_MAIN);
          printf("  位置 (%d,%d) 为空，显示提示灰色\n", next_row, next_col);
        } else {
          int nextqizi_color = get_qizi_color(next_qizi);
          if (nextqizi_color != my_color && nextqizi_color != -1) {
            lv_obj_clear_flag(nextqizi_button, LV_OBJ_FLAG_HIDDEN);
            lv_obj_set_style_bg_color(nextqizi_button, lv_color_hex(0x808080),
                                      LV_PART_MAIN);
            printf("  位置 (%d,%d) 可吃子\n", next_row, next_col, next_qizi);
          } else {
            printf("  位置 (%d,%d) 是己方棋子\n", next_row, next_col,
                   next_qizi);
          }
        }
      }
    }

    // 右
    next_row = row;
    next_col = col + 1;
    if (is_bianjie(next_row, next_col)) {
      const char *next_qizi = get_qizi_by_qipanarr(next_row, next_col);
      lv_obj_t *nextqizi_button = get_button_by_zuobiao(next_row, next_col);

      if (nextqizi_button != NULL) {
        save_zuobiaoarr(next_row, next_col);

        if (next_qizi[0] == '\0') {
          lv_obj_clear_flag(nextqizi_button, LV_OBJ_FLAG_HIDDEN);
          lv_obj_set_style_bg_color(nextqizi_button, lv_color_hex(0x808080),
                                    LV_PART_MAIN);
          printf("  位置 (%d,%d) 为空\n", next_row, next_col);
        } else {
          int target_color = get_qizi_color(next_qizi);
          if (target_color != my_color && target_color != -1) {
            lv_obj_clear_flag(nextqizi_button, LV_OBJ_FLAG_HIDDEN);
            lv_obj_set_style_bg_color(nextqizi_button, lv_color_hex(0x808080),
                                      LV_PART_MAIN);
            printf("  位置 (%d,%d) 可吃子\n", next_row, next_col, next_qizi);
          } else {
            printf("  位置 (%d,%d) 是己方棋子\n", next_row, next_col,
                   next_qizi);
          }
        }
      }
    }
  }

  printf("  共保存 %d 个可走位置\n", save_zuobiao_count);
}

static void parse_zuobiao(const char *zuobiao_str, int *row, int *col) {
  if (zuobiao_str == NULL) {
    *row = -1;
    *col = -1;
    return;
  }
  sscanf(zuobiao_str, "%d_%d", row, col);
  printf("解析坐标：'%s' -> (%d,%d)\n", zuobiao_str, *row, *col);
}

// 统一的棋子按钮点击事件处理函数
void ui_event_button_clicked(lv_event_t *e) {
  lv_event_code_t event_code = lv_event_get_code(e);

  if (event_code == LV_EVENT_CLICKED) {
    const char *coord_str = (const char *)lv_event_get_user_data(e);

    // 检查是否允许下棋
    if (!xiaqi) {
      printf("现在不是你的回合，请等待对方落子！\n");
      return;
    }

    int row = 0, col = 0;
    parse_zuobiao(coord_str, &row, &col);

    if (row < 0 || row >= BOARD_ROWS || col < 0 || col >= BOARD_COLS) {
      printf("无效的坐标！\n");
      return;
    }

    const char *qizi = get_qizi_by_qipanarr(row, col);
    char qizi_value[PIECE_NAME_LEN];
    get_qizi_value(qizi, qizi_value);

    printf("点击按钮，坐标 (%d,%d), 棋子='%s' \n", row, col, qizi);

    if (save_zuobiao_count > 0) {
      re_qipan();
    }

    if (selected_row >= 0 && selected_col >= 0) {
      printf("之前选中的棋子：(%d,%d) %s\n", selected_row, selected_col,
             selected_qizi);

      if (selected_row == row && selected_col == col) {
        printf("取消选中\n");
        selected_row = -1;
        selected_col = -1;
        selected_qizi[0] = '\0';
        return;
      }

      const char *next_qizi = get_qizi_by_qipanarr(row, col);

      // 如果目标位置有棋子，判断是否是同一阵营
      if (next_qizi[0] != '\0') {
        int selected_color = get_qizi_color(selected_qizi);
        int next_color = get_qizi_color(next_qizi);

        if (selected_color == next_color) {
          printf("不能吃己方棋子：%s，请重新选择\n", next_qizi);
          // 取消选中状态
          selected_row = -1;
          selected_col = -1;
          selected_qizi[0] = '\0';
          // 重新选中当前点击的棋子（如果是己方棋子）
          if (qizi[0] != '\0' && get_qizi_color(qizi) == current_zhenyin) {
            printf("选中棋子：%s\n", qizi);
            selected_row = row;
            selected_col = col;
            strcpy(selected_qizi, qizi);
            nextip_by_qizitype(row, col, qizi);
          }
          return;
        } else {
          printf("可以吃子：%s\n", next_qizi);

          // 显示吃子提示
          char wo_chi_zi_msg[100];
          sprintf(wo_chi_zi_msg, "吃掉对方棋子：%s", next_qizi);
          show_popup_message(EAT, wo_chi_zi_msg);

          // 检查被吃的棋子是否是将或帅
          char nextqizi_value[PIECE_NAME_LEN];
          get_qizi_value(next_qizi, nextqizi_value);

          if (strcmp(nextqizi_value, "将") == 0 ||
              strcmp(nextqizi_value, "帅") == 0 ||
              strcmp(nextqizi_value, "將") == 0 ||
              strcmp(nextqizi_value, "帥") == 0) {
            printf("吃掉对方将/帅，你赢了！\n");

            // 显示胜利弹窗
            show_popup_message(WIN, "牛逼克拉斯阿");

            lv_obj_add_flag(ui_QiPan, LV_OBJ_FLAG_HIDDEN);
            lv_obj_add_flag(ui_duishou, LV_OBJ_FLAG_HIDDEN);
            lv_obj_add_flag(ui_myself, LV_OBJ_FLAG_HIDDEN);

            lv_obj_set_x(ui_Button1, 1);
            lv_obj_set_y(ui_Button1, 154);
          }
        }
      }

      printf("走棋：从 (%d,%d) 到 (%d,%d)\n", selected_row, selected_col, row,
             col);

      char selected_qizi_value[PIECE_NAME_LEN];
      get_qizi_value(selected_qizi, selected_qizi_value);

      // 如果吃子，更新对方棋子数量
      printf("检查吃子：next_qizi='%s', next_qizi[0]='%c'\n", next_qizi,
             next_qizi[0]);
      if (next_qizi[0] != '\0') {
        printf("目标位置有棋子，检查颜色...\n");
        // 检查是否是对方棋子
        int selected_color = get_qizi_color(selected_qizi);
        int next_color = get_qizi_color(next_qizi);

        printf("selected_color=%d, next_color=%d\n", selected_color,
               next_color);

        if (selected_color != next_color) // 只有吃对方棋子时才减少数量
        {
          printf("确认是对方棋子，减少对方棋子数量...\n");
          // 获取当前显示的棋子数量
          const char *count_str = lv_label_get_text(ui_duishouqiziCount);
          int count = atoi(count_str);

          printf("当前对方棋子数量：%d\n", count);

          // 数量减 1
          if (count > 0) {
            count--;
            char new_count[8];
            sprintf(new_count, "%d", count);
            lv_label_set_text(ui_duishouqiziCount, new_count);
            printf("吃子！对方棋子剩余：%d\n", count);
          }
        } else {
          printf("警告：棋子颜色相同，不应该发生！\n");
        }
      } else {
        printf("目标位置没有棋子，不吃子\n");
      }

      // 更新棋盘数组
      set_qipanarr(row, col, selected_qizi);
      clear_old_qizi(selected_row, selected_col);

      send_moveinfo(selected_row, selected_col, row, col, selected_qizi);

      xiaqi = 0;
      daojishi_reset();
      printf("已落子，等待对方下棋...\n");

      lv_obj_t *src_label = get_label_by_zuobiao(selected_row, selected_col);
      lv_obj_t *dst_label = get_label_by_zuobiao(row, col);
      lv_obj_t *src_button = get_button_by_zuobiao(selected_row, selected_col);
      lv_obj_t *dst_button = get_button_by_zuobiao(row, col);

      int len = strlen(selected_qizi_value);
      if (len >= 2 && selected_qizi_value[len - 2] == '_') {
        if (selected_qizi_value[len - 1] == 'r' || qizi_value[len - 1] == 'b') {
          selected_qizi_value[len - 2] = '\0';
        }
      }

      if (src_label && dst_label) {
        lv_label_set_text(dst_label, selected_qizi_value);
        lv_label_set_text(src_label, " ");

        // 使用安全函数隐藏/显示按钮
        show_object_safe(dst_button);
        hide_object_safe(src_button);

        lv_color_t bg_color =
            lv_obj_get_style_bg_color(src_button, LV_PART_MAIN);
        lv_obj_set_style_bg_color(dst_button, bg_color, LV_PART_MAIN);

        printf("  更新 UI: 目标位置 Label='%s' (原棋子：%s)\n",
               selected_qizi_value, selected_qizi);
      }

      selected_row = -1;
      selected_col = -1;
      selected_qizi[0] = '\0';

      printArr_qipan();

    } else {
      // 没有选中的棋子，选择当前点击的棋子
      if (qizi[0] != '\0') {
        // 判断是否是己方棋子
        int qizi_color = get_qizi_color(qizi);

        // 检查是否是己方回合
        if (!xiaqi) {
          show_popup_message(DUISHOU_HUIHE, "对手回合，请等待...");
          return;
        }

        if (qizi_color == current_zhenyin) {
          printf("选中棋子：%s\n", qizi);
          selected_row = row;
          selected_col = col;
          strcpy(selected_qizi, qizi);

          // 根据棋子类型显示可走位置
          nextip_by_qizitype(row, col, qizi);
        } else {
          printf("点击的是敌方棋子：%s，不能选中\n", qizi);
          
        }
      } else {
        printf("点击的是空位置，无操作\n");
      }
    }
  }
}

/* #include "myhead.h"

// tcp客户端获取连接
int tcpclient(char *port, char *ip) {
  // 1. 创建tcp通信套接字，选择字节流套接字宏socket() SOCK_STREAM
  int tcpfd = socket(AF_INET, SOCK_STREAM, 0);
  if (tcpfd == -1) {
    perror("tcpfd socket failed\n");
    return -1;
  }
  printf("tcp客户端通信套接字%d\n", tcpfd);

  // 客户端允许本地端口号和地址重用
  // level：SOL_SOCKET   optname：SO_REUSEADDR  optval：int
  int on = 1;
  int ret = setsockopt(tcpfd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(int));
  if (ret == -1) {
    perror("允许允许本地端口号和地址重用失败\n");
    return -1;
  }

  // 2. 配置连接服务端的地址和端口号 struct sockaddr_in
  IPV4 saddr;
  saddr.sin_family = AF_INET;            // IPV4地址
  saddr.sin_port = htons(atoi(port));    // 端口
  saddr.sin_addr.s_addr = inet_addr(ip); // ipv4地址

  // 3. 通过函数建立客户端连接服务端对象 connect()
  ret = connect(tcpfd, (ADDR *)&saddr, SIZE);
  if (ret == -1) {
    perror("connect failed\n");
    return -1;
  }
  printf("客户端连接成功\n");
  return tcpfd;
}

// 接受消息
void *recv_msg(void *arg) {

  pthread_detach(pthread_self());
  // 获取通信套接字
  int tcpfd = *(int *)arg;

  char buffer[1024];
  while (1) {
    sleep(1);
    // --- 新增代码开始：发送获取历史消息指令 ---
    char history_cmd[] =
        "cmd=9&uid=3f2d5feab40ea3844d23321f165ab2db&topic=QtDQMfr0E002\r\n";
    int ret = send(tcpfd, history_cmd, strlen(history_cmd), 0);
    if (ret == -1) {
      perror("发送历史消息请求失败");
    } else {
      printf("已发送获取历史消息请求，请等待接收...\n");
    }

    memset(buffer, 0, 1024);
    recv(tcpfd, buffer, sizeof(buffer), 0); // 读取数据
    printf("读取到数据 ：%s\n", buffer);
  }
}
void *msg(void *arg) {
  pthread_detach(pthread_self());
  // 获取通信套接字
  int tcpfd = *(int *)arg;
  while (1) // ping\r\n
  {
    // 建议60秒发送一次心跳，超过65秒未发送会断线
    send(tcpfd, "ping\r\n", strlen("ping\r\n"), 0);
    sleep(60);
  }
}

// 客户端（主动发起方）
int main(int argc, char *argv[]) {
  // tcp客户端获取连接
  // 巴法云的服务端IP地址119.91.109.180 端口号8344
  int tcpfd = tcpclient("8344", "119.91.109.180");
  if (tcpfd == -1)
    return -1;

  // 子线程接受消息
  pthread_t thread1, thread2;
  pthread_create(&thread1, NULL, recv_msg, (void *)&tcpfd);
  pthread_create(&thread2, NULL, msg, (void *)&tcpfd);

  // 主线程发送消息
  char cmd[] = "cmd=2&uid=3f2d5feab40ea3844d23321f165ab2db&topic=QtDQMfr0E002";
  char str[20];
  char msg[100];
  while (1) {
    memset(str, 0, 20);
    memset(msg, 0, 100);
    printf("请输入发送给灯控制设备的信息：");
    scanf("%s", str);
    sprintf(msg, "%s&msg=%s\r\n", cmd, str);         // 形成完整命令
    int send_len = send(tcpfd, msg, strlen(msg), 0); // 接收返回值

    if (send_len == -1) {
      perror("send failed");
      // 可选：退出循环或重连
      break;
    } else if (send_len < strlen(msg)) {
      printf("警告: 仅发送了 %d 字节，总共 %lu 字节\n", send_len, strlen(msg));
      // 在实际生产中，这里可能需要处理剩余数据的发送
    } else {
      // 发送成功
      printf("消息发送成功: %s\n", msg);
    }
  }

  return 0;
} */
// 象棋棋盘状态管理
#ifndef XIANGQI_BOARD_H
#define XIANGQI_BOARD_H

#include <stdio.h>
#include <string.h>

// 棋盘大小
#define BOARD_ROWS 10
#define BOARD_COLS 9

// 最大棋子名称长度
#define PIECE_NAME_LEN 10

static char qipanarr_qizis[BOARD_ROWS][BOARD_COLS][PIECE_NAME_LEN] = {
    
    {"車_r", "馬_r", "相_r", "仕_r", "帥_r", "仕_r", "相_r", "馬_r", "車_r"},
    
    {"", "", "", "", "", "", "", "", ""},
    
    {"", "炮_r", "", "", "", "", "", "炮_r", ""},
    
    {"兵_r", "", "兵_r", "", "兵_r", "", "兵_r", "", "兵_r"},
   
    {"", "", "", "", "", "", "", "", ""},
  
    {"", "", "", "", "", "", "", "", ""},
  
    {"卒_b", "", "卒_b", "", "卒_b", "", "卒_b", "", "卒_b"},
   
    {"", "炮_b", "", "", "", "", "", "炮_b", ""},
   
    {"", "", "", "", "", "", "", "", ""},

    {"車_b", "馬_b", "象_b", "士_b", "將_b", "士_b", "象_b", "馬_b", "車_b"}
};

// 记录可走位置的数组
static int save_zuobiao[20][2];  // 最多 20 个可走位置
static int save_zuobiao_count = 0;  // 已保存的坐标数量

// 获取指定位置的棋子
static const char* get_qizi_by_qipanarr(int row, int col)
{
    if (row < 0 || row >= BOARD_ROWS || col < 0 || col >= BOARD_COLS)
        return "";
    return qipanarr_qizis[row][col];
}

// 设置指定位置的棋子
static void set_qipanarr(int row, int col, const char *qizi)
{
    if (row < 0 || row >= BOARD_ROWS || col < 0 || col >= BOARD_COLS)
        return;
    strncpy(qipanarr_qizis[row][col], qizi, PIECE_NAME_LEN - 1);
    qipanarr_qizis[row][col][PIECE_NAME_LEN - 1] = '\0';
}

// 清空指定位置的棋子
static void clear_old_qizi(int row, int col)
{
    if (row < 0 || row >= BOARD_ROWS || col < 0 || col >= BOARD_COLS)
        return;
    qipanarr_qizis[row][col][0] = '\0';
}

// 判断棋子颜色
// 0=红方，1=黑方，-1=空位置
static int get_qizi_color(const char *qizi)
{
    if (qizi == NULL || qizi[0] == '\0')
        return -1;
    
    int len = strlen(qizi);
    if (len < 3)
        return -1;
    
    if (strcmp(qizi + len - 2, "_r") == 0)
        return 0;  // 红方
    else if (strcmp(qizi + len - 2, "_b") == 0)
        return 1;  // 黑方
    
    return -1;
}

// 从棋子名称中提取棋子类型
static void get_qizi_value(const char *old_qiziname, char *qizi_value)
{
    if (old_qiziname == NULL || old_qiziname[0] == '\0')
    {
        qizi_value[0] = '\0';
        return;
    }
    
    strncpy(qizi_value, old_qiziname, PIECE_NAME_LEN - 1);
    qizi_value[PIECE_NAME_LEN - 1] = '\0';
    
    int len = strlen(qizi_value);
    if (len >= 2 && qizi_value[len-2] == '_')
    {
        if (qizi_value[len-1] == 'r' || qizi_value[len-1] == 'b')
        {
            qizi_value[len-2] = '\0';
        }
    }
}

// 检查坐标是否在棋盘范围内
static int is_bianjie(int row, int col)
{
    return (row >= 0 && row < BOARD_ROWS && col >= 0 && col < BOARD_COLS);
}

// 清空保存的坐标数组
static void clear_saved_zuobiaos(void)
{
    save_zuobiao_count = 0;
    for (int i = 0; i < 20; i++)
    {
        save_zuobiao[i][0] = -1;
        save_zuobiao[i][1] = -1;
    }
}

// 保存坐标到数组
static void save_zuobiaoarr(int row, int col)
{
    if (save_zuobiao_count < 20)
    {
        save_zuobiao[save_zuobiao_count][0] = row;
        save_zuobiao[save_zuobiao_count][1] = col;
        save_zuobiao_count++;
    }
}
 
static void init_qipan_qizi(void)
{
    strcpy(qipanarr_qizis[0][0], "車_r");
    strcpy(qipanarr_qizis[0][1], "馬_r");
    strcpy(qipanarr_qizis[0][2], "相_r");
    strcpy(qipanarr_qizis[0][3], "仕_r");
    strcpy(qipanarr_qizis[0][4], "帥_r");
    strcpy(qipanarr_qizis[0][5], "仕_r");
    strcpy(qipanarr_qizis[0][6], "相_r");
    strcpy(qipanarr_qizis[0][7], "馬_r");
    strcpy(qipanarr_qizis[0][8], "車_r");
    
    for (int col = 0; col < 9; col++)
        qipanarr_qizis[1][col][0] = '\0';
    
    qipanarr_qizis[2][0][0] = '\0';
    strcpy(qipanarr_qizis[2][1], "炮_r");
    qipanarr_qizis[2][2][0] = '\0';
    qipanarr_qizis[2][3][0] = '\0';
    qipanarr_qizis[2][4][0] = '\0';
    qipanarr_qizis[2][5][0] = '\0';
    qipanarr_qizis[2][6][0] = '\0';
    strcpy(qipanarr_qizis[2][7], "炮_r");
    qipanarr_qizis[2][8][0] = '\0';
    
    strcpy(qipanarr_qizis[3][0], "兵_r");
    qipanarr_qizis[3][1][0] = '\0';
    strcpy(qipanarr_qizis[3][2], "兵_r");
    qipanarr_qizis[3][3][0] = '\0';
    strcpy(qipanarr_qizis[3][4], "兵_r");
    qipanarr_qizis[3][5][0] = '\0';
    strcpy(qipanarr_qizis[3][6], "兵_r");
    qipanarr_qizis[3][7][0] = '\0';
    strcpy(qipanarr_qizis[3][8], "兵_r");
    
    for (int col = 0; col < 9; col++)
        qipanarr_qizis[4][col][0] = '\0';
    
    for (int col = 0; col < 9; col++)
        qipanarr_qizis[5][col][0] = '\0';
    
    strcpy(qipanarr_qizis[6][0], "卒_b");
    qipanarr_qizis[6][1][0] = '\0';
    strcpy(qipanarr_qizis[6][2], "卒_b");
    qipanarr_qizis[6][3][0] = '\0';
    strcpy(qipanarr_qizis[6][4], "卒_b");
    qipanarr_qizis[6][5][0] = '\0';
    strcpy(qipanarr_qizis[6][6], "卒_b");
    qipanarr_qizis[6][7][0] = '\0';
    strcpy(qipanarr_qizis[6][8], "卒_b");
    
    qipanarr_qizis[7][0][0] = '\0';
    strcpy(qipanarr_qizis[7][1], "炮_b");
    qipanarr_qizis[7][2][0] = '\0';
    qipanarr_qizis[7][3][0] = '\0';
    qipanarr_qizis[7][4][0] = '\0';
    qipanarr_qizis[7][5][0] = '\0';
    qipanarr_qizis[7][6][0] = '\0';
    strcpy(qipanarr_qizis[7][7], "炮_b");
    qipanarr_qizis[7][8][0] = '\0';
    
    for (int col = 0; col < 9; col++)
        qipanarr_qizis[8][col][0] = '\0';
    
    strcpy(qipanarr_qizis[9][0], "車_b");
    strcpy(qipanarr_qizis[9][1], "馬_b");
    strcpy(qipanarr_qizis[9][2], "象_b");
    strcpy(qipanarr_qizis[9][3], "士_b");
    strcpy(qipanarr_qizis[9][4], "將_b");
    strcpy(qipanarr_qizis[9][5], "士_b");
    strcpy(qipanarr_qizis[9][6], "象_b");
    strcpy(qipanarr_qizis[9][7], "馬_b");
    strcpy(qipanarr_qizis[9][8], "車_b");
}

#endif

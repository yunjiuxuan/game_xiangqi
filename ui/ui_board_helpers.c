// 棋盘辅助函数：根据坐标获取按钮和 Label 对象
#include "./ui.h"

// 按钮对象数组（按行优先排列）
static lv_obj_t* button_array[10][9] = {{NULL}};
static int button_array_initialized = 0;

// Label 对象数组（按行优先排列）
static lv_obj_t* label_array[10][9] = {{NULL}};
static int label_array_initialized = 0;

// 初始化按钮数组
static void init_button_array(void)
{
    if (button_array_initialized) return;
    
    // 第 0 行
    button_array[0][0] = ui_Button00; button_array[0][1] = ui_Button01; button_array[0][2] = ui_Button02;
    button_array[0][3] = ui_Button03; button_array[0][4] = ui_Button04; button_array[0][5] = ui_Button05;
    button_array[0][6] = ui_Button06; button_array[0][7] = ui_Button07; button_array[0][8] = ui_Button08;
    
    // 第 1 行
    button_array[1][0] = ui_Button10; button_array[1][1] = ui_Button11; button_array[1][2] = ui_Button12;
    button_array[1][3] = ui_Button13; button_array[1][4] = ui_Button14; button_array[1][5] = ui_Button15;
    button_array[1][6] = ui_Button16; button_array[1][7] = ui_Button17; button_array[1][8] = ui_Button18;
    
    // 第 2 行
    button_array[2][0] = ui_Button20; button_array[2][1] = ui_Button21; button_array[2][2] = ui_Button22;
    button_array[2][3] = ui_Button23; button_array[2][4] = ui_Button24; button_array[2][5] = ui_Button25;
    button_array[2][6] = ui_Button26; button_array[2][7] = ui_Button27; button_array[2][8] = ui_Button28;
    
    // 第 3 行
    button_array[3][0] = ui_Button30; button_array[3][1] = ui_Button31; button_array[3][2] = ui_Button32;
    button_array[3][3] = ui_Button33; button_array[3][4] = ui_Button34; button_array[3][5] = ui_Button35;
    button_array[3][6] = ui_Button36; button_array[3][7] = ui_Button37; button_array[3][8] = ui_Button38;
    
    // 第 4 行
    button_array[4][0] = ui_Button40; button_array[4][1] = ui_Button41; button_array[4][2] = ui_Button42;
    button_array[4][3] = ui_Button43; button_array[4][4] = ui_Button44; button_array[4][5] = ui_Button45;
    button_array[4][6] = ui_Button46; button_array[4][7] = ui_Button47; button_array[4][8] = ui_Button48;
    
    // 第 5 行
    button_array[5][0] = ui_Button50; button_array[5][1] = ui_Button51; button_array[5][2] = ui_Button52;
    button_array[5][3] = ui_Button53; button_array[5][4] = ui_Button54; button_array[5][5] = ui_Button55;
    button_array[5][6] = ui_Button56; button_array[5][7] = ui_Button57; button_array[5][8] = ui_Button58;
    
    // 第 6 行
    button_array[6][0] = ui_Button60; button_array[6][1] = ui_Button61; button_array[6][2] = ui_Button62;
    button_array[6][3] = ui_Button63; button_array[6][4] = ui_Button64; button_array[6][5] = ui_Button65;
    button_array[6][6] = ui_Button66; button_array[6][7] = ui_Button67; button_array[6][8] = ui_Button68;
    
    // 第 7 行
    button_array[7][0] = ui_Button70; button_array[7][1] = ui_Button71; button_array[7][2] = ui_Button72;
    button_array[7][3] = ui_Button73; button_array[7][4] = ui_Button74; button_array[7][5] = ui_Button75;
    button_array[7][6] = ui_Button76; button_array[7][7] = ui_Button77; button_array[7][8] = ui_Button78;
    
    // 第 8 行
    button_array[8][0] = ui_Button80; button_array[8][1] = ui_Button81; button_array[8][2] = ui_Button82;
    button_array[8][3] = ui_Button83; button_array[8][4] = ui_Button84; button_array[8][5] = ui_Button85;
    button_array[8][6] = ui_Button86; button_array[8][7] = ui_Button87; button_array[8][8] = ui_Button88;
    
    // 第 9 行
    button_array[9][0] = ui_Button90; button_array[9][1] = ui_Button91; button_array[9][2] = ui_Button92;
    button_array[9][3] = ui_Button93; button_array[9][4] = ui_Button94; button_array[9][5] = ui_Button95;
    button_array[9][6] = ui_Button96; button_array[9][7] = ui_Button97; button_array[9][8] = ui_Button98;
    
    button_array_initialized = 1;
}

// 初始化 Label 数组
static void init_label_array(void)
{
    if (label_array_initialized) return;
    
    // 第 0 行
    label_array[0][0] = ui_Label00; label_array[0][1] = ui_Label01; label_array[0][2] = ui_Label02;
    label_array[0][3] = ui_Label03; label_array[0][4] = ui_Label04; label_array[0][5] = ui_Label05;
    label_array[0][6] = ui_Label06; label_array[0][7] = ui_Label07; label_array[0][8] = ui_Label08;
    
    // 第 1 行
    label_array[1][0] = ui_Label10; label_array[1][1] = ui_Label11; label_array[1][2] = ui_Label12;
    label_array[1][3] = ui_Label13; label_array[1][4] = ui_Label14; label_array[1][5] = ui_Label15;
    label_array[1][6] = ui_Label16; label_array[1][7] = ui_Label17; label_array[1][8] = ui_Label18;
    
    // 第 2 行
    label_array[2][0] = ui_Label20; label_array[2][1] = ui_Label21; label_array[2][2] = ui_Label22;
    label_array[2][3] = ui_Label23; label_array[2][4] = ui_Label24; label_array[2][5] = ui_Label25;
    label_array[2][6] = ui_Label26; label_array[2][7] = ui_Label27; label_array[2][8] = ui_Label28;
    
    // 第 3 行
    label_array[3][0] = ui_Label30; label_array[3][1] = ui_Label31; label_array[3][2] = ui_Label32;
    label_array[3][3] = ui_Label33; label_array[3][4] = ui_Label34; label_array[3][5] = ui_Label35;
    label_array[3][6] = ui_Label36; label_array[3][7] = ui_Label37; label_array[3][8] = ui_Label38;
    
    // 第 4 行
    label_array[4][0] = ui_Label40; label_array[4][1] = ui_Label41; label_array[4][2] = ui_Label42;
    label_array[4][3] = ui_Label43; label_array[4][4] = ui_Label44; label_array[4][5] = ui_Label45;
    label_array[4][6] = ui_Label46; label_array[4][7] = ui_Label47; label_array[4][8] = ui_Label48;
    
    // 第 5 行
    label_array[5][0] = ui_Label50; label_array[5][1] = ui_Label51; label_array[5][2] = ui_Label52;
    label_array[5][3] = ui_Label53; label_array[5][4] = ui_Label54; label_array[5][5] = ui_Label55;
    label_array[5][6] = ui_Label56; label_array[5][7] = ui_Label57; label_array[5][8] = ui_Label58;
    
    // 第 6 行
    label_array[6][0] = ui_Label60; label_array[6][1] = ui_Label61; label_array[6][2] = ui_Label62;
    label_array[6][3] = ui_Label63; label_array[6][4] = ui_Label64; label_array[6][5] = ui_Label65;
    label_array[6][6] = ui_Label66; label_array[6][7] = ui_Label67; label_array[6][8] = ui_Label68;
    
    // 第 7 行
    label_array[7][0] = ui_Label70; label_array[7][1] = ui_Label71; label_array[7][2] = ui_Label72;
    label_array[7][3] = ui_Label73; label_array[7][4] = ui_Label74; label_array[7][5] = ui_Label75;
    label_array[7][6] = ui_Label76; label_array[7][7] = ui_Label77; label_array[7][8] = ui_Label78;
    
    // 第 8 行
    label_array[8][0] = ui_Label80; label_array[8][1] = ui_Label81; label_array[8][2] = ui_Label82;
    label_array[8][3] = ui_Label83; label_array[8][4] = ui_Label84; label_array[8][5] = ui_Label85;
    label_array[8][6] = ui_Label86; label_array[8][7] = ui_Label87; label_array[8][8] = ui_Label88;
    
    // 第 9 行
    label_array[9][0] = ui_Label90; label_array[9][1] = ui_Label91; label_array[9][2] = ui_Label92;
    label_array[9][3] = ui_Label93; label_array[9][4] = ui_Label94; label_array[9][5] = ui_Label95;
    label_array[9][6] = ui_Label96; label_array[9][7] = ui_Label97; label_array[9][8] = ui_Label98;
    
    label_array_initialized = 1;
}

// 根据行列坐标获取对应的按钮对象
lv_obj_t* get_button_by_zuobiao(int row, int col)
{
    if (!button_array_initialized) {
        init_button_array();
    }
    
    if (row < 0 || row >= 10 || col < 0 || col >= 9)
        return NULL;
    
    return button_array[row][col];
}

// 根据行列坐标获取对应的 Label 对象
lv_obj_t* get_label_by_zuobiao(int row, int col)
{
    if (!label_array_initialized) {
        init_label_array();
    }
    
    if (row < 0 || row >= 10 || col < 0 || col >= 9)
        return NULL;
    
    return label_array[row][col];
}

// 中国象棋棋子初始化
#include "../ui.h"
#include "../xiangqi_arr.h"
#include <stdio.h>

// 初始化象棋棋子位置
void init_xiangqi_ui_arr(void) {
  init_qipan_qizi();
  printf("开始初始化象棋棋盘\n");

  // 第 0 行 - 红方
  lv_label_set_text(ui_Label00, "車");
  lv_obj_clear_flag(ui_Button00, LV_OBJ_FLAG_HIDDEN);
  lv_obj_set_style_bg_color(ui_Button00, lv_color_hex(CHESS_RED_COLOR), LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_bg_opa(ui_Button00, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_label_set_text(ui_Label01, "馬");
  lv_obj_clear_flag(ui_Button01, LV_OBJ_FLAG_HIDDEN);
  lv_obj_set_style_bg_color(ui_Button01, lv_color_hex(CHESS_RED_COLOR), LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_bg_opa(ui_Button01, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_label_set_text(ui_Label02, "相");
  lv_obj_clear_flag(ui_Button02, LV_OBJ_FLAG_HIDDEN);
  lv_obj_set_style_bg_color(ui_Button02, lv_color_hex(CHESS_RED_COLOR), LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_bg_opa(ui_Button02, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_label_set_text(ui_Label03, "仕");
  lv_obj_clear_flag(ui_Button03, LV_OBJ_FLAG_HIDDEN);
  lv_obj_set_style_bg_color(ui_Button03, lv_color_hex(CHESS_RED_COLOR), LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_bg_opa(ui_Button03, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_label_set_text(ui_Label04, "帥");
  lv_obj_clear_flag(ui_Button04, LV_OBJ_FLAG_HIDDEN);
  lv_obj_set_style_bg_color(ui_Button04, lv_color_hex(CHESS_RED_COLOR), LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_bg_opa(ui_Button04, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_label_set_text(ui_Label05, "仕");
  lv_obj_clear_flag(ui_Button05, LV_OBJ_FLAG_HIDDEN);
  lv_obj_set_style_bg_color(ui_Button05, lv_color_hex(CHESS_RED_COLOR), LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_bg_opa(ui_Button05, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_label_set_text(ui_Label06, "相");
  lv_obj_clear_flag(ui_Button06, LV_OBJ_FLAG_HIDDEN);
  lv_obj_set_style_bg_color(ui_Button06, lv_color_hex(CHESS_RED_COLOR), LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_bg_opa(ui_Button06, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_label_set_text(ui_Label07, "馬");
  lv_obj_clear_flag(ui_Button07, LV_OBJ_FLAG_HIDDEN);
  lv_obj_set_style_bg_color(ui_Button07, lv_color_hex(CHESS_RED_COLOR), LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_bg_opa(ui_Button07, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_label_set_text(ui_Label08, "車");
  lv_obj_clear_flag(ui_Button08, LV_OBJ_FLAG_HIDDEN);
  lv_obj_set_style_bg_color(ui_Button08, lv_color_hex(CHESS_RED_COLOR), LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_bg_opa(ui_Button08, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

  // 第 1 行 - 全部隐藏
  lv_label_set_text(ui_Label10, " ");
  lv_obj_add_flag(ui_Button10, LV_OBJ_FLAG_HIDDEN);
  lv_label_set_text(ui_Label11, " ");
  lv_obj_add_flag(ui_Button11, LV_OBJ_FLAG_HIDDEN);
  lv_label_set_text(ui_Label12, " ");
  lv_obj_add_flag(ui_Button12, LV_OBJ_FLAG_HIDDEN);
  lv_label_set_text(ui_Label13, " ");
  lv_obj_add_flag(ui_Button13, LV_OBJ_FLAG_HIDDEN);
  lv_label_set_text(ui_Label14, " ");
  lv_obj_add_flag(ui_Button14, LV_OBJ_FLAG_HIDDEN);
  lv_label_set_text(ui_Label15, " ");
  lv_obj_add_flag(ui_Button15, LV_OBJ_FLAG_HIDDEN);
  lv_label_set_text(ui_Label16, " ");
  lv_obj_add_flag(ui_Button16, LV_OBJ_FLAG_HIDDEN);
  lv_label_set_text(ui_Label17, " ");
  lv_obj_add_flag(ui_Button17, LV_OBJ_FLAG_HIDDEN);
  lv_label_set_text(ui_Label18, " ");
  lv_obj_add_flag(ui_Button18, LV_OBJ_FLAG_HIDDEN);

  // 第 2 行 - 红方
  lv_label_set_text(ui_Label20, " ");
  lv_obj_add_flag(ui_Button20, LV_OBJ_FLAG_HIDDEN);
  lv_label_set_text(ui_Label21, "炮");
  lv_obj_clear_flag(ui_Button21, LV_OBJ_FLAG_HIDDEN);
  lv_obj_set_style_bg_color(ui_Button21, lv_color_hex(CHESS_RED_COLOR), LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_bg_opa(ui_Button21, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_label_set_text(ui_Label22, " ");
  lv_obj_add_flag(ui_Button22, LV_OBJ_FLAG_HIDDEN);
  lv_label_set_text(ui_Label23, " ");
  lv_obj_add_flag(ui_Button23, LV_OBJ_FLAG_HIDDEN);
  lv_label_set_text(ui_Label24, " ");
  lv_obj_add_flag(ui_Button24, LV_OBJ_FLAG_HIDDEN);
  lv_label_set_text(ui_Label25, " ");
  lv_obj_add_flag(ui_Button25, LV_OBJ_FLAG_HIDDEN);
  lv_label_set_text(ui_Label26, " ");
  lv_obj_add_flag(ui_Button26, LV_OBJ_FLAG_HIDDEN);
  lv_label_set_text(ui_Label27, "炮");
  lv_obj_clear_flag(ui_Button27, LV_OBJ_FLAG_HIDDEN);
  lv_obj_set_style_bg_color(ui_Button27, lv_color_hex(CHESS_RED_COLOR), LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_bg_opa(ui_Button27, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_label_set_text(ui_Label28, " ");
  lv_obj_add_flag(ui_Button28, LV_OBJ_FLAG_HIDDEN);

  // 第 3 行 - 红方
  lv_label_set_text(ui_Label30, "兵");
  lv_obj_clear_flag(ui_Button30, LV_OBJ_FLAG_HIDDEN);
  lv_obj_set_style_bg_color(ui_Button30, lv_color_hex(CHESS_RED_COLOR), LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_bg_opa(ui_Button30, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_label_set_text(ui_Label31, " ");
  lv_obj_add_flag(ui_Button31, LV_OBJ_FLAG_HIDDEN);
  lv_label_set_text(ui_Label32, "兵");
  lv_obj_clear_flag(ui_Button32, LV_OBJ_FLAG_HIDDEN);
  lv_obj_set_style_bg_color(ui_Button32, lv_color_hex(CHESS_RED_COLOR), LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_bg_opa(ui_Button32, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_label_set_text(ui_Label33, " ");
  lv_obj_add_flag(ui_Button33, LV_OBJ_FLAG_HIDDEN);
  lv_label_set_text(ui_Label34, "兵");
  lv_obj_clear_flag(ui_Button34, LV_OBJ_FLAG_HIDDEN);
  lv_obj_set_style_bg_color(ui_Button34, lv_color_hex(CHESS_RED_COLOR), LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_bg_opa(ui_Button34, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_label_set_text(ui_Label35, " ");
  lv_obj_add_flag(ui_Button35, LV_OBJ_FLAG_HIDDEN);
  lv_label_set_text(ui_Label36, "兵");
  lv_obj_clear_flag(ui_Button36, LV_OBJ_FLAG_HIDDEN);
  lv_obj_set_style_bg_color(ui_Button36, lv_color_hex(CHESS_RED_COLOR), LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_bg_opa(ui_Button36, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_label_set_text(ui_Label37, " ");
  lv_obj_add_flag(ui_Button37, LV_OBJ_FLAG_HIDDEN);
  lv_label_set_text(ui_Label38, "兵");
  lv_obj_clear_flag(ui_Button38, LV_OBJ_FLAG_HIDDEN);
  lv_obj_set_style_bg_color(ui_Button38, lv_color_hex(CHESS_RED_COLOR), LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_bg_opa(ui_Button38, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

  // 第 4 行 - 全部隐藏
  lv_label_set_text(ui_Label40, " ");
  lv_obj_add_flag(ui_Button40, LV_OBJ_FLAG_HIDDEN);
  lv_label_set_text(ui_Label41, " ");
  lv_obj_add_flag(ui_Button41, LV_OBJ_FLAG_HIDDEN);
  lv_label_set_text(ui_Label42, " ");
  lv_obj_add_flag(ui_Button42, LV_OBJ_FLAG_HIDDEN);
  lv_label_set_text(ui_Label43, " ");
  lv_obj_add_flag(ui_Button43, LV_OBJ_FLAG_HIDDEN);
  lv_label_set_text(ui_Label44, " ");
  lv_obj_add_flag(ui_Button44, LV_OBJ_FLAG_HIDDEN);
  lv_label_set_text(ui_Label45, " ");
  lv_obj_add_flag(ui_Button45, LV_OBJ_FLAG_HIDDEN);
  lv_label_set_text(ui_Label46, " ");
  lv_obj_add_flag(ui_Button46, LV_OBJ_FLAG_HIDDEN);
  lv_label_set_text(ui_Label47, " ");
  lv_obj_add_flag(ui_Button47, LV_OBJ_FLAG_HIDDEN);
  lv_label_set_text(ui_Label48, " ");
  lv_obj_add_flag(ui_Button48, LV_OBJ_FLAG_HIDDEN);

  // 第 5 行 - 全部隐藏
  lv_label_set_text(ui_Label50, " ");
  lv_obj_add_flag(ui_Button50, LV_OBJ_FLAG_HIDDEN);
  lv_label_set_text(ui_Label51, " ");
  lv_obj_add_flag(ui_Button51, LV_OBJ_FLAG_HIDDEN);
  lv_label_set_text(ui_Label52, " ");
  lv_obj_add_flag(ui_Button52, LV_OBJ_FLAG_HIDDEN);
  lv_label_set_text(ui_Label53, " ");
  lv_obj_add_flag(ui_Button53, LV_OBJ_FLAG_HIDDEN);
  lv_label_set_text(ui_Label54, " ");
  lv_obj_add_flag(ui_Button54, LV_OBJ_FLAG_HIDDEN);
  lv_label_set_text(ui_Label55, " ");
  lv_obj_add_flag(ui_Button55, LV_OBJ_FLAG_HIDDEN);
  lv_label_set_text(ui_Label56, " ");
  lv_obj_add_flag(ui_Button56, LV_OBJ_FLAG_HIDDEN);
  lv_label_set_text(ui_Label57, " ");
  lv_obj_add_flag(ui_Button57, LV_OBJ_FLAG_HIDDEN);
  lv_label_set_text(ui_Label58, " ");
  lv_obj_add_flag(ui_Button58, LV_OBJ_FLAG_HIDDEN);

  // 第 6 行 - 黑方
  lv_label_set_text(ui_Label60, "卒");
  lv_obj_clear_flag(ui_Button60, LV_OBJ_FLAG_HIDDEN);
  lv_obj_set_style_bg_color(ui_Button60, lv_color_hex(CHESS_BLACK_COLOR), LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_bg_opa(ui_Button60, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_label_set_text(ui_Label61, " ");
  lv_obj_add_flag(ui_Button61, LV_OBJ_FLAG_HIDDEN);
  lv_label_set_text(ui_Label62, "卒");
  lv_obj_clear_flag(ui_Button62, LV_OBJ_FLAG_HIDDEN);
  lv_obj_set_style_bg_color(ui_Button62, lv_color_hex(CHESS_BLACK_COLOR), LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_bg_opa(ui_Button62, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_label_set_text(ui_Label63, " ");
  lv_obj_add_flag(ui_Button63, LV_OBJ_FLAG_HIDDEN);
  lv_label_set_text(ui_Label64, "卒");
  lv_obj_clear_flag(ui_Button64, LV_OBJ_FLAG_HIDDEN);
  lv_obj_set_style_bg_color(ui_Button64, lv_color_hex(CHESS_BLACK_COLOR), LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_bg_opa(ui_Button64, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_label_set_text(ui_Label65, " ");
  lv_obj_add_flag(ui_Button65, LV_OBJ_FLAG_HIDDEN);
  lv_label_set_text(ui_Label66, "卒");
  lv_obj_clear_flag(ui_Button66, LV_OBJ_FLAG_HIDDEN);
  lv_obj_set_style_bg_color(ui_Button66, lv_color_hex(CHESS_BLACK_COLOR), LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_bg_opa(ui_Button66, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_label_set_text(ui_Label67, " ");
  lv_obj_add_flag(ui_Button67, LV_OBJ_FLAG_HIDDEN);
  lv_label_set_text(ui_Label68, "卒");
  lv_obj_clear_flag(ui_Button68, LV_OBJ_FLAG_HIDDEN);
  lv_obj_set_style_bg_color(ui_Button68, lv_color_hex(CHESS_BLACK_COLOR), LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_bg_opa(ui_Button68, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

  // 第 7 行 - 黑方
  lv_label_set_text(ui_Label70, " ");
  lv_obj_add_flag(ui_Button70, LV_OBJ_FLAG_HIDDEN);
  lv_label_set_text(ui_Label71, "炮");
  lv_obj_clear_flag(ui_Button71, LV_OBJ_FLAG_HIDDEN);
  lv_obj_set_style_bg_color(ui_Button71, lv_color_hex(CHESS_BLACK_COLOR), LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_bg_opa(ui_Button71, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_label_set_text(ui_Label72, " ");
  lv_obj_add_flag(ui_Button72, LV_OBJ_FLAG_HIDDEN);
  lv_label_set_text(ui_Label73, " ");
  lv_obj_add_flag(ui_Button73, LV_OBJ_FLAG_HIDDEN);
  lv_label_set_text(ui_Label74, " ");
  lv_obj_add_flag(ui_Button74, LV_OBJ_FLAG_HIDDEN);
  lv_label_set_text(ui_Label75, " ");
  lv_obj_add_flag(ui_Button75, LV_OBJ_FLAG_HIDDEN);
  lv_label_set_text(ui_Label76, " ");
  lv_obj_add_flag(ui_Button76, LV_OBJ_FLAG_HIDDEN);
  lv_label_set_text(ui_Label77, "炮");
  lv_obj_clear_flag(ui_Button77, LV_OBJ_FLAG_HIDDEN);
  lv_obj_set_style_bg_color(ui_Button77, lv_color_hex(CHESS_BLACK_COLOR), LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_bg_opa(ui_Button77, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_label_set_text(ui_Label78, " ");
  lv_obj_add_flag(ui_Button78, LV_OBJ_FLAG_HIDDEN);

  // 第 8 行 - 全部隐藏
  lv_label_set_text(ui_Label80, " ");
  lv_obj_add_flag(ui_Button80, LV_OBJ_FLAG_HIDDEN);
  lv_label_set_text(ui_Label81, " ");
  lv_obj_add_flag(ui_Button81, LV_OBJ_FLAG_HIDDEN);
  lv_label_set_text(ui_Label82, " ");
  lv_obj_add_flag(ui_Button82, LV_OBJ_FLAG_HIDDEN);
  lv_label_set_text(ui_Label83, " ");
  lv_obj_add_flag(ui_Button83, LV_OBJ_FLAG_HIDDEN);
  lv_label_set_text(ui_Label84, " ");
  lv_obj_add_flag(ui_Button84, LV_OBJ_FLAG_HIDDEN);
  lv_label_set_text(ui_Label85, " ");
  lv_obj_add_flag(ui_Button85, LV_OBJ_FLAG_HIDDEN);
  lv_label_set_text(ui_Label86, " ");
  lv_obj_add_flag(ui_Button86, LV_OBJ_FLAG_HIDDEN);
  lv_label_set_text(ui_Label87, " ");
  lv_obj_add_flag(ui_Button87, LV_OBJ_FLAG_HIDDEN);
  lv_label_set_text(ui_Label88, " ");
  lv_obj_add_flag(ui_Button88, LV_OBJ_FLAG_HIDDEN);

  // 第 9 行 - 黑方
  lv_label_set_text(ui_Label90, "車");
  lv_obj_clear_flag(ui_Button90, LV_OBJ_FLAG_HIDDEN);
  lv_obj_set_style_bg_color(ui_Button90, lv_color_hex(CHESS_BLACK_COLOR), LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_bg_opa(ui_Button90, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_label_set_text(ui_Label91, "馬");
  lv_obj_clear_flag(ui_Button91, LV_OBJ_FLAG_HIDDEN);
  lv_obj_set_style_bg_color(ui_Button91, lv_color_hex(CHESS_BLACK_COLOR), LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_bg_opa(ui_Button91, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_label_set_text(ui_Label92, "象");
  lv_obj_clear_flag(ui_Button92, LV_OBJ_FLAG_HIDDEN);
  lv_obj_set_style_bg_color(ui_Button92, lv_color_hex(CHESS_BLACK_COLOR), LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_bg_opa(ui_Button92, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_label_set_text(ui_Label93, "士");
  lv_obj_clear_flag(ui_Button93, LV_OBJ_FLAG_HIDDEN);
  lv_obj_set_style_bg_color(ui_Button93, lv_color_hex(CHESS_BLACK_COLOR), LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_bg_opa(ui_Button93, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_label_set_text(ui_Label94, "將");
  lv_obj_clear_flag(ui_Button94, LV_OBJ_FLAG_HIDDEN);
  lv_obj_set_style_bg_color(ui_Button94, lv_color_hex(CHESS_BLACK_COLOR), LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_bg_opa(ui_Button94, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_label_set_text(ui_Label95, "士");
  lv_obj_clear_flag(ui_Button95, LV_OBJ_FLAG_HIDDEN);
  lv_obj_set_style_bg_color(ui_Button95, lv_color_hex(CHESS_BLACK_COLOR), LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_bg_opa(ui_Button95, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_label_set_text(ui_Label96, "象");
  lv_obj_clear_flag(ui_Button96, LV_OBJ_FLAG_HIDDEN);
  lv_obj_set_style_bg_color(ui_Button96, lv_color_hex(CHESS_BLACK_COLOR), LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_bg_opa(ui_Button96, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_label_set_text(ui_Label97, "馬");
  lv_obj_clear_flag(ui_Button97, LV_OBJ_FLAG_HIDDEN);
  lv_obj_set_style_bg_color(ui_Button97, lv_color_hex(CHESS_BLACK_COLOR), LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_bg_opa(ui_Button97, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_label_set_text(ui_Label98, "車");
  lv_obj_clear_flag(ui_Button98, LV_OBJ_FLAG_HIDDEN);
  lv_obj_set_style_bg_color(ui_Button98, lv_color_hex(CHESS_BLACK_COLOR), LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_bg_opa(ui_Button98, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

  printf("象棋棋子初始化完成\n");

  lv_label_set_text(ui_duishouWinCount, " ");
  lv_label_set_text(ui_myWinCount, " ");
  lv_label_set_text(ui_duishouqiziCount, "17");

  lv_label_set_text(ui_duishoutimecount, "30");

  lv_label_set_text(ui_myqiziCount, "17");

  lv_label_set_text(ui_mytimecount, "30");
}

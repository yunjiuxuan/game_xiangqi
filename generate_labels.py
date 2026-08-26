#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
生成象棋棋盘按钮的 Label 和事件处理代码
"""

# 生成按钮 Label 的声明（用于 ui.h）
def generate_ui_h_declarations():
    content = []
    content.append("// 棋子 Label 声明")
    for row in range(10):  # 0-9 行
        for col in range(9):  # 0-8 列
            label_name = f"ui_Label{row}{col}"
            content.append(f"extern lv_obj_t *{label_name};")
    return "\n".join(content)

# 生成事件函数声明（用于 ui_events.h）
def generate_ui_events_h_declarations():
    content = []
    content.append("// 棋子按钮事件声明")
    for row in range(10):
        for col in range(9):
            func_name = f"ui_event_Button{row}{col}"
            content.append(f"void {func_name}(lv_event_t *e);")
    return "\n".join(content)

# 生成按钮 Label 创建代码和事件绑定
def generate_button_labels_and_events():
    content = []
    for row in range(10):
        content.append(f"\n  /* 第{row}行按钮的 Label */")
        for col in range(9):
            button_name = f"ui_Button{row}{col}"
            label_name = f"ui_Label{row}{col}"
            event_name = f"ui_event_Button{row}{col}"
            
            # 创建 Label
            content.append(f"  {label_name} = lv_label_create({button_name});")
            content.append(f"  lv_obj_set_width({label_name}, LV_SIZE_CONTENT);")
            content.append(f"  lv_obj_set_height({label_name}, LV_SIZE_CONTENT);")
            content.append(f"  lv_obj_set_align({label_name}, LV_ALIGN_CENTER);")
            content.append(f"  lv_label_set_text({label_name}, \" \");")
            content.append(f"  lv_obj_set_style_text_color({label_name}, lv_color_hex(0xFFFFFF),")
            content.append(f"                              LV_PART_MAIN | LV_STATE_DEFAULT);")
            content.append(f"  lv_obj_set_style_text_opa({label_name}, 255, LV_PART_MAIN | LV_STATE_DEFAULT);")
            content.append(f"  lv_obj_set_style_text_align({label_name}, LV_TEXT_ALIGN_CENTER,")
            content.append(f"                              LV_PART_MAIN | LV_STATE_DEFAULT);")
            content.append(f"  lv_obj_set_style_text_font({label_name}, &ui_font_CHINESEsize25,")
            content.append(f"                              LV_PART_MAIN | LV_STATE_DEFAULT);")
            content.append(f"  lv_obj_add_flag({label_name}, LV_OBJ_FLAG_EVENT_BUBBLE);")
            content.append(f"  lv_obj_add_event_cb({button_name}, {event_name}, LV_EVENT_CLICKED, NULL);")
            content.append("")
    
    return "\n".join(content)

# 生成背景颜色设置代码
def generate_bg_color_setup():
    content = []
    content.append("\n  /* 设置按钮背景颜色：0-4 行红色，5-9 行黑色 */")
    for row in range(10):
        # 根据行号确定颜色
        if row <= 4:
            color_macro = "CHESS_RED_COLOR"
        else:
            color_macro = "CHESS_BLACK_COLOR"
        
        content.append(f"  /* 第{row}行 - {color_macro} */")
        for col in range(9):
            button_name = f"ui_Button{row}{col}"
            content.append(f"  lv_obj_set_style_bg_color({button_name}, lv_color_hex({color_macro}),")
            content.append(f"                              LV_PART_MAIN | LV_STATE_DEFAULT);")
            content.append(f"  lv_obj_set_style_bg_opa({button_name}, 255, LV_PART_MAIN | LV_STATE_DEFAULT);")
        content.append("")
    
    return "\n".join(content)

# 生成事件处理函数实现
def generate_event_handlers():
    content = []
    content.append("// 棋子按钮点击事件处理函数")
    content.append("")
    
    for row in range(10):
        content.append(f"/* 第{row}行按钮事件 */")
        for col in range(9):
            button_name = f"ui_Button{row}{col}"
            label_name = f"ui_Label{row}{col}"
            event_name = f"ui_event_Button{row}{col}"
            
            content.append(f"void {event_name}(lv_event_t *e)")
            content.append("{")
            content.append(f"    lv_event_code_t event_code = lv_event_get_code(e);")
            content.append(f"    lv_obj_t *target = lv_event_get_target(e);")
            content.append(f"    if(event_code == LV_EVENT_CLICKED)")
            content.append("    {")
            content.append(f"        const char *label_text = lv_label_get_text({label_name});")
            content.append(f"        printf(\"点击按钮 {button_name}，Label 值：%s\\\\n\", label_text);")
            content.append("    }")
            content.append("}")
            content.append("")
    
    return "\n".join(content)

# 主函数
if __name__ == "__main__":
    print("=== ui.h 中的 Label 声明 ===")
    print(generate_ui_h_declarations())
    print("\n\n=== ui_events.h 中的事件声明 ===")
    print(generate_ui_events_h_declarations())
    print("\n\n=== ui_gamePage.c 中的 Label 创建和事件绑定 ===")
    print(generate_button_labels_and_events())
    print("\n\n=== ui_gamePage.c 中的背景颜色设置 ===")
    print(generate_bg_color_setup())
    print("\n\n=== ui_events.c 中的事件处理函数 ===")
    print(generate_event_handlers())

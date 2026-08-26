#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
生成象棋棋盘按钮的 Label、事件绑定和背景颜色代码
"""

def generate_labels_and_events():
    """生成所有按钮的 Label 创建和事件绑定代码"""
    content = []
    
    for row in range(10):  # 0-9 行
        content.append(f"\n  /* ========== 第{row}行按钮的 Label 和事件绑定 ========== */")
        
        for col in range(9):  # 0-8 列
            button_name = f"ui_Button{row}{col}"
            label_name = f"ui_Label{row}{col}"
            button_info = f"Button{row}{col}"
            
            # 创建 Label
            content.append(f"  // {button_name} 的 Label")
            content.append(f"  {label_name} = lv_label_create({button_name});")
            content.append(f"  lv_obj_set_width({label_name}, LV_SIZE_CONTENT);")
            content.append(f"  lv_obj_set_height({label_name}, LV_SIZE_CONTENT);")
            content.append(f"  lv_obj_set_align({label_name}, LV_ALIGN_CENTER);")
            content.append(f"  lv_label_set_text({label_name}, \" \"); // 初始值为空格")
            content.append(f"  lv_obj_set_style_text_color({label_name}, lv_color_hex(0xFFFFFF),")
            content.append(f"                              LV_PART_MAIN | LV_STATE_DEFAULT);")
            content.append(f"  lv_obj_set_style_text_opa({label_name}, 255, LV_PART_MAIN | LV_STATE_DEFAULT);")
            content.append(f"  lv_obj_set_style_text_align({label_name}, LV_TEXT_ALIGN_CENTER,")
            content.append(f"                              LV_PART_MAIN | LV_STATE_DEFAULT);")
            content.append(f"  lv_obj_set_style_text_font({label_name}, &ui_font_CHINESEsize25,")
            content.append(f"                              LV_PART_MAIN | LV_STATE_DEFAULT);")
            
            # 绑定点击事件，传递按钮信息
            content.append(f"  lv_obj_add_event_cb({button_name}, ui_event_button_clicked, LV_EVENT_CLICKED, (void*)\"{button_info}\");")
            content.append("")
    
    return "\n".join(content)

def generate_bg_colors():
    """生成背景颜色设置代码"""
    content = []
    content.append("\n\n  /* ========== 设置按钮背景颜色：0-4 行红色，5-9 行黑色 ========== */")
    
    for row in range(10):
        # 根据行号确定颜色宏
        if row <= 4:
            color_macro = "CHESS_RED_COLOR"
            color_name = "红色"
        else:
            color_macro = "CHESS_BLACK_COLOR"
            color_name = "黑色"
        
        content.append(f"\n  /* 第{row}行 - {color_name} ({color_macro}) */")
        
        for col in range(9):
            button_name = f"ui_Button{row}{col}"
            content.append(f"  lv_obj_set_style_bg_color({button_name}, lv_color_hex({color_macro}),")
            content.append(f"                              LV_PART_MAIN | LV_STATE_DEFAULT);")
            content.append(f"  lv_obj_set_style_bg_opa({button_name}, 255, LV_PART_MAIN | LV_STATE_DEFAULT);")
    
    return "\n".join(content)

if __name__ == "__main__":
    print("=== 生成的代码分为两部分 ===\n")
    print("第一部分：Label 创建和事件绑定（插入到 ui_gamePage_screen_init 函数末尾）")
    print("=" * 80)
    print(generate_labels_and_events())
    print("\n" + "=" * 80)
    print("\n第二部分：背景颜色设置（插入到 Label 创建代码之后）")
    print("=" * 80)
    print(generate_bg_colors())
    print("\n" + "=" * 80)

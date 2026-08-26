#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
批量修改 ui_gamePage.c 中的事件绑定参数
将 "ButtonXY" 改为 "X_Y" 格式
"""

import re

file_path = r'd:\develop\linux\public\YQ_VScode\JieDuan_2\XiangQi\ui\screens\ui_gamePage.c'

# 读取文件内容
with open(file_path, 'r', encoding='utf-8') as f:
    content = f.read()

# 使用正则表达式替换
# 匹配模式：lv_obj_add_event_cb(ui_ButtonXX, ..., (void*)"ButtonXX")
# 替换为：lv_obj_add_event_cb(ui_ButtonXX, ..., (void*)"X_X")
pattern = r'lv_obj_add_event_cb\(ui_Button(\d)(\d),\s*ui_event_button_clicked,\s*LV_EVENT_CLICKED,\s*\(void\)\*"Button(\d)(\d)"\)'
replacement = r'lv_obj_add_event_cb(ui_Button\1\2, ui_event_button_clicked, LV_EVENT_CLICKED, (void*)"\1_\2")'

# 执行替换
new_content = re.sub(pattern, replacement, content)

# 写回文件
with open(file_path, 'w', encoding='utf-8') as f:
    f.write(new_content)

print("修改完成！")
print(f"文件：{file_path}")

# 统计修改数量
count = len(re.findall(pattern, content))
print(f"共修改 {count} 处事件绑定")

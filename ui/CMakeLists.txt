SET(
    SOURCES screens/ui_gamePage.c ui_changeWin.c
    ui.c
    ui_board_helpers.c
    images/qipan.c
    ui_temporary_image.c
    fonts/ui_font_CHINESEsize25.c
    fonts/ui_font_chinese.c
    fonts/chinese.c) 

add_library(ui ${SOURCES})

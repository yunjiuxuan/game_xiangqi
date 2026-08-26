// 中国象棋棋子移动规则
#ifndef CHESS_RULES_H
#define CHESS_RULES_H

#include "xiangqi_board.h"
#include <stdlib.h>  // for abs()

// 检查是否在九宫格内（将/帅/士的移动范围）
static int is_in_palace(int row, int col, int side)
{
    // side: 0=红方（上方，0-2 行），1=黑方（下方，7-9 行）
    if (side == 0) {
        // 红方九宫格：0-2 行，3-5 列
        return (row >= 0 && row <= 2 && col >= 3 && col <= 5);
    } else {
        // 黑方九宫格：7-9 行，3-5 列
        return (row >= 7 && row <= 9 && col >= 3 && col <= 5);
    }
}

// 检查相/象是否在己方半场
static int is_own_half(int row, int side)
{
    // side: 0=红方（上方，0-4 行），1=黑方（下方，5-9 行）
    if (side == 0) {
        return (row >= 0 && row <= 4);  // 红方相只能在 0-4 行
    } else {
        return (row >= 5 && row <= 9);  // 黑方象只能在 5-9 行
    }
}

// 检查"田"字中心是否有棋子（塞象眼）
static int is_elephant_eye_blocked(int from_row, int from_col, int to_row, int to_col)
{
    int eye_row = (from_row + to_row) / 2;
    int eye_col = (from_col + to_col) / 2;
    
    const char *eye_piece = get_piece_at(eye_row, eye_col);
    return (eye_piece[0] != '\0');  // 有棋子挡住
}

// 检查馬的移动路径是否被阻挡（蹩马腿）
static int is_horse_leg_blocked(int from_row, int from_col, int to_row, int to_col)
{
    int row_diff = to_row - from_row;
    int col_diff = to_col - from_col;
    
    // 检查是横着走还是竖着走
    if (abs(row_diff) == 2 && abs(col_diff) == 1) {
        // 竖着走，检查马腿位置
        int leg_row = from_row + (row_diff > 0 ? 1 : -1);
        const char *leg_piece = get_piece_at(leg_row, from_col);
        return (leg_piece[0] != '\0');  // 有棋子蹩马腿
    } else if (abs(row_diff) == 1 && abs(col_diff) == 2) {
        // 横着走，检查马腿位置
        int leg_col = from_col + (col_diff > 0 ? 1 : -1);
        const char *leg_piece = get_piece_at(from_row, leg_col);
        return (leg_piece[0] != '\0');  // 有棋子蹩马腿
    }
    
    return 0;  // 不是马走日
}

// 检查車的移动路径是否有阻挡
static int is_rook_path_clear(int from_row, int from_col, int to_row, int to_col)
{
    if (from_row == to_row) {
        // 横向移动
        int min_col = (from_col < to_col) ? from_col : to_col;
        int max_col = (from_col > to_col) ? from_col : to_col;
        
        for (int col = min_col + 1; col < max_col; col++) {
            const char *piece = get_piece_at(from_row, col);
            if (piece[0] != '\0') {
                return 0;  // 有阻挡
            }
        }
        return 1;  // 路径畅通
    } else if (from_col == to_col) {
        // 纵向移动
        int min_row = (from_row < to_row) ? from_row : to_row;
        int max_row = (from_row > to_row) ? from_row : to_row;
        
        for (int row = min_row + 1; row < max_row; row++) {
            const char *piece = get_piece_at(row, from_col);
            if (piece[0] != '\0') {
                return 0;  // 有阻挡
            }
        }
        return 1;  // 路径畅通
    }
    
    return 0;  // 不是直线移动
}

// 检查炮的移动（需要炮架）
static int is_cannon_move_valid(int from_row, int from_col, int to_row, int to_col)
{
    if (from_row != to_row && from_col != to_col) {
        return 0;  // 必须直线移动
    }
    
    int piece_count = 0;
    
    if (from_row == to_row) {
        // 横向移动
        int min_col = (from_col < to_col) ? from_col : to_col;
        int max_col = (from_col > to_col) ? from_col : to_col;
        
        for (int col = min_col + 1; col < max_col; col++) {
            const char *piece = get_piece_at(from_row, col);
            if (piece[0] != '\0') {
                piece_count++;
            }
        }
    } else {
        // 纵向移动
        int min_row = (from_row < to_row) ? from_row : to_row;
        int max_row = (from_row > to_row) ? from_row : to_row;
        
        for (int row = min_row + 1; row < max_row; row++) {
            const char *piece = get_piece_at(row, from_col);
            if (piece[0] != '\0') {
                piece_count++;
            }
        }
    }
    
    const char *target_piece = get_piece_at(to_row, to_col);
    
    if (target_piece[0] == '\0') {
        // 移动到空位：中间不能有棋子
        return (piece_count == 0);
    } else {
        // 吃子：中间必须有 1 个棋子（炮架）
        return (piece_count == 1);
    }
}

// 获取棋子可走位置
static int get_piece_moves(int from_row, int from_col, int moves[][2], int max_moves)
{
    const char *piece = get_piece_at(from_row, from_col);
    if (piece[0] == '\0') {
        return 0;
    }
    
    char piece_type[PIECE_NAME_LEN];
    get_piece_type(piece, piece_type);
    
    int piece_color = get_piece_color(piece);
    int count = 0;
    
    // 馬走日
    if (strcmp(piece_type, "馬") == 0 || strcmp(piece_type, "马") == 0) {
        int horse_moves[8][2] = {
            {from_row - 2, from_col - 1}, {from_row - 2, from_col + 1},
            {from_row - 1, from_col - 2}, {from_row - 1, from_col + 2},
            {from_row + 1, from_col - 2}, {from_row + 1, from_col + 2},
            {from_row + 2, from_col - 1}, {from_row + 2, from_col + 1}
        };
        
        for (int i = 0; i < 8 && count < max_moves; i++) {
            int to_row = horse_moves[i][0];
            int to_col = horse_moves[i][1];
            
            if (!is_valid_position(to_row, to_col)) continue;
            if (is_horse_leg_blocked(from_row, from_col, to_row, to_col)) continue;
            
            const char *target_piece = get_piece_at(to_row, to_col);
            if (target_piece[0] == '\0' || get_piece_color(target_piece) != piece_color) {
                moves[count][0] = to_row;
                moves[count][1] = to_col;
                count++;
            }
        }
    }
    // 車走直线
    else if (strcmp(piece_type, "車") == 0 || strcmp(piece_type, "车") == 0) {
        // 四个方向：上、下、左、右
        int directions[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
        
        for (int d = 0; d < 4 && count < max_moves; d++) {
            int dr = directions[d][0];
            int dc = directions[d][1];
            
            for (int step = 1; step < 9 && count < max_moves; step++) {
                int to_row = from_row + dr * step;
                int to_col = from_col + dc * step;
                
                if (!is_valid_position(to_row, to_col)) break;
                
                const char *target_piece = get_piece_at(to_row, to_col);
                if (target_piece[0] == '\0') {
                    // 空位，可以走
                    moves[count][0] = to_row;
                    moves[count][1] = to_col;
                    count++;
                } else {
                    // 有棋子
                    if (get_piece_color(target_piece) != piece_color) {
                        // 敌方棋子，可以吃
                        moves[count][0] = to_row;
                        moves[count][1] = to_col;
                        count++;
                    }
                    break;  // 遇到棋子停止
                }
            }
        }
    }
    // 相/象走田
    else if (strcmp(piece_type, "相") == 0 || strcmp(piece_type, "象") == 0) {
        int elephant_moves[4][2] = {
            {from_row - 2, from_col - 2}, {from_row - 2, from_col + 2},
            {from_row + 2, from_col - 2}, {from_row + 2, from_col + 2}
        };
        
        for (int i = 0; i < 4 && count < max_moves; i++) {
            int to_row = elephant_moves[i][0];
            int to_col = elephant_moves[i][1];
            
            if (!is_valid_position(to_row, to_col)) continue;
            if (!is_own_half(to_row, piece_color)) continue;  // 不能过河
            if (is_elephant_eye_blocked(from_row, from_col, to_row, to_col)) continue;
            
            const char *target_piece = get_piece_at(to_row, to_col);
            if (target_piece[0] == '\0' || get_piece_color(target_piece) != piece_color) {
                moves[count][0] = to_row;
                moves[count][1] = to_col;
                count++;
            }
        }
    }
    // 士/仕走斜线（九宫格内）
    else if (strcmp(piece_type, "士") == 0 || strcmp(piece_type, "仕") == 0) {
        int advisor_moves[4][2] = {
            {from_row - 1, from_col - 1}, {from_row - 1, from_col + 1},
            {from_row + 1, from_col - 1}, {from_row + 1, from_col + 1}
        };
        
        for (int i = 0; i < 4 && count < max_moves; i++) {
            int to_row = advisor_moves[i][0];
            int to_col = advisor_moves[i][1];
            
            if (!is_valid_position(to_row, to_col)) continue;
            if (!is_in_palace(to_row, to_col, piece_color)) continue;  // 必须在九宫格内
            
            const char *target_piece = get_piece_at(to_row, to_col);
            if (target_piece[0] == '\0' || get_piece_color(target_piece) != piece_color) {
                moves[count][0] = to_row;
                moves[count][1] = to_col;
                count++;
            }
        }
    }
    // 将/帅走直线（九宫格内）
    else if (strcmp(piece_type, "將") == 0 || strcmp(piece_type, "将") == 0 ||
             strcmp(piece_type, "帥") == 0 || strcmp(piece_type, "帅") == 0) {
        int king_moves[4][2] = {
            {from_row - 1, from_col}, {from_row + 1, from_col},
            {from_row, from_col - 1}, {from_row, from_col + 1}
        };
        
        for (int i = 0; i < 4 && count < max_moves; i++) {
            int to_row = king_moves[i][0];
            int to_col = king_moves[i][1];
            
            if (!is_valid_position(to_row, to_col)) continue;
            if (!is_in_palace(to_row, to_col, piece_color)) continue;  // 必须在九宫格内
            
            const char *target_piece = get_piece_at(to_row, to_col);
            if (target_piece[0] == '\0' || get_piece_color(target_piece) != piece_color) {
                moves[count][0] = to_row;
                moves[count][1] = to_col;
                count++;
            }
        }
    }
    // 炮走直线（吃子需要炮架）
    else if (strcmp(piece_type, "炮") == 0 || strcmp(piece_type, "砲") == 0) {
        int directions[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
        
        for (int d = 0; d < 4 && count < max_moves; d++) {
            int dr = directions[d][0];
            int dc = directions[d][1];
            
            for (int step = 1; step < 9 && count < max_moves; step++) {
                int to_row = from_row + dr * step;
                int to_col = from_col + dc * step;
                
                if (!is_valid_position(to_row, to_col)) break;
                
                if (is_cannon_move_valid(from_row, from_col, to_row, to_col)) {
                    const char *target_piece = get_piece_at(to_row, to_col);
                    if (target_piece[0] == '\0' || get_piece_color(target_piece) != piece_color) {
                        moves[count][0] = to_row;
                        moves[count][1] = to_col;
                        count++;
                    }
                }
            }
        }
    }
    // 兵/卒走一步
    else if (strcmp(piece_type, "兵") == 0 || strcmp(piece_type, "卒") == 0) {
        // 判断前进方向
        int forward = (piece_color == 0) ? 1 : -1;  // 红方向下（+），黑方往上（-）
        int crossed_river = (piece_color == 0) ? (from_row >= 5) : (from_row <= 4);  // 是否过河
        
        // 前进
        int to_row = from_row + forward;
        int to_col = from_col;
        if (is_valid_position(to_row, to_col)) {
            const char *target_piece = get_piece_at(to_row, to_col);
            if (target_piece[0] == '\0' || get_piece_color(target_piece) != piece_color) {
                moves[count][0] = to_row;
                moves[count][1] = to_col;
                count++;
            }
        }
        
        // 过河后可以横走
        if (crossed_river) {
            // 左
            to_row = from_row;
            to_col = from_col - 1;
            if (is_valid_position(to_row, to_col)) {
                const char *target_piece = get_piece_at(to_row, to_col);
                if (target_piece[0] == '\0' || get_piece_color(target_piece) != piece_color) {
                    moves[count][0] = to_row;
                    moves[count][1] = to_col;
                    count++;
                }
            }
            
            // 右
            to_row = from_row;
            to_col = from_col + 1;
            if (is_valid_position(to_row, to_col)) {
                const char *target_piece = get_piece_at(to_row, to_col);
                if (target_piece[0] == '\0' || get_piece_color(target_piece) != piece_color) {
                    moves[count][0] = to_row;
                    moves[count][1] = to_col;
                    count++;
                }
            }
        }
    }
    
    return count;
}

#endif // CHESS_RULES_H

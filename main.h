#ifndef MAIN_H
#define MAIN_H

#define ROWS 6
#define COLS 7

extern char board[ROWS][COLS];

typedef struct {
    int row;
    int col;
} Position;

int check_winner(int row, int col);
int drop_piece(int col, char piece);
void display_board();
void initialize_board();
Position give_advice(char piece);
int play_classic();
int play_with_computer();



#endif

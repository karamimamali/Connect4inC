#include <stdio.h>

#define ROWS 6
#define COLS 7

char board[ROWS][COLS];

int check_winner(int row, int col);
int drop_piece(int col, char piece);
void display_board();
void initialize_board();

int main() 
{
    initialize_board();
    int turn = 0;
    int row, col;

    while (1) {
        display_board();

        
        printf("Player %d's turn. Enter column (0-6): ", turn % 2 + 1);
        scanf("%d", &col);

        if (col < 0 || col >= COLS) {
            printf("Invalid column. Please enter a number between 0 and 6.\n");
            continue;
        }

        row = drop_piece(col, (turn % 2 == 0) ? 'R' : 'Y');

        if (row == -1) {
            printf("Column is full. Choose another column.\n");
            continue;
        }

        if (check_winner(row, col)) {
            display_board();
            printf("Player %d wins!\n", turn % 2 + 1);
            break;
        }

        turn++;
    }

    return 0;
}



void initialize_board()
{
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            board[i][j] = '-';
        }
    }
}

void display_board() 
{
    printf("\n");
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            printf("%c ", board[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

int drop_piece(int col, char piece) 
{
    for (int i = ROWS - 1; i >= 0; i--) {
        if (board[i][col] == '-') {
            board[i][col] = piece;
            return i;
        }
    }
    return -1; 
}

int check_winner(int row, int col) 
{
    char piece = board[row][col];

    // Check horizontally
    // Check only from one side.
    int count = 1;
    for (int i = col - 1; i >= 0 && board[row][i] == piece; i--) count++;
    for (int i = col + 1; i < COLS && board[row][i] == piece; i++) count++;
    if (count >= 4) return 1;

    // Check vertically
    // Check only from one side.
    count = 1;
    for (int i = row - 1; i >= 0 && board[i][col] == piece; i--) count++;
    for (int i = row + 1; i < ROWS && board[i][col] == piece; i++) count++;
    if (count >= 4) return 1;

    // Check diagonally
    count = 1;
    for (int i = 1; i < 4; i++) 
    {
        if (row - i >= 0 && col - i >= 0 && board[row - i][col - i] == piece) count++;
        else break;
    }
    for (int i = 1; i < 4; i++) 
    {
        if (row + i < ROWS && col + i < COLS && board[row + i][col + i] == piece) count++;
        else break;
    }
    if (count >= 4) return 1;

    count = 1;
    for (int i = 1; i < 4; i++) 
    {
        if (row - i >= 0 && col + i < COLS && board[row - i][col + i] == piece) count++;
        else break;
    }
    for (int i = 1; i < 4; i++) 
    {
        if (row + i < ROWS && col - i >= 0 && board[row + i][col - i] == piece) count++;
        else break;
    }
    if (count >= 4) return 1;

    return 0;
}

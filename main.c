#include <stdio.h>
#include <ctype.h>

#define ROWS 6
#define COLS 7

char board[ROWS][COLS];

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


int main()
{
    int mode;
    int turns;
    printf("---------------------------------\n"
    "PLease choose a mode to play:\n\n"
    "\t1 for Play with computer\n"
    "\t2 for Play classic\n"
    "---------------------------------\n\n"
    "Enter mode: ");
    scanf("%d", &mode);
    if (mode == 1)
    {
        turns = play_with_computer();
    }
    else
    {
        turns = play_classic();
    }   

    printf("---Played %d turns in total!---", turns);

    return 0;
}

int play_with_computer()
{
    initialize_board();
    int turn = 0;
    char *player = "Yellow";
    int row, col;
    char input;

    printf("\n\n\t\t\t\t!Play against Computer!\n\n");

    while (1) 
    {
        display_board();

        printf("\nYour turn. Enter column (1-7). Press 'i' for advice: ");
        scanf(" %c", &input);

        if (input == 'i')
        {
            Position advice = give_advice(player[0]);
            printf("\t---Advice: Place your piece at row %d, column %d---\n", advice.row+1, advice.col+1);
            continue;
        }
        else if (!isdigit(input))
        {
            printf("Invalid input. Please enter a number between 1 and 7.\n");
            continue;
        }
        
        col = input - '0'; 
        
        if (col < 1 || col > COLS) 
        {
            printf("Invalid column. Please enter a number between 1 and 7.\n");
            continue;
        }

        col--; 

        row = drop_piece(col, player[0]);

        if (row == -1) 
        {
            printf("Column is full. Choose another column.\n");
            continue; 
        }

        Position computer_move = give_advice('R');
        drop_piece(computer_move.col, 'R');

        if (check_winner(row, col)) 
        {
            display_board();
            printf("You won!\n");
            break;
        }

        if (check_winner(computer_move.row, computer_move.col)) 
        {
            display_board();
            printf("Computer wins!\n");
            break;
        }

        turn++;
    }

    return turn;
}


int play_classic() 
{
    initialize_board();
    int turn = 0;
    char *player;
    int row, col;
    char input;

    printf("\n\n\t\t\t\t!Welcome to Classic Mode!\n\n");

    while (1) 
    {
        display_board();

        player = (turn % 2 == 0) ? "Red": "Yellow";

        printf("\nPlayer %s's turn. Enter column (1-7). Press 'i' for advice: ", player);
        scanf(" %c", &input);

        if (input == 'i')
        {
            Position advice = give_advice(player[0]);
            printf("\t---Advice: Place your piece at row %d, column %d---\n", advice.row+1, advice.col+1);
            continue;
        }
        else if (!isdigit(input))
        {
            printf("Invalid input. Please enter a number between 1 and 7.\n");
            continue;
        }
        
        col = input - '0'; 
        
        if (col < 1 || col > COLS) 
        {
            printf("Invalid column. Please enter a number between 1 and 7.\n");
            continue;
        }

        col--; 

        row = drop_piece(col, player[0]);

        if (row == -1) 
        {
            printf("Column is full. Choose another column.\n");
            continue; 
        }

        if (check_winner(row, col)) 
        {
            display_board();
            printf("Player %s wins!\n", player);
            break;
        }

        turn++;
    }

    return turn;
}


void initialize_board()
{
    for (int i = 0; i < ROWS; i++) 
    {
        for (int j = 0; j < COLS; j++) 
        {
            board[i][j] = '-';
        }
    }
}

void display_board() 
{
    printf("\n");
    printf("  ");
    for (int t = 0; t < COLS; t++)
    {
        printf("%d ", t+1);
    }
    printf("\n");
    for (int i = 0; i < ROWS; i++) 
    {
        printf("%d ", i+1);
        for (int j = 0; j < COLS; j++) 
        {
            printf("%c ", board[i][j]);
        }
        printf("%d ", i+1);
        printf("\n");
    }
    printf("  ");
    for (int t = 0; t < COLS; t++)
    {
        printf("%d ", t+1);
    }
    
    printf("\n");
}


int drop_piece(int col, char piece) 
{
    for (int i = ROWS - 1; i >= 0; i--) 
    {
        if (board[i][col] == '-') 
        {
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
    int count = 1;
    for (int i = col - 1; i >= 0 && board[row][i] == piece; i--) count++;
    for (int i = col + 1; i < COLS && board[row][i] == piece; i++) count++;
    if (count >= 4) return 1;


    // Check vertically
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

Position give_advice(char piece)
{
    int max_count = -1;
    Position advice_position;
    advice_position.row = -1;
    advice_position.col = -1;

    for (int col = 0; col < COLS; col++) 
    {
        // Check if the column is full
        if (board[0][col] != '-') 
        {
            continue;
        }

        // Find the lowest available row in the current column
        int row = ROWS - 1;
        while (row >= 0 && board[row][col] != '-') 
        {
            row--;
        }

        // Check horizontally
        int horizontal_count = 1;
        for (int i = col - 1; i >= 0 && board[row][i] == piece; i--) 
        {
            horizontal_count++;
        }
        for (int i = col + 1; i < COLS && board[row][i] == piece; i++) 
        {
            horizontal_count++; 
        }

        // Check vertically
        int vertical_count = 1;
        for (int i = row - 1; i >= 0 && board[i][col] == piece; i--) 
        {
            vertical_count++;
        }
        for (int i = row + 1; i < ROWS && board[i][col] == piece; i++) 
        {
            vertical_count++; 
        }

        // Check diagonally (right diagonal)
        int rdiagonal_count = 1;
        for (int i = 1; i < 4; i++) 
        {
            if (row - i >= 0 && col - i >= 0 && board[row - i][col - i] == piece) 
            {
                rdiagonal_count++;
            }
            else 
            {
                break;
            }
        }
        for (int i = 1; i < 4; i++) 
        {
            if (row + i < ROWS && col + i < COLS && board[row + i][col + i] == piece) 
            {
                rdiagonal_count++;
            }
            else 
            {
                break;
            }
        }

        // Check diagonally (left diagonal)
        int ldiagonal_count = 1;
        for (int i = 1; i < 4; i++) 
        {
            if (row - i >= 0 && col + i < COLS && board[row - i][col + i] == piece) 
            {
                ldiagonal_count++;
            }
            else 
            {
                break;
            }
        }
        for (int i = 1; i < 4; i++) 
        {
            if (row + i < ROWS && col - i >= 0 && board[row + i][col - i] == piece) 
            {
                ldiagonal_count++;
            }
            else 
            {
                break;
            }
        }

        // Find the maximum count among horizontal, vertical, and diagonal counts
        int counts[4] = {horizontal_count, vertical_count, rdiagonal_count, ldiagonal_count};
        for (int i = 0; i < 4; i++) 
        {
            if (counts[i] > max_count) 
            {
                max_count = counts[i];
                advice_position.row = row;
                advice_position.col = col;
            }
        }
    }

    return advice_position;
}

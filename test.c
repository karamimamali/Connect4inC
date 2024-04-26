#include <stdio.h>
#include <assert.h>
#include "main.h"


void test_drop_piece() 
{
    initialize_board();
    int row = drop_piece(0, 'R');
    assert(row == ROWS - 1); 
}

void test_check_winner()
{
    initialize_board();
    drop_piece(0, 'R');
    drop_piece(1, 'R');
    drop_piece(2, 'R');
    int winner = check_winner(ROWS - 1, 2); 
    assert(winner == 0); 
    drop_piece(3, 'R');
    winner = check_winner(ROWS - 1, 2); 
    assert(winner == 1);
}

void test_give_advice() {
    initialize_board();
    Position advice = give_advice('R');
    assert(advice.row >= 0 && advice.row < ROWS); 
    assert(advice.col >= 0 && advice.col < COLS); 
}

int main() {
    test_drop_piece();
    test_check_winner();
    test_give_advice();

    printf("All tests passed!\n");
    return 0;
}

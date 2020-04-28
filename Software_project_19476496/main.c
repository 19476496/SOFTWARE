//
// Created by Lili on 26/03/2020.
//

#include <stdio.h>
#include "input_output.h"
int main() {

    // declaration of the players and the board
    player players[PLAYERS_NUM];
    square board[BOARD_SIZE][BOARD_SIZE];

    initialize_players(players);        //function call to init_players asks users basic info and initialises variables
    initialize_board(board);            //init_board is a function used to set each tile of the board to empty red or green
    print_board(board);
    printf("Thanks for playing");
    return 0;
}

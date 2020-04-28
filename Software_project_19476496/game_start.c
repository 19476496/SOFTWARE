//
// Created by redbr on 28/04/2020.
//

#include "game_start.h"

#include <stdio.h>
#include <stdbool.h>

void game_Start(square board[BOARD_SIZE][BOARD_SIZE], player players[]) {
    bool won; //won just tracks wheter to keep playing or print win conditions
    int confirmation = 0;//confirmation
    printf("Basic rules:\n");
    printf("Each player can only pick a piece equal to their chosen colour\n");
    printf("Each player can move in a turn n times where n is the size of the stack\n");
    printf("The max stack size is 5\n");
    printf("If a player uses a stack of 5 on a piece 2 things happen:\n");
    printf("If the bottom piece is equal to the players colour then the player puts that piece in their reserve\n");
    printf("If the piece is not the same colour as the player then it is removed from game\n");
    printf("A reserve piece can be placed anywhere on the board\n");
    printf("IMPORTANT: CONTROLS!\n\n");

    printf("A cursor is given by a + sign beside the current piece. To move one space press one w a s d  and hit enter and then repeat\n");
    printf("w is up S is down a is left d is right \n");
    printf("Pieces are then selected using f, the user will be then prompted to once again move the cursor to the position they would like to place it\n");
    printf("The user can also use r to place a reserve piece on the board in the current position and y to take part of a stack and move it\n");
    printf("If you under stand the rules and controls press 1:");
    scanf("%d", &confirmation); //gives user time to read information before continuing

    int count = 0;
    while (won != true) {//since there are only 2 players we use modulo 2 as we loop around count
        if (players[count % 2].total_pieces == 0 && players[count % 2].reserves == 0) {
            won == true;
            printf("PLayer %d has won!! Well done %s ", ((count + 1) % 2) + 1, players[(count + 1) % 2].player_name);
            printf("The game took %d moves in total\n", count);
            printf("They destroyed %d of the opponents pieces and was left with %d of their own\n",
                   players[(count + 1) % 2].destroyed, players[(count + 1) % 2].total_pieces);
            printf("They were also left with %d reserves by the end of the game\n", players[(count + 1) % 2].reserves);
            return;
        }
        select_piece(board, players,(count%2));//allows user to select move reserve and split stacks
        count++;
    }
}
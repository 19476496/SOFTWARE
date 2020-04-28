//
// Created by redbr on 28/04/2020.
//

#include "print_board.h"
#include <stdio.h>


void print_loc_board(square board[BOARD_SIZE][BOARD_SIZE], player playerx, int move)
{
    int i;
    int j;
    for (i = 0; i < BOARD_SIZE; i++) {
        for (j = 0; j < BOARD_SIZE; j++) {
            if (i == playerx.destination_piece[0] && playerx.destination_piece[1] == j) {
                if (board[i][j].type == VALID) {
                    if (board[i][j].stack == NULL)
                        printf("|+  ");
                    else {
                        if (board[i][j].stack->p_color == GREEN)
                            printf("|%dG+", board[i][j].num_pieces);
                        else
                            printf("|%dR+", board[i][j].num_pieces);
                    }
                }
            } else if (board[i][j].type == VALID) {
                if (board[i][j].stack == NULL)
                    printf("|   ");
                else {
                    if (board[i][j].stack->p_color == GREEN)
                        printf("|%dG ", board[i][j].num_pieces);
                    else
                        printf("|%dR ", board[i][j].num_pieces);
                }
            } else
                printf("| - ");
        }
        if (i == 0 && j == 8) {
            printf("|Player: %s", playerx.player_name);
            continue;
        }
        if (i == 1 && j == 8) {
            if (playerx.player_color == 0) {

                printf("|Player colour: Red\n");
                continue;
            } else {
                printf("|Player colour: Green\n");
                continue;
            }
        }

        if (i == 2 && j == 8) {
            printf("|Player reserves: %d\n", playerx.reserves);
            continue;
        }

        printf("|\n");
    }
return;
}

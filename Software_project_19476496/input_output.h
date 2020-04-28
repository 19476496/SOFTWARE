
#ifndef FOCUS_INPUT_OUTPUT_H
#define FOCUS_INPUT_OUTPUT_H

#endif //FOCUS_INPUT_OUTPUT_H

#include "change_stack.h"

//Function to print the board
void select_piece(square board[8][8],  player players[],int cur);
void move_piece(square board[8][8],  player players[],int cur);
void split_function(square board[8][8],player players[], int cur, int n);
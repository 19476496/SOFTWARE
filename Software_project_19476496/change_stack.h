//
// Created by redbr on 28/04/2020.
//

#ifndef INC_19476496_SOFTWAREPROJECT_2_CHANGE_STACK_H
#define INC_19476496_SOFTWAREPROJECT_2_CHANGE_STACK_H
#include "print_board.h"
void place_reserve(square* s,player players[],int cur);
void push(square board[8][8], player players[],int cur);
void lim_5(square *s, player players[],int cur);
void split_stack(square board[8][8],player players[], int cur, int n);
#endif //INC_19476496_SOFTWAREPROJECT_2_CHANGE_STACK_H

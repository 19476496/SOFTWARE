//
// Created by redbr on 28/04/2020.
//
#include <stdio.h>
#include "change_stack.h"
void push(square board[8][8], player players[],int cur)
{
    if(board[players[cur].destination_piece[0]][players[cur].destination_piece[1]].num_pieces == players[cur].player_color)
    {   //if the location of where we put our piece had one of our pieces facing up the total no.goes down
        players[cur].total_pieces--;
    }
    if(board[players[cur].destination_piece[0]][players[cur].destination_piece[1]].num_pieces == players[(cur+1)%2].player_color)
    {   //Alternatively if we placed the stack onto a stack with an enemies piece facing up they lose 1 visible piece
        players[(cur+1)%2].total_pieces--;
    }

    //updating number of pieces in the stack that we are placing the moved stack onto
    board[players[cur].destination_piece[0]][players[cur].destination_piece[1]].num_pieces += board[players[cur].current_piece[0]][players[cur].current_piece[1]].num_pieces;
    piece *top = board[players[cur].current_piece[0]][players[cur].current_piece[1]].stack; //setting top = to the piece bein moved
    board[players[cur].current_piece[0]][players[cur].current_piece[1]].stack = NULL;       //setting where the piece came from to empty
    piece *curr = top;
    while (curr->next != NULL) //moving through the original stack till we reach its end
    {
        curr = curr->next;
    }

    //when it reaches null we change it so it instead points to the top of the desintation piece on the board
    curr->next = board[players[cur].destination_piece[0]][players[cur].destination_piece[1]].stack;
    board[players[cur].destination_piece[0]][players[cur].destination_piece[1]].stack = top;

    //we make sure to limit the pieces to 5 in case there were more than 5
    //lim_5(&board[players[cur].destination_piece[0]][players[cur].destination_piece[1]],players,cur);

    return;
}
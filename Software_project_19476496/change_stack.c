//
// Created by redbr on 28/04/2020.
//
#include <stdio.h>
#include <stdlib.h>
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
void place_reserve(square *s, player players[],int cur)
{
    if(s->stack == NULL)              // if the location in which we place the reserve is an empty piece
    {                                 // The total amount of our visible pieces not in stacks or reserves goes up
        players[cur].total_pieces++;
    }

    else if(s->stack->p_color == players[cur].player_color)
    {                                   //If we place the stack on one of our own colours we reduce the total visible by 1
        players[cur].total_pieces--;
    }
    else  if(s->stack->p_color == players[(cur+1)%2].player_color) // (cur+1)%2 produces the opposite players value if cur = player 0
        //(cur+1)%2 = player 1
    {
        players[(cur+1)%2].total_pieces--;
    }// If we place a reserve on an enemies piece we reduce their total visible by 1


    players[cur].reserves--; // the user has used one of their reserves
    if (s->stack == NULL)                               //if we are placing on an empty piece
    {
        s->stack = (piece *)malloc(sizeof(piece));      //creating the piece node and allocating it to the location
        s->stack->p_color = players[cur].player_color;  //settings its colour
        s->stack->next = NULL;                          //ensuring it points to nothing
        s->num_pieces = 1;                              //Declaring num_pieces to 1
        return;
    }
    else
    {
        piece *curr;                                //however if we place on an existing stack or piece
        curr = (piece *)malloc(sizeof(piece));      //we define and create a node like normal
        curr->p_color =players[cur].player_color;
        curr->next = s->stack;                      //however we let the pointer point to the top of the stack located in the board position
        s->stack = curr;                            //The position is now updated so that the top is the reserve piece
        s->num_pieces++;                            //Total pieces in that stack increases

        if(s->num_pieces > 5)             //If the stack we placed the reserve on to was size 5 we must free the last piece
        {
            lim_5(s,players,cur);         //function lim_5 limits the stack to only 5 pieces gathering info about excess pieces
            return;

        }
    }
}

void lim_5(square *s, player players[],int cur){

    piece* curr=NULL;
    curr = s->stack; //curr is given the position of the stack passed in in the arguments
    int count = 1;
    piece *last = NULL;  // last is used if we reach 5 pieces we then set last->next to point to null to finish the stack
    while (curr != NULL) // moving until we reach the end of athestack
    {
        if (count < 5)
        {

            curr = curr->next; //moving until we reach the 5th member of the list
            count++;
        }
        else
        {
            last = curr; //if we do have more than 5 in the list then we keep track of where the 5th element is
        }
        if (last != NULL)
        {
            curr = curr->next;
            piece *toremove; //to remove will be used to free up memory
            while (curr != NULL)
            {
                toremove = curr;
                if (players[cur].player_color == curr->p_color)
                {
                    players[cur].reserves++; // if the piece on the bottom of the stack is our colour then we gain a reserve
                }
                if (players[(cur+1)%2].player_color == curr->p_color)
                {
                    players[cur].destroyed++;// if the piece was an enemies it is destroyed and they cant get it back
                }
                curr = curr->next;
                free(toremove); //to remove is freed
                s->num_pieces = 5;
            }
            last->next = NULL;
        }
    }
    return;
}
//
// Created by Lili on 26/03/2020.
//

//
// Created by Lili on 24/03/2020.
//

#include <stdio.h>
#include <stdlib.h>
#include "game_init.h"
//function to get info about players
void initialize_players(player players[PLAYERS_NUM]){
    char colour; //colour holds the users colour value they wish to use
    printf("Please enter info about each player\nPLayer1:\n");
    printf("Name:");
    fgets(players[0].player_name,50,stdin);
    printf("Colour of Player1(r for red g for green): ");
    scanf(" %c",&colour);

    if(colour == 'r')//providing the user presses r this if will execute
    {
        printf("PLayer 1 will be red and player 2 will be green.\n");
        players[0].player_color = RED;
        players[1].player_color = GREEN;
    }
    else //should they not press r this will execute
    {
        printf("PLayer 1 will be green and player 2 will be red.\n");
        players[0].player_color = GREEN;
        players[1].player_color = RED;
    }
    players[0].reserves = 0; //reserves are special pieces used to
    players[1].reserves = 0;
    players[0].destroyed = 0;
    players[1].destroyed = 0;
    players[0].total_pieces = 18;
    players[1].total_pieces = 18;
    printf("Player 2:\nName:");
    fflush(stdin);
    fgets(players[1].player_name,50,stdin);

}

//Set Invalid Squares (where it is not possible to place stacks)
void set_invalid(square * s){
    s->type = INVALID;
    s->stack = NULL;
    s->num_pieces = 0;
}

//Set Empty Squares (with no pieces/stacks)
void set_empty(square * s){
    s->type = VALID;
    s->stack = NULL;
    s->num_pieces = 0;
}

//Set squares  with a GREEN piece
void set_green(square * s){
    s->type = VALID;
    s->stack = (piece *) malloc (sizeof(piece));
    s->stack->p_color = GREEN;
    s->stack->next = NULL;
    s->num_pieces = 1;
}

//Set squares with a RED piece
void set_red(square * s){
    s->type = VALID;
    s->stack = (piece *) malloc (sizeof(piece));
    s->stack->p_color = RED;
    s->stack->next = NULL;
    s->num_pieces = 1;
}

//initializes the board
void initialize_board(square board [BOARD_SIZE][BOARD_SIZE]){

    for(int i=0; i< BOARD_SIZE; i++){
        for(int j=0; j< BOARD_SIZE; j++){
            //invalid squares
            if((i==0 && (j==0 || j==1 || j==6 || j==7)) ||
               (i==1 && (j==0 || j==7)) ||
               (i==6 && (j==0 || j==7)) ||
               (i==7 && (j==0 || j==1 || j==6 || j==7)))
                set_invalid(&board[i][j]);

            else{
                //squares with no pieces
                if(i==0 || i ==7 || j==0 || j == 7)
                    set_empty(&board[i][j]);
                else{
                    //squares with red pieces
                    if((i%2 == 1 && (j < 3 || j> 4)) ||
                       (i%2 == 0 && (j == 3 || j==4)))
                        set_red(&board[i][j]);
                        //green squares
                    else set_green(&board[i][j]);
                }
            }
        }


    }


}


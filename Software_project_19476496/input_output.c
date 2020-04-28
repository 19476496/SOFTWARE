//select piece function is the main function which does the heavy work
//on user location and moving stacks and conveying this info to the user
#include "print_board.h"
#include <stdio.h>
void select_piece(square board[8][8], player players[],int cur)
{
    players[cur].destination_piece[0] = 4; //initializing values to display on screen the original position
    players[cur].destination_piece[1] = 4; //destination piece holds the location of the piece in which we want to move onto another
    int split_value=0; //split value is used in splitting up a stack greater than 2 and moving pieces equal to split stack
    char choice = 0; //choice is used to keep the loop running
    char movement = 0; // movement takes in info in the form of movemental keys w a s d and changes the location of destination piece
    printf("\n\nSelect piece\n");
    while (choice != 'f')
    {
        if(players[cur].destination_piece[0] > 7 || players[cur].destination_piece[0] < 0 || players[cur].destination_piece[1] > 7|| players[cur].destination_piece[1] < 0 || board[players[cur].destination_piece[0]][players[cur].destination_piece[1]].type == INVALID)
        {
            printf("||You have moved off the board or onto an invalid piece these are not usable the cursor will be reset||\n");
            players[cur].destination_piece[0] = 4;
            players[cur].destination_piece[1] = 4; //making sure users dont go off screen or into an invalid area
        }

        print_loc_board(board,players[cur],-1); // print loc board prints out the board with a + sign beside the current cursor location
        printf("Enter move w a s d (f to choose the stack at current cursor): \n");
        printf("To split a stack and move the top n elements of the stack press y\n"); //explaining what each does
        printf("To place a reserve piece press r\n");
        scanf(" %c", &movement);
        switch (movement)
        {
            case ('w'): // if we press w then the cursor moves up so the position of dest_piece decreases the same happens for s a and d
                players[cur].destination_piece[0]--;
                break;

            case ('s'):
                players[cur].destination_piece[0]++;
                break;

            case ('a'):
                players[cur].destination_piece[1]--;
                break;

            case ('d'):
                players[cur].destination_piece[1]++;
                break;
            case ('f'):

                if (board[players[cur].destination_piece[0]][players[cur].destination_piece[1]].stack == NULL)
                {
                    printf("||||You cannot choose an empty square||||\n");
                    break;//error checking
                }
                if (board[players[cur].destination_piece[0]][players[cur].destination_piece[1]].stack->p_color != players[cur].player_color)
                {
                    printf("||You must pick a stack with the same colour as your player||\n");
                    break;//error checking
                }

                //move_piece(board, players,cur);//move pieces allows the user to move the piece they chose onto another board square
                return;



            default:
                printf("Character entered was not an arrow key");
                break; // if any other key is pressed this occurs

        }
    }
}
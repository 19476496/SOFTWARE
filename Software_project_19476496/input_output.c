
#include <stdio.h>
#include <stdlib.h>
#include "input_output.h"

//select piece function is the main function which does the heavy work
//on user location and moving stacks and conveying this info to the user
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

            case ('y')://if the user enters y they wish to split a stack and move n pieces from that stack
                if (board[players[cur].destination_piece[0]][players[cur].destination_piece[1]].stack == NULL)
                {
                    printf("||||You cannot choose an empty square||||\n"); //making sure users dont try to pick empty or invalid squares
                    break;
                }
                if (board[players[cur].destination_piece[0]][players[cur].destination_piece[1]].stack->p_color != players[cur].player_color)
                {
                    printf("||You must pick a stack with the same colour as your player||\n"); //more error checking
                    break;
                }
                if(board[players[cur].destination_piece[0]][players[cur].destination_piece[1]].num_pieces == 1)
                {
                    printf("You cannot split a stack of size one just use the normal command f to choose this stack\n");
                    break; // technically we could but its unneccesary
                }
                printf("Here is the stack with end being the bottom of the stack\n");//we give the user information about whats contained in the stack
                print_stack(&board[players[cur].destination_piece[0]][players[cur].destination_piece[1]]); //prints a linked list format about the stack
                printf("\nEnter the n elements you want from the top of the stack down\n");
                scanf(" %d",&split_value);

                while(split_value >= board[players[cur].destination_piece[0]][players[cur].destination_piece[1]].num_pieces) {
                    printf("You entered a value larger than or equal to the size of the current stack please try again\n");
                    printf("Enter stack split size:"); //more error checking this time in case they go over the number of pieces in the stack
                    scanf(" %d",&split_value);
                    break;
                }
                print_split_stack(&board[players[cur].destination_piece[0]][players[cur].destination_piece[1]],split_value); //prints the stack that they choose with n elements
                split_function(board,players,cur,split_value); //split function call will proceed to allow them to place that stack they created on another stack
                return;
            case ('r'):
                if (players[cur].reserves == 0)
                {
                    printf("|||||There are no reserves|||||||\n");
                }
                else
                {
                    place_reserve(&board[players[cur].destination_piece[0]][players[cur].destination_piece[1]],players,cur);
                    return; //calling reserve function to place reserves
                }

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

                move_piece(board, players,cur);//move pieces allows the user to move the piece they chose onto another board square
                return;



            default:
                printf("Character entered was not an arrow key");
                break; // if any other key is pressed this occurs

        }
    }
}

void move_piece(square board[8][8], player players[],int cur)
{   //move piece allows the user to place the piece they acquired in the selection function onto another stack

    players[cur].current_piece[0] = players[cur].destination_piece[0];//current piece holds the current value about to be placed on another stack
    players[cur].current_piece[1] = players[cur].destination_piece[1];

    char choice = 's';      // choice is used to keep the loop running
    char movement = 'g';    // movement is used to keep track of which direction the user has tried to move in

    //move_count is important as we can only move the amount of times as there are pieces in the stack we chose
    int move_count = board[players[cur].current_piece[0]][players[cur].current_piece[1]].num_pieces;
    printf("\nChoose place to put piece\n");
    while (choice != 'z')
    {
        if(players[cur].destination_piece[0] > 7 || players[cur].destination_piece[0] < 0 || players[cur].destination_piece[1] > 7|| players[cur].destination_piece[1] < 0 || board[players[cur].destination_piece[0]][players[cur].destination_piece[1]].type == INVALID)
        {
            printf("||||You have moved off the board or onto an invalid piece these are not usable the cursor will be reset||||\n");
            players[cur].destination_piece[0] = players[cur].current_piece[0];
            players[cur].destination_piece[1] = players[cur].current_piece[1];
            int move_count = board[players[cur].current_piece[0]][players[cur].current_piece[1]].num_pieces;

        }

        print_loc_board(board,players[cur],move_count);

        printf("Enter move w a s d (f chooses current piece)\n");
        printf("If your moves run out you will choose the piece that you landed on\n");
        scanf(" %c", &movement);
        //if by the time the user has already used up their moves and has tried to move again they will automatically choose what they are located on

        if(move_count == 0)
        {
            movement = 'f';
        }
        switch (movement)
        {
            case ('w')://movement again but with movecount being tracked
                players[cur].destination_piece[0]--;
                move_count--;
                break;
            case ('s'):
                players[cur].destination_piece[0]++;
                move_count--;
                break;
            case ('a'):
                players[cur].destination_piece[1]--;
                move_count--;
                break;
            case ('d'):
                players[cur].destination_piece[1]++;
                move_count--;
                break;
            case ('f'):
                if ((players[cur].destination_piece[0] == players[cur].current_piece[0]) &&  (players[cur].destination_piece[1] == players[cur].current_piece[1]))
                {
                    printf("You cant place the piece on the same place it came from\n");   //making sure the user doesnt double back like in the rules
                    printf("Location and movecounts are being reset try another position\n");
                    move_count = board[players[cur].current_piece[0]][players[cur].current_piece[1]].num_pieces;
                    break;
                }


                push(board, players,cur);//push function is called which puts the stack gotten in selection on to the stack in the current function
                return;
            default:
                printf("Character entered was not an arrow key\n");
                break;
        }
    }
}




void split_function(square board[8][8],player players[], int cur, int n) {
//split works much live move piece but for part of a stack

    players[cur].current_piece[0] = players[cur].destination_piece[0];
    players[cur].current_piece[1] = players[cur].destination_piece[1];
    char choice = 's';
    char movement = 'g';
    int move_count = n;
    printf("\nChoose place to put split stack\n");
    while (choice != 'z') {
        if (players[cur].destination_piece[0] > 7 || players[cur].destination_piece[0] < 0 ||
            players[cur].destination_piece[1] > 7 || players[cur].destination_piece[1] < 0 ||
            board[players[cur].destination_piece[0]][players[cur].destination_piece[1]].type == INVALID) {
            printf("You have moved off the board or onto an invalid piece these are not usable the cursor will be reset\n");
            players[cur].destination_piece[0] = players[cur].current_piece[0];
            players[cur].destination_piece[1] = players[cur].current_piece[1];//error checking
            move_count = n;
        }

        print_loc_board(board,players[cur], move_count);//print out board with current cursor location

        printf("Enter move w a s d (f chooses current piece)\n");
        printf("If your moves run out you will choose the piece that you landed on");
        scanf(" %c", &movement);
        if (move_count == 0) {//making sure the user doesnt try to move more than the designated move given to a piece when split
            movement = 'f';
        }
        switch (movement) {
            case ('w'):
                players[cur].destination_piece[0]--;
                move_count--;
                break;
            case ('s'):
                players[cur].destination_piece[0]++;
                move_count--;
                break;
            case ('a'):
                players[cur].destination_piece[1]--;
                move_count--;
                break;
            case ('d'):
                players[cur].destination_piece[1]++;
                move_count--;
                break;
            case ('f'):
                if ((players[cur].destination_piece[0] == players[cur].current_piece[0]) &&
                    (players[cur].destination_piece[1] == players[cur].current_piece[1])) {
                    printf("You cant place the piece on the same place it came from\n");
                    printf("Location and movecounts are being reset try another position\n");
                    move_count = n; //error checking
                    break;
                }
                split_stack(board,players,cur,n); //function call to split_stack adds part of the stak onto another board square
                return;
            default:
                printf("Character entered was not an arrow key\n");
                break;
        }
    }
}
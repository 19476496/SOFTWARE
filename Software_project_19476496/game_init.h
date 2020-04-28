#ifndef FOCUS_GAME_INIT_H
#define FOCUS_GAME_INIT_H

#endif //FOCUS_GAME_INIT_H

#define BOARD_SIZE 8
#define PLAYERS_NUM 4

//colors that a piece can have
typedef enum color {
    RED,
    GREEN
}color;


//There are 2 main square types
//VALID means that a piece can be placed there with no problems
//Invalid means it is not a usable position on the board
typedef enum square_type {
    VALID,
    INVALID
}square_type;

//Player contains many members which help us to keep track of the users info
typedef struct player{
    color player_color;      //color holds the players color data, wheter they chose red or green
    char player_name[50];    //Name holds player name
    int current_piece[4];    //Current piece is an array which holds the location of a piece that the user wishes to place somewhere
    int destination_piece[4];//destination piece is the stack which is placed onto the current piece
    int reserves;            //reserves can be placed anywhere on the board at any time
    int destroyed;           // tally to keep track of destroyed pieces for winning info at end
    int total_pieces;        //total pieces keeps track of the total amount of pieces on the top of the board visible and usable by the player
}player;

// A piece
typedef struct piece {
    //the color associated with a piece
    color p_color;

    //linked list member which is a pointer to a struct
    //it is a self referential member which points to the next piece in the stack
    struct piece * next;

}piece;

// A Square of the board
typedef struct square {
    // type of the square (VALID/INVALID)
    square_type type;

    //The top piece on the stack
    piece * stack;

    //number of pieces on the square
    int num_pieces;

}square;
//Function to create the players
void initialize_players(player players[PLAYERS_NUM]);

//Function to create the board
void initialize_board(square board[BOARD_SIZE][BOARD_SIZE]);

void set_empty(square * s);



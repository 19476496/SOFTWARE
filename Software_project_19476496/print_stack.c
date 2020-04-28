//
// Created by redbr on 28/04/2020.
//
#include <stdio.h>
#include "print_stack.h"


void print_stack(square *s)
{
    piece *curr = s->stack;          // piece curr points to the stack located in the board position passed into the function
    while (curr != NULL)             // curr moves through the stack till it finds the end (NULL)
    {
        if (curr->p_color == 0)      //reds enum value is 0 so we compare if the value located in this pieces in the stack is 0
        {
            printf("RED->");
        }
        else                         //If it doesnt equate to 0 it must be green
        {
            printf("GREEN->");
        }
        curr = curr->next;           //curr is updated to the next position in the stack
    }
    printf("END");
}

void print_split_stack(square *s,int n)
{
    //split stack is the same as print split stack however we bring in n as an argument to read up to a certain point
    piece *curr = s->stack;
    int counter=0;
    while (counter <n) {            //we want curr points to read up to the nth value in the stack
        if (curr->p_color == 0) {  // same process as print_stack
            printf("RED->");
        } else {
            printf("GREEN->");
        }
        curr = curr->next;
        counter++;
    }

    printf("END");

}
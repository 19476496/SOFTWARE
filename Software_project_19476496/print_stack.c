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

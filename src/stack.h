#pragma once
#include <stdio.h>
#include <stdbool.h>
#include "vec_token.h"
#include "token_type.h"

#define STACKMAX 1024

struct stack  {                         // This structure called "stack" has two data fields. 
    token *input_arr[STACKMAX];         // This char array holds the values inside the stack.
    int top;                            // The variable "top" gives the index of the uppermost 
};                                      // element in the stack.
typedef struct stack stack;  
                                         
void traverse(stack *);              // In left, there are declarations of functions that has
void clearStack(stack *);            // been defined in "stack.c" are declared.
void createEmptyStack(stack *);      // Furthermore, stack struct is defined here.
bool isEmptyStack(stack *);
void pushStack(stack *, token *);
token* popStack(stack *);
token* peekStack(stack *);


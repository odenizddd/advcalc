#pragma once
#include <stdio.h>
#include <stdbool.h>

#define LONG_SIZE 4294967295            // In left, there are constants indicating the decimal ASCII values of 
#define INTMIN 48                       // '0', '9', 'A', 'Z', 'a', 'z' to check whether a character 
#define INTMAX 57                       // will be considered as an integer, or letter. Moreover, the maximum integer
#define LOWERLETTERMIN 97               // value is defined in order to use in rotation.
#define LOWERLETTERMAX 122              // Similarly, the size of stack is defined to make it static.
#define UPPERLETTERMIN 65
#define UPPERLETTERMAX 90
#define STACKMAX 1024

typedef enum {
    TOKEN_TYPE_NUMBER,                  // Grouping integral constants: Six type of tokens have determined.
    TOKEN_TYPE_OPERATOR,                // The reason behind that is to check whether the value read 
    TOKEN_TYPE_L_PARANTHESIS,           // from the char array is "expected". If unexpected, it will be an error.
    TOKEN_TYPE_R_PARANTHESIS,           
    TOKEN_TYPE_FUNCTIONS,               
    TOKEN_TYPE_LETTER
} TokenType;

struct stack  {                         // This structure called "stack" has two data fields. 
    char *input_arr[STACKMAX];          // This char array holds the values inside the stack.
    int top;                            // The variable "top" gives the index of the uppermost 
};                                      // element in the stack.

typedef struct stack ourStack;          // In left, there are declarations of functions that has  
void traverse(ourStack *);              // been defined in "stack.c" are declared.
void clearStack(ourStack *);            // Furthermore, stack struct is defined here.
void createEmptyStack(ourStack *);
void EmptyStack(ourStack *);
bool isEmptyStack(ourStack *);
void pushStack(ourStack *, char *);
char* popStack(ourStack *);
char* peekStack(ourStack *);


#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "stack.h"

int STACKCOUNT = 0;                         // A global variable which counts the top element if necessary.

void createEmptyStack(ourStack *p) {        // This function initializes an empty stack with the top index -1, 
  p->top = -1;                              // which indicates that there is no element inside it.
}
void EmptyStack(ourStack *p){               // This function does the same operations as above;
    p->top=-1;                              // however, it has not been used anywhere.
};

bool isEmptyStack(ourStack *p){             // This function return boolean values after evaluating if the stack is empty.
    if(p->top==-1)                          // If there are at least one element inside the stack, "top" variable will be
        return true;                        // strictly greater than one, which will return false; otherwise, it will 
    else                                    // return true.
        return false;
};

void pushStack(ourStack *p, char *newEl){   // This function enables one to add new elements into the stack.
    p->top++;                               // The top index is increased by one, and the pointer of the element
    p->input_arr[p->top] = newEl;           // to the stack. Also, the global variable "STACKCOUNT" increases by 
    STACKCOUNT++;                           // one as "top" increases by one.
};

char* popStack(ourStack *p){                    // This function enables one to pop a single element.
    p->top--;                                   // At first, the number of elements are decreased by 
    char *pointer = p->input_arr[p->top+1];     // one and the uppermost pointer is returned. Similarly,
    return pointer;                             // the global variable "STACKCOUNT" decreases by 1 as "top"
    STACKCOUNT--;                               // decreases.
};

char* peekStack(ourStack *p){                       // This function returns the top element without removing it.
    char *pointer = p->input_arr[p->top];           // At first, it reaches the adress of the top element, then it
    return pointer;                                 // returns the pointer.
}

void traverse(ourStack *p){                  // This function traverses and prints the values in the stack without removing them.
    if(isEmptyStack(p)) {                    // If the stack is not empty, all pointers (since the elements are pointers) are 
        printf("Your Stack is empty. ");     // printed. This method is just used for testing, there is no other uses in 
    }                                        // anywhere.
    else{
        int i;
        printf("Stack Elements are : ");
        for(i=0; i <= p->top; i++){
            printf("%c\n", *(p->input_arr[i]));
        }
    }
}

void clearStack(ourStack *p){           // This function clears the stack with popping elements.
    while (isEmptyStack(p) == false) {  // The operation is done by popping all elements until
        popStack(p);                    // there is no element remaining.
    }    
}

#include <stdio.h>

#define LONG_SIZE 4294967295            // In left, there are constants indicating the decimal ASCII values of 
#define INTMIN 48                       // '0', '9', 'A', 'Z', 'a', 'z' to check whether a character 
#define INTMAX 57                       // will be considered as an integer, or letter. Moreover, the maximum integer
#define LOWERLETTERMIN 97               // value is defined in order to use in rotation.
#define LOWERLETTERMAX 122              // Similarly, the size of stack is defined to make it static.
#define UPPERLETTERMIN 65
#define UPPERLETTERMAX 90


typedef enum {
    TOKEN_TYPE_NUMBER,                  // Grouping integral constants: Six type of tokens have determined.
    TOKEN_TYPE_OPERATOR,                // The reason behind that is to check whether the value read 
    TOKEN_TYPE_L_PARANTHESIS,           // from the char array is "expected". If unexpected, it will be an error.
    TOKEN_TYPE_R_PARANTHESIS,           
    TOKEN_TYPE_FUNCTIONS,               
    TOKEN_TYPE_LETTER
} TokenType;

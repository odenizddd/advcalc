#include <stdlib.h>
#include <string.h>

#include "token_type.h"

/**
 * @brief Returns a string representation of the token type.
 * Useful for console debugging.
 * 
 * @param type 
 * @return char* 
 */
char* token_type_string(token_type type) {
    char* type_string = NULL;
    if(type == PLUS) {
        type_string = malloc(5);
        strcpy(type_string, "PLUS");
    }else if(type == STAR) {
        type_string = malloc(5);
        strcpy(type_string, "STAR");
    }else if(type == MINUS) {
        type_string = malloc(6);
        strcpy(type_string, "MINUS");
    }else if(type == AND) {
        type_string = malloc(4);
        strcpy(type_string, "AND");
    }else if(type == OR) {
        type_string = malloc(3);
        strcpy(type_string, "OR");
    }else if(type == LEFT_PAREN) {
        type_string = malloc(11);
        strcpy(type_string, "LEFT_PAREN");
    }else if(type == RIGHT_PAREN) {
        type_string = malloc(12);
        strcpy(type_string, "RIGHT_PAREN");
    }else if(type == COMMA) {
        type_string = malloc(6);
        strcpy(type_string, "COMMA");
    }else if(type == ASSIGN) {
        type_string = malloc(7);
        strcpy(type_string, "ASSIGN");
    }else if(type == LEFT_SHIFT) {
        type_string = malloc(11);
        strcpy(type_string, "LEFT_SHIFT");
    }else if(type == RIGHT_SHIFT) {
        type_string = malloc(12);
        strcpy(type_string, "RIGHT_SHIFT");
    }else if(type == LEFT_ROT) {
        type_string = malloc(9);
        strcpy(type_string, "LEFT_ROT");
    }else if(type == RIGHT_ROT) {
        type_string = malloc(10);
        strcpy(type_string, "RIGHT_ROT");
    }else if(type == XOR) {
        type_string = malloc(4);
        strcpy(type_string, "XOR");
    }else if(type == NOT) {
        type_string = malloc(4);
        strcpy(type_string, "NOT");
    }else if(type == VARIABLE) {
        type_string = malloc(9);
        strcpy(type_string, "VARIABLE");
    }else if(type == LITERAL) {
        type_string = malloc(8);
        strcpy(type_string, "LITERAL");
    }else {

    }
    return type_string;
}
#ifndef TOKEN_TYPE_H
#define TOKEN_TYPE_H

/**
 * @brief enumeration for token types
 * 
 */
enum token_type {
    PLUS,
    STAR,
    MINUS,
    AND,
    OR,
    LEFT_PAREN,
    RIGHT_PAREN,
    COMMA,
    ASSIGN,
    LEFT_SHIFT,
    RIGHT_SHIFT,
    LEFT_ROT,
    RIGHT_ROT,
    XOR,
    NOT,
    VARIABLE,
    LITERAL
};

typedef enum token_type token_type;

char* token_type_string(token_type type);

#endif
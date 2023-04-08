#include "tokenizer.h"

/**
 * @brief Consumes a series of characters and spits out vector of tokens.
 * 
 * @param source 
 * @return vec_token* 
 */

vec_token* tokenize(char* source) {
    int source_length = strlen(source);
    vec_token* tokens = create_vec_token_ptr(4);
    //scan loop
    for(int i = 0; i < source_length;) {
        char c = source[i];
        if(c == '%') {
            break;
        }else if(is_letter(c)) {
            int start = i;
            int end = start;
            while(is_letter(source[end])) {
                end++;
            }
            if(is_digit(source[end])) {
                error = 1;
            }
            char* string_token = slice(source, start, end);
            token_type type = VARIABLE;
            if(strcmp("xor", string_token) == 0) {
                type = XOR;
            }else if(strcmp("not", string_token) == 0) {
                type = NOT;
            }else if(strcmp("ls", string_token) == 0) {
                type = LEFT_SHIFT;
            }else if(strcmp("rs", string_token) == 0) {
                type = RIGHT_SHIFT;
            }else if(strcmp("lr", string_token) == 0) {
                type = LEFT_ROT;
            }else if(strcmp("rr", string_token) == 0) {
                type = RIGHT_ROT;
            }else {

            }
            push_vec_token(tokens, create_token_ptr(type, string_token));
            i = end;
        }else if(is_digit(c)) {
            int start = i;
            int end = start;
            while(is_digit(source[end])) {
                end++;
            }
            if(is_letter(source[end])) {
                error = 1;
            }
            push_vec_token(tokens, create_token_ptr(LITERAL, slice(source, start, end)));
            i = end;
        }else if(c == '+') {
            push_vec_token(tokens, create_token_ptr(PLUS, "+"));
            i++;
        }else if(c == '*') {
            push_vec_token(tokens, create_token_ptr(STAR, "*"));
            i++;
        }else if(c == '-') {
            push_vec_token(tokens, create_token_ptr(MINUS, "-"));
            i++;
        }else if(c == '&') {
            push_vec_token(tokens, create_token_ptr(AND, "&"));
            i++;
        }else if(c == '|') {
            push_vec_token(tokens, create_token_ptr(OR, "|"));
            i++;
        }else if(c == '(') {
            push_vec_token(tokens, create_token_ptr(LEFT_PAREN, "("));
            i++;
        }else if(c == ')') {
            push_vec_token(tokens, create_token_ptr(RIGHT_PAREN, ")"));
            i++;
        }else if(c == ',') {
            push_vec_token(tokens, create_token_ptr(COMMA, ","));
            i++;
        }else if(c == '=') {
            push_vec_token(tokens, create_token_ptr(ASSIGN, "="));
            i++;
        }else {
            i++;
        }
    }
    //scan loop end
    if(error) {
        return NULL;
    } else {
        return tokens;
    }
}
#ifndef VEC_TOKEN_H
#define VEC_TOKEN_H

#include "token_type.h"

/**
 * @brief Structure representing a single token.
 * 
 */
struct token {
    token_type type;
    char* text;
};

typedef struct token token;

/** 
 * A vector of tokens. Yes this, indeed is a resizable object.
 * After you create an instance you can keep pushing without any consideration for capacity.
 * It will automatically resize. Although, unfortunately it doesn't support deletion.
 * Which you don't need for this project anyways.
*/
struct vec_token {
    token* data;
    int count;
    int max_count;
};

typedef struct vec_token vec_token;

/*
    These functions support create, push, print and slice operations for a vector of tokens.
*/

token create_token(token_type type, char text[]);
token* create_token_ptr(token_type type, char text[]);
void print_token(token* t);
vec_token create_vec_token(int max_count);
vec_token* create_vec_token_ptr(int max_count);
vec_token* slice_vec_token(vec_token* tokens, int start, int end);
void push_vec_token(vec_token* dynamic_array, token* new_token);
void print_vec_token(vec_token* dynamic_array);

#endif
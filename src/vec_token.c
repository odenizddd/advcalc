#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "vec_token.h"

token create_token(token_type type, char text[]) {
    token* ret = malloc(sizeof(token));
    ret->type = type;
    ret->text = malloc(sizeof(strlen(text)));
    memcpy(ret->text, text, strlen(text));
    return *ret;
}

token* create_token_ptr(token_type type, char text[]) {
    token* ret = malloc(sizeof(token));
    ret->type = type;
    ret->text = malloc(sizeof(strlen(text)));
    memcpy(ret->text, text, strlen(text));
    return ret;
}

void print_token(token* t) {
    printf("type: %s text: %s", token_type_string(t->type), t->text);
}

vec_token create_vec_token(int max_count) {
    vec_token* ret = malloc(sizeof(vec_token));
    ret->data = malloc(sizeof(token) * max_count);
    ret->count = 0;
    ret->max_count = max_count;
    return *ret;
}

vec_token* create_vec_token_ptr(int max_count) {
    vec_token* ret = malloc(sizeof(vec_token));
    ret->data = malloc(sizeof(token) * max_count);
    ret->count = 0;
    ret->max_count = max_count;
    return ret;
}

vec_token* slice_vec_token(vec_token* tokens, int start, int end) {
    vec_token* ret = create_vec_token_ptr(end - start);
    ret->count = end - start;
    ret->max_count = ret->count;
    for(int i = start; i < end; i++) {
        *(ret->data + i - start) = create_token((tokens->data + i)->type, (tokens->data + i)->text);
    }
    return ret;
}

void push_vec_token(vec_token* dynamic_array, token* new_token) {
    if(dynamic_array->count >= dynamic_array->max_count) {
        dynamic_array->data =  realloc(dynamic_array->data, sizeof(token) * dynamic_array->max_count + 1);
        dynamic_array->max_count++;
    }
    *(dynamic_array->data + dynamic_array->count) = *new_token;
    dynamic_array->count++;
}

void print_vec_token(vec_token* dynamic_array) {
    for(int i = 0; i < dynamic_array->count; i++) {
        print_token(dynamic_array->data + i);
        printf("\n");
    }
}
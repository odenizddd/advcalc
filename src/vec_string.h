#ifndef VEC_STRING_H
#define VEC_STRING_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct vec_string {
    char** data;
    int count;
    int max_count;
};

typedef struct vec_string vec_string;

/*
    String vector methods
*/

vec_string create_vec_string(int max_count);
vec_string* create_vec_string_ptr(int max_count);
void push_vec_string(vec_string* dynamic_array, char* new_string);
void print_vec_string(vec_string* dynamic_array);
char* get_string_at(vec_string* dynamic_array, int index);
void set_string_at(vec_string* dynamic_array, int index, char* value);

#endif
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "vec_string.h"

vec_string create_vec_string(int max_count) {
    vec_string* ret = malloc(sizeof(vec_string));
    ret->data = (char**)malloc(sizeof(char*) * max_count);
    ret->count = 0;
    ret->max_count = max_count;
    return *ret;
}

vec_string* create_vec_string_ptr(int max_count) {
    vec_string* ret = malloc(sizeof(vec_string));
    ret->data = (char**)malloc(sizeof(char*) * max_count);
    ret->count = 0;
    ret->max_count = max_count;
    return ret;
}

void push_vec_string(vec_string* dynamic_array, char* new_string) {
    if(dynamic_array->count >= dynamic_array->max_count) {
        dynamic_array->data =  realloc(dynamic_array->data, sizeof(char*) * dynamic_array->max_count + 1);
        dynamic_array->max_count++;
    }
    *(dynamic_array->data + dynamic_array->count) = new_string;
    dynamic_array->count++;
}

void print_vec_string(vec_string* dynamic_array) {
    for(int i = 0; i < dynamic_array->count; i++) {
        printf("%s ", *(dynamic_array->data + i));
    }
}

char* get_string_at(vec_string* dynamic_array, int index) {
    return *(dynamic_array->data + index);
}

void set_string_at(vec_string* dynamic_array, int index, char* value) {
    *(dynamic_array->data + index) = value;
}
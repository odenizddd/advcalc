#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "vec_int32.h"

vec_int32 create_vec_int32(int max_count) {
    vec_int32* ret = malloc(sizeof(vec_int32));
    ret->data = malloc(sizeof(long) * max_count);
    ret->count = 0;
    ret->max_count = max_count;
    return *ret;
}

void push_vec_int32(vec_int32* dynamic_array, long new_int) {
    if(dynamic_array->count >= dynamic_array->max_count) {
        dynamic_array->data =  realloc(dynamic_array->data, sizeof(long) * dynamic_array->max_count + 1);
        dynamic_array->max_count++;
    }
    *(dynamic_array->data + dynamic_array->count) = new_int;
    dynamic_array->count++;
}

void print_vec_int32(vec_int32* dynamic_array) {
    for(int i = 0; i < dynamic_array->count; i++) {
        printf("%ld ", *(dynamic_array->data + i));
    }
}

long get_int32_at(vec_int32* dynamic_array, int index) {
    return *(dynamic_array->data + index);
}

void set_int32_at(vec_int32* dynamic_array, int index, long value) {
    *(dynamic_array->data + index) = value;
}

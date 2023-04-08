#ifndef VEC_INT32_H
#define VEC_INT32_H

/*
    A vector of 32-bit signed integers.
*/

struct vec_int32 {
    long* data;
    int count;
    int max_count;
};

typedef struct vec_int32 vec_int32;

vec_int32 create_vec_int32(int max_count);
void push_vec_int32(vec_int32* dynamic_array, long new_int);
void print_vec_int32(vec_int32* dynamic_array);
long get_int32_at(vec_int32* dynamic_array, int index);
void set_int32_at(vec_int32* dynamic_array, int index, long value);

#endif
#ifndef MAP_H
#define MAP_H

#include "vec_int32.h"
#include "vec_string.h"

/*
    Custom map structure. Map string keys to integer values. Used as a lookup table for variables.
*/

struct map {
    vec_string keys;
    vec_int32 values;
    int count;
};

typedef struct map map;

map create_map();
map* create_map_ptr();
void push_map(map* m, char* key, long val);
void print_map(map* m);
long get_value(map* m, char* key);
void set_value(map* m, char* key, long value);

#endif
#include <string.h>
#include "vec_int32.h"
#include "vec_string.h"
#include "map.h"

map create_map() {
    map* m = (map*) malloc(sizeof(map));
    m->keys = create_vec_string(4);
    m->values = create_vec_int32(4);
    m->count = 0;
    return *m; 
}

map* create_map_ptr() {
    map* m = (map*) malloc(sizeof(map));
    m->keys = create_vec_string(4);
    m->values = create_vec_int32(4);
    m->count = 0;
    return m; 
}

void push_map(map* m, char* key, long val) {
    push_vec_string(&(m->keys), key);
    push_vec_int32(&(m->values), val);
    m->count++;
}

void print_map(map* m) {
    for(int i = 0; i < m->count; i++) {
        printf("key: %s, value: %ld\n", get_string_at(&m->keys, i), get_int32_at(&m->values, i));
    }
}

long get_value(map* m, char* key) {
    for(int i = 0; i < m->count; i++) {
        if(strcmp(key, get_string_at(&m->keys, i)) == 0) {
            return get_int32_at(&m->values, i);
        }
    }
    push_map(m, key, 0);
    return 0;
}

void set_value(map* m, char* key, long value) {
    for(int i = 0; i < m->count; i++) {
        if(strcmp(key, get_string_at(&m->keys, i)) == 0) {
            set_int32_at(&m->values, i, value);
            return;
        }
    }
    push_map(m, key, value);
}
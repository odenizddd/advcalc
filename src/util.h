#ifndef UTIL_H
#define UTIL_H

#include <string.h>
#include <stdlib.h>

#include "vec_token.h"

int is_letter(char c);
int is_digit(char c);
long pow10(int power);
long string_to_int(char* str);
char* slice(char* source, int start, int end);
int find_next_paren(vec_token* tokens, int start);
int priority(token_type type);
int lpboi(vec_token* tokens);
int get_real_index(vec_token* tokens, token_type type);
int get_top_level_comma_index(vec_token* tokens);
long xor(long a, long b);
long ls(long a, long b);
long rs(long a, long b);
long lr(long a, long b);
long rr(long a, long b);
int is_assignable(vec_token* tokens);
int top_level_assignment_index(vec_token* tokens);

#endif
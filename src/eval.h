#ifndef EVAL_H
#define EVAL_H

#include "vec_token.h"
#include "util.h"
#include "map.h"
#include "tokenizer.h"

extern int error;
extern map* m;

long eval(vec_token* tokens);
int run_line(char* source);

#endif
#ifndef TOKENIZER_H
#define TOKENIZER_H

#include <stdio.h>
#include "vec_token.h"
#include "util.h"

extern int error;

vec_token* tokenize(char* source);

#endif
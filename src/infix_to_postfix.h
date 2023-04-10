#include <stdio.h>
#include "vec_token.h"
#include "util.h"
#include "tokenizer.h"
#include "stack.h"

void priority_stack(token* , stack* , vec_token* );
vec_token* infix_to_postfix(vec_token* , vec_token*, stack*);

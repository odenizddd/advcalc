#include <stdio.h>
#include <string.h>
#include "map.h"
#include "eval.h"
#include "stack.h"
#include "token_type.h"
#include "vec_token.h"

int error = 0;
map* m;

int main() {

    /* m = create_map_ptr();

    while(1) {
        char* line = (char*)malloc(256);
        size_t len = 256;
        printf(">");
        getline(&line, &len, stdin);
        if(strlen(line) <= 1) {
            continue;
        }
        int status = run_line(line);
        if(status == -1) {
            printf("Error!\n");
        }else if(status == 1) {

        }else {
            printf("\n");
        }
        error = 0;
    } */
    
    token* token1 = create_token_ptr(PLUS, "+");
    token* token2 = create_token_ptr(STAR, "*");
    token* token3 = create_token_ptr(LITERAL, "123");

    vec_token* tokens = create_vec_token_ptr(4);
    push_vec_token(tokens, token1);
    push_vec_token(tokens, token2);
    push_vec_token(tokens, token3);
    print_vec_token(tokens);
    set_token_at(tokens, 1, token1);
    print_vec_token(tokens);

    return 0;
}
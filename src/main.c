#include <stdio.h>
#include <string.h>
#include "map.h"
#include "eval.h"

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
    
    char* source = "3+4*5";
    vec_token* tokens = tokenize(source);
    print_vec_token(tokens);

    return 0;
}
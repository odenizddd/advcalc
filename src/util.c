#include <string.h>
#include <stdio.h>
#include "util.h"

/**
 * @brief Test if c is a letter.
 * 
 * @param c test char
 * @return 1 if c is a letter otherwise 0 
 */
int is_letter(char c) {
    if((c >= 65 && c <= 90) || (c >= 97 && c <= 122)) {
        return 1;
    } else {
        return 0;
    }
}

/**
 * @brief Test if c is a digit.
 * 
 * @param c test char
 * @return 1 if c  is a digit otherwise 0 
 */
int is_digit(char c) {
    if(c >= 48 && c <= 57) {
        return 1;
    } else {
        return 0;
    }
}

/**
 * @brief Returns ten raised to a power.
 * 
 * @param power
 * @return int 
 */
long pow10(int power) {
    long ret = 1;
    for(int i = 0; i < power; i++) {
        ret *= 10;
    } 
    return ret;
}

/**
 * @brief Converts string to integer.
 * 
 * @param str String to be converted.
 * @return An integer represented by str. 
 */
long string_to_int(char* str) {
    long ret = 0;
    for(int i = 0; i < strlen(str); i++) {
        ret += (long)(*(str+i) - 48) * pow10((strlen(str) - i - 1));
    }
    return ret;
}

/**
 * @brief Returns a string sliced from the source.
 * 
 * @param source Original string
 * @param start Index of the first char in the sliced string
 * @param end Index that is one more than the last char in the sliced string
 * @return char* sliced string
 */
char* slice(char* source, int start, int end) {
    char* ret = malloc(end - start + 1);
    for(int i = 0; i < end - start; i++) {
        *(ret + i) = *(source + start + i);
    }
    *(ret + end - start) = 0;
    return ret;
}

/**
 * @brief Searches for a closing parenthesis that matches an opening
 * parenthesis in a vector of tokens. Set index to one more than
 * an opening parenthesis because this functions assumes an opening
 * parenthesis has already been found.
 * 
 * @param tokens 
 * @param start Index of token where search starts.
 * @return int Index of matching closing parenthesis.
 */
int find_next_paren(vec_token* tokens, int start) {
    int token_count = tokens->count;
    int balance = 1; 
    for(int i = start; i < token_count; i++) {
        token_type type = (tokens->data+i)->type;
        if(type == LEFT_PAREN) {
            balance++;
        }
        if(type == RIGHT_PAREN) {
            balance--;
        }
        if(balance == 0) {
            return i;
        }
    }
    return -1;
}

/**
 * @brief This functions returns the priority level of a binary operator.
 * If there ever be a neen to alter operator precedence just return larger numbers
 * for higher priority operators than for lower ones.
 * 
 * @param type This the token type of the operator.
 * @return Priority level. Large numbers represents higher priority.
 */
int priority(token_type type) {
    if(type == PLUS) {
        return 2;
    }else if(type == MINUS) {
        return 2;
    }else if(type == STAR) {
        return 3;
    }else if(type == AND) {
        return 1;
    }else if(type == OR) {
        return 1;
    }else {
        return 0;
    }
}

/**
 * @brief This functions goes through a vector of binary operator tokens
 * And returns the index of the lowest priority token. Beware that this
 * functions expects only binary tokens in the input vector.
 * 
 * @param tokens 
 * @return int 
 */
int lpboi(vec_token* tokens) {
    //king coiner returned
    //this might name stands for 
    //lowest priority binary operator index
    //return the index of the lpbo
    //in the tokens array of tokens->data
    int count = tokens->count;
    int index = 0;
    int min_level = 10;
    for(int i = count - 1; i >= 0; i--) {
        int level = priority((tokens->data + i)->type);
        if(level < min_level) {
            index = i;
            min_level = level;
        }
    }
    return index;
}

/**
 * @brief This function returns the index of the rightmost token that has a certain type
 * that is not nested within parenthesis. Intended to find the index of the lowest priority
 * binary operator token among all tokens.
 * 
 * @param tokens 
 * @param type 
 * @return int 
 */
int get_real_index(vec_token* tokens, token_type type) {
    int balance = 0;
    for(int i = tokens->count - 1; i >= 0; i--) {
        if((tokens->data+i)->type == LEFT_PAREN) {
            balance--;
        }
        if((tokens->data+i)->type == RIGHT_PAREN) {
            balance++;
        }
        if(balance == 0 && (tokens->data+i)->type == type) {
            return i;
        }
    }
    return -1;
}

/**
 * @brief Returns the index of the first comma that is nested by parenthesis
 * at a depth level of one.
 * 
 * @param tokens 
 * @return int 
 */
int get_top_level_comma_index(vec_token* tokens) {
    int balance = 0;
    for(int i = 0; i < tokens->count; i++){
        if((tokens->data + i)->type == LEFT_PAREN) {
            balance++;
        }
        if((tokens->data + i)->type == RIGHT_PAREN) {
            balance--;
        }
        if(balance == 1 && (tokens->data + i)->type == COMMA) {
            return i;
        }
    } 
    return -1;
}

/**
 * @brief wrapper for xor;
 * 
 * @param a 
 * @param b 
 * @return int 
 */
long xor(long a, long b) {
    return a^b;
}

/**
 * @brief wrapper for left shift
 * 
 * @param a 
 * @param b 
 * @return int 
 */
long ls(long a, long b) {
    return a << b;
}

/**
 * @brief wrapper for right shift
 * 
 * @param a 
 * @param b 
 * @return int 
 */
long rs(long a, long b) {
    return a >> b;
}

/**
 * @brief wrapper for left rotation
 * 
 * @param a 
 * @param b 
 * @return int 
 */
long lr(long a, long b) {
    return (a << b)|(a >> (32 - b));
}

/**
 * @brief wrapper for right rotation
 * 
 * @param a 
 * @param b 
 * @return int 
 */
long rr(long a, long b) {
    return (a >> b)|(a << (32 - b));
}

/**
 * @brief returns 1 if an expression is assignable. Intended to test if
 * left hand side values of assignment operators are actually assignable.
 * 
 * @param tokens 
 * @return int 
 */
int is_assignable(vec_token* tokens) {
    int assignable_count = 0;
    for(int i = 0; i < tokens->count; ) {
        token_type type = (tokens->data+i)->type;
        if(type == VARIABLE) {
            assignable_count++;
            i++;
        }else if(type == LEFT_PAREN) {
            int next_paren_index = find_next_paren(tokens, i+1);
            if(next_paren_index == -1) {
                return -1;
            }else {
                assignable_count++;
                i = next_paren_index+1;
            }
        }else {
            return -1;
        }
    }
    if(assignable_count != 1) {
        return -1;
    }else {
        if(tokens->data->type == VARIABLE) {
            return 1;
        } else {
            return is_assignable(slice_vec_token(tokens, 1, tokens->count - 1));
        }
    }
}

/**
 * @brief returns the index of the first assignment operator that is not nested within any parenthesis
 * 
 * @param tokens 
 * @return int 
 */
int top_level_assignment_index(vec_token* tokens) {
    int balance = 0;
    for(int i = 0; i < tokens->count; i++) {
        token_type type = (tokens->data+i)->type;
        if(type == LEFT_PAREN) {
            balance++;
        }
        if(type == RIGHT_PAREN) {
            balance--;
        }
        if(balance == 0 && type == ASSIGN) {
            return i;
        }
    }
    return -1;
}
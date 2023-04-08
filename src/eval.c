#include "eval.h"

/**
 * @brief Evaluates an expression that is represented as a vector of tokens
 * and returns the result. Sets the error flag to 1 if the expresison is invalid.
 * Make sure to check that flag because this function will return won't crash even if
 * the expression is invalid, İt will return 0;
 * 
 * @param tokens 
 * @return int 
 */

long eval(vec_token* tokens) {
    if(tokens->count == 0) {
        error = 1;
        return 0;
    }
    vec_token bin_ops = create_vec_token(4);
    int top_level_expression_count = 0;
    int binary_operator_count = 0;
    //top level item count loop
    for(int i = 0; i < tokens->count; ) {
        if(!(
            binary_operator_count == top_level_expression_count
        ||  binary_operator_count == top_level_expression_count - 1
        )) {
            error = 1;
            return 0;
        }
        if((tokens->data+i)->type == LEFT_PAREN) {
            int next_paren_index = find_next_paren(tokens, i+1);
            if(next_paren_index == -1) {
                error = 1;
                return 0;
            }else {
                top_level_expression_count++;
            }
            i = next_paren_index + 1;
        }else if((tokens->data+i)->type == XOR) {
            int next_paren_index = find_next_paren(tokens, i+2);
            if(next_paren_index == -1) {
                error = 1;
                return 0;
            }else {
                top_level_expression_count++;
            }
            i = next_paren_index + 1;
        }else if((tokens->data+i)->type == NOT) {
            int next_paren_index = find_next_paren(tokens, i+2);
            if(next_paren_index == -1) {
                error = 1;
                return 0;
            }else {
                top_level_expression_count++;
            }
            i = next_paren_index + 1;
        }else if((tokens->data+i)->type == LEFT_SHIFT) {
            int next_paren_index = find_next_paren(tokens, i+2);
            if(next_paren_index == -1) {
                error = 1;
                return 0;
            }else {
                top_level_expression_count++;
            }
            i = next_paren_index + 1;
        }else if((tokens->data+i)->type == RIGHT_SHIFT) {
            int next_paren_index = find_next_paren(tokens, i+2);
            if(next_paren_index == -1) {
                error = 1;
                return 0;
            }else {
                top_level_expression_count++;
            }
            i = next_paren_index + 1;
        }else if((tokens->data+i)->type == LEFT_ROT) {
            int next_paren_index = find_next_paren(tokens, i+2);
            if(next_paren_index == -1) {
                error = 1;
                return 0;
            }else {
                top_level_expression_count++;
            }
            i = next_paren_index + 1;
        }else if((tokens->data+i)->type == RIGHT_ROT) {
            int next_paren_index = find_next_paren(tokens, i+2);
            if(next_paren_index == -1) {
                error = 1;
                return 0;
            }else {
                top_level_expression_count++;
            }
            i = next_paren_index + 1;
        }else if((tokens->data+i)->type == VARIABLE) {
            top_level_expression_count++;
            i++;
        }else if((tokens->data+i)->type == LITERAL) {
            top_level_expression_count++;
            i++;
        }else if((tokens->data+i)->type == PLUS) {
            binary_operator_count++;
            push_vec_token(&bin_ops, create_token_ptr(PLUS, "+"));
            i++;
        }else if((tokens->data+i)->type == MINUS) {
            binary_operator_count++;
            push_vec_token(&bin_ops, create_token_ptr(MINUS, "-"));
            i++;
        }else if((tokens->data+i)->type == STAR) {
            binary_operator_count++;
            push_vec_token(&bin_ops, create_token_ptr(STAR, "*"));
            i++;
        }else if((tokens->data+i)->type == AND) {
            binary_operator_count++;
            push_vec_token(&bin_ops, create_token_ptr(AND, "&"));
            i++;
        }else if((tokens->data+i)->type == OR) {
            binary_operator_count++;
            push_vec_token(&bin_ops, create_token_ptr(OR, "|"));
            i++;
        }else if((tokens->data+i)->type == COMMA) {
            error = 1;
            return 0;
            i++;
        }else if((tokens->data+i)->type == RIGHT_PAREN) {
            error = 1;
            return 0;
            i++;
        }else if((tokens->data+i)->type == ASSIGN) {
            error = 1;
            return 0;
            i++;
        }else {
            i++;
        }
    }
    //top level item count loop end
    if(error) {
        error = 1;
        return 0;
    } else {
        //recursive evaluation
        if(binary_operator_count != 0) {
            int index = lpboi(&bin_ops);
            token_type type = (bin_ops.data+index)->type;
            int real_index = get_real_index(tokens, type);
            int left_start = 0;
            int left_end = real_index;
            int right_start = real_index + 1;
            int right_end = tokens->count;
            vec_token* left = slice_vec_token(tokens, left_start, left_end);
            vec_token* right = slice_vec_token(tokens, right_start, right_end);
            
            if(type == PLUS) {
                return eval(left) + eval(right);
            }else if(type == MINUS) {
                return eval(left) - eval(right); 
            }else if(type == STAR) {
                return eval(left) * eval(right);
            }else if(type == AND) {
                return eval(left) & eval(right);
            }else if(type == OR) {
                return eval(left) | eval(right);
            }else {

            }
            
        } else {
            token_type type = tokens->data->type;
            if(type == LEFT_PAREN) {
                //slice
                vec_token* child = slice_vec_token(tokens, 1, tokens->count - 1);
                return eval(child);
            }else if(type == LEFT_ROT) {
                int top_level_comma_index = get_top_level_comma_index(tokens);
                vec_token* left = slice_vec_token(tokens, 2, top_level_comma_index);
                vec_token* right = slice_vec_token(tokens, top_level_comma_index + 1, tokens->count - 1);
                return lr(eval(left), eval(right));
            }else if(type == RIGHT_ROT) {
                int top_level_comma_index = get_top_level_comma_index(tokens);
                vec_token* left = slice_vec_token(tokens, 2, top_level_comma_index);
                vec_token* right = slice_vec_token(tokens, top_level_comma_index + 1, tokens->count - 1);
                return rr(eval(left), eval(right));
            }else if(type == LEFT_SHIFT) {
                int top_level_comma_index = get_top_level_comma_index(tokens);
                vec_token* left = slice_vec_token(tokens, 2, top_level_comma_index);
                vec_token* right = slice_vec_token(tokens, top_level_comma_index + 1, tokens->count - 1);
                return ls(eval(left), eval(right));
            }else if(type == RIGHT_SHIFT) {
                int top_level_comma_index = get_top_level_comma_index(tokens);
                vec_token* left = slice_vec_token(tokens, 2, top_level_comma_index);
                vec_token* right = slice_vec_token(tokens, top_level_comma_index + 1, tokens->count - 1);
                return rs(eval(left), eval(right));
            }else if(type == XOR) {
                int top_level_comma_index = get_top_level_comma_index(tokens);
                if(top_level_comma_index == -1) {
                    error = 1;
                    return 0;
                }
                vec_token* left = slice_vec_token(tokens, 2, top_level_comma_index);
                vec_token* right = slice_vec_token(tokens, top_level_comma_index + 1, tokens->count - 1);
                return xor(eval(left), eval(right));
            }else if(type == NOT) {
                vec_token* child = slice_vec_token(tokens, 2, tokens->count - 1);
                return ~eval(child);
            }else if(type == VARIABLE) {
                long val = get_value(m, tokens->data->text);
                if(val == -1) {
                    error = 1;
                    return 0;
                }else {
                    return val;
                }
            }else if(type == LITERAL) {
                return string_to_int(tokens->data->text);
            }else {

            }
        }//recursive evaluation end
    }
    return 0;
}

/**
 * @brief Consumes a line of characters and returns the result.
 * 
 * @param source 
 * @return int 
 */
int run_line(char* source) {
    vec_token* tokens = tokenize(source);
    if(tokens == NULL) {
        return -1;
    }
    if(error) {
        return -1;
    } else {
        int assign_index = top_level_assignment_index(tokens);
        if(assign_index == -1) {
            long val = eval(tokens);
            if(!error) {
                printf("%ld", val);
            }else {
                return -1;
            }
        } else {
            vec_token* left = slice_vec_token(tokens, 0, assign_index);
            vec_token* right = slice_vec_token(tokens, assign_index + 1, tokens->count);
            char* var_to_be_assigned = NULL;
            if(is_assignable(left) == -1) {
                error = 1;
                return -1;
            }else {
                for(int i = 0; i < left->count; i++) {
                    if((left->data+i)->type == VARIABLE) {
                        var_to_be_assigned = (left->data+i)->text;
                    }
                }
                long rvalue = eval(right);
                if(!error) {
                    set_value(m, var_to_be_assigned, rvalue);
                    return 1;
                }else {
                    return -1;
                }
            }
        }
        
    }
    return 0;
}
#include "infix_to_postfix.h"

void priority_stack(token* t, stack* operatorStack, vec_token* postfixExpr){
    /* @brief pushes the operator to the stack directly if it is empty. 
    *  If not empty, it pushes to the stack after popping operators with higher priority.
    *  Native functions (XOR, NOT etc.) are not prioritized yet.
    */
    if (isEmptyStack(operatorStack)){
        pushStack(operatorStack, t);
    }
    else{
        while(priority(t) <= priority(peekStack(operatorStack))){
            push_vec_token(postfixExpr, t);
            if (isEmptyStack(operatorStack)){
                break;
            }
        }
        pushStack(operatorStack, t);
    }
}

vec_token* infix_to_postfix(vec_token* infixExpr, vec_token* postfixExpr, stack* operatorStack){
    /* @brief Sends operators to the priority checking phase. 
    *  Native functions (XOR, NOT etc.) are directly pushed to the stack as their priority is the highest.
    *  Right parenthesis pops until left parenthesis.
    *  No balance check yet, comma pushes from stack directly.
    *  Variables and literals are directly sent to "postfixExpr".
    */
    for (int i = 0; i < sizeof(infixExpr); i++){
        token *t = get_token_at(infixExpr, i);
        switch (t->type)
        {
        case PLUS:
        case MINUS:
        case STAR:
        case AND:
        case OR:
        case ASSIGN:
            priority_stack(t, operatorStack, postfixExpr);
            break;
        case XOR:
        case LEFT_SHIFT:
        case RIGHT_SHIFT:
        case LEFT_ROT:
        case RIGHT_ROT:
        case NOT:
        case LEFT_PAREN:
            pushStack(operatorStack, t);
            break;
        case RIGHT_PAREN:
            while ((peekStack(operatorStack))->type != LEFT_PAREN){
                if (isEmptyStack(operatorStack) == false){
                    token* operator = popStack(operatorStack);
                    push_vec_token(postfixExpr, operator);
                }
            }
            break;
        case COMMA:
            while(priority(t) <= priority(peekStack(operatorStack))){
                push_vec_token(postfixExpr, t);
                if (isEmptyStack(operatorStack)){
                    break;
                }
            }
            break;
        case VARIABLE:
        case LITERAL:
            push_vec_token(postfixExpr, t);
        default:
            break;
        }
    }
    return postfixExpr;
}

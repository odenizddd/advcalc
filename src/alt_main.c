#include <stdio.h>
#include <stdlib.h>
#include "stack.h"
#include <string.h>
#include <ctype.h>

bool isFunction (char);				// In left, there are function declarations.							
bool isOperator(char );				// In left, there are function declarations.
bool isParenthesis(char);			// These functions checks type of the char
bool isDigit(char);					// whether it is an operator, digit, letter or
bool isLetter(char);				// parenthesis. Similarly, the function returns the
int precedence(char *);				// precedences of operators and functions is declared.

bool isFunction(char c){
	switch (c){
	case '^': // Bitwise XOR
	case '<': // Bitwise Left shift 
	case '>': // Bitwise Right shift
	case '~': // Bitwise NOT
	case '@': // Left rotation
	case '#': // Right rotation	
		return true;	
	default:
		return false;
	}
}
bool isOperator(char c){			// If the char is equal to one of these signs,
	switch (c) { 					// the function isOperator returns true.
	case '=': 
	case '|':	
	case '&':
    case '+':
    case '-':
    case '*':
	case ',':
		return true;
    default:
        return false;
    }
}
bool isParenthesis(char c){	 // The function returns true if it is a left/right parentheses.
	if (c == '(' || c == ')'){
		return true;
	}
	return false;
}
bool isDigit(char c){	// The function returns true if it is a digit.
	if((int) c >= INTMIN && (int)c  <= INTMAX)
		return true;		
	else
		return false;
}
bool isLetter(char c){ 	// The function returns true if it is a uppercase/lowercase English letter.
	if ((((int) c >= LOWERLETTERMIN) && ((int) c <= LOWERLETTERMAX)) || ( ((int) c <= UPPERLETTERMAX) && ((int) c >= UPPERLETTERMIN))) {
		return true;
	}
	return false;
}
// "precedence" function determines the precedence levels of the operators and functions used.
// "precedence" function is used in stack operations to decide whether the char is popped or pushed into the operatorStack.
int precedence(char *operator){	
	if (strcmp(operator, "=") == 0 || strcmp(operator, "(") == 0 || strcmp(operator, ")") == 0){
		return 0;
	}
	else if (strcmp(operator, ",") == 0){
		return 1;
	}
	else if (strcmp(operator, "|") == 0){
		return 2;
	}
	else if (strcmp(operator, "&") == 0){
		return 3;
	}
	else if (strcmp(operator, "+") == 0 || strcmp(operator, "-") == 0){
		return 4;
	}
	else if (strcmp(operator, "*") == 0){
		return 5;
	}
	else if (strcmp(operator, "^") == 0 || strcmp(operator, "<") == 0 || strcmp(operator, ">") == 0 || strcmp(operator, "~") == 0 || strcmp(operator, "@") == 0|| strcmp(operator, "#") == 0){
		return 6;
	}
	else {
		return -1;
	}
}
typedef struct Variable				// Variable struct is used to hold values and the names of the variables.
{
	char *varName[128];				// If a variable comes, assign a pointer to the first char of it and put it into the *varName
	char  *val[128];				// values of the variables are stored in the *val array of pointers;
	bool isChanged[128];			// and to check whether it is changed or not isChanged is created.
} Variable;							// for these char pointer arrays we don't use static arrays but dynamic ones so that at 
typedef struct Variable varName;	// every iteration of the for loop, we do not lose the data we have.

int main(){
    printf("> "); // At the very beginning, a new line sign is printed.
    Variable variables;
	char line[257] = "";     // This will be the input line.
    // Creation of two stacks.  
	ourStack *operatorStack = (ourStack *)malloc(sizeof(ourStack));	//stack is impelemented using array and char pointers are put into the operator stack
	createEmptyStack(operatorStack);								//function creating the stack
	ourStack *postStack = (ourStack *)malloc(sizeof(ourStack));		//popstack is used when the expression turn into postfix expression.
    createEmptyStack(postStack);									//function creating the stack
    
	char *destination;												//char pointer array which is used in the isDigit if block.
	char *destLetter;												//char pointer array which is used in the isLetter if block.
	char *destPostNot;												//char pointer array which is used in the postfix expression.
	char *destPost;													//char pointer array which is used in the postfix expression.
	int holderForp;
	
	int counter=0;
	char zero[2]={'0', '\0'};
    
	bool flag_equal=false;
	bool isChanged = false;
    while (fgets(line, sizeof(line), stdin)){				// New lines are taken with "fgets" function.		
		bool faceOperation = false;							// Flags, to control situations.
    	bool equalsExists = false; 							// If false, then print it.
    	bool isError = false;								// Indicates whether an error.
        int typeCheck = -1; 								// Default value.
		int intArray[129];
		char **postArray = (char**)malloc(200*sizeof(char*)); 	//postArray is the pointer to the pointer array which is used when evaluating postfix.
		int postIndex = 0; 										//postIndex is the index of the postArray.
        if(line == NULL){ 										// Ctrl+D terminates the program.
            break;        
		}	
		// postIndex is used to determine the index of the Variable struct which includes two char pointer arrays.
		
        for(int i=0; line[i] != '\0'; i++){ //Traverse the line and read it char by char. line[i] is the ith element of the line we get. 
            int holder = i;
			
            if (line[i] == ' '){						
				continue;			// If the line[i] is a space char then continue to reading from the next char until non-space char is encountered.
			}

			if (line[i] == '%'){	// Nothing is evaluated after the comment sign is seen
				break;
			}

            else if (line[i] == 10 ){  					// If there is an "enter" sign, input reading is concluded.
				if (typeCheck == -1){					// Moreover, if there is nothing in this line, a new line
					printf("> ");						// symbol is reading.
					isError = true;
				}
				break;
			}
			
            else if (isOperator(line[i])){ // This block checks if the line[i] is an operator using the isOperator function.
				if (typeCheck == TOKEN_TYPE_L_PARANTHESIS  || typeCheck == TOKEN_TYPE_FUNCTIONS || typeCheck == TOKEN_TYPE_OPERATOR){
					// "typecheck" is a type control mechanism used with Enum so that we can be sure which type of character can come after the other.
					printf("Error!\n> "); // Gives error when the typeCheck condition does not hold.
					isError = true;
					break;//after getting an error, stop reading line but instead get a new line. 
						 //for loop ends and while loop continue to get new line.
				}
                else if (typeCheck == -1){ // If the line starts with an operator, this is an error.
					printf("Error!\n> ");
					isError = true;
					break;
				}
				typeCheck = TOKEN_TYPE_OPERATOR;//if the type control is passed without any issue, then the type of the line[i] is operator.
				char * pointer = (char*) malloc(2*sizeof(char));
				pointer[0] = line[i];
				pointer[1] = '\0';
				if (line[i] == '='){
					if (isEmptyStack(operatorStack) == false){
						printf("Error!\n> ");//if an equal sign exists in the expression we deal with, then it must be the first sign encountered.
						isError = true;
						break;//getting an error break the for loop, and gets new line instead.
					}
					else if (isEmptyStack(operatorStack)){//stack should be empty to evaluate the expression.
						//creates a char pointer to the equal sign and push it into the operator stack.
						pushStack(operatorStack, pointer);	
						equalsExists = true; //flag controlling the existince of the equal sign not to print the result we get.											 
					}
				}
                else if (line[i] == '+'){									
                    if (isEmptyStack(operatorStack)){ //if the stack is empty than push the char pointer of the plus into the operatorStack.
						pushStack(operatorStack,  pointer);																	 
					}
                    else{	
						if(precedence(pointer) > precedence(peekStack(operatorStack))){
							pushStack(operatorStack, pointer);	
						}
						else if(precedence(pointer) <= precedence(peekStack(operatorStack))){
							while(precedence(pointer) <= precedence(peekStack(operatorStack))){
								//the elements from the stack and put them into postArray until the precedence
								postArray[postIndex] = popStack(operatorStack);								
								postIndex++;							//of the top element is lower than the plus sign.							
								if (isEmptyStack(operatorStack) == true){
									break;
								}
							}											
							pushStack(operatorStack, pointer); //After that push the pointer of the plus into the stack.
						}
					}
                }
				else if (line[i] == '-'){					// In every operator, same operations are applied, except ","
                    if (isEmptyStack(operatorStack)){		// operator.
						pushStack(operatorStack, pointer);												 
					}
                    else{
						if(precedence(pointer) > precedence(peekStack(operatorStack))){
							pushStack(operatorStack, pointer);								
						}
						else if(precedence(pointer) <= precedence(peekStack(operatorStack))){
							while(precedence(pointer) <= precedence(peekStack(operatorStack))){
								postArray[postIndex] = popStack(operatorStack);
								postIndex++;		
								if (isEmptyStack(operatorStack) == true){
									break;
								}					
							}
							pushStack(operatorStack, pointer);	
						}
					}
                }
				else if (line[i] == '*'){
                    if (isEmptyStack(operatorStack)){
						pushStack(operatorStack, pointer);											 
					}
                    else{
						if(precedence(pointer) > precedence(peekStack(operatorStack))){	
							pushStack(operatorStack, pointer);										
						}
						else if(precedence(pointer) <= precedence(peekStack(operatorStack))){
							while(precedence(pointer) <= precedence(peekStack(operatorStack))){
								postArray[postIndex] = popStack(operatorStack);
								postIndex++;	
								if (isEmptyStack(operatorStack) == true){
									break;
								}						
							}	
							pushStack(operatorStack, pointer);	
						}
					}
                }
				else if (line[i] == '&'){
                    if (isEmptyStack(operatorStack)){
						pushStack(operatorStack, pointer);											 
					}
                    else{
						if(precedence(pointer) > precedence(peekStack(operatorStack))){
							pushStack(operatorStack, pointer);											
						}
						else if(precedence(pointer) <= precedence(peekStack(operatorStack))){
							while(precedence(pointer) <= precedence(peekStack(operatorStack))){
								postArray[postIndex] = popStack(operatorStack);
								postIndex++;			
								if (isEmptyStack(operatorStack) == true){
									break;
								}				
							}
							pushStack(operatorStack, pointer);		
						}
					}
                }
				else if (line[i] == '|'){
                    if (isEmptyStack(operatorStack)){	
						pushStack(operatorStack, pointer);											 
					}
                    else{
						if(precedence(pointer) > precedence(peekStack(operatorStack))){	
							pushStack(operatorStack, pointer);									
						}
						else if(precedence(pointer) <= precedence(peekStack(operatorStack))){
							while(precedence(pointer) <= precedence(peekStack(operatorStack))){
								postArray[postIndex] = popStack(operatorStack);
								postIndex++;				
								if (isEmptyStack(operatorStack) == true){
									break;
								}			
							}	
							pushStack(operatorStack, pointer);
						}
					}
                }
				else if (line[i] == ','){   // "," operator only pops operators from the stack. It doesn't go into operatorStack.
					if(precedence(pointer) < precedence(peekStack(operatorStack))){ 
							while(precedence(pointer) < precedence(peekStack(operatorStack))){
								postArray[postIndex] = popStack(operatorStack);
								postIndex++;
								if (isEmptyStack(operatorStack) == true){
									break;
								}	
							}
					}
				}
				continue;
            } // End of isOperator block.
			else if (isParenthesis(line[i])){
				if (line[i] == '('){				
					if (typeCheck == TOKEN_TYPE_NUMBER || typeCheck == TOKEN_TYPE_LETTER || typeCheck == TOKEN_TYPE_R_PARANTHESIS){
						printf("Error!\n> "); // The unexpected valued are checked.
						isError = true;
						break;
					}	
					typeCheck = TOKEN_TYPE_L_PARANTHESIS;  // Current type becomes a left parenthesis.
					char * pointer= & (line[i]);
					pushStack(operatorStack,pointer); // pushStack to the stack
				}
				if (line[i] == ')'){
					if (typeCheck == TOKEN_TYPE_OPERATOR || typeCheck == TOKEN_TYPE_L_PARANTHESIS || typeCheck == TOKEN_TYPE_FUNCTIONS){
						printf("Error!> ");
						isError = true;
						break;
					}
					typeCheck = TOKEN_TYPE_R_PARANTHESIS; 		// Current type becomes a right parenthesis.			
					while (*peekStack(operatorStack) != '('){	// popStack until left parenthesis.
						if (isEmptyStack(operatorStack)){
							printf("Error!> ");      // Stack cannot be empty, paranthesis error!
							isError = true;
							break;
						}
						char* element = popStack(operatorStack);						
						postArray[postIndex] = element;			
						postIndex++;					
					}
					char* element = popStack(operatorStack); // Right parenthesis also goes into operatorStack after pop operations are done.
				}
			} // This is the end of isParenthesis block.
			else if(isDigit(line[i])){				
				if (typeCheck == TOKEN_TYPE_NUMBER ||typeCheck ==  TOKEN_TYPE_LETTER || typeCheck == TOKEN_TYPE_R_PARANTHESIS|| typeCheck == TOKEN_TYPE_FUNCTIONS){
					printf("Error!\n> "); 	// Unexpected types are checked.
					isError = true;
					break;
				}
				typeCheck = TOKEN_TYPE_NUMBER;  // Current type becomes a number.
        		char* pointer= &line[i];		// A pointer is assigned at the beginning of the number.
				int temp = i;					// The index of the pointer is stored.
        		while (isDigit(line[i])) {		// The end of the number is found by iterating "line".
            		i++;					
        		}
				int diff = i - temp;			// A temporary char array is created with a size of that number.
				destination = (char*)malloc(diff*sizeof(char*));
				for (int j = temp; j < i; j++){ // The char array is filled with the number characters.
					destination[j - temp] = line[j]; 
				}
				i--;								
				postArray[postIndex] = destination;		// Then, the pointer is sent to postArray.
				postIndex++;				
    		}
			
			if(isLetter(line[i])){
				if (typeCheck == TOKEN_TYPE_R_PARANTHESIS|| typeCheck == TOKEN_TYPE_NUMBER || typeCheck == TOKEN_TYPE_LETTER|| typeCheck == TOKEN_TYPE_FUNCTIONS ){
					printf("Error!\n> ");
					isError = true;
					break;
				}				
				if (isLetter(line[i-1]) == false){ 					// Here, all possible functiıon names are checked, and
					if (line[i] == 'x'){							// if it holds, a pointer of a char previously assigned 
						if (line[i+1] == 'o'){						// to the function is pushed to operatorStack.
							if (line[i+2] == 'r'){
								if (isLetter(line[i+3]) == false){
									typeCheck = TOKEN_TYPE_FUNCTIONS;
									char elem = '^';
									char *fake = &elem;
									pushStack(operatorStack, fake);								
									// pushStack the xor char in the stack.
									i = i + 2;
									continue;
								}
							}
						}
					}
				}
				if (isLetter(line[i-1]) == false){
					if (line[i] == 'l'){
						if (line[i+1] == 's'){
							if (isLetter(line[i+2]) == false){
								typeCheck = TOKEN_TYPE_FUNCTIONS;
								// pushStack the ls char in the stack.
								char elem = '<';
								char *fake = &elem;								
								pushStack(operatorStack, fake);									
								i = i + 1;
								continue;
							}							
						}
					}
				}
				if (isLetter(line[i-1]) == false){
					if (line[i] == 'r'){
						if (line[i+1] == 's'){
							if (isLetter(line[i+2]) == false){
								typeCheck = TOKEN_TYPE_FUNCTIONS;	
								char elem = '>';
								char *fake = &elem;
								pushStack(operatorStack, fake);							
								// pushStack the rs char in the stack.
								i = i + 1;
								continue;
							}							
						}
					}
				}
				if (isLetter(line[i-1]) == false){
					if (line[i] == 'l'){
						if (line[i+1] == 'r'){
							if (isLetter(line[i+2]) == false){
								typeCheck = TOKEN_TYPE_FUNCTIONS;
								// pushStack the lr char in the stack.
								char elem = '@';
								char *fake = &elem;
								pushStack(operatorStack, fake);							
								i = i + 1;
								continue;
							}							
						}
					}
				}
				if (isLetter(line[i-1]) == false){
					if (line[i] == 'r'){
						if (line[i+1] == 'r'){
							if (isLetter(line[i+2]) == false){
								typeCheck = TOKEN_TYPE_FUNCTIONS;
								// pushStack the rr char in the stack.		
								char elem = '#';
								char *fake = &elem;
								pushStack(operatorStack, fake);			
								i = i + 1;
								continue;
							}							
						}
					}
				}
				if (isLetter(line[i-1]) == false){
					if (line[i] == 'n'){
						if (line[i+1] == 'o'){
							if (line[i+2] == 't'){
								if (isLetter(line[i+3]) == false){
									typeCheck = TOKEN_TYPE_FUNCTIONS;
									// pushStack the not char in the stack.	
									char elem = '~';
									char *fake = &elem;
									pushStack(operatorStack, fake);				
									i = i + 2;
									continue;
								}
							}							
						}
					}
				}			
				typeCheck = TOKEN_TYPE_LETTER;
                char* pointer= &line[i];				// If there is a letter, similar job has done.
                int temp = i;							// The letter is taken and checked whether it is used or not.
                while (isLetter(line[i])) {				// If used, the value is sent to postArray.
                    i++;								// Otherwise, 0 is sent to postArray.
                }
                int diff = i - temp;
                destLetter = (char*)malloc(diff*sizeof(char));//destletter is an array.
                for (int j = temp; j < i; j++){
                    destLetter[j - temp] = line[j];
                }
                i--;
                if(counter==0){
                    variables.varName[0]=destLetter;
                    variables.isChanged[0]=false;
                    variables.val[0]=zero;
                    postArray[postIndex]=variables.val[0];
                    postIndex++;
                    counter++;
                }
                bool flagLetter=false;
                int indexHolder;
                for(int p=0; p<counter; p++){
                    if((strcmp(variables.varName[p], destLetter))==0){
                        indexHolder=p;
                        variables.isChanged[p]=true;
                        postArray[postIndex]=variables.val[p];
                        postIndex++;
                        flagLetter=true;
                        break;
                    }
                    else{
                	    continue;
                    }
                }
                if(!flagLetter){
                    variables.varName[counter]=destLetter;
                    variables.isChanged[counter]=false;
                    variables.val[counter]=zero;
                    postArray[postIndex]=variables.val[counter];
                    postIndex++;
                   counter++;
                }
			}
		} // This is the end of for loop.
		
		if (isError == true){							// If there is an error, postfix expression won't be read.
			continue;
		}
		if (typeCheck == TOKEN_TYPE_OPERATOR || typeCheck == TOKEN_TYPE_FUNCTIONS || typeCheck == TOKEN_TYPE_L_PARANTHESIS){
			printf("Error!\n> ");						// Operators, functions, and left parenthesis cannot be at the
			isError = true;								// end, this means there is an error.
		}
		if (isError == true){							// If there is an error, postfix expression won't be read.
			continue;
		}
		while (isEmptyStack(operatorStack) == false){  	// There might be some elements remaining in operatorStack. 
			char* element = popStack(operatorStack); 	// In this case, operators are popped one by one and added to
			if (*(element) == '('){						// postArray. If there is a left parenthesis, this means that 
				printf("Error!\n> ");					// there is at least one parenthesis block is not closed, and 
				isError = true;							// this is an error.
			}
			postArray[postIndex] = element; 
			postIndex++;
		}
		if (isError == true){							// If there is an error, postfix expression won't be read.
			continue;
		}
		       	
		for (int i = 0; i < postIndex; i++) { 			// Postfix evaluation starts from now on.
			if (isDigit(*postArray[i])){				// If postArray returns a number , the 
				pushStack(postStack, postArray[i]);		// pointer is pushed to postStack.		
			}
			if (isOperator(*postArray[i]) || isFunction(*postArray[i])) { // Another possibility is being an operator.
				faceOperation = true;					// In this case, an operation is faced.
				if (*postArray[i] == '~'){				// "NOT" operation has only one operand so it is evaluated
					int numberInteger = 0;				// separately than the other operations.
					char *numberPointer = popStack(postStack); // A pointer is returned from the stack and converted into
					numberInteger = atoi(numberPointer);	// an integer. Then the operation is made and converted into 
					numberInteger = ~ numberInteger;		// a character again and a pointer is pushed to the stack again
					char *digitPointer;						// unless it is the last operation. Otherwise, the result is
					if (i == postIndex - 1){ 				// printed to the console.
						printf("%d", numberInteger);
						break;
					}
					destPostNot = (char*)malloc(256*sizeof(char*));
					sprintf(destPostNot, "%d", numberInteger);
					digitPointer = &destPostNot[0];
					pushStack(postStack, digitPointer);			
				}
				else{										// Other operators have two operands. Therefore, popping numbers
					int IntegerOne = 0;						// phase is done twice. The operation is chosen in the switch block.
					int IntegerTwo = 0;						// Then, the resulting integer is converted into a character array
					char *pointerOne = popStack(postStack); // and its pointer is pushed back to the stack. If there is no equals 
					IntegerOne = atoi(pointerOne);          // sign in the expression and there is no more operation left, 
					char *pointerTwo = popStack(postStack); // the result is written to the console.
					IntegerTwo = atoi(pointerTwo);
					int numberInteger;
					int temp_holder;
					switch (*postArray[i]){
					case '+':
						numberInteger = IntegerOne + IntegerTwo;
						break;
					case '-':
						numberInteger = IntegerTwo - IntegerOne;
						break;
					case '*':
						numberInteger = IntegerOne * IntegerTwo;
						break;
					case '&':
						numberInteger = IntegerOne & IntegerTwo;
						break;
					case '|':
						numberInteger = IntegerOne | IntegerTwo;
						break;
					case '^':
						numberInteger = IntegerTwo ^ IntegerOne;
						break;
					case '>':
						numberInteger = IntegerTwo >> IntegerOne;
						break;
					case '<':
						numberInteger = IntegerTwo << IntegerOne;
						break;
					case '@':
						numberInteger = (IntegerTwo << IntegerOne) || (IntegerTwo >> (LONG_SIZE - IntegerOne));
						break;
					case '#':
						numberInteger = (IntegerTwo >> IntegerOne) || (IntegerTwo << (LONG_SIZE - IntegerOne));
						break;
					case '=':
						IntegerTwo = IntegerOne;
						numberInteger=IntegerTwo;
						flag_equal=true;
						temp_holder = IntegerTwo;
						break;
					default:
						break;
					}
					char *digitPointer;			
					if ((i == postIndex - 1) && (*postArray[i] != '=')){ 
						printf("%d", numberInteger);
						break;
					}
					destPost = (char*)malloc(256*sizeof(char*));
					sprintf(destPost, "%d", numberInteger);
					digitPointer = &destPost[0];
					pushStack(postStack, digitPointer);
					
					int equalCounter=0;
					int y=0;
					if(equalsExists){
						while(line[y]!='='){
							equalCounter++;
							y++;
						}
					}
					char substring[equalCounter+1];
					if(equalsExists){						
						strncpy(substring,line, equalCounter);
						substring[equalCounter]='\0';						
					}
					bool flagEqual=false;
					for (int c = 0; c<counter; c++){
						if(strcmp(variables.varName[c], substring)==0){
							//free(variables.val[c]);
                            variables.val[c]=(char*)malloc(20*sizeof(char));
						    variables.val[c]=digitPointer;
							flagEqual=true;
							break;
						}
					}
					if(flagEqual==false){
						variables.val[counter-1]=(char*)malloc(sizeof(digitPointer));
						variables.val[counter-1]=digitPointer;
					}		
				}
			} 			
        } // It is the end of postfix evaluation. 
		clearStack(operatorStack);
		if (faceOperation == false){     // If there is no operation in postStack, the number inside is written to the
			int numberInteger = 0;       // console. Then all stacks are cleared, and a new line is printed.
			char *numberPointer = popStack(postStack);
			numberInteger = atoi(numberPointer);
			printf("%d", numberInteger);
		}	
		clearStack(postStack);
		if (equalsExists == true){
			printf("> ");
			continue;
		}
		printf("\n> ");
    }  // This is the end of while loop. 
    return 0;
}

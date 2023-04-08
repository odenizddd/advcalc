CmpE 230 - a simple interpreter written in C
By: Özgür Deniz Demir

To run: make advcalc
        ./advcal

This is an overview of how advcalc interpreter works.

Once the prompt session is fired, new lines are fed into a functions called 'run_line' that tokenizes
and evaluates expressions. 

The tokenization is straightforward. Characters are consumes one by one and
categorized into token_types. Only exception occurs when tokenizer finds characters that represents
variable names, number literals and native functions (xor, not, ls etc.). In that case, it keeps consuming
characters until it finds a non-alphanumeric character. This way it can form multi-character tokens.

Tokens are stored and passed in a vector of tokens. This vector supports slice operation
which is critical for evaluation process because it works recursively.

The evaluation process is handled by a functions called 'eval' which takes as input an expression 
represented as a vector of tokens and and evaluates it and returns the result. The way it works is by applying
mathematical operatons recursively starting from the lowest priority binary operators to highest priority binary
operators. If there are no binary operators that is not nested within parenthesis or native functions it 
evaluates those expressions by extracting expression nested within those parenthesis.
The way the recursion stops is when 'eval' reaches a variable name or a number literal. Number literals are
parsed into integers and variable values are looked up from a map.

Assignment operation is not handled recursively, for this 'run_line' checks if there is an assignment operator
before calling 'eval' if there is it assign the value of right handside to left handside on the map. It also
checks to see if left hand side is assignable beforehands. It only expects variable names that might or might
not be nested within parenthesis.

Error handling is done via an error flag. If an invalid expression is encountered during tokenization or
evaluation this flag is set and later on an error is reported.
# Simple Tokenizer-Lexer

This is a C project that implements a basic tokenizer-lexer for a C-like language. It can recognize keywords, identifiers, numbers, symbols, and handle EOF.

## Build
To compile the project, run: make
To remove compiled files, run: make clean
The lexer executable can be directly run by using: make run

## Usage
The program is currently set up with this hardcoded string in main.c: "int long_variable_name = 123456789;"
When the program is executed, the previously mentioned input will be tokenized and each token will be printed.

## Example:
<KEYWORD, "int">
<IDENTIFIER, "long_variable_name">
<SYMBOL, "=">
<NUMBER, "123456789"
<SYMBOL, ";">
<EOF, "">

## Additional informations:
1. This lexer supports basic keywords: int, float, char, if, else, return, void, while, for.
2. Identifiers, numbers and single -character symbols are also recognized.
3. The string which is used as an input for the lexer can be modified in main.c to test different input strings.

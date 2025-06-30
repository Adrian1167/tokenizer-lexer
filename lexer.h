#ifndef LEXER_H
#define LEXER_H

#include <stddef.h> // for size_t

typedef enum {
    TOKEN_IDENTIFIER,
    TOKEN_KEYWORD,
    TOKEN_NUMBER,
    TOKEN_SYMBOL,
    TOKEN_EOF,
    TOKEN_UNKNOWN
} TokenType;

typedef struct {
    TokenType type;
    char *value; // dynamically allocated string
} Token;

typedef struct {
    const char *src;
    size_t pos;
} Lexer;

void init_lexer(Lexer *lexer, const char *source);
Token get_next_token(Lexer *lexer);
void print_token(const Token *token);
void free_token(Token *token); // NEW: frees token.value

#endif // LEXER_H

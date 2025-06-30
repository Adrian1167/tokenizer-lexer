#define _POSIX_C_SOURCE 200809L /*needed to use strndup() */
#include "lexer.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/* Most common keywords */
static const char *keywords[] = {
    "int", "float", "char", "if", "else", "return", "void", "while", "for", NULL
};

void init_lexer(Lexer *lexer, const char *source) {
    lexer->src = source;
    lexer->pos = 0;
}

static int is_keyword(const char *str) {
    for (int i = 0; keywords[i]; ++i) {
        if (strcmp(str, keywords[i]) == 0) return 1;
    }
    return 0;
}

/* Function which help us skip white spaces and go to the next character position */
static void skip_whitespace(Lexer *lexer) {
    while (isspace(lexer->src[lexer->pos])) {
        lexer->pos++;
    }
}

static int is_symbol(char c) {
    return strchr("+-*/=;(){}", c) != NULL;
}

/* We allocate and return a string copy in order to not declare the token buffer statically. This way we can store a dinamic number of bytes */ 
static char *copy_string(const char *src, size_t start, size_t end) {
    size_t len = end - start;
    char *str = malloc(len + 1);
    if (!str) return NULL;
    memcpy(str, src + start, len);
    str[len] = '\0';
    return str;
}

static Token read_identifier(Lexer *lexer) {
    size_t start = lexer->pos;
    while (isalnum(lexer->src[lexer->pos]) || lexer->src[lexer->pos] == '_') {
        lexer->pos++;
    }

    Token token;
    token.value = copy_string(lexer->src, start, lexer->pos);
    token.type = is_keyword(token.value) ? TOKEN_KEYWORD : TOKEN_IDENTIFIER;
    return token;
}

static Token read_number(Lexer *lexer) {
    size_t start = lexer->pos;
    while (isdigit(lexer->src[lexer->pos])) {
        lexer->pos++;
    }

    Token token;
    token.value = copy_string(lexer->src, start, lexer->pos);
    token.type = TOKEN_NUMBER;
    return token;
}

static Token read_symbol(Lexer *lexer) {
    Token token;
    token.type = TOKEN_SYMBOL;

    char c = lexer->src[lexer->pos++];
    token.value = malloc(2);
    if (token.value) {
        token.value[0] = c;
        token.value[1] = '\0';
    }

    return token;
}

/* Parse the next token */
Token get_next_token(Lexer *lexer) {
    skip_whitespace(lexer);

    char current = lexer->src[lexer->pos];

    if (current == '\0') {
        Token token = { TOKEN_EOF, strdup("") };
        return token;
    }

    if (isalpha(current) || current == '_') return read_identifier(lexer);
    if (isdigit(current)) return read_number(lexer);
    if (is_symbol(current)) return read_symbol(lexer);

    Token token;
    token.type = TOKEN_UNKNOWN;
    token.value = malloc(2);
    if (token.value) {
        token.value[0] = current;
        token.value[1] = '\0';
    }
    lexer->pos++;
    return token;
}

void print_token(const Token *token) {
    const char *type_str = "UNKNOWN";
    switch (token->type) {
        case TOKEN_IDENTIFIER: type_str = "IDENTIFIER"; break;
        case TOKEN_KEYWORD:    type_str = "KEYWORD";    break;
        case TOKEN_NUMBER:     type_str = "NUMBER";     break;
        case TOKEN_SYMBOL:     type_str = "SYMBOL";     break;
        case TOKEN_EOF:        type_str = "EOF";        break;
        default: break;
    }
    printf("<%s, \"%s\">\n", type_str, token->value);
}

/* We need to free the dinamically allocated token buffer */
void free_token(Token *token) {
    if (token && token->value) {
        free(token->value);
        token->value = NULL;
    }
}

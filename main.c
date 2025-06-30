#include <stdio.h>
#include "lexer.h"

int main() {
    const char *source = "int long_variable_name = 123456789;";
    Lexer lexer;
    init_lexer(&lexer, source);

    Token token;
    do {
        token = get_next_token(&lexer);
        print_token(&token);
        free_token(&token); /* free the dinamically allocated token buffer */
    } while (token.type != TOKEN_EOF);

    return 0;
}

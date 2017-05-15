//
// Created by em on 5/13/17.
//

#include "debug.h"

void
xtra_debug_spaces(int padding, const char * line)
{
    int position = -1;
    while (++position < padding) {
        printf(" ");
    }

    printf(line);
}

void
xtra_debug_token(xtra_token_p token, int spaces);

void xtra_debug_token(xtra_token_p token, int spaces) {
    char *message = malloc(sizeof(char));
    sprintf(message, "# (%lu) %s\n", token->size, token->lexer != NULL ? token->lexer : "NULL");
    xtra_debug_spaces(spaces, message);
    if (token->size <= 0) {
        return;
    }


    spaces += 2;

    long position = -1;
    while (++position < token->size) {
        xtra_debug_token((xtra_token_p) xtra_arry_get(token->child, position), spaces);
    }

    spaces -= 2;
    xtra_debug_spaces(spaces, "#!\n");

//    printf("%ds{\n", padding);
//
//    padding += 2;
//
//    long position = -1;
//    while (--position < script->size) {
//        xtra_token_p token = script->child[position];
//        printf("%d", script->child[position]->type);
//
//        if (script->child[position]->size > 0) {
//            xtra_token_debug(script->child[position], padding);
//        }
//    }
//
//    padding -= 2;
//    printf("%ds}\n", padding);
}

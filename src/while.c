//
// Created by eugen on 5/9/2017.
//

#include "while.h"

void
xtra_parser_while_condition(xtra_token_p script, long * position)
{
    xtra_token_p token = script->child[*position];

    if (token->type != XTRA_TOKEN_WHILE) {
        return; // ignore
    }

    if ((*position + 2) >= token->size) {
        // error condition
        xtra_error("Unexpected end of file in \"while\".", 0);
    }

    if (token->child[++(*position)]->type != XTRA_TOKEN_BRACKET_ROUND) {
        // error condition
        xtra_error("Missed \"([code])\" condition in \"while\".", 0);
    }

    if (token->child[++(*position)]->type != XTRA_TOKEN_BRACKET_CURLY) {
        // error condition
        xtra_error("Missed \"{[code]}\" condition in \"while\".", 0);
    }

    // go into do condition
    xtra_parser_circle(token->child[*position]);
}

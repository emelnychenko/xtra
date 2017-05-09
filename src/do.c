//
// Created by eugen on 5/9/2017.
//

#include "do.h"

void
xtra_parser_do_condition(xtra_token_p script, long * position)
{
    xtra_token_p token = script->child[*position];

    if (token->type != XTRA_TOKEN_DO) {
        return; // ignore
    }

    if ((*position + 3) >= token->size) {
        // error condition
        xtra_error("Unexpected end of file in \"do\".", 0);
    }

    if (token->child[++(*position)]->type != XTRA_TOKEN_BRACKET_CURLY) {
        // error condition
        xtra_error("Missed \"{[code]}\" condition in \"do\".", 0);
    }

    // go into do condition
    xtra_parser_circle(token->child[*position]);

    if (token->child[++(*position)]->type != XTRA_TOKEN_WHILE) {
        // error condition
        xtra_error("Missed \"while\" keyword in \"do\".", 0);
    }

    //
    if (token->child[++(*position)]->type != XTRA_TOKEN_BRACKET_ROUND) {
        // error condition
        xtra_error("Missed \"([code])\" condition in \"while\".", 0);
    }
}

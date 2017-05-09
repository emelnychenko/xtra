//
// Created by eugen on 5/9/2017.
//

#include "for.h"

void
xtra_parser_for_condition(xtra_token_p script, long * position)
{
    xtra_token_p token = script->child[*position];

    if (token->type != XTRA_TOKEN_FOR) {
        return; // ignore
    }

    if ((*position + 2) >= token->size) {
        // error condition
        xtra_error("Unexpected end of file in \"for\".", 0);
    }

    if (token->child[++(*position)]->type != XTRA_TOKEN_BRACKET_ROUND) {
        // error condition
        xtra_error("Missed \"([code])\" condition in \"for\".", 0);
    }

    // for (;;)
    // for (int i in [list, array, dictionary, hash])
    // each([array, list, dictionaty, hash], function() {});
    // foreach (any as key)
    if (token->child[++(*position)]->type != XTRA_TOKEN_BRACKET_CURLY) {
        // error condition
        xtra_error("Missed \"{[code]}\" condition in \"for\".", 0);
    }

    // go into for condition
    xtra_parser_circle(
            token->child[*position]
    );
}

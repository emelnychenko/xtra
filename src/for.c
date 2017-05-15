//
// Created by eugen on 5/9/2017.
//

#include "for.h"

void
xtra_parser_for_condition(xtra_token_p script, long * position)
{
    if ((*position + 2) >= script->size) {
        // error condition
        xtra_error("Unexpected end of file in \"for\".", 0);
    }

    if (xtra_bracket_is_left((xtra_token_p) xtra_arry_get(script->child, *position + 1))) {
        ++(*position);
        xtra_brackets_join_conditions(script, position);
    }

    if (((xtra_token_p) xtra_arry_get(script->child, ++(*position)))->type != XTRA_TOKEN_BRACKET_ROUND) {
        // error condition
        xtra_error("Missed \"([code])\" condition in \"for\".", 0);
    }

    if (xtra_bracket_is_left((xtra_token_p) xtra_arry_get(script->child, *position + 1))) {
        ++(*position);
        xtra_brackets_join_conditions(script, position);
    }

    // for (;;)
    // for (int i in [list, array, dictionary, hash])
    // each([array, list, dictionaty, hash], function() {});
    // foreach (any as key)
    if (((xtra_token_p) xtra_arry_get(script->child, ++(*position)))->type != XTRA_TOKEN_BRACKET_CURLY) {
        // error condition
        xtra_error("Missed \"{[code]}\" condition in \"for\".", 0);
    }

    // go into for condition
    xtra_parser_circle(
            (xtra_token_p) xtra_arry_get(script->child, *position)
    );
}

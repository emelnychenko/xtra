//
// Created by eugen on 5/9/2017.
//

#include "do.h"

void
xtra_do_condition_replace(xtra_token_p script, long * position)
{
    if ((*position + 3) >= script->size) {
        // error condition
        xtra_error("Unexpected end of file in \"do\".", 0);
    }

    if (xtra_bracket_is_left((xtra_token_p) xtra_arry_get(script->child, *position + 1))) {
        ++(*position);
        xtra_brackets_join_conditions(script, position);
    }

    if (((xtra_token_p) xtra_arry_get(script->child, ++(*position)))->type != XTRA_TOKEN_BRACKET_CURLY) {
        // error condition
        xtra_error("Missed \"{[code]}\" condition after \"do\".", 0);
    }

    xtra_parser_circle(
            (xtra_token_p) xtra_arry_get(script->child, *position)
    );

    if (((xtra_token_p) xtra_arry_get(script->child, ++(*position)))->type != XTRA_TOKEN_WHILE) {
        // error condition
        xtra_error("Missed \"while\" keyword in \"do\".", 0);
    }

    if (xtra_bracket_is_left((xtra_token_p) xtra_arry_get(script->child, *position + 1))) {
        ++(*position);
        xtra_brackets_join_conditions(script, position);
    }

    if (((xtra_token_p) xtra_arry_get(script->child, ++(*position)))->type != XTRA_TOKEN_BRACKET_ROUND) {
        // error condition
        xtra_error("Missed \"([code])\" condition after \"while\".", 0);
    }
}

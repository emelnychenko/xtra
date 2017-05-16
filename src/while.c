//
// Created by eugen on 5/9/2017.
//

#include "while.h"

void
xtra_while_parse(xtra_sign_p sign, long * position)
{
    if ((*position + 2) >= xtra_sign_arry_len(sign)) {
        // error condition
        xtra_error("Unexpected end of file in \"while\".", 0);
    }

    if (xtra_bracket_is_left(xtra_sign_arry_get(sign, *position + 1))) {
        ++(*position);
        xtra_brackets_join_conditions(sign, position);
    }

    if (xtra_sign_arry_get(sign, ++(*position))->type != XTRA_SIGN_ROUND) {
        // error condition
        xtra_error("Missed \"([code])\" condition in \"while\".", 0);
    }

    if (xtra_bracket_is_left((xtra_sign_p) xtra_sign_arry_get(sign, *position + 1))) {
        ++(*position);
        xtra_brackets_join_conditions(sign, position);
    }

    if (((xtra_sign_p) xtra_sign_arry_get(sign, ++(*position)))->type != XTRA_SIGN_CURLY) {
        // error condition
        xtra_error("Missed \"{[code]}\" condition in \"while\".", 0);
    }

    // go into do condition
    xtra_parser_circle((xtra_sign_p) xtra_sign_arry_get(sign, *position));
}

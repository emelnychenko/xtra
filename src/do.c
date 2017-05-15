//
// Created by eugen on 5/9/2017.
//

#include "do.h"

void
xtra_do_parse(xtra_sign_p sign, long * position)
{
    if ((*position + 3) >= xtra_sign_arry_len(sign)) {
        // error condition
        xtra_error("Unexpected end of file in \"do\".", 0);
    }

    if (xtra_bracket_is_left(xtra_sign_arry_get(sign, *position + 1))) {
        ++(*position);
        xtra_brackets_join_conditions(sign, position);
    }

    if (xtra_sign_arry_get(sign, ++(*position))->type != XTRA_SIGN_BRACKET_CURLY) {
        // error condition
        xtra_error("Missed \"{[code]}\" condition after \"do\".", 0);
    }

    xtra_parser_circle(
            xtra_sign_arry_get(sign, *position)
    );

    if (xtra_sign_arry_get(sign, ++(*position))->type != XTRA_SIGN_WHILE) {
        // error condition
        xtra_error("Missed \"while\" keyword in \"do\".", 0);
    }

    if (xtra_bracket_is_left(xtra_sign_arry_get(sign, *position + 1))) {
        ++(*position);
        xtra_brackets_join_conditions(sign, position);
    }

    if (xtra_sign_arry_get(sign, ++(*position))->type != XTRA_SIGN_BRACKET_ROUND) {
        // error condition
        xtra_error("Missed \"([code])\" condition after \"while\".", 0);
    }
}

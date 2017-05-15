//
// Created by eugen on 5/15/2017.
//

#include "switch.h"

void
xtra_switch_parse(xtra_sign_p sign, long * position)
{
    if ((*position + 2) >= xtra_sign_arry_len(sign)) {
        // error condition
        xtra_error("Unexpected end of file after \"switch\".", 0);
    }

    if (xtra_bracket_is_left((xtra_sign_p) xtra_sign_arry_get(sign, *position + 1))) {
        ++(*position);
        xtra_brackets_join_conditions(sign, position);
    }

    if (((xtra_sign_p) xtra_sign_arry_get(sign, ++(*position)))->type != XTRA_SIGN_BRACKET_ROUND) {
        // error condition
        xtra_error("Missed \"([code])\" condition after \"switch\".", 0);
    }

    if (xtra_bracket_is_left((xtra_sign_p) xtra_sign_arry_get(sign, *position + 1))) {
        ++(*position);
        xtra_brackets_join_conditions(sign, position);
    }

    if (((xtra_sign_p) xtra_sign_arry_get(sign, ++(*position)))->type != XTRA_SIGN_BRACKET_CURLY) {
        // error condition
        xtra_error("Missed \"{[code]}\" condition after \"switch\".", 0);
    }

    // spec implementation
    xtra_parser_circle((xtra_sign_p) xtra_sign_arry_get(sign, *position));
}

void
xtra_switch_cases_parse(xtra_sign_p sign)
{
    //
}
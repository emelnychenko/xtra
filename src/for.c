//
// Created by eugen on 5/9/2017.
//

#include "for.h"

void
xtra_for_parse(xtra_sign_p sign, long * position)
{
    if ((*position + 2) >= xtra_sign_arry_len(sign)) {
        // error condition
        xtra_error("Unexpected end of file in \"for\".", 0);
    }

    if (xtra_bracket_is_left( xtra_sign_arry_get(sign, *position + 1))) {
        ++(*position);
        xtra_brackets_join_conditions(sign, position);
    }

    if (xtra_sign_arry_get(sign, ++(*position))->type != XTRA_SIGN_ROUND) {
        // error condition
        xtra_error("Missed \"([code])\" condition in \"for\".", 0);
    }

    if (xtra_bracket_is_left( xtra_sign_arry_get(sign, *position + 1))) {
        ++(*position);
        xtra_brackets_join_conditions(sign, position);
    }

    // for (;;)
    // for (int i in [list, array, dictionary, hash])
    // each([array, list, dictionaty, hash], function() {});
    // foreach (any as key)
    if (xtra_sign_arry_get(sign, ++(*position))->type != XTRA_SIGN_CURLY) {
        // error condition
        xtra_error("Missed \"{[code]}\" condition in \"for\".", 0);
    }

    // go into for condition
    xtra_parser_circle(
             xtra_sign_arry_get(sign, *position)
    );
}

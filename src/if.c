//
// Created by em on 5/9/17.
//

#include "if.h"

int
xtra_if_join_elseif(xtra_sign_p sign, long * position)
{
    long this = *position, next = *position + 1;

    if (
           xtra_sign_arry_has(sign, next)
        && xtra_sign_arry_type(sign, this) == XTRA_SIGN_ELSE
        && xtra_sign_arry_type(sign, this) == XTRA_SIGN_IF
    ) {
        xtra_sign_arry_free(sign, this);
        xtra_sign_arry_free(sign, next);
        --(*position);

        xtra_sign_free(
                xtra_sign_arry_vsplice(
                        sign,
                        this,
                        2,
                        1,
                        xtra_sign(XTRA_SIGN_ELSEIF)
                )
        );

        return 1;
    }

    return 0;
}

void
xtra_if_parse(xtra_sign_p sign, long * position)
{
    if (xtra_sign_arry_len(sign) <= (*position + 2)) {
        // error condition
        xtra_error("Unexpected end of file in \"if\".", 0);
    }

    if (xtra_bracket_is_left((xtra_sign_p) xtra_sign_arry_get(sign, *position + 1))) {
        ++(*position);
        xtra_brackets_join_conditions(sign, position);
    }

    if (((xtra_sign_p) xtra_sign_arry_get(sign, ++(*position)))->type != XTRA_SIGN_ROUND) { // condition
        // error condition
        xtra_error("Missed \"([code])\" condition in \"if\".", 0);
    }

    if (xtra_bracket_is_left((xtra_sign_p) xtra_sign_arry_get(sign, *position + 1))) {
        ++(*position);
        xtra_brackets_join_conditions(sign, position);
    }

    if (((xtra_sign_p) xtra_sign_arry_get(sign, ++(*position)))->type != XTRA_SIGN_CURLY) { // condition
        // error condition
        xtra_error("Missed \"{[code]}\" condition in \"if\".", 0);
    }

    // go into do condition
    xtra_parser_circle(
            (xtra_sign_p) xtra_sign_arry_get(sign, *position)
    );

    long _position = *position + 1;
    xtra_if_join_elseif(sign, &_position);

    if (((xtra_sign_p) xtra_sign_arry_get(sign, *position + 1))->type == XTRA_SIGN_ELSEIF) {
        // else if condition
        ++(*position);
        xtra_elseif_parse(
                sign, position
        );
    }

    if (((xtra_sign_p) xtra_sign_arry_get(sign, *position + 1))->type != XTRA_SIGN_ELSE) {
        // over condition
        return;
    }

    ++(*position);

    if (xtra_bracket_is_left((xtra_sign_p) xtra_sign_arry_get(sign, *position + 1))) {
        ++(*position);
        xtra_brackets_join_conditions(sign, position);
    }

    if (((xtra_sign_p) xtra_sign_arry_get(sign, ++(*position)))->type != XTRA_SIGN_CURLY) { // condition
        // error condition
        xtra_error("Missed \"{[code]}\" condition after \"else\".", 0);
    }

    // go into do condition
    xtra_parser_circle((xtra_sign_p) xtra_sign_arry_get(sign, *position));
}

void
xtra_elseif_parse(xtra_sign_p sign, long * position)
{
    if (xtra_sign_arry_len(sign) <= ((*position) + 2)) {
        // error condition
        xtra_error("Unexpected end of file after \"elseif\".", 0);
    }

    if (xtra_bracket_is_left((xtra_sign_p) xtra_sign_arry_get(sign, *position + 1))) {
        ++(*position);
        xtra_brackets_join_conditions(sign, position);
    }

    if (((xtra_sign_p) xtra_sign_arry_get(sign, ++(*position)))->type != XTRA_SIGN_ROUND) { // condition
        // error condition
        xtra_error("Missed \"([code])\" condition after \"elseif\".", 0);
    }

    if (xtra_bracket_is_left((xtra_sign_p) xtra_sign_arry_get(sign, *position + 1))) {
        ++(*position);
        xtra_brackets_join_conditions(sign, position);
    }

    if (((xtra_sign_p) xtra_sign_arry_get(sign, ++(*position)))->type != XTRA_SIGN_CURLY) { // condition
        // error condition
        xtra_error("Missed \"{[code]}\" condition after \"elseif\".", 0);
    }

    // go into {} condition
    xtra_parser_circle((xtra_sign_p) xtra_sign_arry_get(sign, *position));

    long _position = *position + 1;
    xtra_if_join_elseif(sign, &_position);

    if (((xtra_sign_p) xtra_sign_arry_get(sign, *position + 1))->type == XTRA_SIGN_ELSEIF) { // condition
        // recursion
        xtra_elseif_parse(
                sign, position
        );
    }
}
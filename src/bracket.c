//
// Created by eugen on 5/9/2017.
//

#include "bracket.h"

void
xtra_brackets_join_conditions(xtra_sign_p sign, long * position)
{
    long start = *position, length;

    xtra_sign_p _sign = xtra_sign(
            xtra_bracket_get_brackets(xtra_sign_arry_get(sign, *position))
    );

    while (++(*position) < xtra_sign_arry_len(sign)) {
        if (
            /**
             *
             */
            xtra_bracket_is_left(xtra_sign_arry_get(sign, *position))
        ) {
            xtra_brackets_join_conditions(sign, position);
        } else if (
            /**
             *
             */
            xtra_brackets_is_related(xtra_sign_arry_get(sign, start), xtra_sign_arry_get(sign, *position))
        ) {
            /**
             *
             */
            xtra_sign_arry_free(sign, start);
            xtra_sign_arry_free(sign, *position);

            length = *position - start;

            //xtra_token_set_parent(_sign, sign);

            xtra_sign_free(
                   xtra_sign_arry_vsplice(sign, start, length + 1, 1, _sign)
            );
            *position -= (length + 1);

            return;
        } else {
            /**
             *
             */
            xtra_sign_arry_push(_sign, xtra_sign_arry_get(sign, *position));
        }
    }
}

int
xtra_bracket_is_left(xtra_sign_p sign)
{
    return sign->type == XTRA_SIGN_SQUARE_L
           || sign->type == XTRA_SIGN_ROUND_L
           || sign->type == XTRA_SIGN_CURLY_L
           || sign->type == XTRA_SIGN_ANGLE_L;
}

int
xtra_bracket_is_right(xtra_sign_p token)
{
    return token->type == XTRA_SIGN_SQUARE_R
           || token->type == XTRA_SIGN_ROUND_R
           || token->type == XTRA_SIGN_CURLY_R
           || token->type == XTRA_SIGN_ANGLE_R;
}

int
xtra_brackets_is_curly(xtra_sign_p token)
{
    return token->type == XTRA_SIGN_CURLY;
}

int
xtra_brackets_is_related(xtra_sign_p ltoken, xtra_sign_p rtoken)
{
    return (
           ltoken->type == XTRA_SIGN_SQUARE_L
        && rtoken->type == XTRA_SIGN_SQUARE_R
    ) || (
           ltoken->type == XTRA_SIGN_ROUND_L
        && rtoken->type == XTRA_SIGN_ROUND_R
    ) || (
           ltoken->type == XTRA_SIGN_CURLY_L
        && rtoken->type == XTRA_SIGN_CURLY_R
    ) || (
           ltoken->type == XTRA_SIGN_ANGLE_L
        && rtoken->type == XTRA_SIGN_ANGLE_R
    );
}

enum xtra_sign_e
xtra_bracket_get_brackets(xtra_sign_p token)
{
    if (token->type == XTRA_SIGN_SQUARE_L || token->type == XTRA_SIGN_SQUARE_R) {
        return XTRA_SIGN_SQUARE;
    } else if (token->type == XTRA_SIGN_ROUND_L || token->type == XTRA_SIGN_ROUND_R) {
        return XTRA_SIGN_ROUND;
    } else if (token->type == XTRA_SIGN_CURLY_L || token->type == XTRA_SIGN_CURLY_R) {
        return XTRA_SIGN_CURLY;
    } else {
        return XTRA_SIGN_ANGLE;
    }
}

enum xtra_sign_e
xtra_bracket_get_related(xtra_sign_p token)
{
    if (token->type == XTRA_SIGN_SQUARE_L) {
        return XTRA_SIGN_SQUARE_R;
    } else if (token->type == XTRA_SIGN_ROUND_L) {
        return XTRA_SIGN_ROUND_R;
    } else if (token->type == XTRA_SIGN_CURLY_L) {
        return XTRA_SIGN_CURLY_R;
    } else if (token->type == XTRA_SIGN_ANGLE_L) {
        return XTRA_SIGN_ANGLE_R;
    } else if (token->type == XTRA_SIGN_SQUARE_R) {
        return XTRA_SIGN_SQUARE_L;
    } else if (token->type == XTRA_SIGN_ROUND_R) {
        return XTRA_SIGN_ROUND_L;
    } else if (token->type == XTRA_SIGN_CURLY_R) {
        return XTRA_SIGN_CURLY_L;
    } else if (token->type == XTRA_SIGN_ANGLE_R) {
        return XTRA_SIGN_ANGLE_L;
    }
}

int
xtra_is_brackets(xtra_sign_p token)
{
    return token->type == XTRA_SIGN_SQUARE
       || token->type == XTRA_SIGN_ROUND
       || token->type == XTRA_SIGN_CURLY
       || token->type == XTRA_SIGN_ANGLE;
}
//
// Created by eugen on 5/9/2017.
//

#include "bracket.h"

void
xtra_brackets_join_conditions(xtra_token_p script, long * position)
{
    long start = *position, length;

    xtra_token_p curly = xtra_token_constuct(
            xtra_bracket_get_brackets(script->child[*position])
    );

    while (++(*position) < script->size) {
        if (
            /**
             *
             */
            xtra_bracket_is_left(script->child[*position])
        ) {
            xtra_brackets_join_conditions(script, position);
        } else if (
            /**
             *
             */
            xtra_brackets_is_related(script->child[start], script->child[*position])
        ) {
            /**
             *
             */
            xtra_token_free_child(script, start);
            xtra_token_free_child(script, *position);

            length = *position - start;

            xtra_token_set_parent(curly, script);

            xtra_token_replace_range_by_one(
                    script, start, length, curly
            );

            *position -= (length + 1);

            return;
        } else {
            /**
             *
             */
            xtra_token_add_child(curly, script->child[*position]);
        }
    }
}

int
xtra_bracket_is_left(xtra_token_p token)
{
    return token->type == XTRA_TOKEN_BRACKET_SQUARE_L
           || token->type == XTRA_TOKEN_BRACKET_ROUND_L
           || token->type == XTRA_TOKEN_BRACKET_CURLY_L
           || token->type == XTRA_TOKEN_BRACKET_ANGLE_L;
}

int
xtra_bracket_is_right(xtra_token_p token)
{
    return token->type == XTRA_TOKEN_BRACKET_SQUARE_R
           || token->type == XTRA_TOKEN_BRACKET_ROUND_R
           || token->type == XTRA_TOKEN_BRACKET_CURLY_R
           || token->type == XTRA_TOKEN_BRACKET_ANGLE_R;
}

int
xtra_brackets_is_curly(xtra_token_p token)
{
    return token->type == XTRA_TOKEN_BRACKET_CURLY;
}

int
xtra_brackets_is_related(xtra_token_p ltoken, xtra_token_p rtoken)
{
    return (
           ltoken->type == XTRA_TOKEN_BRACKET_SQUARE_L
        && rtoken->type == XTRA_TOKEN_BRACKET_SQUARE_R
    ) || (
           ltoken->type == XTRA_TOKEN_BRACKET_ROUND_L
        && rtoken->type == XTRA_TOKEN_BRACKET_ROUND_R
    ) || (
           ltoken->type == XTRA_TOKEN_BRACKET_CURLY_L
        && rtoken->type == XTRA_TOKEN_BRACKET_CURLY_R
    ) || (
           ltoken->type == XTRA_TOKEN_BRACKET_ANGLE_L
        && rtoken->type == XTRA_TOKEN_BRACKET_ANGLE_R
    );
}

enum xtra_token_type
xtra_bracket_get_brackets(xtra_token_p token)
{
    if (token->type == XTRA_TOKEN_BRACKET_SQUARE_L || token->type == XTRA_TOKEN_BRACKET_SQUARE_R) {
        return XTRA_TOKEN_BRACKET_SQUARE;
    } else if (token->type == XTRA_TOKEN_BRACKET_ROUND_L || token->type == XTRA_TOKEN_BRACKET_ROUND_R) {
        return XTRA_TOKEN_BRACKET_ROUND;
    } else if (token->type == XTRA_TOKEN_BRACKET_CURLY_L || token->type == XTRA_TOKEN_BRACKET_CURLY_R) {
        return XTRA_TOKEN_BRACKET_CURLY;
    } else {
        return XTRA_TOKEN_BRACKET_ANGLE;
    }
}

enum xtra_token_type
xtra_bracket_get_related(xtra_token_p token)
{
    if (token->type == XTRA_TOKEN_BRACKET_SQUARE_L) {
        return XTRA_TOKEN_BRACKET_SQUARE_R;
    } else if (token->type == XTRA_TOKEN_BRACKET_ROUND_L) {
        return XTRA_TOKEN_BRACKET_ROUND_R;
    } else if (token->type == XTRA_TOKEN_BRACKET_CURLY_L) {
        return XTRA_TOKEN_BRACKET_CURLY_R;
    } else if (token->type == XTRA_TOKEN_BRACKET_ANGLE_L) {
        return XTRA_TOKEN_BRACKET_ANGLE_R;
    } else if (token->type == XTRA_TOKEN_BRACKET_SQUARE_R) {
        return XTRA_TOKEN_BRACKET_SQUARE_L;
    } else if (token->type == XTRA_TOKEN_BRACKET_ROUND_R) {
        return XTRA_TOKEN_BRACKET_ROUND_L;
    } else if (token->type == XTRA_TOKEN_BRACKET_CURLY_R) {
        return XTRA_TOKEN_BRACKET_CURLY_L;
    } else if (token->type == XTRA_TOKEN_BRACKET_ANGLE_R) {
        return XTRA_TOKEN_BRACKET_ANGLE_L;
    }
}

int
xtra_is_brackets(xtra_token_p token)
{
    return token->type == XTRA_TOKEN_BRACKET_SQUARE
       || token->type == XTRA_TOKEN_BRACKET_ROUND
       || token->type == XTRA_TOKEN_BRACKET_CURLY
       || token->type == XTRA_TOKEN_BRACKET_ANGLE;
}
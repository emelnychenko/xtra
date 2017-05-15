//
// Created by em on 5/9/17.
//

#include "if.h"

int
xtra_if_join_elseif(xtra_token_p script, long * position)
{
    long this = *position, next = *position + 1;

    if (
           xtra_token_child_exists(script, next)
        && xtra_token_is_type_on_position(script, this, XTRA_TOKEN_ELSE)
        && xtra_token_is_type_on_position(script, next, XTRA_TOKEN_IF)
    ) {
        xtra_token_free_child(script, this);
        xtra_token_free_child(script, next);

        --(*position);

        xtra_arry_free(
                xtra_arry_vsplice(
                        script->child,
                        this,
                        2,
                        1,
                        xtra_token_constuct(XTRA_TOKEN_ELSEIF)
                )
        );

        script->size = script->child->len;

        return 1;
    }

    return 0;
}

void
xtra_parser_if_condition(xtra_token_p script, long * position)
{
    if (script->size <= (*position + 2)) {
        // error condition
        xtra_error("Unexpected end of file in \"if\".", 0);
    }

    if (xtra_bracket_is_left((xtra_token_p) xtra_arry_get(script->child, *position + 1))) {
        ++(*position);
        xtra_brackets_join_conditions(script, position);
    }

    if (((xtra_token_p) xtra_arry_get(script->child, ++(*position)))->type != XTRA_TOKEN_BRACKET_ROUND) { // condition
        // error condition
        xtra_error("Missed \"([code])\" condition in \"if\".", 0);
    }

    if (xtra_bracket_is_left((xtra_token_p) xtra_arry_get(script->child, *position + 1))) {
        ++(*position);
        xtra_brackets_join_conditions(script, position);
    }

    if (((xtra_token_p) xtra_arry_get(script->child, ++(*position)))->type != XTRA_TOKEN_BRACKET_CURLY) { // condition
        // error condition
        xtra_error("Missed \"{[code]}\" condition in \"if\".", 0);
    }

    // go into do condition
    xtra_parser_circle(
            (xtra_token_p) xtra_arry_get(script->child, *position)
    );

    long _position = *position + 1;
    xtra_if_join_elseif(script, &_position);

    if (((xtra_token_p) xtra_arry_get(script->child, *position + 1))->type == XTRA_TOKEN_ELSEIF) {
        // else if condition
        ++(*position);
        xtra_parser_elseif_condition(
                script, position
        );
    }

    if (((xtra_token_p) xtra_arry_get(script->child, *position + 1))->type != XTRA_TOKEN_ELSE) {
        // over condition
        return;
    }

    ++(*position);

    if (xtra_bracket_is_left((xtra_token_p) xtra_arry_get(script->child, *position + 1))) {
        ++(*position);
        xtra_brackets_join_conditions(script, position);
    }

    if (((xtra_token_p) xtra_arry_get(script->child, ++(*position)))->type != XTRA_TOKEN_BRACKET_CURLY) { // condition
        // error condition
        xtra_error("Missed \"{[code]}\" condition after \"else\".", 0);
    }

    // go into do condition
    xtra_parser_circle((xtra_token_p) xtra_arry_get(script->child, *position));
}

void
xtra_parser_elseif_condition(xtra_token_p script, long * position)
{
    if (script->size <= ((*position) + 2)) {
        // error condition
        xtra_error("Unexpected end of file after \"elseif\".", 0);
    }

    if (xtra_bracket_is_left((xtra_token_p) xtra_arry_get(script->child, *position + 1))) {
        ++(*position);
        xtra_brackets_join_conditions(script, position);
    }

    if (((xtra_token_p) xtra_arry_get(script->child, ++(*position)))->type != XTRA_TOKEN_BRACKET_ROUND) { // condition
        // error condition
        xtra_error("Missed \"([code])\" condition after \"elseif\".", 0);
    }

    if (xtra_bracket_is_left((xtra_token_p) xtra_arry_get(script->child, *position + 1))) {
        ++(*position);
        xtra_brackets_join_conditions(script, position);
    }

    if (((xtra_token_p) xtra_arry_get(script->child, ++(*position)))->type != XTRA_TOKEN_BRACKET_CURLY) { // condition
        // error condition
        xtra_error("Missed \"{[code]}\" condition after \"elseif\".", 0);
    }

    // go into {} condition
    xtra_parser_circle((xtra_token_p) xtra_arry_get(script->child, *position));

    long _position = *position + 1;
    xtra_if_join_elseif(script, &_position);

    if (((xtra_token_p) xtra_arry_get(script->child, *position + 1))->type == XTRA_TOKEN_ELSEIF) { // condition
        // recursion
        xtra_parser_elseif_condition(
                script, position
        );
    }
}
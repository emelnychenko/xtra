//
// Created by em on 5/9/17.
//

#include "if.h"

void
xtra_parser_if_condition(xtra_token_p script, long * position)
{
    xtra_token_p token = script->child[*position];

    if (token->type != XTRA_TOKEN_IF) {
        // just ignore
        return;
    }

    if (script->size < (*position + 2)) {
        // error condition
        xtra_error("Unexpected end of file in \"if\".", 0);
    }

    if (script->child[++(*position)]->type != XTRA_TOKEN_BRACKET_ROUND) { // condition
        // error condition
        xtra_error("Missed \"([code])\" condition in \"if\".", 0);
    }

    if (script->child[++(*position)]->type != XTRA_TOKEN_BRACKET_CURLY) { // condition
        // error condition
        xtra_error("Missed \"{[code]}\" condition in \"if\".", 0);
    }

    // go into do condition
    xtra_parser_circle(token->child[*position]);

    if (script->child[*position + 1]->type == XTRA_TOKEN_ELSEIF) {
        // else if condition
        xtra_parser_elseif_condition(
                script, position
        );
    }

    if (script->child[*position + 1]->type != XTRA_TOKEN_ELSE) {
        // over condition
        return;
    }

    printf("> \n");

    ++(*position);

    if (script->child[++(*position)]->type != XTRA_TOKEN_BRACKET_CURLY) { // condition
        // error condition
        xtra_error("Missed \"{[code]}\" condition in \"else\".", 0);
    }

    // go into do condition
    xtra_parser_circle(token->child[*position]);
}

void
xtra_parser_elseif_condition(xtra_token_p script, long * position)
{
    xtra_token_p token = script->child[*position];

    if (token->type != XTRA_TOKEN_ELSEIF) {
        return; // ignore
    }

    if (script->size < ((*position) + 2)) {
        // error condition
        xtra_error("Unexpected end of file in \"elseif\".", 0);
    }

    if (script->child[++(*position)]->type != XTRA_TOKEN_BRACKET_ROUND) { // condition
        // error condition
        xtra_error("Missed \"([code])\" condition in \"elseif\".", 0);
    }

    if (script->child[++(*position)]->type != XTRA_TOKEN_BRACKET_CURLY) { // condition
        // error condition
        xtra_error("Missed \"{[code]}\" condition in \"elseif\".", 0);
    }

    // go into {} condition
    xtra_parser_circle(token->child[*position]);

    if (script->child[*position + 1]->type == XTRA_TOKEN_ELSEIF) { // condition
        // recursion
        xtra_parser_logical_condition_elseif(
                script, position
        );
    }
}
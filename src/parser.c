//
// Created by eugen on 5/6/2017.
//

#include "parser.h"

void
xtra_parser_brackets_exchage(xtra_parser_brackets_p brackets, xtra_token_p token)
{
    enum xtra_token_type type = token->type;

    if (type == XTRA_TOKEN_BRACKET_SQUARE_L) {
        brackets->square++;
    } else if (type == XTRA_TOKEN_BRACKET_SQUARE_R) {
        brackets->square--;
    } else if (type == XTRA_TOKEN_BRACKET_ROUND_L) {
        brackets->round++;
    } else if (type == XTRA_TOKEN_BRACKET_ROUND_R) {
        brackets->round--;
    } else if (type == XTRA_TOKEN_BRACKET_CURLY_L) {
        brackets->curly++;
    } else if (type == XTRA_TOKEN_BRACKET_CURLY_R) {
        brackets->curly--;
    } else if (type == XTRA_TOKEN_BRACKET_ANGLE_L) {
        brackets->angle++;
    } else if (type == XTRA_TOKEN_BRACKET_ANGLE_R) {
        brackets->angle--;
    } else if (type == XTRA_TOKEN_UNALLOWED) {
        brackets->unallowed++;
    }
}

void
xtra_parser_circle(xtra_token_p script)
{
    long position = -1;

    while (++position < script->size)  {
        if (script->child[position]->type == XTRA_TOKEN_BRACKET_CURLY) {
            // go deeper
            xtra_parser_circle(script->child[position]);
        }

        if (script->child[position]->type == XTRA_TOKEN_FOR) {
            // for confidition
            xtra_parser_for_condition(script, &position);
        } else if (script->child[position]->type == XTRA_TOKEN_DO) {
            // for confidition
            xtra_parser_do_condition(script, &position);
        } else if (script->child[position]->type == XTRA_TOKEN_WHILE) {
            // for confidition
            xtra_parser_while_condition(script, &position);
        }
    }
}

void
xtra_parser_check(xtra_token_p script)
{
    xtra_parser_brackets_t brackets = {0, 0, 0, 0, 0};
    // brackets open close

    // global rule checker
    long iterator = -1;
    while(++iterator < script->size) {
        xtra_token_p token = script->child[iterator];
        xtra_parser_brackets_exchage(&brackets, token);
    }

    if (brackets.square != 0) {
        char * error = (char *) malloc(sizeof(char));
        sprintf(error, "error: \"%s\" missed.\n", brackets.square > 0 ? "]" : "[");
        xtra_error(error, 1);
    }

    if (brackets.round != 0) {
        char * error = (char *) malloc(sizeof(char));
        sprintf(error, "error: \"%s\" missed.\n", brackets.round > 0 ? ")" : "(");
        xtra_error(error, 1);
    }

    if (brackets.curly != 0) {
        char * error = (char *) malloc(sizeof(char));
        sprintf(error, "error: \"%s\" missed.\n", brackets.curly > 0 ? "}" : "{");
        xtra_error(error, 1);
    }

    if (brackets.angle != 0) {
        char * error = (char *) malloc(sizeof(char));
        sprintf(error, "error: \"%s\" missed.\n", brackets.angle > 0 ? "<" : ">");
        xtra_error(error, 1);
    }

//    if (brackets.unallowed != 0) {
//        char * error = (char *) malloc(sizeof(char));
//        sprintf(error, "error: \"%d\" unallowed.\n", brackets.unallowed);
//        xtra_error(error, 0);
//    }

    // condition logical condition
    xtra_parser_normalize_condition(script);

    // condition logical condition
    xtra_parser_logical_condition(script);
    xtra_parser_circle(script);
}

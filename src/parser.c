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

    if (brackets->square < 0) {
        char * error = (char *) malloc(sizeof(char));
        sprintf(error, "Redundant bracket \"]\" in %s on %lu line %lu column", token->__file, token->__line, token->__column);
        xtra_error(error, 1);
    } else if (brackets->round < 0) {
        char * error = (char *) malloc(sizeof(char));
        sprintf(error, "Redundant bracket \")\" in %s on %lu line %lu column", token->__file, token->__line, token->__column);
        xtra_error(error, 1);
    } else if (brackets->curly < 0) {
        char * error = (char *) malloc(sizeof(char));
        sprintf(error, "Redundant bracket \"}\" in %s on %lu line %lu column", token->__file, token->__line, token->__column);
        xtra_error(error, 1);
    } else if (brackets->angle < 0) {
        char * error = (char *) malloc(sizeof(char));
        sprintf(error, "Redundant bracket \">\" in %s on %lu line %lu column", token->__file, token->__line, token->__column);
        xtra_error(error, 1);
    }
}

void
xtra_parser_circle(xtra_token_p script)
{
    long position = -1;

    // printf("> script %d\n", script->size);

    while (++position < script->size)  {
        xtra_token_p token = (xtra_token_p) xtra_arry_get(script->child, position);

        if (xtra_brackets_is_curly(token) == 1) {
            /**
             *  Go into {}
             *
             *  @recursion
             */
            xtra_parser_circle(token);
        } else if (xtra_if_join_elseif(script, &position) == 1) {
            /**
             *  Convertation "else if" to "elseif"
             *
             *  @silence
             */
        } else if (xtra_bracket_is_left(token) == 1) {
            /**
             *  Convertation "{" and "}" to "{}"
             *
             *  @silence
             */
            xtra_brackets_join_conditions(script, &position);
            // open-close
        } else if (token->type == XTRA_TOKEN_IF) {
            xtra_parser_if_condition(script, &position);
        } else if (token->type == XTRA_TOKEN_FOR) {
            xtra_parser_for_condition(script, &position);
        } else if (token->type == XTRA_TOKEN_DO) {
            /**
             *  Convertation "do {} while ()" to "while () {}"
             *
             *  @silence
             */
            xtra_do_condition_replace(script, &position);
        } else if (token->type == XTRA_TOKEN_WHILE) {
            xtra_parser_while_condition(script, &position);
        } else {
            // other condition
        }

//        if (script->child[position]->type == XTRA_TOKEN_FOR) {
//            // for confidition
//            xtra_parser_for_condition(script, &position);
//        } else if (script->child[position]->type == XTRA_TOKEN_DO) {
//            // for confidition
//            xtra_parser_do_condition(script, &position);
//        } else if (script->child[position]->type == XTRA_TOKEN_WHILE) {
//            // for confidition
//            xtra_parser_while_condition(script, &position);
//        } else if (script->child[position]->type == XTRA_TOKEN_IF) {
//            // if confidition
//            printf("> if \n");
//            xtra_parser_if_condition(script, &position);
//        }
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
        xtra_token_p token = (xtra_token_p) xtra_arry_get(script->child, iterator);
        xtra_parser_brackets_exchage(&brackets, token);
    }

    if (brackets.square != 0) {
        char * error = (char *) malloc(sizeof(char));
        sprintf(error, "Unexpected end of file. Bracket \"]\" missed in %s", script->__file);
        xtra_error(error, 6);
    }

    if (brackets.round != 0) {
        char * error = (char *) malloc(sizeof(char));
        sprintf(error, "Unexpected end of file. Bracket \")\" missed in %s", script->__file);
        xtra_error(error, 6);
    }

    if (brackets.curly != 0) {
        char * error = (char *) malloc(sizeof(char));
        sprintf(error, "Unexpected end of file. Bracket \"}\" missed in %s", script->__file);
        xtra_error(error, 6);
    }

    if (brackets.angle != 0) {
        char * error = (char *) malloc(sizeof(char));
        sprintf(error, "Unexpected end of file. Bracket \">\" missed in %s", script->__file);
        xtra_error(error, 1);
    }

//    if (brackets.unallowed != 0) {
//        char * error = (char *) malloc(sizeof(char));
//        sprintf(error, "error: \"%d\" unallowed.\n", brackets.unallowed);
//        xtra_error(error, 0);
//    }

    // condition logical condition
    //xtra_parser_normalize_condition(script);

    // condition logical condition
    xtra_parser_circle(script);
}

//
// Created by eugen on 5/6/2017.
//

#include "parser.h"

void
xtra_parser_brackets_exchage(xtra_parser_brackets_p brackets, xtra_sign_p sign)
{
    enum xtra_sign_e type = sign->type;

    if (type == XTRA_SIGN_BRACKET_SQUARE_L) {
        brackets->square++;
    } else if (type == XTRA_SIGN_BRACKET_SQUARE_R) {
        brackets->square--;
    } else if (type == XTRA_SIGN_BRACKET_ROUND_L) {
        brackets->round++;
    } else if (type == XTRA_SIGN_BRACKET_ROUND_R) {
        brackets->round--;
    } else if (type == XTRA_SIGN_BRACKET_CURLY_L) {
        brackets->curly++;
    } else if (type == XTRA_SIGN_BRACKET_CURLY_R) {
        brackets->curly--;
    } else if (type == XTRA_SIGN_BRACKET_ANGLE_L) {
        brackets->angle++;
    } else if (type == XTRA_SIGN_BRACKET_ANGLE_R) {
        brackets->angle--;
    } else if (type == XTRA_SIGN_UNALLOWED) {
        brackets->unallowed++;
    }

    if (brackets->square < 0) {
//        char * error = (char *) malloc(sizeof(char));
//        sprintf(error, "Redundant bracket \"]\" in %s on %lu line %lu column", token->__file, token->__line, token->__column);
        xtra_error("Redundant bracket \"]\"", 1);
    } else if (brackets->round < 0) {
//        char * error = (char *) malloc(sizeof(char));
//        sprintf(error, "Redundant bracket \")\" in %s on %lu line %lu column", token->__file, token->__line, token->__column);
        xtra_error("Redundant bracket \")\"", 1);
    } else if (brackets->curly < 0) {
//        char * error = (char *) malloc(sizeof(char));
//        sprintf(error, "Redundant bracket \"}\" in %s on %lu line %lu column", token->__file, token->__line, token->__column);
        xtra_error("Redundant bracket \"}\"", 1);
    } else if (brackets->angle < 0) {
//        char * error = (char *) malloc(sizeof(char));
//        sprintf(error, "Redundant bracket \">\" in %s on %lu line %lu column", token->__file, token->__line, token->__column);
        xtra_error("Redundant bracket \">\"", 1);
    }
}

void
xtra_parser_circle(xtra_sign_p sign)
{
    long position = -1;

    // printf("> script %d\n", script->size);

    while (++position < xtra_sign_arry_len(sign))  {
        xtra_sign_p _sign = xtra_sign_arry_get(sign, position);

        if (xtra_brackets_is_curly(_sign) == 1) {
            /**
             *  Go into {}
             *
             *  @recursion
             */
            xtra_parser_circle(_sign);
        } else if (xtra_if_join_elseif(sign, &position) == 1) {
            /**
             *  Convertation "else if" to "elseif"
             *
             *  @silence
             */
        } else if (xtra_bracket_is_left(_sign) == 1) {
            /**
             *  Convertation "{" and "}" to "{}"
             *
             *  @silence
             */
            xtra_brackets_join_conditions(sign, &position);
            // open-close
        } else if (_sign->type == XTRA_SIGN_IF) {
            xtra_if_parse(sign, &position);
        } else if (_sign->type == XTRA_SIGN_FOR) {
            xtra_for_parse(sign, &position);
        } else if (_sign->type == XTRA_SIGN_DO) {
            /**
             *  Convertation "do {} while ()" to "while () {}"
             *
             *  @silence
             */
            xtra_do_parse(sign, &position);
        } else if (_sign->type == XTRA_SIGN_WHILE) {
            xtra_while_parse(sign, &position);
        } else if (_sign->type == XTRA_SIGN_SWITCH) {
            xtra_switch_parse(sign, &position);
        } else {
            // other condition
        }

//        if (script->child[position]->type == XTRA_SIGN_FOR) {
//            // for confidition
//            xtra_parser_for_condition(script, &position);
//        } else if (script->child[position]->type == XTRA_SIGN_DO) {
//            // for confidition
//            xtra_parser_do_condition(script, &position);
//        } else if (script->child[position]->type == XTRA_SIGN_WHILE) {
//            // for confidition
//            xtra_parser_while_condition(script, &position);
//        } else if (script->child[position]->type == XTRA_SIGN_IF) {
//            // if confidition
//            printf("> if \n");
//            xtra_parser_if_condition(script, &position);
//        }
    }
}

void
xtra_parser_check(xtra_sign_p sign)
{
    xtra_parser_brackets_t brackets = {0, 0, 0, 0, 0};
    // brackets open close

    // global rule checker
    long iterator = -1;
    while(++iterator < xtra_sign_arry_len(sign)) {
        xtra_parser_brackets_exchage(&brackets, xtra_sign_arry_get(sign, iterator));
    }

    if (brackets.square != 0) {
//        char * error = (char *) malloc(sizeof(char));
//        sprintf(error, "Unexpected end of file. Bracket \"]\" missed in %s", sign->__file);
        xtra_error("Unexpected end of file. Bracket \"]\"", 6);
    }

    if (brackets.round != 0) {
//        char * error = (char *) malloc(sizeof(char));
//        sprintf(error, "Unexpected end of file. Bracket \")\" missed in %s", sign->__file);
        xtra_error("Unexpected end of file. Bracket \")\"", 6);
    }

    if (brackets.curly != 0) {
//        char * error = (char *) malloc(sizeof(char));
//        sprintf(error, "Unexpected end of file. Bracket \"}\" missed in %s", sign->__file);
        xtra_error("Unexpected end of file. Bracket \"}\"", 6);
    }

    if (brackets.angle != 0) {
//        char * error = (char *) malloc(sizeof(char));
//        sprintf(error, "Unexpected end of file. Bracket \">\" missed in %s", sign->__file);
        xtra_error("Unexpected end of file. Bracket \">\"", 1);
    }

//    if (brackets.unallowed != 0) {
//        char * error = (char *) malloc(sizeof(char));
//        sprintf(error, "error: \"%d\" unallowed.\n", brackets.unallowed);
//        xtra_error(error, 0);
//    }

    // condition logical condition
    //xtra_parser_normalize_condition(script);

    // condition logical condition
    xtra_parser_circle(sign);
}

//
// Created by eugen on 5/8/2017.
//

#include "logical.h"

/**
 * fixme: ppd condition missed.
 */

void
xtra_parser_logical_condition(xtra_token_p script)
{
    xtra_parser_logical_condition_if_iterate(
            script
    );

    // xtra_parser_logical_condition_switch_iterate(
    //         script
    // );

//    xtra_parser_logical_condition_ternary_iterate(
//            script
//    );
}

void
xtra_parser_logical_condition_if_iterate(xtra_token_p script)
{
    enum xtra_token_type type;
    xtra_token_p token;
    long position = -1;

    // if
    while (++position < script->size)  {
        token = script->child[position];
        type  = token->type;

        if (type == XTRA_TOKEN_BRACKET_CURLY) {
            // go deeper
            xtra_parser_logical_condition_if_iterate(token);
        }

        if (type == XTRA_TOKEN_IF) {
            // if confidition

            xtra_parser_logical_condition_if(
                    script, &position
            );
        }
    }
}
/**
 *  Normalization of short condition (single line)
 *
 *  if (condition)
 *      if (condition)
 *          if (condition)
 *              for (;;)
 *                  do {} while()
 *           else
 *              while() {}
 *
 *
 *
 */
void
xtra_parser_logical_condition_if(xtra_token_p script, long * position)
{
    xtra_token_p token = script->child[*position];

    if (token->type != XTRA_TOKEN_IF) {
        // just ignore
        return;
    }

    if (script->child[++(*position)]->type != XTRA_TOKEN_BRACKET_ROUND) { // condition
        // error of execution
    }

    if (script->child[++(*position)]->type != XTRA_TOKEN_BRACKET_CURLY) { // condition
        // error of execution
    }

    xtra_parser_logical_condition_if_iterate(script->child[*position]);
    // move into curly condition
//    xtra_parser_condition_curly(
//            script, position
//    );

    token = script->child[*position + 1];

    if (token->type == XTRA_TOKEN_ELSEIF) {
        // else if condition
        xtra_parser_logical_condition_elseif(
                script, position
        );
    }

    if (token->type != XTRA_TOKEN_ELSE) {
        // over condition
        return;
    }

    if (script->child[++(*position)]->type != XTRA_TOKEN_BRACKET_CURLY) { // condition
        // error of execution
    }

    xtra_parser_logical_condition_if_iterate(script->child[*position]);

//    xtra_parser_condition_curly(
//            script, position
//    );
}

void
xtra_parser_logical_condition_elseif(xtra_token_p script, long * position)
{
    xtra_token_p token = script->child[*position];

    if (token->type != XTRA_TOKEN_ELSEIF) {
        return;
    }

    if (script->size < ((*position) + 2)) {
        // expression error
        return;
    }

    token = script->child[++(*position)];

    if (token->type != XTRA_TOKEN_BRACKET_ROUND) { // condition
        // expression error
        return;
    }

    if (script->child[++(*position)]->type != XTRA_TOKEN_BRACKET_CURLY) { // condition
        // error of execution
        return;
    }

    xtra_parser_logical_condition_if_iterate(script->child[*position]);

//    // move into curly condition
//    xtra_parser_condition_curly(
//            script, position
//    );

    // recursion
    xtra_parser_logical_condition_elseif(
            script, position
    );

    return;
    // go out
}

// void
// xtra_parser_logical_condition_switch_iterate(xtra_token_p script)
// {
//     enum xtra_token_type type;
//     xtra_token_p token;
//     long position = -1;
//
//     // if
//     while (++position < script->size)  {
//         token = script->child[position];
//         type  = token->type;
//
//         if (type == XTRA_TOKEN_BRACKET_CURLY) {
//             // go deeper
//             xtra_parser_logical_condition_switch_iterate(token);
//         }
//
//         if (type == XTRA_TOKEN_SWITCH) {
//             // switch condition
//
//             xtra_parser_logical_condition_switch(
//                     script, &position
//             );
//         }
//     }
// }
//
// void
// xtra_parser_logical_condition_switch(xtra_token_p script, long * position)
// {
//     xtra_token_p token = script->child[*position];
//
//     if (token->type != XTRA_TOKEN_SWITCH) {
//         // just ignore
//         return;
//     }
//
//     if (script->child[++(*position)]->type != XTRA_TOKEN_BRACKET_ROUND) { // condition
//         // error of execution
//     }
//
//     if (script->child[++(*position)]->type != XTRA_TOKEN_BRACKET_CURLY) { // condition
//         // error of execution
//     }
//
//     xtra_parser_logical_condition_switch_case(script->child[*position]);
// }
//
// void
// xtra_parser_logical_condition_switch_case(xtra_token_p script)
// {
//     long position = -1;
//
//     while (++position < script->size) {
//         // case "": default: ""
//         //
//         // iterate cases
//     }
// }

//void
//xtra_parser_logical_condition_ternary_iterate(xtra_token_p script)
//{
//    enum xtra_token_type type;
//    xtra_token_p token;
//    long position = -1;
//
//    // ternary
//    while (++position < script->size)  {
//        token = script->child[position];
//        type  = token->type;
//
//        if (
//                type == XTRA_TOKEN_BRACKET_CURLY
//                || type == XTRA_TOKEN_BRACKET_SQUARE
//                || type == XTRA_TOKEN_BRACKET_ANGLE
//                || type == XTRA_TOKEN_BRACKET_ROUND
//        ) {
//            // go deeper
//            xtra_parser_logical_condition_ternary_iterate(token);
//        }
//
////        if (type == XTRA_TOKEN_IF) {
////            // if confidition
////
////            xtra_parser_logical_condition_if(
////                    script, &position
////            );
////        }
//    }
//}

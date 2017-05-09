//
// Created by eugen on 5/8/2017.
//

#include "normalize.h"

void
xtra_parser_normalize_condition(xtra_token_p script)
{
    xtra_parser_normalize_condition_elseif(
            script
    );

    xtra_parser_normalize_condition_brackets(
            script
    );

    xtra_parser_normalize_condition_curlies(
            script
    );
}

// else if => elseif
void
xtra_parser_normalize_condition_elseif(xtra_token_p script)
{
    long position = -1;
    while(++position < script->size) {
        if (
                script->child[position]->type == XTRA_TOKEN_ELSE
                && (position + 1) < script->size
                && script->child[position + 1]->type == XTRA_TOKEN_IF
                ) {
            long start = position;

            xtra_token_p _token = xtra_token_constuct(XTRA_TOKEN_ELSEIF);

            position--;

            // replace condition
            xtra_token_replace_range_by_one(
                    script, start, 1, _token
            );
        }
    }
}

void
xtra_parser_normalize_condition_brackets(xtra_token_p script)
{
    long position = -1;
    while(++position < script->size) {
        xtra_token_p token = script->child[position];
        enum xtra_token_type type = token->type;

        if (
                type == XTRA_TOKEN_BRACKET_SQUARE_L
                || type == XTRA_TOKEN_BRACKET_ROUND_L
                || type == XTRA_TOKEN_BRACKET_CURLY_L
                || type == XTRA_TOKEN_BRACKET_ANGLE_L
                ) {
            long start = position;

            xtra_token_p _token = xtra_parser_normalize_condition_bracket_pair(
                    script, &position
            );

            long length = position - start;

            position -= length;

            // replace condition
            xtra_token_replace_range_by_one(
                    script, start, length, _token
            );
        }
    }
}

xtra_token_p
xtra_parser_normalize_condition_bracket_pair(xtra_token_p script, long *position)
{
    enum xtra_token_type type = script->child[*position]->type;


        enum xtra_token_type qtype = type;
        enum xtra_token_type rtype;

        if (type == XTRA_TOKEN_BRACKET_SQUARE_L) {
            rtype = XTRA_TOKEN_BRACKET_SQUARE;
        } else if (type == XTRA_TOKEN_BRACKET_ROUND_L) {
            rtype = XTRA_TOKEN_BRACKET_ROUND;
        } else if (type == XTRA_TOKEN_BRACKET_ANGLE_L) {
            rtype = XTRA_TOKEN_BRACKET_ANGLE;
        } else {
            rtype = XTRA_TOKEN_BRACKET_CURLY;
        }

        xtra_token_p _script = xtra_token_constuct(rtype);
        // create bracket condition and check child bracket

        // forget open bracket
        xtra_token_forget(script->child[*position]);
        while(++(*position) < script->size) {
            enum xtra_token_type _type = script->child[*position]->type;

            if (
                    _type == XTRA_TOKEN_BRACKET_SQUARE_L
                    || _type == XTRA_TOKEN_BRACKET_ROUND_L
                    || _type == XTRA_TOKEN_BRACKET_CURLY_L
                    || _type == XTRA_TOKEN_BRACKET_ANGLE_L
                    ) {
                // subtoken
                xtra_token_add_child(
                        _script, xtra_parser_normalize_condition_bracket_pair(script, position)
                );
            } else if (
                    (qtype == XTRA_TOKEN_BRACKET_SQUARE_L && _type == XTRA_TOKEN_BRACKET_SQUARE_R)
                    || (qtype == XTRA_TOKEN_BRACKET_ROUND_L && _type == XTRA_TOKEN_BRACKET_ROUND_R)
                    || (qtype == XTRA_TOKEN_BRACKET_CURLY_L && _type == XTRA_TOKEN_BRACKET_CURLY_R)
                    || (qtype == XTRA_TOKEN_BRACKET_ANGLE_L && _type == XTRA_TOKEN_BRACKET_ANGLE_R)
                    ) {
                // forget close bracket
                xtra_token_forget(script->child[*position]);
                // close token and export
                return _script;
            } else {
                xtra_token_add_child(
                        _script, script->child[*position]
                );
                // append token into
            }
        }

    // error
    // close token and export
    return _script;
}

void
xtra_parser_normalize_condition_curlies(xtra_token_p script)
{
    long position = -1;

    while(++position < script->size) {
        // while iterate whole script
        // when keyword
        enum xtra_token_type type = script->child[position]->type;

        if (type == XTRA_TOKEN_BRACKET_CURLY) {
            // iterate one more time
            xtra_parser_normalize_condition_curlies(
                    script->child[position]
            );
        } else if (type == XTRA_TOKEN_IF) {
            // if () {}
            if (script->child[++position]->type != XTRA_TOKEN_BRACKET_ROUND) {
                // error: invalid expression
            }

            // {}
            xtra_parser_normalize_condition_curly(
                    script, &position
            );
        } else if (type == XTRA_TOKEN_ELSEIF) {
            // elseif () {}
            if (script->child[++position]->type != XTRA_TOKEN_BRACKET_ROUND) {
                // error: invalid expression
            }

            // {}
            xtra_parser_normalize_condition_curly(
                    script, &position
            );
        } else if (type == XTRA_TOKEN_ELSE) {
            // else
            // {}
            xtra_parser_normalize_condition_curly(
                    script, &position
            );
        } else if (type == XTRA_TOKEN_SWITCH) {
            // switch () {}
            if (script->child[++position]->type != XTRA_TOKEN_BRACKET_ROUND) {
                // error: invalid expression
            }

            // {}
            xtra_parser_normalize_condition_curly(
                    script, &position
            );
        } else if (type == XTRA_TOKEN_FOR) {
            // for () {}
            if (script->child[++position]->type != XTRA_TOKEN_BRACKET_ROUND) {
                // error: invalid expression
            }

            // {}
            xtra_parser_normalize_condition_curly(
                    script, &position
            );
        } else if (type == XTRA_TOKEN_EACH) {
            // each () {}
            if (script->child[++position]->type != XTRA_TOKEN_BRACKET_ROUND) {
                // error: invalid expression
            }

            // {}
            xtra_parser_normalize_condition_curly(
                    script, &position
            );
        } else if (type == XTRA_TOKEN_FOREACH) {
            // foreach () {}
            if (script->child[++position]->type != XTRA_TOKEN_BRACKET_ROUND) {
                // error: invalid expression
            }

            // {}
            xtra_parser_normalize_condition_curly(
                    script, &position
            );
        } else if (type == XTRA_TOKEN_DO) {
            // do {} while ()

            // {}
            xtra_parser_normalize_condition_curly(
                    script, &position
            );

            if (script->child[++position]->type != XTRA_TOKEN_WHILE) {
                // error: invalid expression
            }

            if (script->child[++position]->type != XTRA_TOKEN_BRACKET_ROUND) {
                // error: invalid expression
            }
        } else if (type == XTRA_TOKEN_WHILE) {
            // while () {}
            if (script->child[++position]->type != XTRA_TOKEN_BRACKET_ROUND) {
                // error: invalid expression
            }

            // {}
            xtra_parser_normalize_condition_curly(
                    script, &position
            );
        }
    }
}

void
xtra_parser_normalize_condition_curly(xtra_token_p script, long * position)
{
    if (script->child[*position]->type == XTRA_TOKEN_BRACKET_CURLY) {
        // iterate one more time
        xtra_parser_normalize_condition_curlies(
                script->child[*position]
        );
    } else {
        long start = *position;
        xtra_token_p _script = xtra_token_constuct(XTRA_TOKEN_BRACKET_CURLY);

        while(++(*position) < script->size) {
            // subtoken
            xtra_token_add_child(_script, script->child[*position]);

            if (script->child[*position]->type == XTRA_TOKEN_SEMICOLON) {
                // end of expression include in
                break;
            }
        }

        if (script->child[*position]->type != XTRA_TOKEN_SEMICOLON) {
            // error end of file execution
        }

        long length = *position - start;

        *position -= length;

        // replace condition
        xtra_token_replace_range_by_one(
                script, start, length, _script
        );

        // iterate one more time
        xtra_parser_normalize_condition_curlies(
                _script
        );
    }
}
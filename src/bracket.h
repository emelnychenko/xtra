//
// Created by eugen on 5/9/2017.
//

#ifndef XTRA_BRACKET_H
#define XTRA_BRACKET_H

#include "token.h"

void
xtra_brackets_join_conditions(xtra_token_p, long *);

int
xtra_bracket_is_left(xtra_token_p);

int
xtra_bracket_is_right(xtra_token_p);

int
xtra_brackets_is_curly(xtra_token_p);

int
xtra_brackets_is_related(xtra_token_p, xtra_token_p);

enum xtra_token_type
xtra_bracket_get_related(xtra_token_p);

int
xtra_is_brackets(xtra_token_p);

#endif //XTRA_BRACKET_H

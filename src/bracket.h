//
// Created by eugen on 5/9/2017.
//

#ifndef XTRA_BRACKET_H
#define XTRA_BRACKET_H

#include "sign.h"

void
xtra_brackets_join_conditions(xtra_sign_p, long *);

int
xtra_bracket_is_left(xtra_sign_p);

int
xtra_bracket_is_right(xtra_sign_p);

int
xtra_brackets_is_curly(xtra_sign_p);

int
xtra_brackets_is_related(xtra_sign_p, xtra_sign_p);

enum xtra_sign_e
xtra_bracket_get_brackets(xtra_sign_p);

enum xtra_sign_e
xtra_bracket_get_related(xtra_sign_p);

int
xtra_is_brackets(xtra_sign_p);

#endif //XTRA_BRACKET_H

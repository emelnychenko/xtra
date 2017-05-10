//
// Created by eugen on 5/8/2017.
//

#ifndef EXTRA_NORMALIZE_H
#define EXTRA_NORMALIZE_H

#include "../xtra.h"
#include "../error.h"

void
xtra_parser_normalize_condition(xtra_token_p);

void
xtra_parser_normalize_condition_elseif(xtra_token_p);

void
xtra_parser_normalize_condition_brackets(xtra_token_p);

xtra_token_p
xtra_parser_normalize_condition_bracket_pair(xtra_token_p, long *);

void
xtra_parser_normalize_condition_curlies(xtra_token_p);

void
xtra_parser_normalize_condition_curly(xtra_token_p, long *);

#endif //EXTRA_NORMALIZE_H

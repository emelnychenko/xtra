//
// Created by eugen on 5/6/2017.
//

#ifndef EXTRA_PARSER_H
#define EXTRA_PARSER_H

#include <stdio.h>
#include <stdlib.h>

#include "error.h"
#include "bracket.h"
#include "if.h"
#include "do.h"
#include "for.h"
#include "while.h"
#include "switch.h"

struct xtra_parser_brackets_s
{
    long square;
    long round;
    long curly;
    long angle;
    long unallowed;
};

typedef struct xtra_parser_brackets_s xtra_parser_brackets_t;
typedef xtra_parser_brackets_t * xtra_parser_brackets_p;

void
xtra_parser_brackets_exchage(xtra_parser_brackets_p, xtra_sign_p);

void
xtra_parser_circle(xtra_sign_p);

void
xtra_parser_check(xtra_sign_p);

void
xtra_parser_condition_normalize(xtra_sign_p, long *);

#endif //EXTRA_PARSER_H

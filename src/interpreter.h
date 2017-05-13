//
// Created by eugen on 5/6/2017.
//

#ifndef EXTRA_INTERPRETER_H
#define EXTRA_INTERPRETER_H

#include <ctype.h>

#include "token.h"
#include "memory.h"
#include "lexer.h"
#include "string.h"
#include "parser.h"

int
xtra_interpreter_eval(char *);

char *
xtra_interpreter_read(char *);

#endif //EXTRA_INTERPRETER_H

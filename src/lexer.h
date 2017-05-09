//
// Created by eugen on 5/6/2017.
//

#ifndef EXTRA_LEXER_H
#define EXTRA_LEXER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "token.h"

xtra_token_p
xtra_lexer_eval(char *, long);

char *
xtra_lexer_keyop(char *, long, long *);

int
xtra_lexer_validate_undefined(char *, long);

int
xtra_lexer_is_int(char *, long);

int
xtra_lexer_is_double(char *, long);

int
xtra_lexer_is_binary(char *, long);

void
xtra_lexer_comment_inline(char *, long *);

void
xtra_lexer_comment_block(char *, long *, long);

char *
xtra_lexer_string(char *, long, long *, char);

char *
xtra_lexer_normalize(char *, long);

int
xtra_lexer_int(char * text);

double
xtra_lexer_double(char * text);

#endif //EXTRA_LEXER_H

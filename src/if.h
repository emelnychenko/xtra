//
// Created by em on 5/9/17.
//

#ifndef XTRA_IF_H
#define XTRA_IF_H

#include "sign.h"
#include "parser.h"
#include "error.h"
#include "bracket.h"

int
xtra_if_join_elseif(xtra_sign_p, long *);

void
xtra_if_parse(xtra_sign_p, long *);

void
xtra_elseif_parse(xtra_sign_p, long *);

#endif //XTRA_IF_H

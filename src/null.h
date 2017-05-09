//
// Created by eugen on 5/1/2017.
//

#ifndef EXTRA_NULL_H
#define EXTRA_NULL_H

#include "var.h"

xtra_var_p
xtra_var_null_construct();

void
xtra_var_null_destruct(xtra_var_p);

int
xtra_var_is_null(xtra_var_p);

#endif //EXTRA_NULL_H

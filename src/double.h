//
// Created by eugen on 5/1/2017.
//

#ifndef EXTRA_DOUBLE_H
#define EXTRA_DOUBLE_H

#include "var.h"

xtra_var_p
xtra_var_double_construct(double);

void
xtra_var_double_destruct(xtra_var_p);

double
xtra_var_double_get(xtra_var_p);

void
xtra_var_double_set(xtra_var_p, double);

int
xtra_var_is_double(xtra_var_p);

xtra_var_p
xtra_var_double_to_int(xtra_var_p);

xtra_var_p
xtra_var_double_to_bool(xtra_var_p);

#endif //EXTRA_DOUBLE_H

//
// Created by eugen on 5/1/2017.
//

#ifndef EXTRA_DOUBLE_H
#define EXTRA_DOUBLE_H

#include "var.h"
#include "bool.h"
#include "int.h"

xtra_var_p
xtra_double(xtra_double_t);

void
xtra_double_destruct(xtra_var_p);

xtra_double_t
xtra_double_get(xtra_var_p);

void
xtra_double_set(xtra_var_p, xtra_double_t);

xtra_var_p
xtra_double_to_int(xtra_var_p);

xtra_var_p
xtra_double_to_bool(xtra_var_p);

#endif //EXTRA_DOUBLE_H

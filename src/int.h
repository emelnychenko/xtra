//
// Created by eugen on 5/1/2017.
//

#ifndef EXTRA_INTEGER_H
#define EXTRA_INTEGER_H

#include "var.h"

xtra_var_p
xtra_int(xtra_int_t);

xtra_int_t
xtra_int_get(xtra_var_p);

void
xtra_int_set(xtra_var_p, xtra_int_t);

xtra_var_p
xtra_int_to_bool(xtra_var_p);

xtra_var_p
xtra_int_to_double(xtra_var_p);

#endif //EXTRA_INTEGER_H

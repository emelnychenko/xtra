//
// Created by eugen on 5/1/2017.
//

#ifndef XTRA_BOOL_H
#define XTRA_BOOL_H

#include "var.h"

xtra_var_p
xtra_bool(xtra_bool_t);

xtra_bool_t
xtra_bool_get(xtra_var_p);

void
xtra_bool_set(xtra_var_p, xtra_bool_t);

xtra_var_p
xtra_bool_to_int(xtra_var_p);

xtra_var_p
xtra_bool_to_double(xtra_var_p);

#endif //XTRA_BOOL_H

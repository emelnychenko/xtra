//
// Created by eugen on 5/1/2017.
//

#include "int.h"

xtra_var_p
xtra_var_int_construct(int val)
{
    xtra_var_p var = xtra_var_contruct(XTRA_VAR_INT);
    var->xtra_var_int = val;
    return var;
}

int
xtra_var_int_get(xtra_var_p var)
{
    return var->xtra_var_int;
}

void
xtra_var_int_set(xtra_var_p var, int val)
{
    var->xtra_var_int = val;
}
//
// Created by eugen on 5/1/2017.
//

#include "bool.h"

xtra_var_p
xtra_var_bool_construct(int val)
{
    xtra_var_p var = xtra_var_contruct(XTRA_VAR_BOOL);
    var->xtra_var_bool = val > 0;
    return var;
}

int
xtra_var_bool_get(xtra_var_p xtra_var)
{
    return xtra_var->xtra_var_bool;
}

void
xtra_var_bool_set(xtra_var_p var, int val)
{
    var->xtra_var_bool = val > 0;
}


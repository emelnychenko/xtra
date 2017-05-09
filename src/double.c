//
// Created by eugen on 5/1/2017.
//

#include "double.h"

xtra_var_p
xtra_var_double_construct(double val)
{
    xtra_var_p var = xtra_var_contruct(XTRA_VAR_DOUBLE);
    var->xtra_var_double = val;
    return var;
}

void
xtra_var_double_destruct(xtra_var_p var)
{
    xtra_var_destruct(var);
}

double
xtra_var_double_get(xtra_var_p var)
{
    return var->xtra_var_double;
}

void
xtra_var_double_set(xtra_var_p var, double val)
{
    var->xtra_var_double = val;
}

int
xtra_var_is_double(xtra_var_p var)
{
    return var->type == XTRA_VAR_DOUBLE;
}

xtra_var_p
xtra_var_double_to_int(xtra_var_p var)
{
    return xtra_var_int_construct(
            (int) var->xtra_var_double
    );
}

xtra_var_p
xtra_var_double_to_bool(xtra_var_p var)
{
    return xtra_var_bool_construct(
            var->xtra_var_double
    );
}

//
// Created by eugen on 5/1/2017.
//

#include "null.h"

xtra_var_p
xtra_var_null_construct()
{
    return xtra_var_contruct(XTRA_VAR_NULL);
}

void
xtra_var_null_destruct(xtra_var_p var)
{
    xtra_var_destruct(var);
}

int
xtra_var_is_null(xtra_var_p var)
{
    var->type == XTRA_VAR_NULL;
}
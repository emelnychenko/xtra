//
// Created by eugen on 5/1/2017.
//

#include "var.h"

xtra_var_p
xtra_var_contruct(enum xtra_var_type type)
{
    xtra_var_p var;

    if (type != XTRA_VAR_NULL) {
        var = malloc(sizeof(xtra_var_p));
    }

    var->type = type;
    return  var;
}

void
xtra_var_destruct(xtra_var_p var)
{
    if (var->type == XTRA_VAR_NULL)
        return;

    free(var);

    var->type = XTRA_VAR_NULL;
}

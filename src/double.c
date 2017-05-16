//
// Created by eugen on 5/1/2017.
//

#include "double.h"

xtra_var_p
xtra_double(xtra_double_t val)
{
    xtra_var_p var = xtra_var(XTRA_VAR_DOUBLE);
    var->d = val;
    return var;
}

xtra_double_t
xtra_double_get(xtra_var_p var) {
    return var->d;
}

void
xtra_double_set(xtra_var_p var, xtra_double_t val) {
    var->d = val;
}

xtra_var_p
xtra_double_to_int(xtra_var_p var) {
    return xtra_int((xtra_int_t) var->d);
}

xtra_var_p
xtra_double_to_bool(xtra_var_p var) {
    return xtra_bool((xtra_bool_t) var->d);
}

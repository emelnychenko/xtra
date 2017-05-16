//
// Created by eugen on 5/1/2017.
//

#include "int.h"

xtra_var_p
xtra_int(xtra_int_t val) {
    xtra_var_p var = xtra_var(XTRA_VAR_INT);
    var->i = val;
    return var;
}

xtra_int_t
xtra_var_int_get(xtra_var_p var) {
    return var->i;
}

void
xtra_var_int_set(xtra_var_p var, xtra_int_t val) {
    var->i = val;
}

xtra_var_p
xtra_int_to_bool(xtra_var_p var) {
    return xtra_bool((xtra_bool_t) var->i);
}

xtra_var_p
xtra_int_to_double(xtra_var_p var) {
    return xtra_double((xtra_double_t) var->i);
}

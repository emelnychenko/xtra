//
// Created by eugen on 5/1/2017.
//

#include "bool.h"

xtra_var_p
xtra_bool(xtra_bool_t val) {
    xtra_var_p var = xtra_var(XTRA_VAR_BOOL);
    var->b = val > 0;
    return var;
}

xtra_bool_t
xtra_bool_get(xtra_var_p xtra_var) {
    return xtra_var->b;
}

void
xtra_bool_set(xtra_var_p var, xtra_bool_t val) {
    var->b = val > 0;
}

xtra_var_p
xtra_bool_to_int(xtra_var_p var) {
    return xtra_int((xtra_int_t) var->b);
}

xtra_var_p
xtra_bool_to_double(xtra_var_p var) {
    return xtra_double((xtra_double_t) var->b);
}

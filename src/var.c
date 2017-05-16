//
// Created by eugen on 5/1/2017.
//

#include "var.h"

xtra_var_p
xtra_var(enum xtra_var_e type) {
    xtra_var_p var;

    if (type != XTRA_VAR_NULL) {
        var = (xtra_var_p) malloc(sizeof(xtra_var_t));
    }

    var->i = 0;
    var->b = 0;
    var->d = 0;
    var->s = NULL;
    var->t = type;
    return  var;
}

void
xtra_var_free(xtra_var_p var) {
    if (var->t != XTRA_VAR_NULL) {
        free(var);
        var->t = XTRA_VAR_NULL;
    }
}

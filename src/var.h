//
// Created by eugen on 5/1/2017.
//

#ifndef EXTRA_VAR_H
#define EXTRA_VAR_H

#include <stdlib.h>

enum
xtra_var_type {
    XTRA_VAR_NULL,
    XTRA_VAR_INT,
    XTRA_VAR_BOOL,
    XTRA_VAR_DOUBLE,
    XTRA_VAR_STRING
};

struct
xtra_var_s {
    enum xtra_var_type type;
    int xtra_var_int;
    int xtra_var_bool : 1;
    double xtra_var_double;
};

typedef struct xtra_var_s xtra_var_t;
typedef xtra_var_t * xtra_var_p;

xtra_var_p
xtra_var_contruct(enum xtra_var_type);

void
xtra_var_destruct(xtra_var_p);

#include "null.h"
#include "int.h"
#include "bool.h"
#include "double.h"
#endif //EXTRA_VAR_H

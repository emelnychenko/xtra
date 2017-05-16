//
// Created by eugen on 5/1/2017.
//

#ifndef EXTRA_VAR_H
#define EXTRA_VAR_H

#include <stdlib.h>
#include "arry.h"

typedef struct xtra_var_s   xtra_var_t;
typedef xtra_var_t *        xtra_var_p;

typedef int         xtra_int_t;
typedef int         xtra_bool_t;
typedef double      xtra_double_t;
typedef char *      _xtra_var_s;
typedef xtra_arry_p _xtra_var_e;
typedef xtra_arry_p _xtra_var_a;

enum xtra_var_e {
    XTRA_VAR_NULL,
    XTRA_VAR_INT,
    XTRA_VAR_BOOL,
    XTRA_VAR_DOUBLE,
    XTRA_VAR_STRING,
    XTRA_VAR_ENUM,
    XTRA_VAR_ARRAY,
    XTRA_VAR_HASH,
    XTRA_VAR_OBJECT,
};

struct xtra_var_s {
    enum xtra_var_e t;
    xtra_int_t      i;
    xtra_bool_t     b : 1;
    xtra_double_t   d;
    _xtra_var_s     s;
    _xtra_var_e     e;
    _xtra_var_a     a;
};

xtra_var_p
xtra_var(enum xtra_var_e);

void
xtra_var_free(xtra_var_p);

#include "null.h"
#include "int.h"
#include "bool.h"
#include "double.h"

#endif //EXTRA_VAR_H

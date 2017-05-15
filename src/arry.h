//
// Created by em on 5/13/17.
//

#ifndef XTRA_ARRY_H
#define XTRA_ARRY_H

#include <stdlib.h>
#include <stdarg.h>

typedef int xtra_arry_len_t;

struct xtra_arry_s {
    void **         val;
    size_t          mem;
    xtra_arry_len_t len;
};

typedef struct xtra_arry_s xtra_arry_t;
typedef xtra_arry_t* xtra_arry_p;

xtra_arry_p
xtra_arry(size_t);

xtra_arry_len_t
xtra_arry_add(xtra_arry_p, void*);

void *
xtra_arry_get(xtra_arry_p, xtra_arry_len_t);

xtra_arry_len_t
xtra_arry_set(xtra_arry_p, xtra_arry_len_t, void*);

void *
xtra_arry_pop(xtra_arry_p);

#define xtra_arry_push xtra_arry_add

void *
xtra_arry_shift(xtra_arry_p);

xtra_arry_len_t
xtra_arry_unshift(xtra_arry_p, void*);

xtra_arry_p
xtra_arry_concat(xtra_arry_p, xtra_arry_p);

xtra_arry_p
xtra_arry_slice(xtra_arry_p, xtra_arry_len_t, xtra_arry_len_t);

xtra_arry_p
xtra_arry_splice(xtra_arry_p, xtra_arry_len_t, xtra_arry_len_t);

xtra_arry_p
xtra_arry_vsplice(xtra_arry_p, xtra_arry_len_t, xtra_arry_len_t, xtra_arry_len_t, void *, ...);

xtra_arry_p
xtra_arry_asplice(xtra_arry_p, xtra_arry_len_t, xtra_arry_len_t, xtra_arry_p);

void
xtra_arry_reverse(xtra_arry_p);

void
xtra_arry_free(xtra_arry_p);


#endif //XTRA_ARRY_H

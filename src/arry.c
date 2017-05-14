//
// Created by em on 5/13/17.
//

#include "arry.h"

xtra_arry_p
xtra_arry(size_t mem)
{
    xtra_arry_p arry = (xtra_arry_p) malloc(sizeof(xtra_arry_t));
    arry->val = (void**) malloc(mem);
    arry->mem = mem;
    arry->len = 0;
    return arry;
}

xtra_arry_len_t
xtra_arry_add(xtra_arry_p arry, void* item)
{
    xtra_arry_len_t position = arry->len;
    ++arry->len;
    arry->val = (void**) realloc(arry->val, arry->len * arry->mem);
    arry->val[position] = item;
    return position;
}

void *
xtra_arry_get(xtra_arry_p arry, xtra_arry_len_t position)
{
    return position >= arry->len ?
           NULL : arry->val[position];
}

xtra_arry_len_t
xtra_arry_set(xtra_arry_p arry, xtra_arry_len_t position, void* item)
{
    --arry->len;
    while(position >= ++arry->len) {
        arry->val = (void**) realloc(arry->val, arry->len * arry->mem);
        arry->val[arry->len - 1] = NULL;
    }

    arry->val[position] = item;
    return position;
}

void *
xtra_arry_pop(xtra_arry_p arry)
{
    if (arry->len <= 0) return NULL;

    --arry->len;
    void * item = arry->val[arry->len];
    arry->val[arry->len] = NULL;
    arry->val = (void**) realloc(arry->val, arry->len * arry->mem);
    return item;
}

void *
xtra_arry_shift(xtra_arry_p arry)
{
    if (arry->len <= 0) return NULL;

    void * item = arry->val[0];
    xtra_arry_len_t position = 0;
    while (++position < arry->len) {
        arry->val[position - 1] = arry->val[position];
    }
    --arry->len;
    arry->val[arry->len] = NULL;
    arry->val = (void**) realloc(arry->val, arry->len * arry->mem);
    return item;
}

xtra_arry_len_t
xtra_arry_unshift(xtra_arry_p arry, void * item)
{
    ++arry->len;
    arry->val = (void**) realloc(arry->val, arry->len * arry->mem);

    xtra_arry_len_t position = arry->len - 1;
    while (--position >= 0) {
        arry->val[position + 1] = arry->val[position];
    }

    arry->val[0] = item;
    return 0;
}

xtra_arry_p
xtra_arry_concat(xtra_arry_p arryi, xtra_arry_p arryj)
{
    if (arryi->mem != arryj->mem) {
        return NULL;
    }

    xtra_arry_len_t pos;
    xtra_arry_p arryk = xtra_arry(arryi->mem);

    pos = -1;
    while(++pos < arryi->len) {
        xtra_arry_add(arryk, arryi->val[pos]);
    }

    pos = -1;
    while(++pos < arryj->len) {
        xtra_arry_add(arryk, arryj->val[pos]);
    }

    return arryk;
}

#include <stdio.h>

xtra_arry_p
xtra_arry_slice(xtra_arry_p arryi, xtra_arry_len_t start, xtra_arry_len_t len)
{
    if (len <= 0) return NULL;

    xtra_arry_p arryj = xtra_arry(arryi->mem);
    xtra_arry_len_t end = start + len;

    if (end >= arryi->len) return NULL;

    for (xtra_arry_len_t pos = start; pos <= end; ++pos) {
        xtra_arry_add(arryj, arryi->val[pos]);
    }

    return arryj;
}

xtra_arry_p
xtra_arry_splice(xtra_arry_p arryi, xtra_arry_len_t start, xtra_arry_len_t len)
{
    if (len <= 0) return NULL;

    xtra_arry_p arryj = xtra_arry(arryi->mem);
    xtra_arry_len_t end = start + len;

    if (end >= arryi->len) return NULL;

    for (xtra_arry_len_t pos = start; pos <= end; ++pos) {
        xtra_arry_add(arryj, arryi->val[pos]);
        for (xtra_arry_len_t _pos = pos + 1; _pos < arryi->len; ++_pos) {
            arryi->val[_pos - 1] = arryi->val[_pos];
        }
    }

    arryi->len -= ++len;
    arryi->val = (void**) realloc(arryi->val, arryi->len * arryi->mem);
    return arryj;
}

xtra_arry_p
xtra_arry_vsplice(xtra_arry_p arryi, xtra_arry_len_t start, xtra_arry_len_t len, xtra_arry_len_t argc, void* argv, ...)
{
    xtra_arry_p arryj = xtra_arry_splice(arryi, start, len);
    if (arryj == NULL) return NULL;

    if (argc <= 0) return arryj;

    arryi->len += argc;
    arryi->val = (void**) realloc(arryi->val, arryi->len * arryi->mem);

    // iterate
    va_list argv_list;
    va_start(argv_list, argv);

//    xtra_arry_len_t swp = arryi->len - argc;

//    for (xtra_arry_len_t pos = 0; pos < ; ++pos) {
//
//    }
//
//    for (xtra_arry_len_t pos = start; pos < (start + argc); ++pos) {
//        for (xtra_arry_len_t _pos = pos + 1; _pos < arryi->len; ++_pos) {
//            arryi->val[_pos - 1] = arryi->val[_pos];
//        }
//        xtra_arry_p _pos
//        while
//    }

//            arryi->val[pos] = (void*) va_arg(list, void*);

    va_end(argv_list);
    return arryj;
}

xtra_arry_p
xtra_arry_csplice(xtra_arry_p arryi, xtra_arry_len_t start, xtra_arry_len_t len, xtra_arry_p arryj) {
    xtra_arry_p arryk = xtra_arry_splice(arryi, start, len);
    if (arryk == NULL) return NULL;

    if (arryj->len <= 0) return arryk;

    arryi->len += arryj->len;
    arryi->val = (void**) realloc(arryi->val, arryi->len * arryi->mem);

    // iterate
    // there

    return arryk;
}
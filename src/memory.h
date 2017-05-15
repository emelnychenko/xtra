//
// Created by eugen on 5/10/2017.
//

#ifndef XTRA_MEMORY_H
#define XTRA_MEMORY_H

#include <stdlib.h>
//#include "token.h"

typedef struct xtra_memory_profile_s  xtra_memory_profile_t;
typedef        xtra_memory_profile_t * xtra_memory_profile_p;

struct xtra_memory_profile_s {
    size_t usage;
};
//

xtra_memory_profile_p
xtra_memory_profile();

void
xtra_memory_add(xtra_memory_profile_p, size_t);

void
xtra_memory_del(xtra_memory_profile_p, size_t);
#endif //XTRA_MEMORY_H

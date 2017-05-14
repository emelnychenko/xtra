//
// Created by eugen on 5/10/2017.
//

#include "memory.h"

//xtra_memory_profile_p
//xtra_memory_profile_construct()
//{
//    xtra_memory_profile_p profile = {0};
//    profile = (xtra_memory_profile_p) malloc(sizeof(xtra_memory_profile_t));
//
//    return profile;
//}

xtra_memory_profile_p
xtra_memory_profile()
{
    xtra_memory_profile_p profile = (xtra_memory_profile_p) malloc(sizeof(xtra_memory_profile_t));
    profile->usage = 0;
    return profile;
}

void
xtra_memory_pfl_add(xtra_memory_profile_p pfl, size_t usage)
{
    pfl->usage += usage;
}

void
xtra_memory_pfl_del(xtra_memory_profile_p pfl, size_t usage)
{
    pfl->usage -= usage;
}
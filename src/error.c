//
// Created by em on 5/9/17.
//

#include "error.h"

void
xtra_error(const char * message, long code)
{
    perror(message); exit(EXIT_FAILURE);
}
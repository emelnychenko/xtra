#include "src/xtra.h"
#include <unistd.h>
#include "src/arry.h"

int * intdup(int const * src, size_t len)
{
    int * p = malloc(len * sizeof(int));
    memcpy(p, src, len * sizeof(int));
    return p;
}

int main(int argc, char **argv) {
    xtra_interpreter_eval(argv[1]);

    //xtra_arry_p arry = xtra_arry(sizeof(int*));
    //xtra_memory_profile_p pfl = xtra_memory_profile();

//    while (1) {
//        sleep(1);
//    }

    return 0;
}

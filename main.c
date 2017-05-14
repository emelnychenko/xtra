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
    //xtra_interpreter_eval(argv[1]);

    xtra_arry_p arry = xtra_arry(sizeof(int*));
    //xtra_memory_profile_p pfl = xtra_memory_profile();

    int position = -1;
    while (++position < 10) {
        int * append = intdup(&position, sizeof(int));
        xtra_arry_push(arry, append);
    }

//    for (int i = 0; i < arry->len; ++i) {
//        printf("%d, %d\n", i, *((int*) arry->val[i]));
//    }

    //int* out = (int*) (xtra_arry_get(arry, 5));
    int pos = 122;
    xtra_arry_p _arry = xtra_arry_vsplice(arry, 1, 1, 1, &pos);
    for (int i = 0; i < arry->len; ++i) {
        printf("%d => %d\n", i, *((int*) arry->val[i]));
    }

    //printf("%d %lu\n", _arry->len, (50003 * sizeof(int*) + sizeof(xtra_arry_p)));

//    while (1) {
//        sleep(1);
//    }

    return 0;
}

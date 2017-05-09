#include "src/xtra.h"
#include <unistd.h>

int main(int argc, char **argv) {
    xtra_interpreter_eval(argv[1]);

//    while (1) {
//        sleep(1);
//    }

    return 0;
}

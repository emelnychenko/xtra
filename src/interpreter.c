//
// Created by eugen on 5/6/2017.
//

#include "interpreter.h"

int
xtra_interpreter_eval(char * path)
{
    char * text = xtra_interpreter_read(path);
    long length = (long) strlen(text);

    //
    xtra_token_p script = xtra_lexer_eval(
        text, length, path
    );

    //free(text);


    // check script syntax
    xtra_parser_check(script);

    long memory = (long) xtra_memory_sizeof_token(script);

    printf("script memory: %lu\n", memory);

//    xtra_token_debug(script, 0);

    return 1;
}

char *
xtra_interpreter_read(char * path)
{
    FILE * file = fopen (path, "rb");

    if(!file) {
        perror(path);
        exit(1);
    }

    fseek(file , 0L, SEEK_END);
    long length = ftell(file);
    rewind(file);

    /* allocate memory for entire content */
    char * buff = calloc(1, (size_t) length + 1);

    if (!buff) {
        fclose(file);
        fputs("memory alloc fails",stderr);
        exit(1);
    }

    /* copy the file into the buffer */
    if(1 != fread(buff, (size_t) length, 1 , file)) {
        fclose(file),free(buff),fputs("entire read fails",stderr),exit(1);
    }

    /* do your work here, buffer is a string contains the whole text */
    fclose(file);

    return buff;
}
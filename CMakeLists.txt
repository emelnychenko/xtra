cmake_minimum_required(VERSION 3.0)
project(xtra)

set(CMAKE_C_STANDARD 99)

set(SOURCE_FILES
    main.c
    src/xtra.h
    src/int.c
    src/int.h
    src/bool.c
    src/bool.h
    src/double.c
    src/double.h
    src/var.c
    src/var.h
    src/null.c
    src/null.h
    src/interpreter.c
    src/interpreter.h
    src/lexer.c
    src/lexer.h
    src/parser.c
    src/parser.h
    src/token.c
    src/token.h
    src/enum.c
    src/enum.h
    src/parser/logical.c
    src/parser/logical.h
    src/parser/normalize.c
    src/parser/normalize.h
        src/for.c
        src/for.h
        src/while.c
        src/while.h
        src/do.c
        src/do.h
        src/error.c src/error.h src/if.c src/if.h src/bracket.c src/bracket.h)

add_executable(xtra ${SOURCE_FILES})

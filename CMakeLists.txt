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
    src/enum.c
    src/enum.h
    src/for.c
    src/for.h
    src/while.c
    src/while.h
    src/do.c
    src/do.h
    src/error.c
    src/error.h
    src/if.c
    src/if.h
    src/bracket.c
    src/bracket.h
    src/memory.c
    src/memory.h
    src/debug.c
    src/debug.h
        src/arry.c src/arry.h src/io.c src/io.h src/switch.c src/switch.h src/sign.c src/sign.h)

add_executable(xtra ${SOURCE_FILES})

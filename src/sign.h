//
// Created by eugen on 5/15/2017.
//

#ifndef XTRA_SIGN_H
#define XTRA_SIGN_H

#include <stdlib.h>
#include <string.h>
#include "var.h"
#include "arry.h"

enum xtra_sign_e {
    XTRA_SIGN_DOC,                 // abstract document
    XTRA_SIGN_UNALLOWED,           // any which do not matchess
    XTRA_SIGN_UNDEFINED,           // any which do not matchess
    XTRA_SIGN_IDENTITY,            // +
    XTRA_SIGN_NEGATION,            // -
    XTRA_SIGN_PLUS,                // +
    XTRA_SIGN_MINUS,               // -
    XTRA_SIGN_MULTIPLY,            // *
    XTRA_SIGN_DIVINE,              // /
    XTRA_SIGN_DOT,                 // .
    XTRA_SIGN_TRIPLE_DOT,          // ...
    XTRA_SIGN_MOD,                 // %
    XTRA_SIGN_EXP,                 // **
    XTRA_SIGN_QUESTION_MARK,        // ?
    XTRA_SIGN_DOUBLE_QUESTION_MARK, // ??
    XTRA_SIGN_QUOTATION_MARK,       // '
    XTRA_SIGN_DOUBLE_QUOTATION_MARK,// "
    XTRA_SIGN_COMMA,               // ,
    XTRA_SIGN_COLON,               // :
    XTRA_SIGN_DOUBLE_COLON,        // ::
    XTRA_SIGN_SEMICOLON,           // ;
    XTRA_SIGN_ASSIGN,              // =
    XTRA_SIGN_PLUS_ASSIGN,         // +=
    XTRA_SIGN_MINUS_ASSIGN,        // -=
    XTRA_SIGN_MULTIPLY_ASSIGN,     // *=
    XTRA_SIGN_DIVINE_ASSIGN,       // /=
    XTRA_SIGN_MOD_ASSIGN,          // %=
    XTRA_SIGN_PLUS_PLUS,           // ++
    XTRA_SIGN_MINUS_MINUS,         // --
    XTRA_SIGN_GREATER,             // >
    XTRA_SIGN_GREATER_EQUAL,       // >=
    XTRA_SIGN_LESS,                // <
    XTRA_SIGN_LESS_EQUAL,          // <=
    XTRA_SIGN_EQUAL ,              // ==
    XTRA_SIGN_ASSOCIATE,           // =>
    XTRA_SIGN_IDENTICAL ,          // ===
    XTRA_SIGN_NOT_EQUAL ,          // !=, <>
    XTRA_SIGN_NOT_IDENTICAL ,      // !==
    XTRA_SIGN_NOT_SPACESHIP ,      // <=>
    XTRA_SIGN_AND,                 // and, &&
    XTRA_SIGN_OR,                  // or, ||
    XTRA_SIGN_XOR,                 // xor, ^^
    XTRA_SIGN_NOT,                 // !
    XTRA_SIGN_BITWISE_AND,             // &
    XTRA_SIGN_BITWISE_OR,              // |
    XTRA_SIGN_BITWISE_XOR,             // ^
    XTRA_SIGN_BITWISE_NOT,             // ~
    XTRA_SIGN_BITWISE_SHIFT_L,         // <<
    XTRA_SIGN_BITWISE_SHIFT_R,         // >>
    XTRA_SIGN_IF,                  // if
    XTRA_SIGN_ELSE,                // else
    XTRA_SIGN_ELSEIF,              // elseif
    XTRA_SIGN_DO,                  // do
    XTRA_SIGN_WHILE,               // while
    XTRA_SIGN_SWITCH,              // switch
    XTRA_SIGN_CASE,                // case
    XTRA_SIGN_DEFAULT,             // default
    XTRA_SIGN_BREAK,               // break
    XTRA_SIGN_SQUARE,               // [...]
    XTRA_SIGN_SQUARE_L,             // [
    XTRA_SIGN_SQUARE_R,             // ]
    XTRA_SIGN_ROUND,                // (...)
    XTRA_SIGN_ROUND_L,              // (
    XTRA_SIGN_ROUND_R,              // )
    XTRA_SIGN_CURLY,                // {...}
    XTRA_SIGN_CURLY_L,              // {
    XTRA_SIGN_CURLY_R,              // }
    XTRA_SIGN_ANGLE,                // <...>
    XTRA_SIGN_ANGLE_L,              // <
    XTRA_SIGN_ANGLE_R,              // >
    XTRA_SIGN_EOF,                  // EOF
    XTRA_SIGN_EOL,                  // EOL
    XTRA_SIGN_PPD_DIR_NULL,         // #
    XTRA_SIGN_PPD_DIR_DEFINE,       // #define
    XTRA_SIGN_PPD_ERROR,            // #error
    XTRA_SIGN_PPD_IF,               // #if
    XTRA_SIGN_PPD_ELIF,             // #elif
    XTRA_SIGN_PPD_IFDEF,            // #ifdef
    XTRA_SIGN_PPD_IFNDEF,           // #ifndef
    XTRA_SIGN_PPD_ENDIF,            // #endif
    XTRA_SIGN_PPD_ELSE,             // #else
    XTRA_SIGN_PPD_INCLUDE,          // #include
    XTRA_SIGN_PPD_IMPORT,           // #import
    XTRA_SIGN_PPD_LINE,             // #line
    XTRA_SIGN_PPD_UNDEF,            // #undef
    XTRA_SIGN_PPD_USE,              // #use #using
    XTRA_SIGN_TYPE,                 // xtra_var, var
    XTRA_SIGN_BINARY,               // bindry 0x, 0X 0b, 0B
    XTRA_SIGN_TRUE,                 // true
    XTRA_SIGN_FALSE,                // false
    XTRA_SIGN_FOR,                  // for
    XTRA_SIGN_EACH,                 // each
    XTRA_SIGN_FOREACH,              // foreach
    XTRA_SIGN_IN,                   // in
    XTRA_SIGN_RETURN,               // return
    XTRA_SIGN_WHEN,                 // when
    XTRA_SIGN_THEN,                 // then
    XTRA_SIGN_AS,                   // as
    XTRA_SIGN_IS,                   // is
    XTRA_SIGN_END,                  // end
    XTRA_SIGN_INTERPOLATION,        // $""
    XTRA_SIGN_VAR,                  // xtra_var *
    XTRA_SIGN_NULL,                 // xtra_var_null, null
    XTRA_SIGN_INT,                  // xtra_var_int, int, integer
    XTRA_SIGN_DOUBLE,               // xtra_var_double, double, float
    XTRA_SIGN_BOOL,                 // xtra_var_bool, bool, boolean
    XTRA_SIGN_STRING,               // xtra_var_string, str, string
    XTRA_SIGN_CONST,                // xtra_var_const, const, define
    XTRA_SIGN_ENUM,                // xtra_var_enum, enum
    XTRA_SIGN_ARRAY,               // xtra_var_array, array
    XTRA_SIGN_DICTIONARY,          // xtra_var_array, dictionary,
    XTRA_SIGN_HASH,                // xtra_var_array, hash
    XTRA_SIGN_USE,                 // use, using
    XTRA_SIGN_FUNCTION,            // function
    XTRA_SIGN_NAMESPACE,           // namespace
    XTRA_SIGN_CLASS,               // class
    XTRA_SIGN_THROW,               // throw
    XTRA_SIGN_TRY,                 // try
    XTRA_SIGN_CATCH,               // catch
    XTRA_SIGN_FINALLY,             // finally
    XTRA_SIGN_NEW,                 // new
    XTRA_SIGN_DELETE,              // delete, del
    XTRA_SIGN_OBJECT,              // xtra_var_object
    XTRA_SIGN_STATIC,              // static
    XTRA_SIGN_ABSTRACT,            // abstract
    XTRA_SIGN_PUBLIC,              // public
    XTRA_SIGN_PROTECTED,           // proteced
    XTRA_SIGN_EXTENDS,             // extends
    XTRA_SIGN_PRIVATE,             // private
    XTRA_SIGN_INTERFACE,           // interface
    XTRA_SIGN_IMPLEMENTS,          // implements
    XTRA_SIGN_ASYNC,               // async
    XTRA_SIGN_AWAIT,               // await
};

typedef struct xtra_sign_s  xtra_sign_t;
typedef        xtra_sign_t* xtra_sign_p;
typedef int                 xtra_sign_l;

struct xtra_sign_s {
    enum xtra_sign_e type;
    xtra_arry_p      arry;
     xtra_var_p      var;
};

xtra_sign_p
xtra_sign(enum xtra_sign_e);

xtra_sign_p
xtra_sign_with_arry(enum xtra_sign_e, xtra_arry_p);

xtra_var_p
xtra_sign_var_get(xtra_sign_p);

void
xtra_sign_var_set(xtra_sign_p, xtra_var_p);

xtra_arry_p
xtra_sign_arry(xtra_sign_p);

xtra_sign_l
xtra_sign_arry_len(xtra_sign_p);

enum xtra_sign_e
xtra_sign_arry_type(xtra_sign_p, xtra_sign_l);

xtra_sign_l
xtra_sign_arry_add(xtra_sign_p, xtra_sign_p);

xtra_sign_p
xtra_sign_arry_get(xtra_sign_p, xtra_sign_l);

int
xtra_sign_arry_has(xtra_sign_p, xtra_sign_l);

void
xtra_sign_arry_set(xtra_sign_p, xtra_sign_l, xtra_sign_p);

xtra_sign_p
xtra_sign_arry_pop(xtra_sign_p);

#define xtra_sign_arry_push xtra_sign_arry_add

xtra_sign_p
xtra_sign_arry_shift(xtra_sign_p);

xtra_sign_l
xtra_sign_arry_unshift(xtra_sign_p, xtra_sign_p);

xtra_sign_p
xtra_sign_arry_concat(xtra_sign_p, xtra_sign_p);

xtra_sign_p
xtra_sign_arry_slice(xtra_sign_p, xtra_sign_l, xtra_sign_l);

xtra_sign_p
xtra_sign_arry_splice(xtra_sign_p, xtra_sign_l, xtra_sign_l);

xtra_sign_p
xtra_sign_arry_vsplice(xtra_sign_p, xtra_sign_l, xtra_sign_l, xtra_sign_l, xtra_sign_p, ...);

xtra_sign_p
xtra_sign_arry_asplice(xtra_sign_p, xtra_sign_l, xtra_sign_l, xtra_sign_p);

void
xtra_sign_arry_reverse(xtra_sign_p);

void
xtra_sign_arry_free(xtra_sign_p, xtra_sign_l);

void
xtra_sign_free(xtra_sign_p);

enum xtra_sign_e
xtra_sign_define(char *);

#endif //XTRA_SIGN_H

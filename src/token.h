//
// Created by eugen on 5/6/2017.
//

#ifndef EXTRA_TOKEN_H
#define EXTRA_TOKEN_H

typedef struct xtra_token_s xtra_token_t;
typedef xtra_token_t * xtra_token_p;

#include "lexer.h"
#include "var.h"

enum xtra_token_type {
    XTRA_TOKEN_SCRIPT,              // any which do not matchess
    //
    XTRA_TOKEN_UNALLOWED,           // any which do not matchess
    XTRA_TOKEN_UNDEFINED,           // any which do not matchess
    XTRA_TOKEN_IDENTITY,            // +
    XTRA_TOKEN_NEGATION,            // -
    XTRA_TOKEN_PLUS,                // +
    XTRA_TOKEN_MINUS,               // -
    XTRA_TOKEN_MULTIPLY,            // *
    XTRA_TOKEN_DIVINE,              // /
    XTRA_TOKEN_DOT,                 // .
    XTRA_TOKEN_TRIPLE_DOT,          // ...
    XTRA_TOKEN_MOD,                 // %
    XTRA_TOKEN_EXP,                 // **
    XTRA_TOKEN_QUESTION_MARK,           // ?
    XTRA_TOKEN_DOUBLE_QUESTION_MARK,    // ??
    XTRA_TOKEN_QUOTATION_MARK,          // '
    XTRA_TOKEN_DOUBLE_QUOTATION_MARK,   // "
    XTRA_TOKEN_COMMA,               // ,
    XTRA_TOKEN_COLON,               // :
    XTRA_TOKEN_DOUBLE_COLON,        // ::
    XTRA_TOKEN_SEMICOLON,           // ;
    XTRA_TOKEN_ASSIGN,              // =
    XTRA_TOKEN_PLUS_ASSIGN,         // +=
    XTRA_TOKEN_MINUS_ASSIGN,        // -=
    XTRA_TOKEN_MULTIPLY_ASSIGN,     // *=
    XTRA_TOKEN_DIVINE_ASSIGN,       // /=
    XTRA_TOKEN_MOD_ASSIGN,          // %=
    XTRA_TOKEN_PLUS_PLUS,           // ++
    XTRA_TOKEN_MINUS_MINUS,         // --
    XTRA_TOKEN_GREATER,             // >
    XTRA_TOKEN_GREATER_EQUAL,       // >=
    XTRA_TOKEN_LESS,                // <
    XTRA_TOKEN_LESS_EQUAL,          // <=
    XTRA_TOKEN_EQUAL ,              // ==
    XTRA_TOKEN_ASSOCIATE,           // =>
    XTRA_TOKEN_IDENTICAL ,          // ===
    XTRA_TOKEN_NOT_EQUAL ,          // !=, <>
    XTRA_TOKEN_NOT_IDENTICAL ,      // !==
    XTRA_TOKEN_NOT_SPACESHIP ,      // <=>
    XTRA_TOKEN_AND,                 // and, &&
    XTRA_TOKEN_OR,                  // or, ||
    XTRA_TOKEN_XOR,                 // xor, ^^
    XTRA_TOKEN_NOT,                 // !
    XTRA_TOKEN_BITWISE_AND,             // &
    XTRA_TOKEN_BITWISE_OR,              // |
    XTRA_TOKEN_BITWISE_XOR,             // ^
    XTRA_TOKEN_BITWISE_NOT,             // ~
    XTRA_TOKEN_BITWISE_SHIFT_L,         // <<
    XTRA_TOKEN_BITWISE_SHIFT_R,         // >>
    XTRA_TOKEN_IF,                  // if
    XTRA_TOKEN_ELSE,                // else
    XTRA_TOKEN_ELSEIF,              // elseif
    XTRA_TOKEN_DO,                  // do
    XTRA_TOKEN_WHILE,               // while
    XTRA_TOKEN_SWITCH,              // switch
    XTRA_TOKEN_CASE,                // case
    XTRA_TOKEN_DEFAULT,             // default
    XTRA_TOKEN_BREAK,               // break
    XTRA_TOKEN_BRACKET_SQUARE,      // [...]
    XTRA_TOKEN_BRACKET_SQUARE_L,    // [
    XTRA_TOKEN_BRACKET_SQUARE_R,    // ]
    XTRA_TOKEN_BRACKET_ROUND,       // (...)
    XTRA_TOKEN_BRACKET_ROUND_L,     // (
    XTRA_TOKEN_BRACKET_ROUND_R,     // )
    XTRA_TOKEN_BRACKET_CURLY,       // {...}
    XTRA_TOKEN_BRACKET_CURLY_L,     // {
    XTRA_TOKEN_BRACKET_CURLY_R,     // }
    XTRA_TOKEN_BRACKET_ANGLE,       // <...>
    XTRA_TOKEN_BRACKET_ANGLE_L,     // <
    XTRA_TOKEN_BRACKET_ANGLE_R,     // >
    XTRA_TOKEN_EOF,                 // EOF
    XTRA_TOKEN_EOL,                 // EOL
    XTRA_TOKEN_PPD_DIR_NULL,        // #
    XTRA_TOKEN_PPD_DIR_DEFINE,      // #define
    XTRA_TOKEN_PPD_ERROR,           // #error
    XTRA_TOKEN_PPD_IF,              // #if
    XTRA_TOKEN_PPD_ELIF,            // #elif
    XTRA_TOKEN_PPD_IFDEF,           // #ifdef
    XTRA_TOKEN_PPD_IFNDEF,          // #ifndef
    XTRA_TOKEN_PPD_ENDIF,           // #endif
    XTRA_TOKEN_PPD_ELSE,            // #else
    XTRA_TOKEN_PPD_INCLUDE,         // #include
    XTRA_TOKEN_PPD_IMPORT,          // #import
    XTRA_TOKEN_PPD_LINE,            // #line
    XTRA_TOKEN_PPD_UNDEF,           // #undef
    XTRA_TOKEN_PPD_USE,             // #use #using
    XTRA_TOKEN_TYPE,                // xtra_var, var
    XTRA_TOKEN_BINARY,              // bindry 0x, 0X 0b, 0B
    XTRA_TOKEN_TRUE,                // true
    XTRA_TOKEN_FALSE,               // false
    XTRA_TOKEN_FOR,                 // for
    XTRA_TOKEN_EACH,                // each
    XTRA_TOKEN_FOREACH,             // foreach
    XTRA_TOKEN_IN,                  // in
    XTRA_TOKEN_RETURN,              // return
    XTRA_TOKEN_WHEN,                // when
    XTRA_TOKEN_THEN,                // then
    XTRA_TOKEN_AS,                  // as
    XTRA_TOKEN_IS,                  // is
    XTRA_TOKEN_END,                 // end
    XTRA_TOKEN_INTERPOLATION,       // $""
    XTRA_TOKEN_VAR,                 // xtra_var *
    XTRA_TOKEN_NULL,                // xtra_var_null, null
    XTRA_TOKEN_INT,                 // xtra_var_int, int, integer
    XTRA_TOKEN_DOUBLE,              // xtra_var_double, double, float
    XTRA_TOKEN_BOOL,                // xtra_var_bool, bool, boolean
    XTRA_TOKEN_STRING,              // xtra_var_string, str, string
    XTRA_TOKEN_CONST,               // xtra_var_const, const, define
    XTRA_TOKEN_ENUM,                // xtra_var_enum, enum
    XTRA_TOKEN_ARRAY,               // xtra_var_array, array
    XTRA_TOKEN_DICTIONARY,          // xtra_var_array, dictionary,
    XTRA_TOKEN_HASH,                // xtra_var_array, hash
    XTRA_TOKEN_USE,                 // use, using
    XTRA_TOKEN_FUNCTION,            // function
    XTRA_TOKEN_NAMESPACE,           // namespace
    XTRA_TOKEN_CLASS,               // class
    XTRA_TOKEN_THROW,               // throw
    XTRA_TOKEN_TRY,                 // try
    XTRA_TOKEN_CATCH,               // catch
    XTRA_TOKEN_FINALLY,             // finally
    XTRA_TOKEN_NEW,                 // new
    XTRA_TOKEN_DELETE,              // delete, del
    XTRA_TOKEN_OBJECT,              // xtra_var_object
    XTRA_TOKEN_STATIC,              // static
    XTRA_TOKEN_ABSTRACT,            // abstract
    XTRA_TOKEN_PUBLIC,              // public
    XTRA_TOKEN_PROTECTED,           // proteced
    XTRA_TOKEN_EXTENDS,             // extends
    XTRA_TOKEN_PRIVATE,             // private
    XTRA_TOKEN_INTERFACE,           // interface
    XTRA_TOKEN_IMPLEMENTS,          // implements
    XTRA_TOKEN_ASYNC,               // async
    XTRA_TOKEN_AWAIT,               // await
};

struct xtra_token_s {
    enum xtra_token_type type;
    char * lexer;
    long line;
    long column;
    long size;
    xtra_token_p * child;
};

xtra_token_p
xtra_token_constuct(enum xtra_token_type);

void
xtra_token_add_child(xtra_token_p, xtra_token_p);

void
xtra_token_replace_range_by_one(xtra_token_p script, long start, long length, xtra_token_p token);

void
xtra_token_forget(xtra_token_p);

void
xtra_token_forget_deep(xtra_token_p);

enum xtra_token_type
xtra_token_define_type(char *);

#endif //EXTRA_TOKEN_H

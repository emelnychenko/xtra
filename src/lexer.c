//
// Created by eugen on 5/6/2017.
//

#include "lexer.h"

/**
 * fixme: interpolation values
 *
 * @param text
 * @param length
 * @return
 */
xtra_token_p
xtra_lexer_eval(char * text, long length)
{
    long position = -1;
    char ch;
    char * op;
    long _length = 0;
    enum xtra_token_type token_type;

    xtra_token_p script = xtra_token_constuct(XTRA_TOKEN_SCRIPT);
    script->lexer = text;

    while (position <= length) {
        int include = 1;
        ch = text[++position];

        if (ch == '/' && position < length && text[position + 1] == '/') {
            xtra_lexer_comment_inline(text, &position); // inline comment
            include = 0;
        } else if (ch == '/' && position < length && text[position + 1] == '*') {
            xtra_lexer_comment_block(text, &position, length); // block comment /* */
            include = 0;
        } else if ( // preprocessor implementation
                ch == '\0'
                || ch == '\n'
                || ch == ';'
                || ch == '('
                || ch == ')'
                || ch == '['
                || ch == ']'
                || ch == '{'
                || ch == '}'
                || ch == ','
                || ch == '^'
                || ch == '~'
        ) {
            // 1 char lexer
            op = ( char *) calloc(0, sizeof( char));
            op[0] = ch;
            op[1] = '\0';

            if (ch == '\0') {
                token_type = XTRA_TOKEN_EOF;
            } else if (ch == '\n') {
                token_type = XTRA_TOKEN_EOL;
            } else {
                token_type = xtra_token_define_type(op);
            }
        } else if (
                ch == '='
                || ch == '+'
                || ch == '-'
                || ch == '*'
                || ch == '/'
                || ch == '&'
                || ch == '|'
                || ch == '%'
                || ch == '!'
                || ch == '<'
                || ch == '>'
                || (ch == '.' && (position + 2) <= length && text[position + 1] == '.' && text[position + 2] == '.') // ...
                || (ch == '$' && (position + 1) <= length && (text[position + 1] == '"' || text[position + 1] == '\'')) // interpolation c# like
                || ch == '#'
        ) {
            // logical cast

            if (ch == '^') {
                // ^
                // 1 char lexer
                // op = ( char *) calloc(0, sizeof( char));
                op = "^";
            } else if (ch == '~') {
                // ^
                // op = ( char *) calloc(0, sizeof( char));
                op = "~";
            } else if (ch == '=') {
                if (length >= (position + 2) && text[position + 1] == '=' && text[position + 2] == '=') {
                    // ===
                    // op = ( char *) calloc(2, sizeof( char));
                    op = "===";
                    position += 2;
                }  else if (length >= (position + 1) && text[position + 1] == '=') {
                    // ==
                    // op = ( char *) calloc(1, sizeof( char));
                    op = "==";
                    position++;
                } else if (length >= (position + 1) && text[position + 1] == '=') {
                    // ==
                    // op = ( char *) calloc(1, sizeof( char));
                    op = "=>";
                    position++;
                } else {
                    // =
                    op = "=";
                }
            } else if (ch == '!') {
                if (length >= (position + 2) && text[position + 1] == '=' && text[position + 2] == '=') {
                    // !==
                    // op = ( char *) calloc(2, sizeof( char));
                    op = "!==";
                    position += 2;
                }  else if (length >= (position + 1) && text[position + 1] == '=') {
                    // !=
                    // op = ( char *) calloc(1, sizeof( char));
                    op = "!=";
                    position++;
                } else {
                    // !
                    // op = ( char *) calloc(0, sizeof( char));
                    op = "!";
                }
            } else if (ch == '$') {
                ++position;
                _length = 0;
                token_type = XTRA_TOKEN_INTERPOLATION;
                op = xtra_lexer_string(text, position, &_length, text[position]);

                //printf("s %s\n", op);

                //free(op); export to token
                position += _length;
            } else if (ch == '+') {
                if (length >= (position + 1) && text[position + 1] == '+') {
                    // ++
                    // op = ( char *) calloc(1, sizeof( char));
                    op = "++";
                    position++;
                } else if (length >= (position + 1) && text[position + 1] == '=') {
                    // +=
                    // op = ( char *) calloc(1, sizeof( char));
                    op = "+=";
                    position++;
                } else {
                    // +
                    //op = ( char *) calloc(0, sizeof( char));
                    op = "+";
                }
            } else if (ch == '-') {
                if (length >= (position + 1) && text[position + 1] == '-') {
                    // --
                    // op = ( char *) calloc(1, sizeof( char));
                    op = "--";
                    position++;
                } else if (length >= (position + 1) && text[position + 1] == '=') {
                    // -=
                    // op = ( char *) calloc(1, sizeof( char));
                    op = "-=";
                    position++;
                } else {
                    // -
                    // op = ( char *) calloc(0, sizeof( char));
                    op = "-";
                }
            } else if (ch == '/') {
                if (length >= (position + 1) && text[position + 1] == '=') {
                    // /=
                    // op = ( char *) calloc(1, sizeof( char));
                    op = "/=";
                    position++;
                } else {
                    // /
                    // op = ( char *) calloc(0, sizeof( char));
                    op = "/";
                }
            } else if (ch == '*') {
                if (length >= (position + 1) && text[position + 1] == '*') {
                    // **
                    // op = ( char *) calloc(1, sizeof( char));
                    op = "**";
                    position++;
                } else if (length >= (position + 1) && text[position + 1] == '=') {
                    // *=
                    // op = ( char *) calloc(1, sizeof( char));
                    op = "*=";
                    position++;
                } else {
                    // *
                    // op = ( char *) calloc(0, sizeof( char));
                    op = "*";
                }
            } else if (ch == '%') {
                if (length >= (position + 1) && text[position + 1] == '=') {
                    // %=
                    // op = ( char *) calloc(1, sizeof( char));
                    op = "%=";
                    position++;
                } else {
                    // %
                    // op = ( char *) calloc(0, sizeof( char));
                    op = "%";
                }
            } else if (ch == '&') {
                if (length >= (position + 1) && text[position + 1] == '&') {
                    // &&
                    // op = ( char *) calloc(1, sizeof( char));
                    op = "&&";
                    position++;
                } else {
                    // &
                    // op = ( char *) calloc(0, sizeof( char));
                    op = "&";
                }
            } else if (ch == '|') {
                if (length >= (position + 1) && text[position + 1] == '|') {
                    // ||
                    // op = ( char *) calloc(1, sizeof( char));
                    op = "||";
                    position++;
                } else {
                    // |
                    // op = ( char *) calloc(0, sizeof( char));
                    op = "|";
                }
            } else if (ch == '<') {
                if (length >= (position + 2) && text[position + 1] == '=' && text[position + 2] == '>') {
                    // <=>
                    // op = ( char *) calloc(2, sizeof( char));
                    op = "<=>";
                    position += 2;
                } else if (length >= (position + 1) && text[position + 1] == '<') {
                    // <<
                    op = ( char *) calloc(1, sizeof( char));
                    op = "<<";
                    position++;
                } else if (length >= (position + 1) && text[position + 1] == '>') {
                    // <>
                    // op = ( char *) calloc(1, sizeof( char));
                    op = "<>";
                    position++;
                } else if (length >= (position + 1) && text[position + 1] == '=') {
                    // <=
                    // op = ( char *) calloc(1, sizeof( char));
                    op = "<=";
                    position++;
                } else {
                    // <
                    // op = ( char *) calloc(0, sizeof( char));
                    op = "<";
                }
            } else if (ch == '>') {
                if (length >= (position + 1) && text[position + 1] == '>') {
                    // >>
                    // op = ( char *) calloc(1, sizeof( char));
                    op = ">>";
                    position++;
                } else {
                    // >
                    // op = ( char *) calloc(0, sizeof( char));
                    op = ">";
                }
            } else if (ch == '.') {
                if (length >= (position + 2) && text[position + 1] == '.' && text[position + 2] == '.') {
                    // ...
                    // op = ( char *) calloc(2, sizeof( char));
                    op = "...";
                    position += 2;
                } else {
                    // .
                    //op = ( char *) calloc(0, sizeof( char));
                    op = ".";
                }
            } else if (ch == ':') {
                if (length >= (position + 1) && text[position + 1] == ':') {
                    // ::
                    // op = ( char *) calloc(1, sizeof( char));
                    op = "::";
                    position++;
                } else {
                    // :
                    // op = ( char *) calloc(0, sizeof( char));
                    op = ":";
                }
            } else if (ch == '#') {
                if (
                        length >= (position + 6)
                        && text[position + 1] == 'd'
                        && text[position + 2] == 'e'
                        && text[position + 3] == 'f'
                        && text[position + 4] == 'i'
                        && text[position + 5] == 'n'
                        && text[position + 6] == 'e'
                ) {
                    // #define
                    //op = ( char *) calloc(6, sizeof( char));
                    op = "#define";
                    position += 6;
                } else if (
                        length >= (position + 3)
                        && text[position + 1] == 'd'
                        && text[position + 2] == 'e'
                        && text[position + 3] == 'f'
                ) {
                    // #def
                    //op = ( char *) calloc(6, sizeof( char));
                    op = "#define";
                    position += 3;
                } else if (
                        length >= (position + 5)
                        && text[position + 1] == 'e'
                        && text[position + 2] == 'r'
                        && text[position + 3] == 'r'
                        && text[position + 4] == 'o'
                        && text[position + 5] == 'r'
                ) {
                    // #error
                    //op = ( char *) calloc(5, sizeof( char));
                    op = "#error";
                    position += 5;
                } else if (
                        length >= (position + 2)
                        && text[position + 1] == 'i'
                        && text[position + 2] == 'f'
                ) {
                    // #if
                    // op = ( char *) calloc(2, sizeof( char));
                    op = "#if";
                    position += 2;
                } else if (
                        length >= (position + 4)
                        && text[position + 1] == 'e'
                        && text[position + 2] == 'l'
                        && text[position + 3] == 'i'
                        && text[position + 4] == 'f'
                ) {
                    // #elif
                    // op = ( char *) calloc(4, sizeof( char));
                    op = "#elif";
                    position += 4;
                } else if (
                        length >= (position + 5)
                        && text[position + 1] == 'e'
                        && text[position + 2] == 'l'
                        && text[position + 3] == 's'
                        && text[position + 4] == 'i'
                        && text[position + 5] == 'f'
                ) {
                    // #elsif
                    // op = ( char *) calloc(4, sizeof( char));
                    op = "#elif";
                    position += 5;
                } else if (
                        length >= (position + 6)
                        && text[position + 1] == 'e'
                        && text[position + 2] == 'l'
                        && text[position + 3] == 's'
                        && text[position + 4] == 'e'
                        && text[position + 5] == 'i'
                        && text[position + 6] == 'f'
                ) {
                    // #elseif
                    // op = ( char *) calloc(4, sizeof( char));
                    op = "#elif";
                    position += 6;
                } else if (
                        length >= (position + 5)
                        && text[position + 1] == 'i'
                        && text[position + 2] == 'f'
                        && text[position + 3] == 'd'
                        && text[position + 4] == 'e'
                        && text[position + 5] == 'f'
                        ) {
                    // #ifdef
                    // op = ( char *) calloc(5, sizeof( char));
                    op = "#ifdef";
                    position += 5;
                } else if (
                        length >= (position + 6)
                        && text[position + 1] == 'i'
                        && text[position + 2] == 'f'
                        && text[position + 3] == 'n'
                        && text[position + 4] == 'd'
                        && text[position + 5] == 'e'
                        && text[position + 6] == 'f'
                        ) {
                    // #ifndef
                    // op = ( char *) calloc(6, sizeof( char));
                    op = "#ifndef";
                    position += 6;
                } else if (
                        length >= (position + 5)
                        && text[position + 1] == 'e'
                        && text[position + 2] == 'n'
                        && text[position + 3] == 'd'
                        && text[position + 4] == 'i'
                        && text[position + 5] == 'f'
                ) {
                    // #endif
                    // op = ( char *) calloc(5, sizeof( char));
                    op = "#endif";
                    position += 5;
                } else if (
                        length >= (position + 7)
                        && text[position + 1] == 'i'
                        && text[position + 2] == 'n'
                        && text[position + 3] == 'c'
                        && text[position + 4] == 'l'
                        && text[position + 5] == 'u'
                        && text[position + 6] == 'd'
                        && text[position + 7] == 'e'
                ) {
                    // #include
                    // op = ( char *) calloc(7, sizeof( char));
                    op = "#include";
                    position += 7;
                } else if (
                        length >= (position + 6)
                        && text[position + 1] == 'i'
                        && text[position + 2] == 'm'
                        && text[position + 3] == 'p'
                        && text[position + 4] == 'o'
                        && text[position + 5] == 'r'
                        && text[position + 6] == 't'
                ) {
                    // #import
                    // op = ( char *) calloc(6, sizeof( char));
                    op = "#import";
                    position += 6;
                } else if (
                        length >= (position + 4)
                        && text[position + 1] == 'l'
                        && text[position + 2] == 'i'
                        && text[position + 3] == 'n'
                        && text[position + 4] == 'e'
                ) {
                    // #line
                    // op = ( char *) calloc(4, sizeof( char));
                    op = "#line";
                    position += 4;
                } else if (
                        length >= (position + 8)
                        && text[position + 1] == 'u'
                        && text[position + 2] == 'n'
                        && text[position + 3] == 'd'
                        && text[position + 4] == 'e'
                        && text[position + 5] == 'f'
                        && text[position + 6] == 'i'
                        && text[position + 7] == 'n'
                        && text[position + 8] == 'e'
                ) {
                    // #undefine
                    // op = ( char *) calloc(5, sizeof( char));
                    op = "#undef";
                    position += 8;
                } else if (
                        length >= (position + 5)
                        && text[position + 1] == 'u'
                        && text[position + 2] == 'n'
                        && text[position + 3] == 'd'
                        && text[position + 4] == 'e'
                        && text[position + 5] == 'f'
                ) {
                    // #undef
                    // op = ( char *) calloc(5, sizeof( char));
                    op = "#undef";
                    position += 5;
                } else if (
                        length >= (position + 5)
                        && text[position + 1] == 'u'
                        && text[position + 2] == 's'
                        && text[position + 3] == 'i'
                        && text[position + 4] == 'n'
                        && text[position + 5] == 'g'
                ) {
                    // #using
                    // op = ( char *) calloc(3, sizeof( char));
                    op = "#use";
                    position += 5;
                } else if (
                        length >= (position + 3)
                        && text[position + 1] == 'u'
                        && text[position + 2] == 's'
                        && text[position + 3] == 'e'
                ) {
                    // #use
                    // op = ( char *) calloc(3, sizeof( char));
                    op = "#use";
                    position += 3;
                } else {
                    // # ... \n
                    xtra_lexer_comment_inline(text, &position); // empty ppd like a inline comment
                    include = 0;
                }
            }

            if (include == 1) {
                token_type = xtra_token_define_type(op);
            }
        } else if (ch == '\'' || ch == '"') {
            _length = 0;
            token_type = XTRA_TOKEN_STRING;
            op = xtra_lexer_string(text, position, &_length, ch);

            //printf("s %s\n", op);

            //free(op); export to token
            position += _length;

            // string token
        } else if (!isspace(ch)) {
            // > 1 char lexer
            _length = 0;
            // find op expression to end of line or ;
            op = xtra_lexer_keyop(text, position, &_length);
            token_type = xtra_token_define_type(op);

            if (token_type == XTRA_TOKEN_UNDEFINED) {
                if (xtra_lexer_is_int(op, _length) == 1) {
                    token_type = XTRA_TOKEN_INT;
                    // int
                    //printf(
                    //    "i %d\n", xtra_lexer_int(op)
                    //);
                } else if (xtra_lexer_is_double(op, _length) == 1) {
                    token_type = XTRA_TOKEN_DOUBLE;
                    // double
                    //printf(
                     //    "d %f\n", xtra_lexer_double(op)
                    //);
                } else if (xtra_lexer_is_binary(op, _length) == 1) {
                    // binary prefix
                    token_type = XTRA_TOKEN_BINARY;
                } else if (xtra_lexer_validate_undefined(op, _length) == 1) {
                    // need parse next thinks .,+= etc
                    //printf("v %s\n", op);
                } else {
                    token_type = XTRA_TOKEN_UNALLOWED;
                    // lexical error. bad value
                }
            } else {
                // known token
                //printf("+ %s\n", op);
            }
            // then find out token
//            xtra_token_p token = ;
             // memcpy should use
            //free(op); export to token
            position += _length;
        } else {
            // whitespace
            include = 0;
        }

        if (include == 1) {
            script->size++;
            script->child = realloc(script->child, (sizeof (xtra_token_p *) * script->size));
            script->child[script->size - 1] = xtra_token_constuct(token_type);
            script->child[script->size - 1]->lexer = op;
        }
    }

    return script;
}

char *
xtra_lexer_keyop(char * text, long position, long * length)
{
    char ch = text[position];
    long _length = 0;

    // a-zA-Z0-9.?$_-
    while (
            !isspace(ch)
            && ch != ';'
            && ch != ':'
            && ch != '\0'
            && ch != '\n'
            && ch != '('
            && ch != ')'
            && ch != '['
            && ch != ']'
            && ch != '{'
            && ch != '}'
//            && (ch != '.' && text[position + 1] != '.' && text[position + 2] != '.')
            && ch != '"'
            && ch != '\''
            && ch != ','
            && ch != '^'
            && ch != '~'
            && ch != '+'
            && ch != '-'
            && ch != '&'
            && ch != '|'
            && ch != '!'
            && ch != '='
            && ch != '/'
            && ch != '*'
            && ch != '<'
            && ch != '>'
            && ch != '#'
    ) {
        // three dots break
        if (ch == '.' && text[position + 1] != '\0' && text[position + 1] == '.' && text[position + 2] != '\0' && text[position + 2] == '.') {
            break;
        }

        // interpolation break
        if (ch == '$' && text[position + 1] != '\0' && (text[position + 1] == '"' || text[position + 1] == '\'')) {
            break;
        }

        ch = text[++position]; ++_length;
    }

    char * op = ( char *) calloc(_length, sizeof( char));
    position -= _length;

    while ((*length) < _length) {
        op[*length] = text[position];

        (*length)++; position++;
    }

    op[_length] = '\0';
    (*length)--;

    return op;
}

int
xtra_lexer_validate_undefined(char * text, long length)
{
    long position = -1;
    char ch;

    while (++position <= length) {
        ch = text[position];

        if (!isalnum(ch) && ch != '-' && ch != '_' && ch != '$' && ch != '?' && ch != '.') {
            return 0;
        }
    }

    return 1;
//
//    // a-zA-Z0-9.?$_-!
//    while (
//            !isspace(ch)
//            && ch != ';'
//            && ch != '\0'
//            && ch != '('
//            && ch != ')'
//            && ch != '['
//            && ch != ']'
//            && ch != '{'
//            && ch != '}'
//            ) {
//        ch = text[++position]; ++_length;
//    }
}

void
xtra_lexer_comment_inline(char * text, long * position)
{
    char ch = text[*position];

    while (ch != '\n' && ch != '\0') {
        ch = text[++(*position)];
    }
}

void
xtra_lexer_comment_block(char * text, long * position, long length)
{
    char ch = text[*position];

    while (ch != '\0') {
        if (ch == '*' && *position < length && text[*position + 1] == '/') {
            ++(*position);
            break;
        }

        ch = text[++(*position)];
    }
}

/**
 * fixme: text normalization
 *
 * @param text
 * @param position
 * @param length
 * @param delimiter
 * @return
 */
char *
xtra_lexer_string(char * text, long position, long * length, char delimiter)
{
    char ch = text[++position];
    long _length = 0;

    // a-zA-Z0-9.?$_-
    while (ch != '\0') {
        if (ch == delimiter && text[position - 1] != '\\') {
            break;
        }
        ch = text[++position]; ++_length;
    }

    char * op = ( char *) calloc(_length, sizeof( char));
    position -= _length;

    while ((*length) < _length) {
        op[*length] = text[position];

        (*length)++; position++;
    }

    op[_length] = '\0';

    // fixme: backslashes

    (*length)++; // compensation of delimiters

    return op;
}

char *
xtra_lexer_normalize(char * string, long length)
{
    long position = -1, _length = 0;

    while (++position < length) {
        if (string[position] == '\\') {
            ++position;
        }

        _length++;
    }

    char * _string = ( char *) calloc(_length, sizeof( char));

    position = -1;
    while (++position < length) {
        if (string[position] == '\\') {
            _string[position] = string[++position];
        } else {
            _string[position] = string[position];
        }
    }

    _string[length] = '\0';

    free(string);

    return _string;
}

int
xtra_lexer_is_int(char * text, long length)
{
    long position = 0;

    while (position < length) {
        if (isdigit(text[position++]) == 0)
            return 0;
    }

    return 1;
}

int
xtra_lexer_is_double(char * text, long length)
{
    long position = -1;
    int dot_turn = 0;

    while (++position < length) {
        if (isdigit(text[position]) == 0) {
            if (text[position] == '.' && dot_turn == 0) {
                dot_turn = 1;
            } else {
                return 0;
            }
        }
    }

    return dot_turn == 1;
}

int
xtra_lexer_is_binary(char * text, long length)
{
    if (length > 1) {
        if (text[0] == '0' && (text[1] == 'x' || text[1] == 'X')) {
            return 1;
        }

        if (text[0] == '0' && (text[1] == 'b' || text[1] == 'B')) {
            return 1;
        }
    }

    return 0;
}

int
xtra_lexer_int(char * text)
{
    return atoi(text);
}

double
xtra_lexer_double(char * text)
{
    return atof(text);
}

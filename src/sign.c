//
// Created by eugen on 5/15/2017.
//

#include "sign.h"

xtra_sign_p
xtra_sign(enum xtra_sign_e type) {
    xtra_sign_p sign = (xtra_sign_p) malloc(sizeof(xtra_sign_t));
    sign->type = type;
    sign->arry = NULL;
    return sign;
}

xtra_sign_p
xtra_sign_with_arry(enum xtra_sign_e type, xtra_arry_p arry) {
    xtra_sign_p sign = xtra_sign(type);
    sign->arry = arry;
    return sign;
}

xtra_arry_p
xtra_sign_arry(xtra_sign_p sign) {
    if (sign->arry == NULL) { sign->arry = xtra_arry(sizeof(xtra_sign_p)); }
    return sign->arry;
}

xtra_sign_l
xtra_sign_arry_len(xtra_sign_p sign) {
    return sign->arry == NULL ? 0 : (xtra_sign_l) sign->arry->len;
}

enum xtra_sign_e
xtra_sign_arry_type(xtra_sign_p sign, xtra_sign_l cell) {
    return xtra_sign_arry_get(sign, cell)->type;
}

xtra_sign_l
xtra_sign_arry_add(xtra_sign_p sign, xtra_sign_p _sign) {
    return (xtra_sign_l) xtra_arry_add(xtra_sign_arry(sign), _sign);
}

xtra_sign_p
xtra_sign_arry_get(xtra_sign_p sign, xtra_sign_l cell) {
    return (xtra_sign_p) xtra_arry_get(xtra_sign_arry(sign), cell);
}

int
xtra_sign_arry_has(xtra_sign_p sign, xtra_sign_l cell) {
    return xtra_arry_has(xtra_sign_arry(sign), cell);
}

void
xtra_sign_arry_set(xtra_sign_p sign, xtra_sign_l cell, xtra_sign_p _sign) {
    xtra_arry_set(xtra_sign_arry(sign), cell, _sign);
}

xtra_sign_p
xtra_sign_arry_pop(xtra_sign_p sign) {
    return (xtra_sign_p) xtra_arry_pop(xtra_sign_arry(sign));
}

xtra_sign_p
xtra_sign_arry_shift(xtra_sign_p sign) {
    return (xtra_sign_p) xtra_arry_shift(xtra_sign_arry(sign));
}

xtra_sign_l
xtra_sign_arry_unshift(xtra_sign_p sign, xtra_sign_p _sign) {
    return (xtra_sign_l) xtra_arry_unshift(xtra_sign_arry(sign), _sign);
}

xtra_sign_p
xtra_sign_arry_concat(xtra_sign_p sign, xtra_sign_p _sign)
{
    return xtra_sign_with_arry(XTRA_SIGN_DOC, xtra_arry_concat(xtra_sign_arry(sign), xtra_sign_arry(_sign)));
}

xtra_sign_p
xtra_sign_arry_slice(xtra_sign_p sign, xtra_sign_l start, xtra_sign_l count) {
    return xtra_sign_with_arry(XTRA_SIGN_DOC, xtra_arry_slice(xtra_sign_arry(sign), start, count));
}

xtra_sign_p
xtra_sign_arry_splice(xtra_sign_p sign, xtra_sign_l start, xtra_sign_l count) {
    return xtra_sign_with_arry(XTRA_SIGN_DOC, xtra_arry_splice(xtra_sign_arry(sign), start, count));
}

xtra_sign_p
xtra_sign_arry_vsplice(xtra_sign_p sign, xtra_sign_l start, xtra_sign_l count, xtra_sign_l argc, xtra_sign_p argv, ...) {
    va_list list;
    va_start(list, argv);
    xtra_sign_p sign_ = xtra_sign_with_arry(XTRA_SIGN_DOC, xtra_arry_vlsplice(xtra_sign_arry(sign), start, count, argc, argv, list));
    va_end(list);
    return sign_;
}

xtra_sign_p
xtra_sign_arry_asplice(xtra_sign_p sign, xtra_sign_l start, xtra_sign_l count, xtra_sign_p _sign) {
    return xtra_sign_with_arry(XTRA_SIGN_DOC, xtra_arry_asplice(xtra_sign_arry(sign), start, count, xtra_sign_arry(_sign)));
}

void
xtra_sign_arry_reverse(xtra_sign_p sign) {
    xtra_arry_reverse(xtra_sign_arry(sign));
}

void
xtra_sign_arry_free(xtra_sign_p sign, xtra_sign_l cell) {
    xtra_sign_free(xtra_sign_arry_get(sign, cell));
    xtra_sign_arry_set(sign, cell, NULL);
}

void
xtra_sign_free(xtra_sign_p sign) {
    if (sign->arry != NULL) { xtra_arry_free(sign->arry); }
    free(sign);
}

enum xtra_sign_e
xtra_sign_define(char * string) {
    enum xtra_sign_e type;

    if (strcmp(string, "+") == 0) {
        type = XTRA_SIGN_PLUS;
    } else if (strcmp(string, "-") == 0) {
        type = XTRA_SIGN_MINUS;
    } else if (strcmp(string, "*") == 0) {
        type = XTRA_SIGN_MULTIPLY;
    } else if (strcmp(string, "/") == 0) {
        type = XTRA_SIGN_DIVINE;
    } else if (strcmp(string, "%") == 0) {
        type = XTRA_SIGN_MOD;
    } else if (strcmp(string, "**") == 0) {
        type = XTRA_SIGN_EXP;
    } else if (strcmp(string, "++") == 0) {
        type = XTRA_SIGN_PLUS_PLUS;
    } else if (strcmp(string, "--") == 0) {
        type = XTRA_SIGN_MINUS_MINUS;
    } else if (strcmp(string, "!") == 0) {
        type = XTRA_SIGN_NOT;
    } else if (strcmp(string, "?") == 0) {
        type = XTRA_SIGN_QUESTION_MARK;
    } else if (strcmp(string, "??") == 0) {
        type = XTRA_SIGN_DOUBLE_QUESTION_MARK;
    } else if (strcmp(string, "'") == 0) {
        type = XTRA_SIGN_QUOTATION_MARK;
    } else if (strcmp(string, "\"") == 0) {
        type = XTRA_SIGN_DOUBLE_QUOTATION_MARK;
    } else if (strcmp(string, ",") == 0) {
        type = XTRA_SIGN_COMMA;
    } else if (strcmp(string, ".") == 0) {
        type = XTRA_SIGN_DOT;
    } else if (strcmp(string, "...") == 0) {
        type = XTRA_SIGN_TRIPLE_DOT;
    } else if (strcmp(string, ":") == 0) {
        type = XTRA_SIGN_COLON;
    } else if (strcmp(string, "::") == 0) {
        type = XTRA_SIGN_DOUBLE_COLON;
    } else if (strcmp(string, ";") == 0) {
        type = XTRA_SIGN_SEMICOLON;
    } else if (strcmp(string, "=") == 0) {
        type = XTRA_SIGN_ASSIGN;
    } else if (strcmp(string, "+=") == 0) {
        type = XTRA_SIGN_PLUS_ASSIGN;
    } else if (strcmp(string, "-=") == 0) {
        type = XTRA_SIGN_MINUS_ASSIGN;
    } else if (strcmp(string, "*=") == 0) {
        type = XTRA_SIGN_MULTIPLY_ASSIGN;
    } else if (strcmp(string, "/=") == 0) {
        type = XTRA_SIGN_DIVINE_ASSIGN;
    } else if (strcmp(string, "%=") == 0) {
        type = XTRA_SIGN_MOD_ASSIGN;
    } else if (strcmp(string, ">") == 0) {
        type = XTRA_SIGN_GREATER;
    } else if (strcmp(string, ">=") == 0) {
        type = XTRA_SIGN_GREATER_EQUAL;
    } else if (strcmp(string, "<") == 0) {
        type = XTRA_SIGN_LESS;
    } else if (strcmp(string, "<=") == 0) {
        type = XTRA_SIGN_LESS_EQUAL;
    } else if (strcmp(string, "==") == 0) {
        type = XTRA_SIGN_EQUAL;
    } else if (strcmp(string, "=>") == 0) {
        type = XTRA_SIGN_ASSOCIATE;
    } else if (strcmp(string, "===") == 0) {
        type = XTRA_SIGN_IDENTICAL;
    } else if (strcmp(string, "!=") == 0 || strcmp(string, "<>") == 0) {
        type = XTRA_SIGN_NOT_EQUAL;
    } else if (strcmp(string, "!==") == 0) {
        type = XTRA_SIGN_NOT_IDENTICAL;
    } else if (strcmp(string, "<=>") == 0) {
        type = XTRA_SIGN_NOT_SPACESHIP;
    } else if (strcasecmp(string, "and") == 0 || strcmp(string, "&&") == 0) {
        type = XTRA_SIGN_AND;
    } else if (strcasecmp(string, "or") == 0 || strcmp(string, "||") == 0) {
        type = XTRA_SIGN_OR;
    } else if (strcasecmp(string, "xor") == 0 || strcmp(string, "^^") == 0) {
        type = XTRA_SIGN_XOR;
    } else if (strcmp(string, "!") == 0) {
        type = XTRA_SIGN_NOT;
    } else if (strcmp(string, "&") == 0) {
        type = XTRA_SIGN_BITWISE_AND;
    } else if (strcmp(string, "|") == 0) {
        type = XTRA_SIGN_BITWISE_OR;
    } else if (strcmp(string, "^") == 0) {
        type = XTRA_SIGN_BITWISE_XOR;
    } else if (strcmp(string, "~") == 0) {
        type = XTRA_SIGN_BITWISE_NOT;
    } else if (strcmp(string, "<<") == 0) {
        type = XTRA_SIGN_BITWISE_SHIFT_L;
    } else if (strcmp(string, ">>") == 0) {
        type = XTRA_SIGN_BITWISE_SHIFT_R;
    } else if (strcasecmp(string, "if") == 0) {
        type = XTRA_SIGN_IF;
    } else if (strcasecmp(string, "else") == 0) {
        type = XTRA_SIGN_ELSE;
    } else if (strcasecmp(string, "elseif") == 0 || strcasecmp(string, "elsif") == 0 || strcasecmp(string, "elif") == 0) {
        type = XTRA_SIGN_ELSEIF;
    } else if (strcasecmp(string, "do") == 0) {
        type = XTRA_SIGN_DO;
    } else if (strcasecmp(string, "while") == 0) {
        type = XTRA_SIGN_WHILE; // minus-assign
    } else if (strcasecmp(string, "for") == 0) {
        type = XTRA_SIGN_FOR; // minus-assign
    } else if (strcasecmp(string, "each") == 0) {
        type = XTRA_SIGN_EACH; // minus-assign
    } else if (strcasecmp(string, "foreach") == 0) {
        type = XTRA_SIGN_FOREACH; // minus-assign
    } else if (strcasecmp(string, "end") == 0) {
        type = XTRA_SIGN_END; // minus-assign
    } else if (strcasecmp(string, "in") == 0) {
        type = XTRA_SIGN_IN; // minus-assign
    } else if (strcasecmp(string, "return") == 0) {
        type = XTRA_SIGN_RETURN; // minus-assign
    } else if (strcasecmp(string, "when") == 0) {
        type = XTRA_SIGN_WHEN; // minus-assign
    } else if (strcasecmp(string, "then") == 0) {
        type = XTRA_SIGN_THEN; // minus-assign
    } else if (strcasecmp(string, "as") == 0) {
        type = XTRA_SIGN_AS; // minus-assign
    } else if (strcasecmp(string, "is") == 0) {
        type = XTRA_SIGN_IS; // minus-assign
    } else if (strcasecmp(string, "switch") == 0) {
        type = XTRA_SIGN_SWITCH; // minus-assign
    } else if (strcasecmp(string, "case") == 0) {
        type = XTRA_SIGN_CASE; // minus-assign
    } else if (strcasecmp(string, "default") == 0) {
        type = XTRA_SIGN_DEFAULT; // minus-assign
    } else if (strcasecmp(string, "break") == 0) {
        type = XTRA_SIGN_BREAK; // minus-assign
    } else if (strcmp(string, "[") == 0) {
        type = XTRA_SIGN_BRACKET_SQUARE_L; // minus-assign
    } else if (strcmp(string, "]") == 0) {
        type = XTRA_SIGN_BRACKET_SQUARE_R; // minus-assign
    } else if (strcmp(string, "(") == 0) {
        type = XTRA_SIGN_BRACKET_ROUND_L; // minus-assign
    } else if (strcmp(string, ")") == 0) {
        type = XTRA_SIGN_BRACKET_ROUND_R; // minus-assign
    } else if (strcmp(string, "{") == 0) {
        type = XTRA_SIGN_BRACKET_CURLY_L; // minus-assign
    } else if (strcmp(string, "}") == 0) {
        type = XTRA_SIGN_BRACKET_CURLY_R; // minus-assign
    } else if (strcmp(string, "<") == 0) {
        type = XTRA_SIGN_BRACKET_ANGLE_L; // minus-assign
    } else if (strcmp(string, ">") == 0) {
        type = XTRA_SIGN_BRACKET_ANGLE_R; // minus-assign
    } else if (strcasecmp(string, "null") == 0) {
        type = XTRA_SIGN_NULL;
    } else if (strcasecmp(string, "var") == 0) {
        type = XTRA_SIGN_TYPE; // XTRA_SIGN_VAR;
    } else if (strcmp(string, "int") == 0 || strcasecmp(string, "integer") == 0) {
        type = XTRA_SIGN_TYPE; //XTRA_SIGN_INT;
    } else if (strcasecmp(string, "double") == 0 || strcasecmp(string, "float") == 0) {
        type = XTRA_SIGN_TYPE; //XTRA_SIGN_DOUBLE;
    } else if (strcasecmp(string, "bool") == 0 || strcasecmp(string, "boolean") == 0) {
        type = XTRA_SIGN_TYPE; //XTRA_SIGN_BOOL;
    } else if (strcasecmp(string, "true") == 0) {
        type = XTRA_SIGN_TRUE;
    } else if (strcasecmp(string, "false") == 0) {
        type = XTRA_SIGN_FALSE;
    } else if (strcasecmp(string, "sting") == 0 || strcasecmp(string, "str") == 0) {
        type = XTRA_SIGN_TYPE; //XTRA_SIGN_STRING;
    } else if (strcasecmp(string, "enum") == 0) {
        type = XTRA_SIGN_TYPE; //XTRA_SIGN_ENUM;
    } else if (strcasecmp(string, "const") == 0) {
        type = XTRA_SIGN_TYPE; //XTRA_SIGN_CONST;
    } else if (strcasecmp(string, "array") == 0 || strcasecmp(string, "list") == 0) {
        type = XTRA_SIGN_TYPE; //XTRA_SIGN_ARRAY;
    } else if (strcasecmp(string, "dictionary") == 0) {
        type = XTRA_SIGN_TYPE; //XTRA_SIGN_DICTIONARY;
    } else if (strcasecmp(string, "hash") == 0) {
        type = XTRA_SIGN_TYPE; //XTRA_SIGN_HASH;
    } else if (strcasecmp(string, "use") == 0 || strcasecmp(string, "using") == 0) {
        type = XTRA_SIGN_USE;
    } else if (strcasecmp(string, "function") == 0 || strcasecmp(string, "func") == 0 || strcasecmp(string, "fn") == 0) {
        type = XTRA_SIGN_FUNCTION;
    } else if (strcasecmp(string, "namespace") == 0 || strcasecmp(string, "ns") == 0) {
        type = XTRA_SIGN_NAMESPACE;
    } else if (strcasecmp(string, "class") == 0) {
        type = XTRA_SIGN_CLASS;
    } else if (strcasecmp(string, "throw") == 0) {
        type = XTRA_SIGN_THROW;
    } else if (strcasecmp(string, "try") == 0) {
        type = XTRA_SIGN_TRY;
    } else if (strcasecmp(string, "catch") == 0) {
        type = XTRA_SIGN_CATCH;
    } else if (strcasecmp(string, "finally") == 0) {
        type = XTRA_SIGN_FINALLY;
    } else if (strcasecmp(string, "new") == 0) {
        type = XTRA_SIGN_NEW;
    } else if (strcasecmp(string, "delete") == 0 || strcasecmp(string, "del") == 0) {
        type = XTRA_SIGN_DELETE;
    } else if (strcasecmp(string, "object") == 0) {
        type = XTRA_SIGN_OBJECT;
    } else if (strcasecmp(string, "static") == 0) {
        type = XTRA_SIGN_STATIC;
    } else if (strcasecmp(string, "abstract") == 0) {
        type = XTRA_SIGN_ABSTRACT;
    } else if (strcasecmp(string, "public") == 0) {
        type = XTRA_SIGN_PUBLIC;
    } else if (strcasecmp(string, "protected") == 0) {
        type = XTRA_SIGN_PROTECTED;
    } else if (strcasecmp(string, "private") == 0) {
        type = XTRA_SIGN_PRIVATE;
    } else if (strcasecmp(string, "extends") == 0) {
        type = XTRA_SIGN_EXTENDS;
    } else if (strcasecmp(string, "interface") == 0) {
        type = XTRA_SIGN_INTERFACE;
    } else if (strcasecmp(string, "implements") == 0) {
        type = XTRA_SIGN_IMPLEMENTS;
    } else if (strcasecmp(string, "async") == 0) {
        type = XTRA_SIGN_ASYNC;
    }  else if (strcasecmp(string, "await") == 0) {
        type = XTRA_SIGN_AWAIT;
    } else if (strcasecmp(string, "#") == 0) {
        type = XTRA_SIGN_PPD_DIR_NULL;
    } else if (strcasecmp(string, "#define") == 0) {
        type = XTRA_SIGN_PPD_DIR_DEFINE;
    } else if (strcasecmp(string, "#error") == 0) {
        type = XTRA_SIGN_PPD_ERROR;
    } else if (strcasecmp(string, "#if") == 0) {
        type = XTRA_SIGN_PPD_IF;
    } else if (strcasecmp(string, "#elif") == 0) {
        type = XTRA_SIGN_PPD_ELIF;
    } else if (strcasecmp(string, "#endif") == 0) {
        type = XTRA_SIGN_PPD_ENDIF;
    } else if (strcasecmp(string, "#ifdef") == 0) {
        type = XTRA_SIGN_PPD_IFDEF;
    } else if (strcasecmp(string, "#ifndef") == 0) {
        type = XTRA_SIGN_PPD_IFNDEF;
    } else if (strcasecmp(string, "#else") == 0) {
        type = XTRA_SIGN_PPD_ELSE;
    } else if (strcasecmp(string, "#include") == 0) {
        type = XTRA_SIGN_PPD_INCLUDE;
    } else if (strcasecmp(string, "#import") == 0) {
        type = XTRA_SIGN_PPD_IMPORT;
    } else if (strcasecmp(string, "#line") == 0) {
        type = XTRA_SIGN_PPD_LINE;
    } else if (strcasecmp(string, "#undef") == 0) {
        type = XTRA_SIGN_PPD_UNDEF;
    } else if (strcasecmp(string, "#use") == 0 || strcasecmp(string, "#using") == 0) {
        type = XTRA_SIGN_PPD_USE;
    }  else {
        type = XTRA_SIGN_UNDEFINED;
    }

    return type;
}
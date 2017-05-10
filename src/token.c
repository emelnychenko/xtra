//
// Created by eugen on 5/6/2017.
//

#include "token.h"

xtra_token_p
xtra_token_constuct(enum xtra_token_type type)
{
    xtra_token_p token = (xtra_token_p) malloc(sizeof(xtra_token_t));
    token->type         = type;
    token->size         = 0;
    token->line         = 0;
    token->column       = 0;
    token->lexer        = NULL;
    token->file         = NULL;
    token->namespace    = NULL;
    token->child  = malloc(sizeof(xtra_token_p *));
    return token;
}

enum xtra_token_type
xtra_token_get_type_on_position(xtra_token_p script, long position)
{
    return script->child[position]->type;
}

int
xtra_token_is_type_on_position(xtra_token_p script, long position, enum xtra_token_type type)
{
    return script->child[position]->type == type;
}

int
xtra_token_child_exists(xtra_token_p script, long position)
{
    return position > 0 && position < script->size;
}

xtra_token_p
xtra_token_get_child(xtra_token_p script, long position)
{
    return script->child[position];
}

void
xtra_token_free_child(xtra_token_p script, long position)
{
    return xtra_token_forget(script->child[position]);
}

void
xtra_token_add_child(xtra_token_p script, xtra_token_p token)
{
    script->size++;
    script->child = realloc(script->child, (sizeof (xtra_token_p *) * script->size));
    script->child[script->size - 1] = token;
}

void
xtra_token_replace_range_by_one(xtra_token_p script, long start, long length, xtra_token_p token)
{
    script->child[start] = token;

    if (length == 0)
        return;

    long end = start + length;

    while (++start <= end) {
        while (++start < script->size) {
            script->child[start - 1] = script->child[start];
        }
    }

    // realloc
    script->size -= length;
    script->child = realloc(
            script->child, (sizeof (xtra_token_p *) * script->size)
    );
}

void
xtra_token_forget(xtra_token_p token)
{
    if (token->size < 0) {
        // token already cleaned
        return;
    }

    if (token->lexer != NULL) {
        token->lexer = NULL;
//        printf("%s\n", token->lexer);
        //free(token->lexer);
    }

    token->size = -1;
    free(token->child);
    free(token);
}

void
xtra_token_debug(xtra_token_p script, int padding)
{
    printf("%ds{\n", padding);

    padding += 2;

    long position = -1;
    while (--position < script->size) {
        xtra_token_p token = script->child[position];
        printf("%d", script->child[position]->type);

        if (script->child[position]->size > 0) {
            xtra_token_debug(script->child[position], padding);
        }
    }

    padding -= 2;
    printf("%ds}\n", padding);
}

void
xtra_token_forget_deep(xtra_token_p token)
{

}

enum xtra_token_type
xtra_token_define_type(char * expression)
{
    enum xtra_token_type token_type;

    if (strcmp(expression, "+") == 0) {
        token_type = XTRA_TOKEN_PLUS;
    } else if (strcmp(expression, "-") == 0) {
        token_type = XTRA_TOKEN_MINUS;
    } else if (strcmp(expression, "*") == 0) {
        token_type = XTRA_TOKEN_MULTIPLY;
    } else if (strcmp(expression, "/") == 0) {
        token_type = XTRA_TOKEN_DIVINE;
    } else if (strcmp(expression, "%") == 0) {
        token_type = XTRA_TOKEN_MOD;
    } else if (strcmp(expression, "**") == 0) {
        token_type = XTRA_TOKEN_EXP;
    } else if (strcmp(expression, "++") == 0) {
        token_type = XTRA_TOKEN_PLUS_PLUS;
    } else if (strcmp(expression, "--") == 0) {
        token_type = XTRA_TOKEN_MINUS_MINUS;
    } else if (strcmp(expression, "!") == 0) {
        token_type = XTRA_TOKEN_NOT;
    } else if (strcmp(expression, "?") == 0) {
        token_type = XTRA_TOKEN_QUESTION_MARK;
    } else if (strcmp(expression, "??") == 0) {
        token_type = XTRA_TOKEN_DOUBLE_QUESTION_MARK;
    } else if (strcmp(expression, "'") == 0) {
        token_type = XTRA_TOKEN_QUOTATION_MARK;
    } else if (strcmp(expression, "\"") == 0) {
        token_type = XTRA_TOKEN_DOUBLE_QUOTATION_MARK;
    } else if (strcmp(expression, ",") == 0) {
        token_type = XTRA_TOKEN_COMMA;
    } else if (strcmp(expression, ".") == 0) {
        token_type = XTRA_TOKEN_DOT;
    } else if (strcmp(expression, "...") == 0) {
        token_type = XTRA_TOKEN_TRIPLE_DOT;
    } else if (strcmp(expression, ":") == 0) {
        token_type = XTRA_TOKEN_COLON;
    } else if (strcmp(expression, "::") == 0) {
        token_type = XTRA_TOKEN_DOUBLE_COLON;
    } else if (strcmp(expression, ";") == 0) {
        token_type = XTRA_TOKEN_SEMICOLON;
    } else if (strcmp(expression, "=") == 0) {
        token_type = XTRA_TOKEN_ASSIGN;
    } else if (strcmp(expression, "+=") == 0) {
        token_type = XTRA_TOKEN_PLUS_ASSIGN;
    } else if (strcmp(expression, "-=") == 0) {
        token_type = XTRA_TOKEN_MINUS_ASSIGN;
    } else if (strcmp(expression, "*=") == 0) {
        token_type = XTRA_TOKEN_MULTIPLY_ASSIGN;
    } else if (strcmp(expression, "/=") == 0) {
        token_type = XTRA_TOKEN_DIVINE_ASSIGN;
    } else if (strcmp(expression, "%=") == 0) {
        token_type = XTRA_TOKEN_MOD_ASSIGN;
    } else if (strcmp(expression, ">") == 0) {
        token_type = XTRA_TOKEN_GREATER;
    } else if (strcmp(expression, ">=") == 0) {
        token_type = XTRA_TOKEN_GREATER_EQUAL;
    } else if (strcmp(expression, "<") == 0) {
        token_type = XTRA_TOKEN_LESS;
    } else if (strcmp(expression, "<=") == 0) {
        token_type = XTRA_TOKEN_LESS_EQUAL;
    } else if (strcmp(expression, "==") == 0) {
        token_type = XTRA_TOKEN_EQUAL;
    } else if (strcmp(expression, "=>") == 0) {
        token_type = XTRA_TOKEN_ASSOCIATE;
    } else if (strcmp(expression, "===") == 0) {
        token_type = XTRA_TOKEN_IDENTICAL;
    } else if (strcmp(expression, "!=") == 0 || strcmp(expression, "<>") == 0) {
        token_type = XTRA_TOKEN_NOT_EQUAL;
    } else if (strcmp(expression, "!==") == 0) {
        token_type = XTRA_TOKEN_NOT_IDENTICAL;
    } else if (strcmp(expression, "<=>") == 0) {
        token_type = XTRA_TOKEN_NOT_SPACESHIP;
    } else if (strcasecmp(expression, "and") == 0 || strcmp(expression, "&&") == 0) {
        token_type = XTRA_TOKEN_AND;
    } else if (strcasecmp(expression, "or") == 0 || strcmp(expression, "||") == 0) {
        token_type = XTRA_TOKEN_OR;
    } else if (strcasecmp(expression, "xor") == 0 || strcmp(expression, "^^") == 0) {
        token_type = XTRA_TOKEN_XOR;
    } else if (strcmp(expression, "!") == 0) {
        token_type = XTRA_TOKEN_NOT;
    } else if (strcmp(expression, "&") == 0) {
        token_type = XTRA_TOKEN_BITWISE_AND;
    } else if (strcmp(expression, "|") == 0) {
        token_type = XTRA_TOKEN_BITWISE_OR;
    } else if (strcmp(expression, "^") == 0) {
        token_type = XTRA_TOKEN_BITWISE_XOR;
    } else if (strcmp(expression, "~") == 0) {
        token_type = XTRA_TOKEN_BITWISE_NOT;
    } else if (strcmp(expression, "<<") == 0) {
        token_type = XTRA_TOKEN_BITWISE_SHIFT_L;
    } else if (strcmp(expression, ">>") == 0) {
        token_type = XTRA_TOKEN_BITWISE_SHIFT_R;
    } else if (strcasecmp(expression, "if") == 0) {
        token_type = XTRA_TOKEN_IF;
    } else if (strcasecmp(expression, "else") == 0) {
        token_type = XTRA_TOKEN_ELSE;
    } else if (strcasecmp(expression, "elseif") == 0 || strcasecmp(expression, "elsif") == 0 || strcasecmp(expression, "elif") == 0) {
        token_type = XTRA_TOKEN_ELSEIF;
    } else if (strcasecmp(expression, "do") == 0) {
        token_type = XTRA_TOKEN_DO;
    } else if (strcasecmp(expression, "while") == 0) {
        token_type = XTRA_TOKEN_WHILE; // minus-assign
    } else if (strcasecmp(expression, "for") == 0) {
        token_type = XTRA_TOKEN_FOR; // minus-assign
    } else if (strcasecmp(expression, "each") == 0) {
        token_type = XTRA_TOKEN_EACH; // minus-assign
    } else if (strcasecmp(expression, "foreach") == 0) {
        token_type = XTRA_TOKEN_FOREACH; // minus-assign
    } else if (strcasecmp(expression, "end") == 0) {
        token_type = XTRA_TOKEN_END; // minus-assign
    } else if (strcasecmp(expression, "in") == 0) {
        token_type = XTRA_TOKEN_IN; // minus-assign
    } else if (strcasecmp(expression, "return") == 0) {
        token_type = XTRA_TOKEN_RETURN; // minus-assign
    } else if (strcasecmp(expression, "when") == 0) {
        token_type = XTRA_TOKEN_WHEN; // minus-assign
    } else if (strcasecmp(expression, "then") == 0) {
        token_type = XTRA_TOKEN_THEN; // minus-assign
    } else if (strcasecmp(expression, "as") == 0) {
        token_type = XTRA_TOKEN_AS; // minus-assign
    } else if (strcasecmp(expression, "is") == 0) {
        token_type = XTRA_TOKEN_IS; // minus-assign
    } else if (strcasecmp(expression, "switch") == 0) {
        token_type = XTRA_TOKEN_SWITCH; // minus-assign
    } else if (strcasecmp(expression, "case") == 0) {
        token_type = XTRA_TOKEN_CASE; // minus-assign
    } else if (strcasecmp(expression, "default") == 0) {
        token_type = XTRA_TOKEN_DEFAULT; // minus-assign
    } else if (strcasecmp(expression, "break") == 0) {
        token_type = XTRA_TOKEN_BREAK; // minus-assign
    } else if (strcmp(expression, "[") == 0) {
        token_type = XTRA_TOKEN_BRACKET_SQUARE_L; // minus-assign
    } else if (strcmp(expression, "]") == 0) {
        token_type = XTRA_TOKEN_BRACKET_SQUARE_R; // minus-assign
    } else if (strcmp(expression, "(") == 0) {
        token_type = XTRA_TOKEN_BRACKET_ROUND_L; // minus-assign
    } else if (strcmp(expression, ")") == 0) {
        token_type = XTRA_TOKEN_BRACKET_ROUND_R; // minus-assign
    } else if (strcmp(expression, "{") == 0) {
        token_type = XTRA_TOKEN_BRACKET_CURLY_L; // minus-assign
    } else if (strcmp(expression, "}") == 0) {
        token_type = XTRA_TOKEN_BRACKET_CURLY_R; // minus-assign
    } else if (strcmp(expression, "<") == 0) {
        token_type = XTRA_TOKEN_BRACKET_ANGLE_L; // minus-assign
    } else if (strcmp(expression, ">") == 0) {
        token_type = XTRA_TOKEN_BRACKET_ANGLE_R; // minus-assign
    } else if (strcasecmp(expression, "null") == 0) {
        token_type = XTRA_TOKEN_NULL;
    } else if (strcasecmp(expression, "var") == 0) {
        token_type = XTRA_TOKEN_TYPE; // XTRA_TOKEN_VAR;
    } else if (strcmp(expression, "int") == 0 || strcasecmp(expression, "integer") == 0) {
        token_type = XTRA_TOKEN_TYPE; //XTRA_TOKEN_INT;
    } else if (strcasecmp(expression, "double") == 0 || strcasecmp(expression, "float") == 0) {
        token_type = XTRA_TOKEN_TYPE; //XTRA_TOKEN_DOUBLE;
    } else if (strcasecmp(expression, "bool") == 0 || strcasecmp(expression, "boolean") == 0) {
        token_type = XTRA_TOKEN_TYPE; //XTRA_TOKEN_BOOL;
    } else if (strcasecmp(expression, "true") == 0) {
        token_type = XTRA_TOKEN_TRUE;
    } else if (strcasecmp(expression, "false") == 0) {
        token_type = XTRA_TOKEN_FALSE;
    } else if (strcasecmp(expression, "sting") == 0 || strcasecmp(expression, "str") == 0) {
        token_type = XTRA_TOKEN_TYPE; //XTRA_TOKEN_STRING;
    } else if (strcasecmp(expression, "enum") == 0) {
        token_type = XTRA_TOKEN_TYPE; //XTRA_TOKEN_ENUM;
    } else if (strcasecmp(expression, "const") == 0) {
        token_type = XTRA_TOKEN_TYPE; //XTRA_TOKEN_CONST;
    } else if (strcasecmp(expression, "array") == 0 || strcasecmp(expression, "list") == 0) {
        token_type = XTRA_TOKEN_TYPE; //XTRA_TOKEN_ARRAY;
    } else if (strcasecmp(expression, "dictionary") == 0) {
        token_type = XTRA_TOKEN_TYPE; //XTRA_TOKEN_DICTIONARY;
    } else if (strcasecmp(expression, "hash") == 0) {
        token_type = XTRA_TOKEN_TYPE; //XTRA_TOKEN_HASH;
    } else if (strcasecmp(expression, "use") == 0 || strcasecmp(expression, "using") == 0) {
        token_type = XTRA_TOKEN_USE;
    } else if (strcasecmp(expression, "function") == 0 || strcasecmp(expression, "func") == 0 || strcasecmp(expression, "fn") == 0) {
        token_type = XTRA_TOKEN_FUNCTION;
    } else if (strcasecmp(expression, "namespace") == 0 || strcasecmp(expression, "ns") == 0) {
        token_type = XTRA_TOKEN_NAMESPACE;
    } else if (strcasecmp(expression, "class") == 0) {
        token_type = XTRA_TOKEN_CLASS;
    } else if (strcasecmp(expression, "throw") == 0) {
        token_type = XTRA_TOKEN_THROW;
    } else if (strcasecmp(expression, "try") == 0) {
        token_type = XTRA_TOKEN_TRY;
    } else if (strcasecmp(expression, "catch") == 0) {
        token_type = XTRA_TOKEN_CATCH;
    } else if (strcasecmp(expression, "finally") == 0) {
        token_type = XTRA_TOKEN_FINALLY;
    } else if (strcasecmp(expression, "new") == 0) {
        token_type = XTRA_TOKEN_NEW;
    } else if (strcasecmp(expression, "delete") == 0 || strcasecmp(expression, "del") == 0) {
        token_type = XTRA_TOKEN_DELETE;
    } else if (strcasecmp(expression, "object") == 0) {
        token_type = XTRA_TOKEN_OBJECT;
    } else if (strcasecmp(expression, "static") == 0) {
        token_type = XTRA_TOKEN_STATIC;
    } else if (strcasecmp(expression, "abstract") == 0) {
        token_type = XTRA_TOKEN_ABSTRACT;
    } else if (strcasecmp(expression, "public") == 0) {
        token_type = XTRA_TOKEN_PUBLIC;
    } else if (strcasecmp(expression, "protected") == 0) {
        token_type = XTRA_TOKEN_PROTECTED;
    } else if (strcasecmp(expression, "private") == 0) {
        token_type = XTRA_TOKEN_PRIVATE;
    } else if (strcasecmp(expression, "extends") == 0) {
        token_type = XTRA_TOKEN_EXTENDS;
    } else if (strcasecmp(expression, "interface") == 0) {
        token_type = XTRA_TOKEN_INTERFACE;
    } else if (strcasecmp(expression, "implements") == 0) {
        token_type = XTRA_TOKEN_IMPLEMENTS;
    } else if (strcasecmp(expression, "async") == 0) {
        token_type = XTRA_TOKEN_ASYNC;
    }  else if (strcasecmp(expression, "await") == 0) {
        token_type = XTRA_TOKEN_AWAIT;
    } else if (strcasecmp(expression, "#") == 0) {
        token_type = XTRA_TOKEN_PPD_DIR_NULL;
    } else if (strcasecmp(expression, "#define") == 0) {
        token_type = XTRA_TOKEN_PPD_DIR_DEFINE;
    } else if (strcasecmp(expression, "#error") == 0) {
        token_type = XTRA_TOKEN_PPD_ERROR;
    } else if (strcasecmp(expression, "#if") == 0) {
        token_type = XTRA_TOKEN_PPD_IF;
    } else if (strcasecmp(expression, "#elif") == 0) {
        token_type = XTRA_TOKEN_PPD_ELIF;
    } else if (strcasecmp(expression, "#endif") == 0) {
        token_type = XTRA_TOKEN_PPD_ENDIF;
    } else if (strcasecmp(expression, "#ifdef") == 0) {
        token_type = XTRA_TOKEN_PPD_IFDEF;
    } else if (strcasecmp(expression, "#ifndef") == 0) {
        token_type = XTRA_TOKEN_PPD_IFNDEF;
    } else if (strcasecmp(expression, "#else") == 0) {
        token_type = XTRA_TOKEN_PPD_ELSE;
    } else if (strcasecmp(expression, "#include") == 0) {
        token_type = XTRA_TOKEN_PPD_INCLUDE;
    } else if (strcasecmp(expression, "#import") == 0) {
        token_type = XTRA_TOKEN_PPD_IMPORT;
    } else if (strcasecmp(expression, "#line") == 0) {
        token_type = XTRA_TOKEN_PPD_LINE;
    } else if (strcasecmp(expression, "#undef") == 0) {
        token_type = XTRA_TOKEN_PPD_UNDEF;
    } else if (strcasecmp(expression, "#use") == 0 || strcasecmp(expression, "#using") == 0) {
        token_type = XTRA_TOKEN_PPD_USE;
    }  else {
        token_type = XTRA_TOKEN_UNDEFINED;
    }

    return token_type;
}
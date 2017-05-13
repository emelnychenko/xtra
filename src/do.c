//
// Created by eugen on 5/9/2017.
//

#include "do.h"

void
xtra_do_condition_replace(xtra_token_p script, long * position)
{
    long start = *position;

    if ((start + 3) >= script->child[*position]->size) {
        // error condition
        xtra_error("Unexpected end of file in \"do\".", 0);
    }

    if (script->child[++start]->type != XTRA_TOKEN_BRACKET_CURLY) {
        // error condition
        xtra_error("Missed \"{[code]}\" condition in \"do\".", 0);
    }

    if (script->child[++start]->type != XTRA_TOKEN_WHILE) {
        // error condition
        xtra_error("Missed \"while\" keyword in \"do\".", 0);
    }

    //
    if (script->child[++start]->type != XTRA_TOKEN_BRACKET_ROUND) {
        // error condition
        xtra_error("Missed \"([code])\" condition in \"while\".", 0);
    }

    // remove & free do token
    xtra_token_free(
        xtra_token_del_child(script, *position)
    );

    // shuffle
    xtra_token_p token_curly        = script->child[*position];
    xtra_token_p token_round        = script->child[*position + 2];

    script->child[*position]        = script->child[*position + 1];
    script->child[*position + 1]    = token_round;
    script->child[*position + 2]    = token_curly;

    --(*position);
}

//
// Created by eugen on 5/8/2017.
//

#ifndef EXTRA_LOGICAL_H
#define EXTRA_LOGICAL_H

#include "../token.h"
#include "../error.h"

void
xtra_parser_logical_condition(xtra_token_p script);

void
xtra_parser_logical_condition_if_iterate(xtra_token_p);

void
xtra_parser_logical_condition_if(xtra_token_p, long *);

void
xtra_parser_logical_condition_elseif(xtra_token_p, long *);

// void
// xtra_parser_logical_condition_switch_iterate(xtra_token_p);
//
// void
// xtra_parser_logical_condition_switch(xtra_token_p, long *);

//void
//xtra_parser_logical_condition_ternary_iterate(xtra_token_p);

//void
//xtra_parser_logical_condition_ppd_if();
//
//void
//xtra_parser_logical_condition_ppd_ifdef();
//
//void
//xtra_parser_logical_condition_ppd_ifndef();
//
//void
//xtra_parser_logical_condition_ppd_elseif();
//
//void
//xtra_parser_logical_condition_ppd_switch();
//
//void
//xtra_parser_logical_condition_ppd_case();
//
//void
//xtra_parser_logical_condition_ppd_case();

#endif //EXTRA_LOGICAL_H

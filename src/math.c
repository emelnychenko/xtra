//
// Created by eugen on 5/1/2017.
//

#include "math.h"
#include <math.h>

xtra_var_p
xtra_math_abs(xtra_var_p var)
{
    switch (var->type)
    {
        case XTRA_VAR_INT:
            return xtra_var_int_construct(
                    abs(var->xtra_var_int)
            );
            break;

        case XTRA_VAR_DOUBLE:
            return xtra_var_double_construct(
                    fabs(var->xtra_var_double)
            );
            break;
    }
}

xtra_var_p
xtra_math_acos(xtra_var_p var)
{
    return xtra_var_double_construct(
            acos(var->xtra_var_double)
    );
}

xtra_var_p
xtra_math_acosh(xtra_var_p var)
{
    return xtra_var_double_construct(
            acosh(var->xtra_var_double)
    );
}

xtra_var_p
xtra_math_asin(xtra_var_p var)
{
    return xtra_var_double_construct(
            asin(var->xtra_var_double)
    );
}

xtra_var_p
xtra_math_asinh(xtra_var_p var)
{
    return xtra_var_double_construct(
            acosh(var->xtra_var_double)
    );
}

xtra_var_p
xtra_math_atan2(xtra_var_p var1, xtra_var_p var2)
{
    return xtra_var_double_construct(
            atan2(var1->xtra_var_double, var2->xtra_var_double)
    );
}

xtra_var_p
xtra_math_atan(xtra_var_p var)
{
    return xtra_var_double_construct(
            atan(var->xtra_var_double)
    );
}

xtra_var_p
xtra_math_atanh(xtra_var_p var)
{
    return xtra_var_double_construct(
            atanh(var->xtra_var_double)
    );
}

// base convert

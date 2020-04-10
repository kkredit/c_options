/**
 * \file
 *
 * \brief
 * \details
 *
 * \copyright Copyright (c) 2020, Kevin Kredit.
 */

#include <stdio.h>
#include "lib.h"

int main() {
    int x = 1;
    int y = 2;
    OPTION(int) sum = lib_add(&x, &y);
    printf("Sum: %d\n", UNWRAP_OR(int, sum, 0));
    // UNWRAP_OR needs to be a macro for generality, but option_int_t needs to be a forward
    // declaration (so unable to be expanded locally in a macro) for type enforcement...
    // Solution: it is a macro that expands to a function call
    sum = lib_add(&x, NULL);
    printf("Sum: %d\n", UNWRAP_OR(int, sum, 0));

    return 0;
}

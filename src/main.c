/**
 * \file main.c
 *
 * \brief An example application using a library with option types
 * \details
 *      The application does not need to include "options.h", since the library
 *      already has. It is ready to take advantage of the forced error handling
 *      through the type system.
 *
 * \copyright Copyright (c) 2020, Kevin Kredit.
 */

#include <stdio.h>
#include <assert.h>
#include "lib.h"

int main() {
    int x = 1;
    int y = 2;

    OPTION(int) sum1 = lib_add(&x, &y);
    assert(IS_JUST(int, sum1));

    // printf("Sum: %d\n", sum); // -- compile-time type error!
    printf("Sum1 unwrapped: %d\n", UNWRAP(int, sum1));
    printf("Sum1 unwrap-ored: %d\n", UNWRAP_OR(int, sum1, 0));

    OPTION(int) sum2 = lib_add(&x, NULL);
    assert(IS_NONE(int, sum2));

    // printf("Sum2 unwrapped: %d\n", UNWRAP(int, sum2)); // -- assert failure in UNWRAP!
    printf("Sum2 unwrap-ored: %d\n", UNWRAP_OR(int, sum2, 0));

    OPTION(int) sum1or2 = OR(int, sum1, sum2);
    printf("sum1or2 unwrapped: %d\n", UNWRAP(int, sum1or2));
    OPTION(int) sum2or1 = OR(int, sum2, sum1);
    printf("sum2or1 unwrapped: %d\n", UNWRAP(int, sum2or1));

    OPTION(int) sum1and2 = AND(int, sum1, sum2);
    assert(IS_NONE(int, sum1and2));
    OPTION(int) sum2and1 = AND(int, sum2, sum1);
    assert(IS_NONE(int, sum2and1));

    return 0;
}

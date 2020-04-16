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

    /* JUST and NONE constructers */
    OPTION(int) just3 = JUST(int, 3);
    OPTION(int) none = NONE(int);

    // assert(3 != JUST(int, 3)); // Compile-time error, incomparable types
    // assert(NULL != NONE(int)); // Compile-time error, incomparable types


    /* IS_NONE and IS_JUST */
    assert(IS_JUST(int, just3));
    assert(!IS_NONE(int, just3));

    assert(!IS_JUST(int, none));
    assert(IS_NONE(int, none));


    /* UNWRAP and UNWRAP_OR */
    assert(3 == UNWRAP(int, just3));
    // UNWRAP(int, none); // Run-time assertion failure, cannot unwrap a 'none'

    assert(3 == UNWRAP_OR(int, just3, 4));
    assert(4 == UNWRAP_OR(int, none, 4));


    /* EQ  and EQUAL */
    // assert(just3 == just3); // Compile-time error, incomparable types
    assert(EQ(int, just3, just3));
    assert(!EQ(int, none, just3));
    assert(!EQ(int, just3, none));
    assert(EQ(int, none, none));
    assert(!EQUAL(int, none, none));

    OPTION(int) another3 = JUST(int, 3);
    assert(EQ(int, just3, another3));


    /* OR and AND */
    OPTION(int) just5 = JUST(int, 5);

    assert(EQ(int, just3, OR(int, just3, none)));
    assert(EQ(int, just3, OR(int, just3, just5)));
    assert(EQ(int, just5, OR(int, none, just5)));
    assert(EQ(int, none, OR(int, none, none)));

    assert(EQ(int, none, AND(int, just3, none)));
    assert(EQ(int, just5, AND(int, just3, just5)));
    assert(EQ(int, none, AND(int, none, just5)));
    assert(EQ(int, none, AND(int, none, none)));


    /* A successful API call */
    int x = 1;
    int y = 2;

    OPTION(int) sum = lib_add(&x, &y);
    // printf("Sum: %d\n", sum); // Compile-time type error, 'sum' is not of type 'int'
    assert(IS_JUST(int, sum));
    assert(3 == UNWRAP(int, sum));


    /* An unsuccessful API call */
    sum = lib_add(&x, NULL);
    assert(IS_NONE(int, sum));


    /* IF_LET */
    IF_LET(int, just3, z, {
        assert(3 == z);
    })
    // assert(3 == z);; // Compile-time type error, 'z' is undefined

    IF_LET(int, none, z, {
        assert(false);
        (void)z;
    })


    /* IF_NOT */
    IF_NOT(int, just3, {
        assert(false);
    })

    IF_NOT(int, none, {
        assert(true);
    })

    return 0;
}

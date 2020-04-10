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
#include "lib.h"

int main() {
    int x = 1;
    int y = 2;

    OPTION(int) sum = lib_add(&x, &y);
    // printf("Sum: %d\n", sum); // -- type error!
    printf("Sum: %d\n", UNWRAP_OR(int, sum, 0));

    sum = lib_add(&x, NULL);
    printf("Sum: %d\n", UNWRAP_OR(int, sum, 0));

    return 0;
}

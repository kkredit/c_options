/**
 * \file lib.c
 *
 * \brief An example library that uses option types in its API
 * \details
 *      Includes "options_internal.h" and declares "DEFN_OPTION(int)" in order
 *      to implement the OPTION(int) type for the API.
 *
 * \copyright Copyright (c) 2020, Kevin Kredit.
 */

#include <stddef.h>
#include "lib.h"
#include "options_internal.h"

DEFN_OPTION(int)

OPTION(int) lib_add(int *x, int *y) {
    if (NULL == x || NULL == y) {
        return NONE(int);
    }
    else {
        return JUST(int, *x + *y);
    }
}

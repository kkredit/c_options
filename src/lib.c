/**
 * \file
 *
 * \brief
 * \details
 *
 * \copyright Copyright (c) 2020, Kevin Kredit.
 */

#include <stddef.h>
#include "lib.h"

DEFN_OPTION(int)

OPTION(int) lib_add(int *x, int *y) {
    if (NULL == x || NULL == y) {
        return NONE(int);
    }
    else {
        return JUST(int, *x + *y);
    }
}

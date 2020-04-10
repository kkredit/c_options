/**
 * \file lib.h
 *
 * \brief An example library that uses option types in its API
 * \details
 *      Includes "options.h" and declares "DECL_OPTION(int)" in order to make
 *      the OPTION(int) type available to the API.
 *
 * \copyright Copyright (c) 2020, Kevin Kredit.
 */

#include "options.h"

DECL_OPTION(int)

OPTION(int) lib_add(int *x, int *y);

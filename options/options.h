/**
 * \file options.h
 *
 * \brief Declares types and functions for users of option types
 * \details
 *      To be included from the header of any file that uses option types in its
 *      API. Intentionally obfuscates the internal representation of the option
 *      data types. This can be evaded by the user, of course, but the goal is
 *      to make it hard enough that even in our laziest moments, it's easier to
 *      go through the accessor methods.
 *
 * \copyright Copyright (c) 2020, Kevin Kredit.
 */

#ifndef OPTION_PUBLIC_H
#define OPTION_PUBLIC_H

/******************************************************************************
 *                                                                 Inclusions */

#include <stdbool.h>

/******************************************************************************
 *                                                                    Defines */

// Operations
#define OPTION(t) option_##t
#define NONE(t) none_##t()
#define JUST(t, x) just_##t(x)

#define IS_NONE(t, x) is_none_##t(x)
#define IS_JUST(t, x) is_just_##t(x)

#define UNWRAP(t, x) unwrap_##t(x)
#define UNWRAP_OR(t, x, y) unwrap_or_##t(x, y)

#define EQ(t, x, y) eq_##t(x, y)
#define EQUAL(t, x, y) equal_##t(x, y)

#define OR(t, x, y) or_##t(x, y)
#define AND(t, x, y) and_##t(x, y)

// More? For inspiration, see
// https://notes.iveselov.info/programming/cheatsheet-rust-option-vs-haskell-maybe

// Declaration
#define DECL_OPTION(type) \
    struct option_obfuscated_##type { \
        char data[sizeof(bool) + sizeof(type)]; \
    }; \
    typedef struct option_obfuscated_##type OPTION(type); \
    OPTION(type) none_##type(void); \
    OPTION(type) just_##type(type x); \
    bool is_none_##type(OPTION(type) x); \
    bool is_just_##type(OPTION(type) x); \
    type unwrap_##type(OPTION(type) x); \
    type unwrap_or_##type(OPTION(type) x, type y); \
    bool eq_##type(OPTION(type) x, OPTION(type) y); \
    bool equal_##type(OPTION(type) x, OPTION(type) y); \
    OPTION(type) or_##type(OPTION(type) x, OPTION(type) y); \
    OPTION(type) and_##type(OPTION(type) x, OPTION(type) y);

#endif /* header guard */

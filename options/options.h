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

#define OPTION(t) option_##t
#define NONE(t) none_##t()
#define JUST(t, v) just_##t(v)

#define UNWRAP_OR(t, v, d) unwrap_or_##t(v, d)

// This would be defined in the header
#define DECL_OPTION(type) \
    struct option_obfuscated_##type { \
        char data[sizeof(bool) + sizeof(type)]; \
    }; \
    typedef struct option_obfuscated_##type OPTION(type); \
    OPTION(type) none_##type(void); \
    OPTION(type) just_##type(type x); \
    type unwrap_or_##type(OPTION(type) x, type alt);
    // ...

#endif /* header guard */

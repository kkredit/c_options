/**
 * \file
 *
 * \brief
 * \details
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
// #define OPTION(t) struct option_s_##t
#define UNWRAP_OR(t, v, d) unwrap_or_##t(v, d)
#define NONE(t) none_##t()
#define JUST(t, v) just_##t(v)

// This would be defined in the header

// TODO: want the struct definition undeclared, so users can't abuse the system. But for that to be
// true, OPTION(t) is an incomplete type, which can't be referenced directly. I can make it a
// pointer, but then we have dynamic memory management :/
// See https://stackoverflow.com/questions/13634495/c-typedef-incomplete-type
#define DECL_OPTION(type) \
    struct option_s_##t { \
        bool present; \
        union { \
            type value; \
            int err; \
        } u;\
    }; \
    typedef struct option_s_##t OPTION(type); \
    OPTION(type) none_##type(void); \
    OPTION(type) just_##type(type x); \
    type unwrap_or_##type(OPTION(type) x, type def);
    // ...

// This would be defined in the implementation file
// option_##type;
#define DEFN_OPTION(type) \
    OPTION(type) none_##type(void) { \
        OPTION(type) none = { \
            .present = false, \
            .u.err = -1 \
        }; \
        return none; \
    } \
    OPTION(type) just_##type(type x) { \
        OPTION(type) just = { \
            .present = true, \
            .u.value = x \
        }; \
        return just; \
    } \
    type unwrap_or_##type(OPTION(type) x, type def) { \
        return x.present ? x.u.value : def; \
    }
    // ...

#endif /* header guard */

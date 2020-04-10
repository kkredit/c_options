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

// TODO: put these somewhere invisible to the calling library
#define OPTION_INTERNAL(t) option_internal_##t
#define OBFUSCATE(t, x) x.u.obfuscated
#define DEOBFUSCATE(x) { .u.obfuscated = x }

// This would be defined in the header

// TODO: want the struct definition undeclared, so users can't abuse the system. But for that to be
// true, OPTION(t) is an incomplete type, which can't be referenced directly. I can make it a
// pointer, but then we have dynamic memory management :/
// See https://stackoverflow.com/questions/13634495/c-typedef-incomplete-type
#define DECL_OPTION(type) \
    struct option_obfuscated_##type { \
        char data[sizeof(bool) + sizeof(type)]; \
    }; \
    typedef struct option_obfuscated_##type OPTION(type); \
    OPTION(type) none_##type(void); \
    OPTION(type) just_##type(type x); \
    type unwrap_or_##type(OPTION(type) x, type def);
    // ...

// This would be defined in the implementation file
// option_##type;
#define DEFN_OPTION(type) \
    struct option_s_##type { \
        union { \
            struct { \
                bool present; \
                type value; \
            } internal; \
            OPTION(type) obfuscated; \
        } u; \
    }; \
    typedef struct option_s_##type OPTION_INTERNAL(type); \
    OPTION(type) none_##type(void) { \
        OPTION_INTERNAL(type) none = { \
            .u.internal.present = false, \
        }; \
        return OBFUSCATE(type, none); \
    } \
    OPTION(type) just_##type(type x) { \
        OPTION_INTERNAL(type) just = { \
            .u.internal.present = true, \
            .u.internal.value = x \
        }; \
        return OBFUSCATE(type, just); \
    } \
    type unwrap_or_##type(OPTION(type) x, type def) { \
        OPTION_INTERNAL(type) actual = DEOBFUSCATE(x); \
        return actual.u.internal.present ? actual.u.internal.value : def; \
    }
    // ...

#endif /* header guard */

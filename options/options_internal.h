/**
 * \file options_internal.h
 *
 * \brief Defines functions and internal representations of option types
 * \details
 *      To be included by the implementation file for an API that uses option
 *      types. Converts to the internal representation and performs wrapping
 *      and unwrapping operations.
 *
 * \copyright Copyright (c) 2020, Kevin Kredit.
 */

#ifndef OPTION_INTERNAL_H
#define OPTION_INTERNAL_H

/******************************************************************************
 *                                                                 Inclusions */
#include <assert.h>
#include "options.h"

/******************************************************************************
 *                                                                    Defines */

#define OPTION_INTERNAL(t) option_internal_##t
#define OBFUSCATE(x) ((x).u.obfuscated)
#define DEOBFUSCATE(x) { .u.obfuscated = (x) }

// This would be defined in the implementation file
#define DEFN_OPTION(type) \
    struct option_s_##type { \
        union { \
            struct { \
                bool present; \
                type value; \
            } actual; \
            OPTION(type) obfuscated; \
        } u; \
    }; \
    typedef struct option_s_##type OPTION_INTERNAL(type); \
    OPTION(type) none_##type(void) { \
        OPTION_INTERNAL(type) none = { \
            .u.actual.present = false, \
        }; \
        return OBFUSCATE(none); \
    } \
    OPTION(type) just_##type(type x) { \
        OPTION_INTERNAL(type) just = { \
            .u.actual.present = true, \
            .u.actual.value = x \
        }; \
        return OBFUSCATE(just); \
    } \
    bool is_none_##type(OPTION(type) x) { \
        OPTION_INTERNAL(type) dx = DEOBFUSCATE(x); \
        return !dx.u.actual.present; \
    } \
    bool is_just_##type(OPTION(type) x) { \
        OPTION_INTERNAL(type) dx = DEOBFUSCATE(x); \
        return dx.u.actual.present; \
    } \
    type unwrap_##type(OPTION(type) x) { \
        OPTION_INTERNAL(type) dx = DEOBFUSCATE(x); \
        assert(dx.u.actual.present); \
        return dx.u.actual.value; \
    } \
    type unwrap_or_##type(OPTION(type) x, type alt) { \
        OPTION_INTERNAL(type) dx = DEOBFUSCATE(x); \
        return dx.u.actual.present ? dx.u.actual.value : alt; \
    } \
    OPTION(type) or_##type(OPTION(type) x, OPTION(type) y) { \
        OPTION_INTERNAL(type) dx = DEOBFUSCATE(x); \
        return dx.u.actual.present ? x : y; \
    } \
    OPTION(type) and_##type(OPTION(type) x, OPTION(type) y) { \
        OPTION_INTERNAL(type) dx = DEOBFUSCATE(x); \
        return dx.u.actual.present ? y : x; \
    } \
    bool eq_##type(OPTION(type) x, OPTION(type) y) { \
        OPTION_INTERNAL(type) dx = DEOBFUSCATE(x); \
        OPTION_INTERNAL(type) dy = DEOBFUSCATE(y); \
        return (!dx.u.actual.present && !dy.u.actual.present) || \
               (dx.u.actual.present && dy.u.actual.present \
                && dx.u.actual.value == dy.u.actual.value); \
    } \
    bool equal_##type(OPTION(type) x, OPTION(type) y) { \
        OPTION_INTERNAL(type) dx = DEOBFUSCATE(x); \
        OPTION_INTERNAL(type) dy = DEOBFUSCATE(y); \
        return (dx.u.actual.present && dy.u.actual.present \
                && dx.u.actual.value == dy.u.actual.value); \
    }

#endif /* header guard */

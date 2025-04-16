#pragma once

/** Helper macro, mainly to be used by emtpy macros to force the caller to put
 *  a semicolon when empty.
 */
#define NOOP (void) 0

#if defined(DEBUG_BUILD)
    #if defined(_MSC_VER)
        #include <intrin.h>
        /** If a debugger is attached it will stop execution here,
            if no debugger is present the process will likely crash. */
        #define DEBUG_BREAK() (__nop(), __debugbreak())
    #else
        // Warnings require C++23
        // #warning "DEBUG_BREAK() macro un-implemented for current toolchain"
        #define DEBUG_BREAK() NOOP
    #endif
#else
    #define DEBUG_BREAK() NOOP
#endif


/** Ignores the value \p x with a no-op operation. Commonly use to be
 * explicit about unused return values or variables.
 * @param x Any value
 */
#define IGNORE(x) (void) (x)

/** Shorthand notation to the attribute <c>[[maybe_unused]]</c>. */
#define M_UNUSED [[maybe_unused]]

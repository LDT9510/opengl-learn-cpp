#pragma once

#if (defined(RELEASE_BUILD) || defined(DEBUG_RELEASE_BUILD)) && defined(ASSERTIONS_IN_RELEASE)
    /** ASSERTIONS_IN_RELEASE: assertions were manually activated in this build **/
    #define ASSERTIONS_ENABLED 1
    #if defined(RELEASE_BUILD)
    // C++ 23 only
    // #warning "Assertions enabled in RELEASE mode (ASSERTIONS_IN_RELEASE: ON)"
    #endif
#else
    #if defined(DEBUG_BUILD)
        /** DEBUG BUILD: Engine assertions are enabled. **/
        #define ASSERTIONS_ENABLED 1
    #else
        /** RELEASE BUILD: Engine assertions are disabled. **/
        #define ASSERTIONS_ENABLED 0
    #endif
#endif


#if ASSERTIONS_ENABLED
    #include "core/utils/assertions_internal/assertions_on.h"
#else
    #include "core/utils/assertions_internal/assertions_off.h"
#endif

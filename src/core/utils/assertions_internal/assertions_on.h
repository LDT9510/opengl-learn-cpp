#pragma once

#include "core/utils/helper_macros.h"

#include <spdlog/spdlog.h>

/** ALL BUILDS: Logs a message with ERROR level and terminate the engine execution,
 *   triggers a break-point if debugging, use printf semantics for the message.
 */
#define CRASH(format, ...)                            \
    do {                                              \
        SPDLOG_CRITICAL(format, __VA_ARGS__);         \
        DEBUG_BREAK();                                \
        SPDLOG_INFO("Terminating engine execution."); \
        std::terminate();                             \
    } while (0)


/** DEBUG BUILD: Asserts that expr is truthy. Triggers a break-point if debugging.
 *   Provide a message using printf semantics.
 */
#define CHECK_F(expr, msg, ...)             \
    do {                                    \
        if (!expr) CRASH(msg, __VA_ARGS__); \
    } while (0)

/** DEBUG BUILD: Asserts that expr is truthy. Triggers a break-point if debugging.
 *   Expression is stripped from RELEASE.
 */
#define CHECK(expr) CHECK_F(expr, "Assertion: failed '%s'", #expr)

/** DEBUG BUILD: Asserts that the evaluated pointer is not null. */
#define CHECK_NOT_NULL(pointer) CHECK_F(pointer != nullptr, "Assertion: '%s' is null", #pointer)

/** DEBUG BUILD: Asserts that this line of code is never reached. */
#define CHECK_UNREACHABLE() CRASH("Assertion: Unreachable code reached")

/** DEBUG BUILD: Run the provided code block on debug builds only. It must
 *   not contain any side effect
 */
#define CHECK_CODE_BLOCK(codeBlock) \
    do {                            \
        codeBlock                   \
    } while (0)

/** DEBUG BUILDS: Same behavior as DX_CHECK_F macro. Provide a message using
 *   printf semantics.
 */
#define VERIFY_F(expr, msg, ...)                \
    do {                                        \
        if (!expr) LOG_FATAL(msg, __VA_ARGS__); \
    } while (0)

/** DEBUG BUILDS: Same behavior as DX_CHECK macro. Provide a message using
 *   printf semantics.
 */
#define VERIFY(expr) VERIFY_F(expr, "Verification: failed '%s'", #expr)

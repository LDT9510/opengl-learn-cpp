#pragma once

#include "utils/helper_macros.h"

#include <spdlog/spdlog.h>

/** Logs a message with ERROR level and terminate the engine execution,
 *  triggers a break-point if debugging, use printf semantics for the message.
 */
#define CRASH(format, ...)                            \
    do {                                              \
        SPDLOG_CRITICAL(format, __VA_ARGS__);         \
        DEBUG_BREAK();                                \
        SPDLOG_INFO("Terminating engine execution."); \
        std::terminate();                             \
    } while (0)


/** Asserts that expr is truthy. Triggers a break-point if debugging.
 *  Provide a message using printf semantics.
 */
#define CHECK_F(expr, msg, ...)      \
    do {                             \
        if (!(expr)) {               \
            CRASH(msg, __VA_ARGS__); \
        }                            \
    } while (0)

/** Asserts that expr is truthy. Triggers a break-point if debugging.
 *  Expression is stripped from RELEASE.
 */
#define CHECK(expr) CHECK_F(expr, "Assertion: failed '{}'", #expr)

/** Asserts that the evaluated pointer is not null. */
#define CHECK_NOT_NULL(pointer) CHECK_F(pointer != nullptr, "Assertion: '{}' is null", #pointer)

/** Asserts that this line of code is never reached. */
#define CHECK_UNREACHABLE() CHECK_F(false, "Assertion: Unreachable code reached")

/** Run the provided code block on debug builds only. It must
 *  not contain any side effect
 */
#define CHECK_CODE_BLOCK(codeBlock) \
    do {                            \
        codeBlock                   \
    } while (0)

/** Same behavior as DX_CHECK_F macro */
#define VERIFY_F(expr, msg, ...)              \
    do {                                      \
        if (!(expr)) CRASH(msg, __VA_ARGS__); \
    } while (0)

/** Same behavior as DX_CHECK macro */
#define VERIFY(expr) VERIFY_F(expr, "Verification: failed '{}'", #expr)

/** Same behavior as CHECK_NOT_NULL macro */
#define VERIFY_NOT_NULL(pointer) VERIFY_F(pointer, "")

#pragma once

#include "utils/helper_macros.h"

#include <spdlog/spdlog.h>

/** Logs a message with ERROR level and terminate the engine execution,
 *  triggers a break-point if debugging, use printf semantics for the message.
 */
#define crash(format, ...)                                    \
	do {                                                  \
		SPDLOG_CRITICAL(format, __VA_ARGS__);         \
		DEBUG_BREAK;                                  \
		SPDLOG_INFO("Terminating engine execution."); \
		std::terminate();                             \
	} while (0)

/** Asserts that expr is truthy. Triggers a break-point if debugging.
 *  Provide a message using printf semantics.
 */
#define check_f(expr, msg, ...)                  \
	do {                                     \
		if (!(expr)) {                   \
			crash(msg, __VA_ARGS__); \
		}                                \
	} while (0)

/** Asserts that expr is truthy. Triggers a break-point if debugging.
 *  Expression is stripped from RELEASE.
 */
#define check(expr) check_f(expr, "Assertion: failed '{}'", #expr)

/** Asserts that the evaluated pointer is not null. */
#define check_not_null(pointer) check_f((pointer) != nullptr, "Assertion: '{}' is null", #pointer)

/** Assumes that this line of code can never be reached
 * for optimization purposes. If reached undefined behaviours occurs,
 * use with caution.
 */
#define check_unreachable() check_f(false, "Assertion: Unreachable code reached")

/** Run the provided code block on debug builds only. It must
 *  not contain any side effect
 */
#define check_code_block(codeBlock) \
	do {                        \
		codeBlock           \
	} while (0)

/** Same behavior as `check_f` macro */
#define verify_f(expr, msg, ...)                 \
	do {                                     \
		if (!(expr))                     \
			CRASH(msg, __VA_ARGS__); \
	} while (0)

/** Same behavior as `check` macro */
#define verify(expr) VERIFY_F(expr, "Verification: failed '{}'", #expr)

/** Same behavior as `check_not_null` macro */
#define verify_not_null(pointer) VERIFY_F(pointer, "")

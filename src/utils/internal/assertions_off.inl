#pragma once

#include "utils/backports.h"
#include "utils/helper_macros.h"

/** Does nothing. Expression is not evaluated. */
#define CRASH(format, ...) NOOP

/** Does nothing. Expression is not evaluated. */
#define CHECK_F(expr, msg, ...) NOOP

/** Does nothing. Expression is not evaluated. */
#define CHECK(expr) NOOP

/** Does nothing. Expression is not evaluated. */
#define CHECK_NOT_NULL(pointer) NOOP

/** Assumes that this line of code can never be reached
 * for optimization purposes. If reached undefined behaviours occurs,
 * use with caution.
 */
#define CHECK_UNREACHABLE() Unreachable()

/** Does nothing. Expression is not evaluated. */
#define CHECK_CODE_BLOCK(codeBlock) NOOP

/** Does nothing. Expression is always evaluated. */
#define VERIFY_F(expr, msg, ...) expr

/** Does nothing. Expression is always evaluated. */
#define VERIFY(expr) VERIFY_F(expr, "") expr

/** Does nothing. Expression is always evaluated. */
#define VERIFY_NOT_NULL(pointer) VERIFY_F(pointer, "")

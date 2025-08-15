#pragma once

#include "utils/backports.h"
#include "utils/helper_macros.h"

/** Does nothing. Expression is not evaluated. */
#define crash(format, ...) NOOP

/** Does nothing. Expression is not evaluated. */
#define check_f(expr, msg, ...) NOOP

/** Does nothing. Expression is not evaluated. */
#define check(expr) NOOP

/** Assumes that this line of code can never be reached
 * for optimization purposes. If reached undefined behaviours occurs,
 * use with caution.
 */
#define check_unreachable() unreachable()

/** Does nothing. Expression is not evaluated. */
#define check_not_null(pointer) NOOP

/** Does nothing. Expression is not evaluated. */
#define check_code_block(codeBlock) NOOP

/** Does nothing. Expression is always evaluated. */
#define verify_f(expr, msg, ...) expr

/** Does nothing. Expression is always evaluated. */
#define verify(expr) VERIFY_F(expr, "") expr

/** Does nothing. Expression is always evaluated. */
#define verify_not_null(pointer) VERIFY_F(pointer, "")

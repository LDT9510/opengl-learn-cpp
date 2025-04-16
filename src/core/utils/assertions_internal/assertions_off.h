#pragma once

#include "core/utils/backports.h"
#include "core/utils/helper_macros.h"

/// RELEASE BUILD: Does nothing. Expression is not evaluated.
#define CRASH(format, ...) NOOP

/// RELEASE BUILD: Does nothing. Expression is not evaluated.
#define CHECK_F(expr, msg, ...) NOOP

/// RELEASE BUILD: Does nothing. Expression is not evaluated.
#define CHECK(expr) NOOP

/// RELEASE BUILD: Does nothing. Expression is not evaluated.
#define CHECK_NOT_NULL(pointer) NOOP

/// RELEASE BUILD: Assumes that this line of code can never be reached
/// for optimization purposes. If reached undefined behaviours occurs,
/// use with caution.
#define CHECK_UNREACHABLE() Unreachable_()

/// RELEASE BUILD: Does nothing. Expression is not evaluated.
#define CHECK_CODE_BLOCK(codeBlock) NOOP

/// RELEASE BUILD: Does nothing. Expression is evaluated.
#define VERIFY_F(expr, msg, ...) expr

/// RELEASE BUILD: Does nothing. Expression is evaluated.
#define VERIFY(expr) VERIFY_F(expr, "")

/// RELEASE BUILD: Does nothing. Expression is evaluated.
#define VERIFY_NOT_NULL(pointer) VERIFY_F(pointer, "")

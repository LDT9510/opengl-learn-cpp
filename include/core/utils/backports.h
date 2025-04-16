#pragma once

namespace core::backports
{
/// Backport of https://en.cppreference.com/w/cpp/utility/unreachable (C++23)
[[noreturn]] inline void Unreachable_()
{
    // Uses compiler specific extensions if possible.
    // Even if no extension is used, undefined behavior is still raised by
    // an empty function body and the noreturn attribute.
    #if defined(_MSC_VER) && !defined(__clang__) // MSVC
    __assume(false);
    #else // GCC, Clang
    __builtin_unreachable();
    #endif
}
} // namespace dx::utils

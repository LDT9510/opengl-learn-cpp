include("Utils")
include("ExternalsUtils")

# REQUIRES SDL3
block()
    set(lib_name "spdlog")
    Announce("Configuring \"${lib_name}\" external library.")

    ForceBool(SPDLOG_BUILD_ALL OFF)  # Build all artifacts
    ForceBool(SPDLOG_BUILD_BENCH OFF)  # Build benchmarks (Requires https://github.com/google/benchmark.git to be installed)
    ForceBool(SPDLOG_BUILD_EXAMPLE OFF)  # Build example
    ForceBool(SPDLOG_BUILD_EXAMPLE_HO OFF)  # Build header only example
    ForceBool(SPDLOG_BUILD_PIC OFF)  # Build position independent code (-fPIC)
    ForceBool(SPDLOG_BUILD_SHARED OFF)  # Build shared library
    ForceBool(SPDLOG_BUILD_TESTS OFF)  # Build tests
    ForceBool(SPDLOG_BUILD_TESTS_HO OFF)  # Build tests using the header only version
    ForceBool(SPDLOG_BUILD_WARNINGS OFF)  # Enable compiler warnings
    ForceBool(SPDLOG_CLOCK_COARSE OFF)  # non supported option
    ForceBool(SPDLOG_DISABLE_DEFAULT_LOGGER OFF)  # Disable default logger creation
    ForceBool(SPDLOG_ENABLE_PCH OFF)  # Build static or shared library using precompiled header to speed up compilation time
    ForceBool(SPDLOG_FMT_EXTERNAL ON)  # Use external fmt library instead of bundled
    ForceBool(SPDLOG_FMT_EXTERNAL_HO OFF)  # Use external fmt header-only library instead of bundled
    ForceBool(SPDLOG_FWRITE_UNLOCKED ON)  # Use the unlocked variant of fwrite. Leave this on unless your libc doesn't have it
    ForceBool(SPDLOG_INSTALL OFF)  # Generate the install target
    ForceBool(SPDLOG_MSVC_UTF8 ON)  # Enable/disable msvc /utf-8 flag required by fmt lib
    ForceBool(SPDLOG_NO_ATOMIC_LEVELS OFF)  # prevent spdlog from using of std::atomic log levels (use only if your code never modifies log levels concurrently
    ForceBool(SPDLOG_NO_EXCEPTIONS OFF)  # Compile with -fno-exceptions. Call abort() on any spdlog exceptions
    ForceBool(SPDLOG_NO_THREAD_ID OFF)  # prevent spdlog from querying the thread id on each log call if thread id is not needed
    ForceBool(SPDLOG_NO_TLS OFF)  # prevent spdlog from using thread local storage
    ForceBool(SPDLOG_PREVENT_CHILD_FD OFF)  # Prevent from child processes to inherit log file descriptors
    ForceBool(SPDLOG_SANITIZE_ADDRESS OFF)  # Enable address sanitizer in tests
    ForceBool(SPDLOG_SANITIZE_THREAD OFF)  # Enable thread sanitizer in tests
    ForceBool(SPDLOG_SYSTEM_INCLUDES OFF)  # Include as system headers (skip for clang-tidy).
    ForceBool(SPDLOG_TIDY OFF)  # run clang-tidy
    ForceBool(SPDLOG_USE_STD_FORMAT OFF)  # Use std::format instead of fmt library.
    ForceBool(SPDLOG_WCHAR_CONSOLE OFF)  # Support wchar output to console
    ForceBool(SPDLOG_WCHAR_FILENAMES OFF)  # Support wchar filenames
    ForceBool(SPDLOG_WCHAR_SUPPORT OFF)  # Support wchar api

    AddExternalSubdirectory(${lib_name})
endblock()

function(setup_target_compiler_definitions TARGET)
    # helper closure to fixate the target
    function(custom_add_macro_definition CONDITION DEFINITION #[[OPT_MESSAGE]])
        set(OPT_MESSAGE ${ARGN})
        conditional_add_macro_definition(${TARGET} ${CONDITION} ${DEFINITION} ${OPT_MESSAGE})
    endfunction()

    # build type
    custom_add_macro_definition(${CONFIG_IS_DEV} DEV_BUILD "Build type: Development")
    custom_add_macro_definition(${CONFIG_IS_SHIPPING} SHIPPING_BUILD "Build type: Shipping")
    custom_add_macro_definition(${CONFIG_IS_PROFILE} PROFILE_BUILD "Build type: Profile (Shipping with debug info)")

    # compiler type
    custom_add_macro_definition(${CXX_COMPILER_IS_GNU_LIKE} COMPILER_GNU_LIKE)
    custom_add_macro_definition(${CXX_COMPILER_IS_MSVC_LIKE} COMPILER_MSVC_LIKE)

    # compiler
    custom_add_macro_definition(${CXX_COMPILER_IS_CLANG} COMPILER_CLANG)
    custom_add_macro_definition(${CXX_COMPILER_IS_GCC} COMPILER_GCC)
    custom_add_macro_definition(${CXX_COMPILER_IS_MSVC} COMPILER_MSVC)

    # platform
    custom_add_macro_definition(${TARGET_PLATFORM_IS_WINDOWS} PLATFORM_WINDOWS)
    custom_add_macro_definition(${TARGET_PLATFORM_IS_LINUX} PLATFORM_LINUX)
    custom_add_macro_definition(${TARGET_PLATFORM_IS_MACOS} PLATFORM_MACOS)
    custom_add_macro_definition(${TARGET_PLATFORM_IS_WEB} PLATFORM_WEB)

    # assertions
    custom_add_macro_definition(${CONFIG_IS_DEV} ENABLE_ASSERTIONS "Enabling assertions")

    # logging
    custom_add_macro_definition(${FORCE_DISABLE_LOGGING} SPDLOG_ACTIVE_LEVEL=6 "Disabling all logging") # equivalent to SPDLOG_LEVEL_OFF
    custom_add_macro_definition(${CONFIG_IS_DEV} SPDLOG_ACTIVE_LEVEL=1 "Log level set to DEBUG") # equivalent to SPDLOG_LEVEL_DEBUG

    assign_bool(LOG_LEVEL_INFO CONFIG_IS_SHIPPING OR CONFIG_IS_PROFILE)
    custom_add_macro_definition(${LOG_LEVEL_INFO} SPDLOG_ACTIVE_LEVEL=6 "Log level set to INFO") # equivalent to SPDLOG_LEVEL_DEBUG

    assign_bool(DISABLE_SOURCE_IN_LOGS CONFIG_IS_SHIPPING)
    custom_add_macro_definition(${DISABLE_SOURCE_IN_LOGS} SPDLOG_NO_SOURCE_LOC "Disabling source code showing in logs.")
endfunction()
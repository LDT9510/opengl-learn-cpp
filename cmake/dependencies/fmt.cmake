include("Utils")

#[[ Configure {fmt}.
    Parameters:
        target: The target to configure the library for.
        use_thirdparty_includes: Activate the "#include thirdparty/..." convention.
]]
function(configure_external_fmt target use_thirdparty_includes)
    set(LIB_NAME "fmt")
    announce("Configuring \"${LIB_NAME}\" external library.")

    force_bool(FMT_DOC OFF)
    force_bool(FMT_INSTALL OFF)
    force_bool(FMT_TEST OFF)
    force_bool(FMT_FUZZ OFF)
    force_bool(FMT_CUDA_TEST OFF)
    force_bool(FMT_OS ON)
    force_bool(FMT_MODULE OFF)
    force_bool(FMT_SYSTEM_HEADERS OFF)
    force_bool(FMT_UNICODE ON)

    add_external_subdirectory(${LIB_NAME})
    target_link_libraries(${target} PRIVATE fmt::fmt)

    if (use_thirdparty_includes)
        copy_thirdparty_includes_glob(${LIB_NAME} "include/fmt/*.h")

        target_include_thirdparty(${target} ${LIB_NAME})
    endif ()


endfunction()
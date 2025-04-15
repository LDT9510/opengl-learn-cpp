include("Utils")

#[[ Configure glad.
    Parameters:
        target: The target to configure the library for.
        use_thirdparty_includes: Activate the "#include thirdparty/..." convention.
]]
function(configure_external_glad target use_thirdparty_includes)
    set(LIB_NAME "glad")
    announce("Configuring \"${LIB_NAME}\" external library.")

    add_external_subdirectory(${LIB_NAME})
    target_link_libraries(${target} PRIVATE glad)

    if(use_thirdparty_includes)
        copy_thirdparty_includes(${LIB_NAME} "include/glad/gl.h")
        copy_thirdparty_includes(${LIB_NAME} "include/KHR/khrplatform.h")

        target_include_thirdparty(${target} ${LIB_NAME})
    endif ()
endfunction()
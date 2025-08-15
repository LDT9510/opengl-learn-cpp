include("Utils")
include("ExternalsUtils")

block()
    set(LIB_NAME "imgui")
    announce("Configuring \"${LIB_NAME}\" external library.")

    force_bool(IMGUI_DEMO ON)  # Build the demo window

    add_external_subdirectory(${LIB_NAME})
    
    if (TARGET_PLATFORM_IS_WINDOWS AND CXX_COMPILER_IS_GNU_LIKE)
        # fix CLang on Windows
        target_compile_definitions(ImGui PUBLIC "_CRT_USE_BUILTIN_OFFSETOF")
    endif ()
endblock()

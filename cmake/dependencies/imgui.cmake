include("Utils")
include("ExternalsUtils")

block()
    set(lib_name "imgui")
    Announce("Configuring \"${lib_name}\" external library.")

    ForceBool(IMGUI_DEMO ON)  # Build the demo window

    AddExternalSubdirectory(${lib_name})
    
    if (TARGET_PLATFORM_IS_WINDOWS AND CXX_COMPILER_IS_GNU_LIKE)
        # fix CLang on Windows
        target_compile_definitions(ImGui PUBLIC "_CRT_USE_BUILTIN_OFFSETOF")
    endif ()
endblock()

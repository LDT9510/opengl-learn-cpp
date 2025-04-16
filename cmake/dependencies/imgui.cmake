include("Utils")
include("ExternalsUtils")

function(configure_external_imgui target)
    set(LIB_NAME "imgui")
    announce("Configuring \"${LIB_NAME}\" external library.")

    force_bool(IMGUI_DEMO ON)  # Build the demo window

    add_external_subdirectory(${LIB_NAME})
endfunction()

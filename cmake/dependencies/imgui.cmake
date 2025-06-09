include("Utils")
include("ExternalsUtils")

block()
    set(lib_name "imgui")
    Announce("Configuring \"${lib_name}\" external library.")

    ForceBool(IMGUI_DEMO ON)  # Build the demo window

    AddExternalSubdirectory(${lib_name})
endblock()

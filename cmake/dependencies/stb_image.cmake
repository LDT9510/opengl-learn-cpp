include("Utils")
include("ExternalsUtils")

block()
    set(lib_name "stb_image")
    Announce("Configuring \"${lib_name}\" external library.")

    AddExternalSubdirectory(${lib_name})
endblock()

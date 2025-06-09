include("Utils")
include("ExternalsUtils")

block()
    set(lib_name "glad")
    Announce("Configuring \"${lib_name}\" external library.")

    AddExternalSubdirectory(${lib_name})
endblock()

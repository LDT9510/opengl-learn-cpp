include("Utils")
include("ExternalsUtils")

function(configure_external_fmt)
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
endfunction()
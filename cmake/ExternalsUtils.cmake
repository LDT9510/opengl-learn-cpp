#[[ Adds a subdirectory with a binary directory at with root at 
    "${CMAKE_BINARY_DIR}/external/${lib_name}" and mark it as
    EXCLUDE_FROM_ALL.
]]
macro(add_external_subdirectory lib_name)
    add_subdirectory("${EXTERNAL_LIBS_SOURCES_DIR}/${lib_name}" "${CMAKE_BINARY_DIR}/external/${lib_name}" EXCLUDE_FROM_ALL)
endmacro()

#[[ Should be used to copy header files to a custom included path
    this allows includes to be used like `#include "thirdparty/<lib_name>/..."`.
    
    Parameters:
        lib_name: The name of the external library, should match the subdirectory inside ${EXTERNAL_LIBS_SOURCES_DIR}
        path: The path to the file to copy, should be relative to "${EXTERNAL_LIBS_SOURCES_DIR}/${lib_name}".
]]
function(copy_thirdparty_includes lib_name path)
    set(origin_dir "${EXTERNAL_LIBS_SOURCES_DIR}/${lib_name}")
    set(destination_dir "${THIRDPARTY_INCLUDES_DIR}/${lib_name}/")

    file(COPY "${origin_dir}/${path}" DESTINATION "${destination_dir}")
endfunction()

#[[ Same as `copy_thirdparty_includes` but accepts a glob expression
    that will be used to collect several files.
    
    Parameters:
        lib_name: The name of the external library, should match the subdirectory 
                  inside ${EXTERNAL_LIBS_SOURCES_DIR}.
        glob_expr: A "Glob" expression that should match several file paths. It should be relative to 
                   "${EXTERNAL_LIBS_SOURCES_DIR}/${lib_name}".
        [base_dir]: An optional directory name where the files will be copied to, it will be created
                  at "${EXTERNAL_LIBS_SOURCES_DIR}/${lib_name}/${base_dir}"
]]
function(copy_thirdparty_includes_glob lib_name glob_expr #[[base_dir: ARGV2]])
    set(origin_dir "${EXTERNAL_LIBS_SOURCES_DIR}/${lib_name}")
    set(base_destination_dir "${THIRDPARTY_INCLUDES_DIR}/${lib_name}/")

    file(GLOB collected_files "${origin_dir}/${glob_expr}")

    if (ARGV2)
        set(destination_dir ${base_destination_dir}/${base_dir})
    else ()
        set(destination_dir ${base_destination_dir}/)
    endif ()

    foreach (file_path ${collected_files})
        file(COPY "${file_path}" DESTINATION "${destination_dir}")
    endforeach ()
endfunction()

#[[ Add the path "${EXTERNAL_LIBS_SOURCES_DIR}/${lib_name}" to the ${target} include directories,
    this allows includes to be used like `#include "thirdparty/<lib_name>/...".
]]
macro(target_include_thirdparty target lib_name)
    target_include_directories(${target} SYSTEM PUBLIC "${THIRDPARTY_INCLUDES_DIR}/..")

    # add to the project sources, to help IDE's code analysis
    file(GLOB_RECURSE thirdparty_includes
            ${THIRDPARTY_INCLUDES_DIR}/${lib_name}/*.h
            ${THIRDPARTY_INCLUDES_DIR}/${lib_name}/*.hpp)
    
    target_sources(${target} PRIVATE ${thirdparty_includes})
endmacro()
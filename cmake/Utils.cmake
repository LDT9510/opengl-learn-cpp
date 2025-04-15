#[[ Prints a message with a custom formatting. ]]
function(announce message)
    message("=========================================================")
    message("${message}")
    message("=========================================================")
endfunction()

#[[ Same as set(${name} ${value} CACHE BOOL "" FORCE). ]]
macro(force_bool name value)
    set(${name} ${value} CACHE BOOL "" FORCE)
endmacro()

#[[ Same as set(${name} ${value} CACHE STRING "" FORCE). ]]
macro(force_string name value)
    set(${name} ${value} CACHE STRING "" FORCE)
endmacro()

#[[ Prints every element from ${list_var}. ]]
function(print_list list_var)
    foreach (item ${list_var})
        message(STATUS "DEBUG item: ${item}")
    endforeach ()
endfunction()

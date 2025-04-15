include("SymlinkContent")
include("ExternalsUtils")
include("dependencies/SDL3")
include("dependencies/fmt")
include("dependencies/glad")
include("dependencies/spdlog")

project("opengl-learn" LANGUAGES CXX)

file(GLOB_RECURSE CORE_FILES "core/*.cpp" "core/*.h")
file(GLOB_RECURSE INCLUDE_FILES "../include/core/*.h")

add_executable(${PROJECT_NAME} "main.cpp" ${CORE_FILES} ${INCLUDE_FILES})
target_include_directories(${PROJECT_NAME} PRIVATE "../include")

# C++ standard stuff
set_target_properties(${PROJECT_NAME} PROPERTIES CXX_STANDARD 20)
set_target_properties(${PROJECT_NAME} PROPERTIES CXX_STANDARD_REQUIRED ON)
set_target_properties(${PROJECT_NAME} PROPERTIES CXX_EXTENSIONS OFF)

# set warnings
target_compile_options(${PROJECT_NAME} PRIVATE
        "$<${COMPILER_GCC_LIKE}:-Wall;-Wextra;-W;-Werror;-pedantic-errors>"
        "$<${COMPILER_MSVC_LIKE}:/nologo;/W4;/WX>"
)

# set custom definitions
target_compile_definitions(${PROJECT_NAME} PRIVATE
        # build configuration
        $<$<CONFIG:Debug>:DEBUG_BUILD=1>
        $<$<CONFIG:Release>:RELEASE_BUILD>
        $<$<CONFIG:RelWithDebInfo>:DEBUG_RELEASE_BUILD>
        
        # logging
        $<$<CONFIG:Release>:SPDLOG_NO_SOURCE_LOC>
        
        # options
        $<$<BOOL:ASSERTIONS_IN_RELEASE>:ASSERTIONS_IN_RELEASE>
        $<$<BOOL:DISABLE_LOGGING>:DISABLE_LOGGING>
)

# this is set by the Emscripten toolchain
if (EMSCRIPTEN)
    set_target_properties(${PROJECT_NAME} PROPERTIES SUFFIX ".html")

    # do emscripten stuff, handle resources
else ()
    # add symlink to resources
    symlink_content(${PROJECT_NAME} contents)

    # desktop specific stuff
endif ()

# configure external dependencies
configure_external_sdl3(${PROJECT_NAME} ON)
configure_external_fmt(${PROJECT_NAME} ON)
configure_external_glad(${PROJECT_NAME} ON)
configure_external_spdlog(${PROJECT_NAME} ON)

include("SymlinkContent")

project("opengl-learn" LANGUAGES CXX)

# ========== Libraries ===========
add_subdirectory(libs/dev_ui)

file(GLOB_RECURSE CORE_FILES "core/*.cpp" "core/*.h")
file(GLOB_RECURSE INCLUDE_FILES "../include/core/*.h")

add_executable(${PROJECT_NAME} "main.cpp" ${CORE_FILES} ${INCLUDE_FILES})
target_include_directories(${PROJECT_NAME} PUBLIC "../include" PRIVATE "core")
target_link_libraries(${PROJECT_NAME} PRIVATE
        SDL3::SDL3
        fmt::fmt
        spdlog::spdlog
        glad
        DevUi
)


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
        $<$<CONFIG:Debug>:DEBUG_BUILD>
        $<$<CONFIG:Release>:RELEASE_BUILD>
        $<$<CONFIG:RelWithDebInfo>:DEBUG_RELEASE_BUILD>

        # logging
        $<$<CONFIG:Release>:SPDLOG_NO_SOURCE_LOC>

        # options
        $<$<BOOL:${ASSERTIONS_IN_RELEASE}>:ASSERTIONS_IN_RELEASE>
        $<$<BOOL:${DISABLE_LOGGING}>:DISABLE_LOGGING>
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

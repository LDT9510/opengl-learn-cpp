cmake_minimum_required(VERSION 3.23)
project("OpenglLearn" CXX)

# set the CMake modules path, required to import using " include(...)"
list(APPEND CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake")

# ========== Global Configuration ===========
include("GlobalConfig")
include("Options")
include("SymlinkContent")
include("ExternalsUtils")

# ========== Dependencies ===========
# order matters for transitive dependencies!
include("dependencies/SDL3")
include("dependencies/fmt")
include("dependencies/glad")
include("dependencies/spdlog")
include("dependencies/imgui")
include("dependencies/glm")
include("dependencies/physfs")
include("dependencies/stb_image")
include("dependencies/tracy")

# ============================ Main Project =============================
Announce("Configuring main project")

# project sources
set(project_files
        src/main.cpp
        src/core/event_handler.cpp
        src/core/filesystem.cpp
        src/core/renderer.cpp
        src/core/shader.cpp
        src/core/timing.cpp
        src/core/window.cpp
        src/dev_ui/dev_ui.cpp)

# main executable, includes, linked libraries and compiler flags
add_executable(${PROJECT_NAME} ${project_files})
target_include_directories(${PROJECT_NAME} PRIVATE "src")
target_link_libraries(${PROJECT_NAME} PRIVATE
        SDL3::SDL3
        fmt::fmt
        spdlog::spdlog
        glad
        glm::glm
        ImGui
        PhysFS::PhysFS-static
        stb_image
        Tracy::TracyClient
)

# C++ features
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_20)

# compiler flags
if (CXX_COMPILER_IS_GNU_LIKE)
    target_compile_options(${PROJECT_NAME} PRIVATE
            -Wall
            -Wextra
            -W
            -Werror
            -pedantic-errors
            -Wno-language-extension-token
    )
elseif (CXX_COMPILER_IS_MSVC_LIKE)
    target_compile_options(${PROJECT_NAME} PRIVATE
            /W4
            /WX
    )
else ()
    message(FATAL_ERROR "Unknown compiler frontend.")
endif ()

if (NOT TARGET_PLATFORM_IS_WEB)
    # content handling
    SymlinkContent(${PROJECT_NAME} "contents")
else ()
    # handle content when targeting the web, this is different 
    # from other platforms
endif ()

# source code macro pre-definitions
function(AddMacroDefinitions definitions)
    target_compile_definitions(${PROJECT_NAME} PRIVATE ${definitions})
endfunction()

# build type
if (CONFIG_IS_DEV)
    AddMacroDefinitions("DEV_BUILD")
    message(STATUS "Build type: Development")
elseif (CONFIG_IS_SHIPPING)
    AddMacroDefinitions("SHIPPING_BUILD")
    message(STATUS "Build type: Shipping")
elseif (CONFIG_IS_PROFILE)
    AddMacroDefinitions("PROFILE_BUILD")
    message(STATUS "Build type: Profile (Shipping with debug info)")
endif ()

# assertions
if (CONFIG_IS_DEV OR FORCE_ENABLE_ASSERTIONS)
    AddMacroDefinitions("ENABLE_ASSERTIONS")
    message(STATUS "Enabling assertions")
endif ()

# logging
if (FORCE_DISABLE_LOGGING)
    AddMacroDefinitions("SPDLOG_ACTIVE_LEVEL=6")  # equivalent to SPDLOG_LEVEL_OFF
    message(STATUS "Disabling all logging")
elseif (CONFIG_IS_DEV)
    AddMacroDefinitions("SPDLOG_ACTIVE_LEVEL=1") # equivalent to SPDLOG_LEVEL_DEBUG
    message(STATUS "Log level set to DEBUG")
elseif (CONFIG_IS_SHIPPING OR CONFIG_IS_PROFILE)
    AddMacroDefinitions("SPDLOG_ACTIVE_LEVEL=2")  # equivalent to SPDLOG_LEVEL_INFO
    message(STATUS "Log level set to INFO")
    if (CONFIG_IS_SHIPPING)
        AddMacroDefinitions("SPDLOG_NO_SOURCE_LOC")
        message(STATUS "Disabling source code showing in logs.")
    endif ()
endif ()

# platform
message(STATUS "Building for '${CMAKE_SYSTEM_NAME}' platform")

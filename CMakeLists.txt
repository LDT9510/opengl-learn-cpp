cmake_minimum_required(VERSION 3.23)
project("OpenGL-Learn" C)

# set the CMake modules path, required to import using " include(...)"
list(APPEND CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake")

include("dependencies/SDL3")
include("dependencies/fmt")
include("dependencies/glad")
include("dependencies/spdlog")
include("dependencies/imgui")

# ========== Global Configuration ===========
include("Config")
include("Options")

# =========== Dependencies ===============
# order matters for transitive dependencies!
configure_external_sdl3(${PROJECT_NAME})
configure_external_fmt(${PROJECT_NAME})
configure_external_spdlog(${PROJECT_NAME}) # depends on {fmt}
configure_external_glad(${PROJECT_NAME})
configure_external_imgui(${PROJECT_NAME})

# ========== Game ===========
add_subdirectory(src)

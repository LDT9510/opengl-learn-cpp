project("DevUi" LANGUAGES CXX)

# dont use a variable for the target so CLion auto-completes
add_library(DevUi STATIC "src/dev_ui.cpp")

target_sources(${PROJECT_NAME} PRIVATE
        "imgui_backends/imgui_impl_opengl3.cpp"
        "imgui_backends/imgui_impl_sdl3.cpp")

target_include_directories(${PROJECT_NAME}
        PUBLIC "include"
        PRIVATE "imgui_backends" "embedded_font")

# this is an ugly patch to fix the imgui implementation header imports
target_include_directories(${PROJECT_NAME} PRIVATE "${EXTERNAL_LIBS_SOURCES_DIR}/imgui/include/imgui")

target_link_libraries(${PROJECT_NAME} PUBLIC ImGui PRIVATE SDL3::SDL3)

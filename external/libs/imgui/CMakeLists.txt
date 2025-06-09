project(ImGui
        VERSION 1.91.7
        DESCRIPTION "Immediate mode library"
        LANGUAGES CXX
)

option(IMGUI_DEMO "Compiles a simple ${PROJECT_NAME} demo project" OFF)

add_library(ImGui STATIC
        "src/imgui.cpp"
        "src/imgui_draw.cpp"
        "src/imgui_tables.cpp"
        "src/imgui_widgets.cpp"
        "src/imgui_impl_opengl3.cpp"
        "src/imgui_impl_sdl3.cpp")

if (IMGUI_DEMO)
    message(STATUS "Including the demo sources.")
    target_sources(${PROJECT_NAME} PRIVATE "src/imgui_demo.cpp")
endif ()

target_include_directories(${PROJECT_NAME} SYSTEM
        PUBLIC "include" "include/imgui/backends" "include/imgui")

target_compile_definitions(${PROJECT_NAME} PUBLIC
        IMGUI_DISABLE_OBSOLETE_FUNCTIONS
        IMGUI_DISABLE_OBSOLETE_KEYIO
)

target_link_libraries(ImGui PRIVATE SDL3::SDL3)

message(STATUS "${PROJECT_NAME} configured correctly.")
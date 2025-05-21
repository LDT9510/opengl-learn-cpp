#include "dev_ui/dev_ui.h"

#include "roboto_medium.h"

#include <SDL3/SDL.h>
#include <imgui_impl_opengl3.h>
#include <imgui_impl_sdl3.h>

void dev_ui::InitForWindow(SDL_Window* sdlWindow, SDL_GLContext sdlContext)
{
    ImGui::CreateContext();
    // second parameter is not used
    ImGui_ImplSDL3_InitForOpenGL(sdlWindow, sdlContext);
    ImGui_ImplOpenGL3_Init();

    ImGui::GetIO().Fonts->AddFontFromMemoryCompressedTTF(
        RobotoMedium_compressed_data, RobotoMedium_compressed_size, 20.0f
    );
}

void dev_ui::CreateFrame()
{
    ImGui_ImplSDL3_NewFrame();
    ImGui_ImplOpenGL3_NewFrame();
    im::NewFrame();
}

void dev_ui::RenderFrame()
{
    im::Render();
    ImGui_ImplOpenGL3_RenderDrawData(im::GetDrawData());
}

void dev_ui::Shutdown()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplSDL3_Shutdown();
    im::DestroyContext();
}

void dev_ui::ProcessInput(const SDL_Event& event)
{
    ImGui_ImplSDL3_ProcessEvent(&event);
}

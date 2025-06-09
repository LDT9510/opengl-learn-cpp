#pragma once

// ReSharper disable CppInconsistentNaming
union SDL_Event;
struct SDL_Window;
struct SDL_GLContextState;
// ReSharper restore CppInconsistentNaming

namespace dev_ui
{
    void InitForWindow(SDL_Window* sdlWindow, SDL_GLContextState* sdlContext);
    void CreateFrame();
    void RenderFrame();
    void Shutdown();
    void ProcessInput(const SDL_Event& event);
} // namespace dev_ui

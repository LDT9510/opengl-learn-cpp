// ReSharper disable CppInconsistentNaming
#pragma once

#include <imgui/imgui.h>

union SDL_Event;
struct SDL_Window;
struct SDL_GLContextState;

namespace dev_ui {

// ImGui namespace short alias
namespace im = ImGui;

void InitForWindow(SDL_Window* sdlWindow, SDL_GLContextState* sdlContext);
void CreateFrame();
void RenderFrame();
void Shutdown();
void ProcessInput(const SDL_Event& event);

} // namespace core::dev_ui

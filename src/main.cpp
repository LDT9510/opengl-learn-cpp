#include "core/event_handler.h"
#include "core/renderer.h"
#include "core/window.h"

#include <SDL3/SDL.h>
#include <dev_ui/dev_ui.h>
#include <windows.h>
#include <fmt/format.h>

#include <string>

int main() {
    auto window = core::Window::InitializeWithContext({
        .title       = fmt::format("Learning OpenGL (PID: {})", std::to_string(GetCurrentProcessId())).c_str(),
        .isResizable = false,
    });

    core::EventHandler eventHandler{{
        .windowsResizingCallback = core::Window::OnWindowResizing,
        .windowsQuitCallback     = [&window]() { window.OnWindowQuitEvent(); },
    }};

    // requires an initialized OpenGL context
    core::Renderer renderer;
    renderer.SetupRendering();

    eventHandler.RegisterKeyboardInputHandler([&renderer,
                                               &window](const core::EventHandler& handler) {
        renderer.HandleInput(handler);
        window.HandleInput(handler);
    });

    while (window.ShouldStayOpen()) {
        dev_ui::CreateFrame();

        eventHandler.CollectAndProcessInput();

        renderer.Render();

        core::Renderer::RenderDevUi();

        dev_ui::RenderFrame();

        window.GlSwap();
    }

    SDL_Quit();
    dev_ui::Shutdown();

    return 0;
}

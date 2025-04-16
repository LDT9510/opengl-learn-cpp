#include "core/event_handler.h"
#include "core/renderer.h"
#include "core/window.h"

#include <thirdparty/SDL3/SDL.h>

int main() {
    auto window = core::Window::InitializeWithContext({
        .title       = "Learning OpenGL",
        .isResizable = false,
    });

    core::EventHandler eventHandler{{
        .windowsResizingCallback = core::Window::OnWindowResizing,
        .windowsQuitCallback     = [&window]() { window.OnWindowQuitEvent(); },
    }};

    core::Renderer renderer;

    window.KeyboardInputHandler(eventHandler);

    while (window.ShouldStayOpen()) {
        eventHandler.CollectInputAndProcessEvents();

        renderer.Render();

        window.GlSwap();
    }

    SDL_Quit();

    return 0;
}

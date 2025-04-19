#include "core/event_handler.h"
#include "core/renderer.h"
#include "core/window.h"

#include <SDL3/SDL.h>
#include <dev_ui/dev_ui.h>

int main() {
    auto window = core::Window::InitializeWithContext({
        .title       = "Learning OpenGL",
        .isResizable = false,
    });

    core::EventHandler eventHandler{{
        .windowsResizingCallback = core::Window::OnWindowResizing,
        .windowsQuitCallback     = [&window]() { window.OnWindowQuitEvent(); },
    }};

    // requires an initialized OpenGL context
    core::Renderer renderer;
    renderer.Setup();

    window.KeyboardInputHandler(eventHandler);

    while (window.ShouldStayOpen()) {
        dev_ui::CreateFrame();
        
        eventHandler.CollectInputAndProcessEvents();

        renderer.Render();
        
        renderer.RenderDevUi();

        dev_ui::RenderFrame();

        window.GlSwap();
    }

    SDL_Quit();
    dev_ui::Shutdown();

    return 0;
}

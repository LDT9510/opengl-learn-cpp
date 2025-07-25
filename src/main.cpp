#include "core/event_handler.h"
#include "core/filesystem.h"
#include "core/renderer.h"
#include "core/window.h"
#include "dev_ui/dev_ui.h"
#include "utils/helper_macros.h"

#include <SDL3/SDL.h>
#include <tracy/Tracy.hpp>

using namespace core;

i32 main(M_UNUSED i32 argc, M_UNUSED char** argv)
{
    TracyNoop;

    // TODO: only if debug
    spdlog::set_level(spdlog::level::debug);

    fs::Create(argv);

    Window window = Window::InitializeWithContext({
        .Title       = "Learning OpenGL",
        .Width       = 800,
        .Height      = 600,
        .IsResizable = false,
    });

    EventHandler eventHandler{{
        .WindowsResizingCallback = Window::OnWindowResizing,
        .WindowsQuitCallback     = [&window]() { window.OnWindowQuitEvent(); },
    }};

    // requires an initialized OpenGL context
    Renderer renderer;
    renderer.SetupRendering();

    eventHandler.RegisterKeyboardInputHandler(
        [&renderer, &window](const EventHandler& handler)
        {
            renderer.HandleInput(handler);
            window.HandleInput(handler);
        }
    );

    while (window.ShouldStayOpen())
    {
        dev_ui::CreateFrame();

        eventHandler.CollectInput();

        eventHandler.ProcessInput();

        renderer.Render();

        renderer.PrepareDevUi();

        dev_ui::RenderFrame();

        window.Gl_Swap();
    }

    SDL_Quit();
    dev_ui::Shutdown();

    fs::Destroy();

    return 0;
}

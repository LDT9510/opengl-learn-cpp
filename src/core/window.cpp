#include "window.h"

#include "dev_ui/dev_ui.h"
#include "event_handler.h"
#include "utils/assertions.h"

#include <SDL3/SDL.h>
#include <glad/gl.h>
#include <spdlog/spdlog.h>

#ifdef _WIN32
    #define WIN32_LEAN_AND_MEAN
    #include <windows.h>
#endif

namespace core {
static void PrintSdlVersion() {
    M_UNUSED constexpr i32 compiled = SDL_VERSION; /* hardcoded number from SDL headers */
    M_UNUSED const i32     linked   = SDL_GetVersion(); /* reported by linked SDL library */

    SPDLOG_INFO(
        "Compiled against SDL version: {}.{}.{}",
        SDL_VERSIONNUM_MAJOR(compiled),
        SDL_VERSIONNUM_MINOR(compiled),
        SDL_VERSIONNUM_MICRO(compiled)
    );

    SPDLOG_INFO(
        "Linked against SDL version: {}.{}.{}",
        SDL_VERSIONNUM_MAJOR(linked),
        SDL_VERSIONNUM_MINOR(linked),
        SDL_VERSIONNUM_MICRO(linked)
    );
}

void Window::SdlWindowDeleter::operator()(SDL_Window* sdlWindowHandle) const {
    SDL_DestroyWindow(sdlWindowHandle);
}

// ReSharper disable once CppParameterMayBeConst
void Window::SdlContextDeleter::operator()(SDL_GLContext sdlGlContextHandle) const {
    SDL_GL_DestroyContext(sdlGlContextHandle);
}

Window Window::InitializeWithContext(const Config& config) {
#ifdef _WIN32
    // fix window scaling on MS Windows
    SetProcessDPIAware();
#endif

    if (!SDL_Init(SDL_INIT_VIDEO)) {
        CRASH("SDL could not initialize: %s", SDL_GetError());
    }

    PrintSdlVersion();

    // setup OpenGL
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, config.Gl_MajorVersion);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, config.Gl_MinorVersion);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

    i32 sdlFlags = SDL_WINDOW_OPENGL;

    if (config.IsResizable) {
        sdlFlags |= SDL_WINDOW_RESIZABLE;
    }

    // Create a window and context
    SDL_Window* windowHandle =
        SDL_CreateWindow(config.Title.c_str(), config.Width, config.Height, sdlFlags);

    if (windowHandle == nullptr) {
        CRASH("Window could not be created: {}", SDL_GetError());
    }

    // ReSharper disable once CppLocalVariableMayBeConst
    SDL_GLContext contextHandle = SDL_GL_CreateContext(windowHandle);

    if (contextHandle == nullptr) {
        CRASH("OpenGL context could not be created: {}", SDL_GetError());
    }

    M_UNUSED const i32 gladLoadedVersion = gladLoadGL(SDL_GL_GetProcAddress);
    SPDLOG_INFO(
        "Glad: Loaded OpenGL {}.{} Core Profile",
        GLAD_VERSION_MAJOR(gladLoadedVersion),
        GLAD_VERSION_MINOR(gladLoadedVersion)
    );

    if (M_UNUSED const auto rendererStr = glGetString(GL_RENDERER)) {
        SPDLOG_INFO("OpenGL renderer: {}", reinterpret_cast<const char*>(rendererStr));
    }

    if (M_UNUSED const auto glVersion = glGetString(GL_VERSION)) {
        SPDLOG_INFO("OpenGL version: {}", reinterpret_cast<const char*>(glVersion));
    }

    if (M_UNUSED const auto glslVersion = glGetString(GL_SHADING_LANGUAGE_VERSION)) {
        SPDLOG_INFO("GLSL version: {}", reinterpret_cast<const char*>(glslVersion));
    }

    i32 nrAttributes;
    glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nrAttributes);
    SPDLOG_INFO("Maximum number of vertex attributes supported: {} ", nrAttributes);

    dev_ui::InitForWindow(windowHandle, contextHandle);

    return Window{windowHandle, contextHandle};
}

b8 Window::ShouldStayOpen() const {
    return !m_ShouldClose;
}

void Window::Gl_Swap() const {
    SDL_GL_SwapWindow(m_Window.get());
}

void Window::OnWindowResizing(const i32 newSizeX, const i32 newSizeY) {
    glViewport(0, 0, newSizeX, newSizeY);
}

void Window::OnWindowQuitEvent() {
    m_ShouldClose = true;
}

void Window::HandleInput(const EventHandler& eventHandler) {
    if (eventHandler.IsKeyPressed(SDLK_ESCAPE)) m_ShouldClose = true;
}

SDL_Window* Window::GetWindowHandle() const {
    return m_Window.get();
}

SDL_GLContext Window::GetGlContext() const {
    return m_Gl_Context.get();
}
} // namespace core

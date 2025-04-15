#include "core/window.h"

#include "core/event_handler.h"
#include "core/utils/assertions.h"

#include <thirdparty/SDL3/SDL.h>
#include <thirdparty/glad/gl.h>

#ifdef _WIN32
    #define WIN32_LEAN_AND_MEAN
    #include <windows.h>
#endif

static void PrintSdlVersion();

void core::Window::SdlWindowDeleter::operator()(SDL_Window* sdlWindowHandle) const {
    SDL_DestroyWindow(sdlWindowHandle);
}

void core::Window::SdlContextDeleter::operator()(
    // ReSharper disable once CppParameterMayBeConst
    SDL_GLContext sdlGlContextHandle
) const {
    SDL_GL_DestroyContext(sdlGlContextHandle);
}

core::Window core::Window::InitializeWithContext(const Config& config) {
#ifdef _WIN32
    // fix window scaling on Windows
    SetProcessDPIAware();
#endif

    if (!SDL_Init(SDL_INIT_VIDEO)) {
        CRASH("SDL could not initialize: %s", SDL_GetError());
    }

    PrintSdlVersion();

    // setup OpenGL
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, config.glMajorVersion);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, config.glMinorVersion);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

    int sdlFlags = SDL_WINDOW_OPENGL;

    if (config.isResizable) {
        sdlFlags |= SDL_WINDOW_RESIZABLE;
    }

    // Create a window and context
    SDL_Window* pWindowHandle =
        SDL_CreateWindow(config.title, config.width, config.height, sdlFlags);

    if (pWindowHandle == nullptr) {
        CRASH("Window could not be created: {}", SDL_GetError());
    }

    // ReSharper disable once CppLocalVariableMayBeConst
    SDL_GLContext pContextHandle = SDL_GL_CreateContext(pWindowHandle);

    if (pContextHandle == nullptr) {
        CRASH("OpenGL context could not be created: {}", SDL_GetError());
    }

    const int gladLoadedVersion = gladLoadGL(SDL_GL_GetProcAddress);
    SPDLOG_INFO(
        "Glad: Loaded OpenGL {}.{} Core Profile",
        GLAD_VERSION_MAJOR(gladLoadedVersion),
        GLAD_VERSION_MINOR(gladLoadedVersion)
    );

    if (auto rendererStr = reinterpret_cast<const char*>(glGetString(GL_RENDERER))) {
        SPDLOG_INFO("OpenGL renderer: {}", rendererStr);
    }

    if (auto rendererStr = reinterpret_cast<const char*>(glGetString(GL_VENDOR))) {
        SPDLOG_INFO("OpenGL vendor: {}", rendererStr);
    }

    if (auto glVersion = reinterpret_cast<const char*>(glGetString(GL_VERSION))) {
        SPDLOG_INFO("OpenGL version: {}", glVersion);
    }

    if (auto glslVersion =
            reinterpret_cast<const char*>(glGetString(GL_SHADING_LANGUAGE_VERSION))) {
        SPDLOG_INFO("GLSL version: {}", glslVersion);
    }


    int nrAttributes;
    glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nrAttributes);
    SPDLOG_INFO("Maximum number of vertex attributes supported: {} ", nrAttributes);

    return Window{pWindowHandle, pContextHandle};
}

bool core::Window::ShouldStayOpen() const {
    return !m_shouldClose;
}

void core::Window::GlSwap() const {
    SDL_GL_SwapWindow(m_window.get());
}

void core::Window::OnWindowResizing(const int newSizeX, const int newSizeY) {
    glViewport(0, 0, newSizeX, newSizeY);
}

void core::Window::OnWindowQuitEvent() {
    m_shouldClose = true;
}

void core::Window::KeyboardInputHandler(const EventHandler& eventHandler) {
    if (eventHandler.CheckKeyEvent(SDL_SCANCODE_ESCAPE)) m_shouldClose = true;
}

static void PrintSdlVersion() {
    constexpr int compiled = SDL_VERSION; /* hardcoded number from SDL headers */
    const int     linked   = SDL_GetVersion(); /* reported by linked SDL library */

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

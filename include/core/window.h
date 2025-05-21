#pragma once

#include <SDL3/SDL.h>
#include <memory>

namespace core {

class EventHandler;

class Window {
    static constexpr int kDefaultWidth          = 1280;
    static constexpr int kDefaultHeight         = 800;
    static constexpr int kDefaultGLMajorVersion = 3;
    static constexpr int kDefaultGLMinorVersion = 3;

    struct SdlWindowDeleter {
        void operator()(SDL_Window* sdlWindowHandle) const;
    };

    struct SdlContextDeleter {
        void operator()(SDL_GLContext sdlGlContextHandle) const;
    };

public:
    static constexpr int kScreenWidth  = 800;
    static constexpr int kScreenHeight = 600;

    using SdlWindowPtr    = std::unique_ptr<SDL_Window, SdlWindowDeleter>;
    using SdlGlContextPtr = std::unique_ptr<SDL_GLContextState, SdlContextDeleter>;

    struct Config {
        const char* title          = "OpenGL App";
        int         width          = kDefaultWidth;
        int         height         = kDefaultHeight;
        int         glMajorVersion = kDefaultGLMajorVersion;
        int         glMinorVersion = kDefaultGLMinorVersion;
        bool        isResizable    = true;
    };

    static Window InitializeWithContext(const Config& config);
    static void   OnWindowResizing(int newSizeX, int newSizeY);

    bool ShouldStayOpen() const;
    void GlSwap() const;
    void OnWindowQuitEvent();
    void HandleInput(const EventHandler& eventHandler);

    SDL_Window*   GetWindowHandle() const { return m_window.get(); }
    SDL_GLContext GetGlContext() const { return m_glContext.get(); }

private:
    // ReSharper disable once CppParameterMayBeConst
    explicit Window(SDL_Window* window, SDL_GLContext context) noexcept :
        m_window{window}, m_glContext{context} {}

    SdlWindowPtr    m_window      = nullptr;
    SdlGlContextPtr m_glContext   = nullptr;
    bool            m_shouldClose = false;
};

} // namespace core

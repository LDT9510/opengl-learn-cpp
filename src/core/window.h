#pragma once

#include "core/types.h"

#include <SDL3/SDL.h>

#include <memory>
#include <string>

namespace core
{
    static constexpr i32 DEFAULT_WINDOW_WIDTH     = 1280;
    static constexpr i32 DEFAULT_WINDOW_HEIGHT    = 800;
    static constexpr i32 DEFAULT_GL_MAJOR_VERSION = 3;
    static constexpr i32 DEFAULT_GL_MINOR_VERSION = 3;

    class EventHandler;

    class Window
    {
        class SdlWindowDeleter
        {
        public:
            void operator()(SDL_Window* sdlWindowHandle) const;
        };

        class SdlContextDeleter
        {
        public:
            void operator()(SDL_GLContext sdlGlContextHandle) const;
        };

    public:
        static constexpr i32 SCREEN_WIDTH  = 800;
        static constexpr i32 SCREEN_HEIGHT = 600;

        using SdlWindowPtr    = std::unique_ptr<SDL_Window, SdlWindowDeleter>;
        using SdlGlContextPtr = std::unique_ptr<SDL_GLContextState, SdlContextDeleter>;

        struct Config
        {
            std::string Title           = "OpenGL App";
            i32         Width           = DEFAULT_WINDOW_WIDTH;
            i32         Height          = DEFAULT_WINDOW_HEIGHT;
            i32         Gl_MajorVersion = DEFAULT_GL_MAJOR_VERSION;
            i32         Gl_MinorVersion = DEFAULT_GL_MINOR_VERSION;
            b8          IsResizable     = true;
        };

        static Window InitializeWithContext(const Config& config);
        static void   OnWindowResizing(i32 newSizeX, i32 newSizeY);
        b8            ShouldStayOpen() const;
        void          Gl_Swap() const;
        void          OnWindowQuitEvent();
        void          HandleInput(const EventHandler& eventHandler);
        SDL_Window*   GetWindowHandle() const;
        SDL_GLContext GetGlContext() const;

    private:
        explicit Window(SDL_Window* window, SDL_GLContext context) noexcept :
            m_Window{window}, m_Gl_Context{context}
        {
        }

        SdlWindowPtr    m_Window      = nullptr;
        SdlGlContextPtr m_Gl_Context  = nullptr;
        b8              m_ShouldClose = false;
    };
} // namespace core

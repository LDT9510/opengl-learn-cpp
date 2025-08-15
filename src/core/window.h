#pragma once

#include "core/types.h"

#include <SDL3/SDL.h>

#include <memory>
#include <string>

namespace core
{

class event_handler;

class window {
	class sdl_window_deleter {
	    public:
		void operator()(SDL_Window *sdl_window_handle) const;
	};

	class sdl_context_deleter {
	    public:
		void operator()(SDL_GLContext sdl_gl_context_handle) const;
	};

    public:
	static constexpr i32 DEFAULT_WINDOW_WIDTH = 1280;
	static constexpr i32 DEFAULT_WINDOW_HEIGHT = 800;
	static constexpr i32 DEFAULT_GL_MAJOR_VERSION = 3;
	static constexpr i32 DEFAULT_GL_MINOR_VERSION = 3;

	using sdl_window_ptr_t = std::unique_ptr<SDL_Window, sdl_window_deleter>;
	using sdl_gl_context_ptr_t = std::unique_ptr<SDL_GLContextState, sdl_context_deleter>;

	struct config {
		std::string title = "OpenGL App";
		i32         width = DEFAULT_WINDOW_WIDTH;
		i32         h = DEFAULT_WINDOW_HEIGHT;
		i32         gl_major_version = DEFAULT_GL_MAJOR_VERSION;
		i32         gl_minor_version = DEFAULT_GL_MINOR_VERSION;
		b8          is_resizable = true;
	};

	static window initialize_with_context(const config &config);
	static void   on_window_resizing(i32 new_size_x, i32 new_size_y);
	b8            should_stay_open() const;
	void          gl_swap() const;
	void          on_window_quit_event();
	void          handle_input(const event_handler &event_handler);
	SDL_Window   *get_window_handle() const;
	SDL_GLContext get_gl_context() const;

    private:
	explicit window(SDL_Window *window, SDL_GLContext context) noexcept
	        : m_window{ window }
	        , m_gl_context{ context }
	{
	}

	sdl_window_ptr_t     m_window = nullptr;
	sdl_gl_context_ptr_t m_gl_context = nullptr;
	b8                   m_should_close = false;
};
} // namespace core

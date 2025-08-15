#include "core/window.h"

#include "core/event_handler.h"
#include "dev_ui/dev_ui.h"
#include "utils/assertions.h"

#include <SDL3/SDL.h>
#include <glad/gl.h>
#include <spdlog/spdlog.h>

#ifdef _WIN32
#	define WIN32_LEAN_AND_MEAN
#	include <windows.h>
#endif

namespace core
{

namespace
{
void print_sdl_version()
{
	//NOLINTNEXTLINE(*-math-missing-parentheses)
	M_UNUSED constexpr i32 compiled = SDL_VERSION; /* hardcoded number from SDL headers */
	M_UNUSED const i32     linked = SDL_GetVersion(); /* reported by linked SDL library */

	SPDLOG_INFO("Compiled against SDL version: {}.{}.{}", SDL_VERSIONNUM_MAJOR(compiled),
	            SDL_VERSIONNUM_MINOR(compiled), SDL_VERSIONNUM_MICRO(compiled));

	SPDLOG_INFO("Linked against SDL version: {}.{}.{}", SDL_VERSIONNUM_MAJOR(linked),
	            SDL_VERSIONNUM_MINOR(linked), SDL_VERSIONNUM_MICRO(linked));
}
}

void window::sdl_window_deleter::operator()(SDL_Window *sdl_window_handle) const
{
	SDL_DestroyWindow(sdl_window_handle);
}

// ReSharper disable once CppParameterMayBeConst
void window::sdl_context_deleter::operator()(SDL_GLContext sdl_gl_context_handle) const
{
	SDL_GL_DestroyContext(sdl_gl_context_handle);
}

window window::initialize_with_context(const config &config)
{
#ifdef _WIN32
	// fix window scaling on MS Windows
	SetProcessDPIAware();
#endif

	if (!SDL_Init(SDL_INIT_VIDEO)) {
		crash("SDL could not initialize: %s", SDL_GetError());
	}

	print_sdl_version();

	// setup OpenGL
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, config.gl_major_version);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, config.gl_minor_version);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

	u32 sdl_flags = SDL_WINDOW_OPENGL;

	if (config.is_resizable) {
		sdl_flags |= SDL_WINDOW_RESIZABLE;
	}

	// Create a window and context
	SDL_Window *window_handle =
	        SDL_CreateWindow(config.title.c_str(), config.width, config.h, sdl_flags);

	if (window_handle == nullptr) {
		crash("Window could not be created: {}", SDL_GetError());
	}

	// ReSharper disable once CppLocalVariableMayBeConst
	SDL_GLContext context_handle = SDL_GL_CreateContext(window_handle);

	if (context_handle == nullptr) {
		crash("OpenGL context could not be created: {}", SDL_GetError());
	}

	M_UNUSED const i32 glad_loaded_version = gladLoadGL(SDL_GL_GetProcAddress);
	SPDLOG_INFO("Glad: Loaded OpenGL {}.{} Core Profile",
	            GLAD_VERSION_MAJOR(glad_loaded_version),
	            GLAD_VERSION_MINOR(glad_loaded_version));

	if (M_UNUSED const auto renderer_str = glGetString(GL_RENDERER)) {
		SPDLOG_INFO("OpenGL renderer: {}", reinterpret_cast<const char *>(renderer_str));
	}

	if (M_UNUSED const auto gl_version = glGetString(GL_VERSION)) {
		SPDLOG_INFO("OpenGL version: {}", reinterpret_cast<const char *>(gl_version));
	}

	if (M_UNUSED const auto glsl_version = glGetString(GL_SHADING_LANGUAGE_VERSION)) {
		SPDLOG_INFO("GLSL version: {}", reinterpret_cast<const char *>(glsl_version));
	}

	i32 nr_attributes;
	glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nr_attributes);
	SPDLOG_INFO("Maximum number of vertex attributes supported: {} ", nr_attributes);

	dev_ui::init_for_window(window_handle, context_handle);

	return window{ window_handle, context_handle };
}

b8 window::should_stay_open() const
{
	return !m_should_close;
}

void window::gl_swap() const
{
	SDL_GL_SwapWindow(m_window.get());
}

void window::on_window_resizing(const i32 new_size_x, const i32 new_size_y)
{
	glViewport(0, 0, new_size_x, new_size_y);
}

void window::on_window_quit_event()
{
	m_should_close = true;
}

void window::handle_input(const event_handler &event_handler)
{
	if (event_handler.is_key_pressed(SDLK_ESCAPE)) {
		m_should_close = true;
	}
}

SDL_Window *window::get_window_handle() const
{
	return m_window.get();
}

SDL_GLContext window::get_gl_context() const
{
	return m_gl_context.get();
}
} // namespace core

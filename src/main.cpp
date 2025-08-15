#include "core/event_handler.h"
#include "core/filesystem.h"
#include "core/renderer.h"
#include "core/window.h"
#include "dev_ui/dev_ui.h"
#include "utils/helper_macros.h"

#include <SDL3/SDL.h>
#include <tracy/Tracy.hpp>

using namespace core;

i32 main(M_UNUSED i32 argc, M_UNUSED char **argv) //
{
	TracyNoop;

	// TODO: only if debug
	spdlog::set_level(spdlog::level::debug);

	fs::create(argv);

	window wnd = window::initialize_with_context({
	        .title = "Learning OpenGL",
	        .width = 800,
	        .h = 600,
	        .is_resizable = false,
	});

	event_handler evh{ {
		.windows_resizing_callback = window::on_window_resizing,
		.windows_quit_callback = [&wnd]() { wnd.on_window_quit_event(); },
	} };

	// requires an initialized OpenGL context
	renderer rendr;
	rendr.setup_rendering();

	evh.register_keyboard_input_handler([&rendr, &wnd](const event_handler &handler) {
		rendr.handle_input(handler);
		wnd.handle_input(handler);
	});

	while (wnd.should_stay_open()) {
		dev_ui::create_frame();
		evh.collect_input();
		evh.process_input();
		rendr.render();
		rendr.prepare_dev_ui();
		dev_ui::render_frame();
		wnd.gl_swap();
	}

	SDL_Quit();
	dev_ui::shutdown();
	fs::destroy();

	return 0;
}

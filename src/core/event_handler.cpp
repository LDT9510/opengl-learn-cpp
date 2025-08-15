

#include "core/event_handler.h"

#include "dev_ui/dev_ui.h"

#include <SDL3/SDL.h>

namespace core
{
event_handler::event_handler(config config)
        : m_window_resizing_fn{ std::move(config.windows_resizing_callback) }
        , m_window_quit_fn{ std::move(config.windows_quit_callback) }
{
}

// TODO either handle all events here or defer them
void event_handler::collect_input()
{
	m_last_keyboard_state = m_current_keyboard_state;
	m_keyboard_input_available = false;

	SDL_Event e;
	while (SDL_PollEvent(&e)) {
		dev_ui::process_input(e);

		switch (e.type) {
		case SDL_EVENT_QUIT:
			m_window_quit_fn();
			break;

		case SDL_EVENT_WINDOW_PIXEL_SIZE_CHANGED:
			m_window_resizing_fn(e.window.data1, e.window.data2);
			break;

		case SDL_EVENT_MOUSE_WHEEL:
			if (m_mouse_wheel_direction_fn)
				(*m_mouse_wheel_direction_fn)(e.wheel.y);
			break;

		case SDL_EVENT_MOUSE_MOTION:
			if (m_mouse_offset_fn) {
				(*m_mouse_offset_fn)(e.motion.xrel, -e.motion.yrel);
			}
			break;

		case SDL_EVENT_KEY_DOWN:
		case SDL_EVENT_KEY_UP:
			m_keyboard_input_available = true;
			break;

		default:
			break;
		}
	}

	i32       num_keys;
	const b8 *keyboard_state = SDL_GetKeyboardState(&num_keys);
	std::copy_n(keyboard_state, num_keys,
	            m_current_keyboard_state.data()); // store the previous state
}

void event_handler::process_input() const
{
	if (m_keyboard_input_available && m_keyboard_input_handler_fn) {
		(*m_keyboard_input_handler_fn)(*this);
	}
}

b8 event_handler::is_key_pressed(SDL_Keycode key_code) const
{
	return m_current_keyboard_state[SDL_GetScancodeFromKey(key_code, nullptr)];
}

b8 event_handler::is_key_released(SDL_Keycode key_code) const
{
	return !is_key_pressed(SDL_GetScancodeFromKey(key_code, nullptr));
}

b8 event_handler::is_key_just_pressed(SDL_Keycode key_code) const
{
	auto scancode = SDL_GetScancodeFromKey(key_code, nullptr);
	return m_current_keyboard_state[scancode] && !m_last_keyboard_state[scancode];
}

void event_handler::clear_optional_callbacks()
{
	m_mouse_offset_fn = std::nullopt;
	m_mouse_wheel_direction_fn = std::nullopt;
	m_keyboard_input_handler_fn = std::nullopt;
}
} // namespace core

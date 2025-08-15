#pragma once

#include "core/types.h"

#include <SDL3/SDL.h>

#include <array>
#include <functional>
#include <optional>

namespace core
{
class event_handler {
	using mouse_offset_fn_t = std::function<void(f32 x_offset, f32 y_offset)>;
	using mouse_wheel_direction_fn_t = std::function<void(f32 mouse_wheel_direction)>;
	using windows_resizing_fn_t = std::function<void(i32 new_size_x, i32 mew_size_y)>;
	using windows_quit_fn_t = std::function<void()>;
	using keyboard_input_handler_fn_t = std::function<void(const event_handler &evh)>;

    public:
	struct config {
		windows_resizing_fn_t windows_resizing_callback;
		windows_quit_fn_t     windows_quit_callback;
	};

	explicit event_handler(config config);
	~event_handler() = default;

	event_handler(const event_handler &other) = delete;
	event_handler &operator=(const event_handler &other) = delete;
	event_handler(event_handler &&other) noexcept = default;
	event_handler &operator=(event_handler &&other) noexcept = default;

	void           register_mouse_offset_callback(const mouse_offset_fn_t &callback)
	{
		m_mouse_offset_fn = callback;
	}

	void register_mouse_wheel_direction_callback(const mouse_wheel_direction_fn_t &callback)
	{
		m_mouse_wheel_direction_fn = callback;
	}

	void register_keyboard_input_handler(const keyboard_input_handler_fn_t &callback)
	{
		m_keyboard_input_handler_fn = callback;
	}

	void clear_optional_callbacks();
	void collect_input();
	void process_input() const;
	b8   is_key_pressed(SDL_Keycode key_code) const;
	b8   is_key_released(SDL_Keycode key_code) const;
	b8   is_key_just_pressed(SDL_Keycode key_code) const;

    private:
	std::array<b8, SDL_SCANCODE_COUNT>         m_current_keyboard_state{};
	std::array<b8, SDL_SCANCODE_COUNT>         m_last_keyboard_state{};
	b8                                         m_keyboard_input_available{};
	windows_resizing_fn_t                      m_window_resizing_fn;
	windows_quit_fn_t                          m_window_quit_fn;
	std::optional<keyboard_input_handler_fn_t> m_keyboard_input_handler_fn;
	std::optional<mouse_offset_fn_t>           m_mouse_offset_fn;
	std::optional<mouse_wheel_direction_fn_t>  m_mouse_wheel_direction_fn;
};
} // namespace core

#pragma once

#include "core/shader.h"
#include "core/types.h"

namespace core
{
class event_handler;
class filesystem;

class renderer {
    public:
	renderer();
	~renderer();

	renderer(const renderer &other) = delete;
	renderer &operator=(const renderer &other) = delete;
	renderer(renderer &&other) noexcept = default;
	renderer &operator=(renderer &&other) noexcept = default;

	void setup_rendering() const;
	void render() const;
	void handle_input(const event_handler &event_handler);
	void prepare_dev_ui();
	b8   reload_shaders();

    private:
	shader m_shader;
	u32    m_vao{};
	u32    m_vbo{};
	u32    m_ebo{};
	u32    m_texture{};
	b8     m_is_shader_reloading{};
	b8     m_is_wireframe_active{};
};
} // namespace core

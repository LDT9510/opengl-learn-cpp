#pragma once

#include "core/shader.h"
#include "shaders/shader_source.h"

namespace core {

using namespace shaders;

class EventHandler;

class Renderer {
public:
    Renderer();
    ~Renderer();

    static void RenderDevUi();

    void SetupRendering() const;
    void Render() const;
    void HandleInput(const EventHandler& eventHandler);


private:
    unsigned int m_vao;
    unsigned int m_vbo;
    unsigned int m_ebo;
    Shader       m_shader{vertex::kSource, fragment::kSource};

    bool m_wireframeActive{false};
};

} // namespace core

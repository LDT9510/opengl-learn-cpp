#pragma once

#include "shaders/shader_source.h"

#include "core/shader.hpp"

namespace core {

using namespace shaders;

class Renderer {
public:
    Renderer();
    ~Renderer();

    void Setup() const;
    void Render() const;
    void RenderDevUi();

private:
    unsigned int m_vao;
    unsigned int m_vbo;
    core::Shader m_shader{vertex::kSource, fragment::kSource};
};

} // namespace core

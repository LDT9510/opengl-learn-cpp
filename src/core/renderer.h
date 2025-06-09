#pragma once

#include "../utils/types.h"
#include "core/shader.h"

namespace core
{
    class EventHandler;
    class Filesystem;

    class Renderer
    {
    public:
        Renderer();
        Renderer(const Renderer& other)            = delete;
        Renderer& operator=(const Renderer& other) = delete;
        ~Renderer();

        Renderer(Renderer&& other) noexcept
        {
            *this = std::move(other);
        }

        Renderer& operator=(Renderer&& other) noexcept
        {
            if (this == &other) return *this;

            m_Vao               = other.m_Vao;
            m_Vbo               = other.m_Vbo;
            m_Ebo               = other.m_Ebo;
            m_Texture           = other.m_Texture;
            m_Shader            = std::move(other.m_Shader);
            m_IsWireframeActive = other.m_IsWireframeActive;

            // when moved, reset "other" program ID so that its destructor
            // don't destroy the program
            other.m_Vao     = 0;
            other.m_Vbo     = 0;
            other.m_Ebo     = 0;
            other.m_Texture = 0;

            return *this;
        }

        void SetupRendering() const;
        void Render() const;
        void HandleInput(const EventHandler& eventHandler);
        void PrepareDevUi();
        b8   ReloadShaders();


    private:
        u32    m_Vao{};
        u32    m_Vbo{};
        u32    m_Ebo{};
        u32    m_Texture{};
        Shader m_Shader;
        b8     m_IsShaderReloading{};
        b8     m_IsWireframeActive{};
    };
} // namespace core

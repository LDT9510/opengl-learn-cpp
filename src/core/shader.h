#pragma once

#include "core/filesystem.h"

#include <glm/fwd.hpp>

namespace core
{
    class Shader
    {
    public:
        Shader() = default;
        Shader(const CoreShaderFile& vertexFileName, const CoreShaderFile& fragmentFileName);
        Shader(const std::string& vertexCode, const std::string& fragmentCode);
        ~Shader();

        Shader(const Shader& other)            = delete;
        Shader& operator=(const Shader& other) = delete;

        Shader(Shader&& other) noexcept
        {
            *this = std::move(other);
        }

        Shader& operator=(Shader&& other) noexcept
        {
            if (this == &other) return *this;
            m_ProgramId = other.m_ProgramId;
            m_IsValid   = other.m_IsValid;

            // when moved, reset "other" program ID so that its destructor
            // don't destroy the program
            other.m_ProgramId = 0;

            return *this;
        }

        b8 IsValid() const
        {
            return m_IsValid;
        };

        void Use() const;
        void SetBool(const std::string& name, b8 value) const;
        void SetInt32(const std::string& name, i32 value) const;
        void SetFloat(const std::string& name, f32 value) const;
        void SetVec2(const std::string& name, const glm::vec2& value) const;
        void SetVec2(const std::string& name, f32 x, f32 y) const;
        void SetVec3(const std::string& name, const glm::vec3& value) const;
        void SetVec3(const std::string& name, f32 x, f32 y, f32 z) const;
        void SetVec4(const std::string& name, const glm::vec4& value) const;
        void SetVec4(const std::string& name, f32 x, f32 y, f32 z, f32 w) const;
        void SetMat2(const std::string& name, const glm::mat2& mat) const;
        void SetMat3(const std::string& name, const glm::mat3& mat) const;
        void SetMat4(const std::string& name, const glm::mat4& mat) const;

    private:
        u32        m_ProgramId = 0;
        b8         m_IsValid   = false;
        mutable b8 m_Warned    = false;
    };
} // namespace core

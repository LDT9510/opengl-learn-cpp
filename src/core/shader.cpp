#include "shader.h"

#include <glad/gl.h>
#include <glm/glm.hpp>
#include <spdlog/spdlog.h>

namespace core
{
    static u32 CreateShader(const std::string& shaderCode, u32 shaderType, std::string_view shaderName)
    {
        i32 success  = 0;
        u32 shaderId = glCreateShader(shaderType);

        const char* sourcePtr = shaderCode.c_str();
        glShaderSource(shaderId, 1, &sourcePtr, nullptr);
        glCompileShader(shaderId);

        glGetShaderiv(shaderId, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            char infoLog[512];
            glGetShaderInfoLog(shaderId, 512, nullptr, infoLog);
            SPDLOG_ERROR("\"Shader '{}' compilation failed: {}", shaderName, infoLog);
        }
        else
        {
            SPDLOG_INFO("Shader loaded OK: {}", shaderName);
        }

        return shaderId;
    }

    static b8 CompileFromGlslCode(const std::string& vertexCode, const std::string& fragmentCode, u32* outProgramId)
    {
        i32 success = 0;
        b8  isValid = true;

        if (vertexCode.empty() || fragmentCode.empty())
        {
            isValid = false;
            SPDLOG_ERROR("Shader source was empty");
        }
        else
        {
            const u32 vertexId   = CreateShader(vertexCode, GL_VERTEX_SHADER, "VERTEX");
            const u32 fragmentId = CreateShader(fragmentCode, GL_FRAGMENT_SHADER, "FRAGMENT");
            *outProgramId        = glCreateProgram();

            glAttachShader(*outProgramId, vertexId);
            glAttachShader(*outProgramId, fragmentId);
            glLinkProgram(*outProgramId);

            glGetProgramiv(*outProgramId, GL_LINK_STATUS, &success);
            if (!success)
            {
                char infoLog[512];
                glGetProgramInfoLog(*outProgramId, 512, nullptr, infoLog);
                SPDLOG_ERROR("Shader program linking failed: {}", infoLog);
                isValid = false;
            }

            glDeleteShader(vertexId);
            glDeleteShader(fragmentId);
        }

        return isValid;
    }

    Shader::Shader(const CoreShaderFile& vertexFileName, const CoreShaderFile& fragmentFileName)
    {
        auto vertexSource   = fs::Instance().ReadFile<std::string>(vertexFileName);
        auto fragmentSource = fs::Instance().ReadFile<std::string>(fragmentFileName);

        m_IsValid = CompileFromGlslCode(vertexSource, fragmentSource, &m_ProgramId);
    }

    Shader::Shader(const std::string& vertexCode, const std::string& fragmentCode)
    {
        m_IsValid = CompileFromGlslCode(vertexCode, fragmentCode, &m_ProgramId);
    }

    Shader::~Shader()
    {
        glDeleteProgram(m_ProgramId);
    }

    void Shader::Use() const
    {
        if (m_IsValid)
        {
            glUseProgram(m_ProgramId);
        }
        else if (!m_Warned)
        {
            SPDLOG_ERROR("Invalid shader");
            m_Warned = true;
        }
    }

    void Shader::SetBool(const std::string& name, const b8 value) const
    {
        glUniform1i(glGetUniformLocation(m_ProgramId, name.c_str()), static_cast<i32>(value));
    }

    void Shader::SetInt32(const std::string& name, const i32 value) const
    {
        glUniform1i(glGetUniformLocation(m_ProgramId, name.c_str()), value);
    }

    void Shader::SetFloat(const std::string& name, const f32 value) const
    {
        glUniform1f(glGetUniformLocation(m_ProgramId, name.c_str()), value);
    }

    void Shader::SetVec2(const std::string& name, const glm::vec2& value) const
    {
        glUniform2fv(glGetUniformLocation(m_ProgramId, name.c_str()), 1, &value[0]);
    }

    void Shader::SetVec2(const std::string& name, const f32 x, const f32 y) const
    {
        glUniform2f(glGetUniformLocation(m_ProgramId, name.c_str()), x, y);
    }

    void Shader::SetVec3(const std::string& name, const glm::vec3& value) const
    {
        glUniform3fv(glGetUniformLocation(m_ProgramId, name.c_str()), 1, &value[0]);
    }

    void Shader::SetVec3(const std::string& name, const f32 x, const f32 y, const f32 z) const
    {
        glUniform3f(glGetUniformLocation(m_ProgramId, name.c_str()), x, y, z);
    }

    void Shader::SetVec4(const std::string& name, const glm::vec4& value) const
    {
        glUniform4fv(glGetUniformLocation(m_ProgramId, name.c_str()), 1, &value[0]);
    }

    void Shader::SetVec4(const std::string& name, const f32 x, const f32 y, const f32 z, const f32 w) const
    {
        glUniform4f(glGetUniformLocation(m_ProgramId, name.c_str()), x, y, z, w);
    }

    void Shader::SetMat2(const std::string& name, const glm::mat2& mat) const
    {
        glUniformMatrix2fv(glGetUniformLocation(m_ProgramId, name.c_str()), 1, GL_FALSE, &mat[0][0]);
    }

    void Shader::SetMat3(const std::string& name, const glm::mat3& mat) const
    {
        glUniformMatrix3fv(glGetUniformLocation(m_ProgramId, name.c_str()), 1, GL_FALSE, &mat[0][0]);
    }

    void Shader::SetMat4(const std::string& name, const glm::mat4& mat) const
    {
        glUniformMatrix4fv(glGetUniformLocation(m_ProgramId, name.c_str()), 1, GL_FALSE, &mat[0][0]);
    }
} // namespace core

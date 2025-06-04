#include "core/shader.h"

#include <glad/gl.h>
#include <glm/glm.hpp>
#include <spdlog/spdlog.h>

static unsigned int CreateShader(
    const char* shaderCode, const unsigned int shaderType, const std::string_view shaderName
) {
    int                success = 0;
    const unsigned int shaderId{glCreateShader(shaderType)};
    glShaderSource(shaderId, 1, &shaderCode, nullptr);
    glCompileShader(shaderId);
    glGetShaderiv(shaderId, GL_COMPILE_STATUS, &success);
    if (!success) {
        char infoLog[512];
        glGetShaderInfoLog(shaderId, 512, nullptr, infoLog);
        SPDLOG_ERROR("\"Shader '{}' compilation failed: {}", shaderName, infoLog);
    } else {
        SPDLOG_INFO("Shader loaded OK: {}", shaderName);
    }

    return shaderId;
}

core::Shader::Shader(const std::string_view vertexCode, const std::string_view fragmentCode) {
    int success = 0;

    if (vertexCode.empty() || fragmentCode.empty()) {
        m_isValid = false;
    } else {
        const unsigned int vertexId = CreateShader(vertexCode.data(), GL_VERTEX_SHADER, "VERTEX");
        const unsigned int fragmentId =
            CreateShader(fragmentCode.data(), GL_FRAGMENT_SHADER, "FRAGMENT");
        m_programId = glCreateProgram();

        glAttachShader(m_programId, vertexId);
        glAttachShader(m_programId, fragmentId);
        glLinkProgram(m_programId);

        glGetProgramiv(m_programId, GL_LINK_STATUS, &success);
        if (!success) {
            char infoLog[512];
            glGetProgramInfoLog(m_programId, 512, nullptr, infoLog);
            SPDLOG_ERROR("Shader program linking failed: {}", infoLog);
        }

        glDeleteShader(vertexId);
        glDeleteShader(fragmentId);
        m_isValid = true;
    }
}

core::Shader::~Shader() {
    glDeleteProgram(m_programId);
}

void core::Shader::Use() const {
    if (m_isValid) {
        glUseProgram(m_programId);
    } else {
        SPDLOG_ERROR("Invalid shader");
    }
}

void core::Shader::SetBool(const char* name, const bool value) const {
    glUniform1i(glGetUniformLocation(m_programId, name), static_cast<int>(value));
}

void core::Shader::SetInt(const char* name, const int value) const {
    glUniform1i(glGetUniformLocation(m_programId, name), value);
}

void core::Shader::SetFloat(const char* name, const float value) const {
    glUniform1f(glGetUniformLocation(m_programId, name), value);
}

void core::Shader::SetVec2(const std::string& name, const glm::vec2& value) const {
    glUniform2fv(glGetUniformLocation(m_programId, name.c_str()), 1, &value[0]);
}

void core::Shader::SetVec2(const std::string& name, const float x, const float y) const {
    glUniform2f(glGetUniformLocation(m_programId, name.c_str()), x, y);
}

void core::Shader::SetVec3(const std::string& name, const glm::vec3& value) const {
    glUniform3fv(glGetUniformLocation(m_programId, name.c_str()), 1, &value[0]);
}

void core::Shader::SetVec3(
    const std::string& name, const float x, const float y, const float z
) const {
    glUniform3f(glGetUniformLocation(m_programId, name.c_str()), x, y, z);
}

void core::Shader::SetVec4(const std::string& name, const glm::vec4& value) const {
    glUniform4fv(glGetUniformLocation(m_programId, name.c_str()), 1, &value[0]);
}

void core::Shader::SetVec4(
    const std::string& name, const float x, const float y, const float z, const float w
) const {
    glUniform4f(glGetUniformLocation(m_programId, name.c_str()), x, y, z, w);
}

void core::Shader::SetMat2(const std::string& name, const glm::mat2& mat) const {
    glUniformMatrix2fv(glGetUniformLocation(m_programId, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}

void core::Shader::SetMat3(const std::string& name, const glm::mat3& mat) const {
    glUniformMatrix3fv(glGetUniformLocation(m_programId, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}

void core::Shader::SetMat4(const std::string& name, const glm::mat4& mat) const {
    glUniformMatrix4fv(glGetUniformLocation(m_programId, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}

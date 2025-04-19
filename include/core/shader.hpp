#pragma once

// #include <glm/glm.hpp>

namespace core {

class Shader {
public:
    Shader(const char* vertexCode, const char* fragmentCode);
    Shader(const Shader& other) = delete;

    Shader(Shader&& other) noexcept :
        m_programId{other.m_programId}, m_isValid{other.m_isValid} {
        // when moved, reset the program ID so that the other destructor
        // don't destroy the program
        other.m_programId = 0u;
    };

    Shader& operator=(const Shader& other) = delete;

    Shader& operator=(Shader&& other) noexcept {
        if (this == &other) return *this;
        m_programId = other.m_programId;
        m_isValid   = other.m_isValid;

        // when moved, reset the program ID so that the other destructor
        // don't destroy the program
        other.m_programId = 0u;

        return *this;
    }

    ~Shader();

    void Use() const;
    // void SetBool(const char* name, bool value) const;
    // void SetInt(const char* name, int value) const;
    // void SetFloat(const char* name, float value) const;
    // void SetVec2(const std::string& name, const glm::vec2& value) const;
    // void SetVec2(const std::string& name, float x, float y) const;
    // void SetVec3(const std::string& name, const glm::vec3& value) const;
    // void SetVec3(const std::string& name, float x, float y, float z) const;
    // void SetVec4(const std::string& name, const glm::vec4& value) const;
    // void SetVec4(const std::string& name, float x, float y, float z, float w) const;
    // void SetMat2(const std::string& name, const glm::mat2& mat) const;
    // void SetMat3(const std::string& name, const glm::mat3& mat) const;
    // void SetMat4(const std::string& name, const glm::mat4& mat) const;

private:
    unsigned int m_programId;
    bool         m_isValid;
};

} // namespace core

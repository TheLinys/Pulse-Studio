#include "pspch.h"
#include "Shader.h"
#include <GLAD/glad.h>
#include <glm/gtc/type_ptr.hpp>

namespace PulseStudio {

    Shader::Shader() : m_RendererID(0)
    {
    }

    Shader::~Shader()
    {
        if (m_RendererID != 0)
        {
            glDeleteProgram(m_RendererID);
        }
    }

    bool Shader::LoadFromSource(const char* vertexSource, const char* fragmentSource) 
    {
        // Compile shaders
        uint32_t vertexShader = CompileShader(GL_VERTEX_SHADER, vertexSource);
        if (vertexShader == 0) return false;

        uint32_t fragmentShader = CompileShader(GL_FRAGMENT_SHADER, fragmentSource);
        if (fragmentShader == 0)
        {
            glDeleteShader(vertexShader);
            return false;
        }

        // Create shader program
        m_RendererID = glCreateProgram();
        glAttachShader(m_RendererID, vertexShader);
        glAttachShader(m_RendererID, fragmentShader);
        glLinkProgram(m_RendererID);

        // Check linking errors
        int success;
        char infoLog[512];
        glGetProgramiv(m_RendererID, GL_LINK_STATUS, &success);
        if (!success)
        {
            glGetProgramInfoLog(m_RendererID, 512, NULL, infoLog);
            LOG_ERROR(std::format("Shader program linking failed: {0}", infoLog));
            glDeleteProgram(m_RendererID);
            m_RendererID = 0;
        }

        // Clean up shaders
        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);

        return success;
    }

    uint32_t Shader::CompileShader(uint32_t type, const char* source)
    {
        uint32_t shader = glCreateShader(type);
        glShaderSource(shader, 1, &source, NULL);
        glCompileShader(shader);

        // Check compilation errors
        int success;
        char infoLog[512];
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(shader, 512, NULL, infoLog);
            const char* shaderType = (type == GL_VERTEX_SHADER) ? "Vertex" : "Fragment";
            LOG_ERROR(std::format("{0} shader compilation failed: {1}", shaderType, infoLog));
            glDeleteShader(shader);
            return 0;
        }

        return shader;
    }

    void Shader::Bind() const 
    {
        if (m_RendererID != 0)
            glUseProgram(m_RendererID);
    }

    void Shader::Unbind() const 
    {
        glUseProgram(0);
    }

    int Shader::GetUniformLocation(const std::string& name)
    {
        auto it = m_UniformLocationCache.find(name);
        if (it != m_UniformLocationCache.end())
            return it->second;

        int location = glGetUniformLocation(m_RendererID, name.c_str());
        if (location == -1)
            LOG_WARN(std::format("Uniform '{0}' not found in shader.", name));

        m_UniformLocationCache[name] = location;
        return location;
    }

    // Uniform setting implementations
    void Shader::SetFloat(const std::string& name, float value) 
    {
        glUniform1f(GetUniformLocation(name), value);
    }

    void Shader::SetFloat2(const std::string& name, const glm::vec2& value)
    {
        glUniform2f(GetUniformLocation(name), value.x, value.y);
    }

    void Shader::SetFloat3(const std::string& name, const glm::vec3& value) 
    {
        glUniform3f(GetUniformLocation(name), value.x, value.y, value.z);
    }

    void Shader::SetFloat4(const std::string& name, const glm::vec4& value) 
    {
        glUniform4f(GetUniformLocation(name), value.x, value.y, value.z, value.w);
    }

    void Shader::SetMat3(const std::string& name, const glm::mat3& matrix)
    {
        glUniformMatrix3fv(GetUniformLocation(name), 1, GL_FALSE, glm::value_ptr(matrix));
    }

    void Shader::SetMat4(const std::string& name, const glm::mat4& matrix)
    {
        glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, glm::value_ptr(matrix));
    }

    void Shader::SetInt(const std::string& name, int value)
    {
        glUniform1i(GetUniformLocation(name), value);
    }

    void Shader::SetBool(const std::string& name, bool value)
    {
        glUniform1i(GetUniformLocation(name), (int)value);
    }

}
#pragma once

#include "pspch.h"

#include <glm/glm.hpp>
#include <glad/glad.h>

namespace PulseStudio {

    /**
     * @brief Supported shader data types for vertex attributes
     */
    enum class ShaderDataType
    {
        None = 0, Float, Float2, Float3, Float4, Mat3, Mat4, Int, Int2, Int3, Int4, Bool
    };

    /**
     * @brief Converts ShaderDataType to OpenGL base type
     */
    static uint32_t ShaderDataTypeToOpenGLBaseType(ShaderDataType type)
    {
        switch (type)
        {
        case ShaderDataType::Float:    return GL_FLOAT;
        case ShaderDataType::Float2:   return GL_FLOAT;
        case ShaderDataType::Float3:   return GL_FLOAT;
        case ShaderDataType::Float4:   return GL_FLOAT;
        case ShaderDataType::Mat3:     return GL_FLOAT;
        case ShaderDataType::Mat4:     return GL_FLOAT;
        case ShaderDataType::Int:      return GL_INT;
        case ShaderDataType::Int2:     return GL_INT;
        case ShaderDataType::Int3:     return GL_INT;
        case ShaderDataType::Int4:     return GL_INT;
        case ShaderDataType::Bool:     return GL_BOOL;
        default: return 0;
        }
    }

    /**
     * @brief Describes the layout of a vertex buffer element
     */
    struct BufferElement
    {
        std::string Name;
        ShaderDataType Type;
        uint32_t Size;
        uint32_t Offset;
        bool Normalized;

        BufferElement(ShaderDataType type, const std::string& name, bool normalized = false)
            : Name(name), Type(type), Size(ShaderDataTypeSize(type)), Offset(0), Normalized(normalized) 
        {
        }

        uint32_t GetComponentCount() const
        {
            switch (Type)
            {
            case ShaderDataType::Float:   return 1;
            case ShaderDataType::Float2:  return 2;
            case ShaderDataType::Float3:  return 3;
            case ShaderDataType::Float4:  return 4;
            case ShaderDataType::Mat3:    return 3 * 3;
            case ShaderDataType::Mat4:    return 4 * 4;
            case ShaderDataType::Int:     return 1;
            case ShaderDataType::Int2:    return 2;
            case ShaderDataType::Int3:    return 3;
            case ShaderDataType::Int4:    return 4;
            case ShaderDataType::Bool:    return 1;
            default: return 0;
            }
        }

    private:
        static uint32_t ShaderDataTypeSize(ShaderDataType type)
        {
            switch (type) 
            {
            case ShaderDataType::Float:    return 4;
            case ShaderDataType::Float2:   return 4 * 2;
            case ShaderDataType::Float3:   return 4 * 3;
            case ShaderDataType::Float4:   return 4 * 4;
            case ShaderDataType::Mat3:     return 4 * 3 * 3;
            case ShaderDataType::Mat4:     return 4 * 4 * 4;
            case ShaderDataType::Int:      return 4;
            case ShaderDataType::Int2:     return 4 * 2;
            case ShaderDataType::Int3:     return 4 * 3;
            case ShaderDataType::Int4:     return 4 * 4;
            case ShaderDataType::Bool:     return 1;
            default: return 0;
            }
        }
    };

    /**
     * @brief Manages OpenGL shader program compilation, linking, and uniform setting
     *
     * The Shader class handles the complete lifecycle of GLSL shaders,
     * from source compilation to program linking and runtime uniform updates.
     * It provides type-safe methods for setting shader uniforms.
     */
    class Shader
    {
    public:
        Shader();
        ~Shader();

        bool LoadFromSource(const char* vertexSource, const char* fragmentSource);

        void Bind() const;

        void Unbind() const;

        // Uniform setting methods
        void SetFloat(const std::string& name, float value);
        void SetFloat2(const std::string& name, const glm::vec2& value);
        void SetFloat3(const std::string& name, const glm::vec3& value);
        void SetFloat4(const std::string& name, const glm::vec4& value);
        void SetMat3(const std::string& name, const glm::mat3& matrix);
        void SetMat4(const std::string& name, const glm::mat4& matrix);
        void SetInt(const std::string& name, int value);
        void SetBool(const std::string& name, bool value);
        
        uint32_t GetRendererID() const { return m_RendererID; }

    private:
        uint32_t CompileShader(uint32_t type, const char* source);

        int GetUniformLocation(const std::string& name);

        uint32_t m_RendererID;
        std::unordered_map<std::string, int> m_UniformLocationCache;
    };

}
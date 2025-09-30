#include "pspch.h"
#include "Renderer.h"
#include "Shader.h"
#include "Buffer.h"
#include <GLAD/glad.h>

#include <glm/fwd.hpp>

namespace PulseStudio {

    // Static member definitions
    std::shared_ptr<Shader> Renderer::s_QuadShader = nullptr;
    std::shared_ptr<VertexArray> Renderer::s_QuadVertexArray = nullptr;
    std::shared_ptr<VertexBuffer> Renderer::s_QuadVertexBuffer = nullptr;
    std::shared_ptr<IndexBuffer> Renderer::s_QuadIndexBuffer = nullptr;
    glm::vec4 Renderer::s_ClearColor = glm::vec4(0.1f, 0.1f, 0.1f, 1.0f);
    bool Renderer::s_Initialized = false;

    // Simple vertex and fragment shaders for 2D rendering
    const char* quadVertexShaderSource = R"(
        #version 330 core
        layout (location = 0) in vec2 aPosition;
        
        uniform vec2 uPosition;
        uniform vec2 uSize;
        
        void main() {
            vec2 screenPosition = aPosition * uSize + uPosition;
            // Convert to normalized device coordinates [-1, 1]
            vec2 ndc = (screenPosition / 800.0 - 0.5) * 2.0;
            gl_Position = vec4(ndc.x, -ndc.y, 0.0, 1.0);
        }
    )";

    const char* quadFragmentShaderSource = R"(
        #version 330 core
        out vec4 FragColor;
        uniform vec4 uColor;
        
        void main() {
            FragColor = uColor;
        }
    )";

    void Renderer::Init()
    {
        if (s_Initialized)
        {
            LOG_WARN("Renderer already initialized.");
            return;
        }
        
        LOG_INFO("Initializing Renderer.");
        
        // Enable blending for transparency
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        
        // Setup shaders and geometry
        SetupShaders();
        SetupQuadGeometry();
        
        s_Initialized = true;
        LOG_INFO("Renderer initialized successfully.");
    }

    void Renderer::Shutdown()
    {
        if (!s_Initialized) return;
        
        LOG_INFO("Shutting down Renderer.");
        
        // Release resources
        s_QuadShader = nullptr;
        s_QuadVertexArray = nullptr;
        s_QuadVertexBuffer = nullptr;
        s_QuadIndexBuffer = nullptr;
        
        s_Initialized = false;
        LOG_INFO("Renderer shutdown complete.");
    }

    void Renderer::SetupShaders()
    {
        // Create and compile the quad shader
        s_QuadShader = std::make_shared<Shader>();
        s_QuadShader->LoadFromSource(quadVertexShaderSource, quadFragmentShaderSource);
    }

    void Renderer::SetupQuadGeometry()
    {
        // Vertex data for a unit quad [0,1]x[0,1]
        float vertices[] =
        {
            0.0f, 0.0f,  // bottom-left
            1.0f, 0.0f,  // bottom-right
            1.0f, 1.0f,  // top-right
            0.0f, 1.0f   // top-left
        };
        
        // Index data for two triangles
        unsigned int indices[] =
        {
            0, 1, 2,  // first triangle
            2, 3, 0   // second triangle
        };
        
        // Create and configure vertex array
        s_QuadVertexArray = std::make_shared<VertexArray>();
        s_QuadVertexArray->Bind();
        
        // Create and fill vertex buffer
        s_QuadVertexBuffer = std::make_shared<VertexBuffer>(vertices, sizeof(vertices));
        s_QuadVertexBuffer->SetLayout({
            { ShaderDataType::Float2, "aPosition" }
        });
        s_QuadVertexArray->AddVertexBuffer(s_QuadVertexBuffer);
        
        // Create and fill index buffer
        s_QuadIndexBuffer = std::make_shared<IndexBuffer>(indices, 6);
        s_QuadVertexArray->SetIndexBuffer(s_QuadIndexBuffer);
        
        // Unbind to prevent accidental modification
        s_QuadVertexArray->Unbind();
    }

    void Renderer::SetClearColor(const glm::vec4& color)
    {
        s_ClearColor = color;
        glClearColor(color.r, color.g, color.b, color.a);
    }

    void Renderer::Clear()
    {
        glClear(GL_COLOR_BUFFER_BIT);
    }

    void Renderer::BeginScene()
    {
        // Placeholder for future scene management
    }

    void Renderer::EndScene()
    {
        // Placeholder for future scene management
    }

    void Renderer::DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color)
    {
        if (!s_Initialized)
        {
            PS_ERROR("Renderer not initialized. Call Renderer::Init() first.");
            return;
        }
        
        // Use the quad shader
        s_QuadShader->Bind();
        
        // Set shader uniforms
        s_QuadShader->SetFloat2("uPosition", position);
        s_QuadShader->SetFloat2("uSize", size);
        s_QuadShader->SetFloat4("uColor", color);
        
        // Bind vertex array and draw
        s_QuadVertexArray->Bind();
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
        s_QuadVertexArray->Unbind();
        
        // Unbind shader
        s_QuadShader->Unbind();
    }

    void Renderer::Flush()
    {
        // Placeholder for future batching system
    }

}
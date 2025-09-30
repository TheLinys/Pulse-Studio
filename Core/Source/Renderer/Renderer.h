#pragma once

#include "pspch.h"

#include <glm/glm.hpp>

namespace PulseStudio {

	// Forward declarations
    class Shader;
    class VertexArray;
    class VertexBuffer;
    class IndexBuffer;

    /**
     * @brief High-level rendering command system
     *
     * The Renderer class provides static methods for issuing rendering commands.
     * It manages the rendering state and provides simple interfaces for drawing
     * 2D shapes like quads, which are essential for UI rendering.
     */
    class Renderer
    {
    public:
        static void Init();

        static void Shutdown();

        static void SetClearColor(const glm::vec4& color);

        static void Clear();

        static void BeginScene();

        static void EndScene();

        static void DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color);

        static void Flush();

    private:
        // Private constructor to prevent instantiation (static class)
        Renderer() = default;

        // Internal initialization methods
        static void SetupShaders();
        static void SetupQuadGeometry();

        // Core rendering resources
        static std::shared_ptr<Shader> s_QuadShader;
        static std::shared_ptr<VertexArray> s_QuadVertexArray;
        static std::shared_ptr<VertexBuffer> s_QuadVertexBuffer;
        static std::shared_ptr<IndexBuffer> s_QuadIndexBuffer;

        // Rendering state
        static glm::vec4 s_ClearColor;
        static bool s_Initialized;
    };

}

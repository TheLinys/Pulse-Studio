#pragma once

#include "pspch.h"
#include "Shader.h"

namespace PulseStudio {

    /**
     * @brief Describes the layout of vertex buffer data
     *
     * BufferLayout defines how vertex attributes are arranged in a vertex buffer.
     * It specifies the type, size, and layout of each vertex attribute.
     */
    class BufferLayout
    {
    public:
        BufferLayout() = default;
        BufferLayout(const std::initializer_list<BufferElement>& elements) : m_Elements(elements)
        {
            CalculateOffsetsAndStride();
        }

        const std::vector<BufferElement>& GetElements() const { return m_Elements; }
        uint32_t GetStride() const { return m_Stride; }

        std::vector<BufferElement>::iterator begin() { return m_Elements.begin(); }
        std::vector<BufferElement>::iterator end() { return m_Elements.end(); }
        std::vector<BufferElement>::const_iterator begin() const { return m_Elements.begin(); }
        std::vector<BufferElement>::const_iterator end() const { return m_Elements.end(); }

    private:
        void CalculateOffsetsAndStride()
        {
            uint32_t offset = 0;
            m_Stride = 0;
            for (auto& element : m_Elements) {
                element.Offset = offset;
                offset += element.Size;
                m_Stride += element.Size;
            }
        }

        std::vector<BufferElement> m_Elements;
        uint32_t m_Stride = 0;
    };

    /**
     * @brief Wrapper for OpenGL vertex array objects
     *
     * VertexArray manages the vertex array object which stores the configuration
     * of vertex buffers and their layout. It simplifies vertex specification.
     */
    class VertexArray
    {
    public:
        VertexArray();
        ~VertexArray();

        void Bind() const;
        void Unbind() const;

        void AddVertexBuffer(const std::shared_ptr<class VertexBuffer>& vertexBuffer);
        void SetIndexBuffer(const std::shared_ptr<class IndexBuffer>& indexBuffer);

        const std::vector<std::shared_ptr<class VertexBuffer>>& GetVertexBuffers() const { return m_VertexBuffers; }
        const std::shared_ptr<class IndexBuffer>& GetIndexBuffer() const { return m_IndexBuffer; }

    private:
        uint32_t m_RendererID;
        std::vector<std::shared_ptr<class VertexBuffer>> m_VertexBuffers;
        std::shared_ptr<class IndexBuffer> m_IndexBuffer;
    };

    /**
     * @brief Wrapper for OpenGL vertex buffer objects
     *
     * VertexBuffer stores vertex data in GPU memory. It supports flexible
     * vertex layouts through the BufferLayout system.
     */
    class VertexBuffer
    {
    public:
        VertexBuffer(float* vertices, uint32_t size);
        ~VertexBuffer();

        void Bind() const;
        void Unbind() const;

        const class BufferLayout& GetLayout() const { return m_Layout; }
        void SetLayout(const BufferLayout& layout) { m_Layout = layout; }

    private:
        uint32_t m_RendererID;
        BufferLayout m_Layout;
    };

    /**
     * @brief Wrapper for OpenGL index buffer objects
     *
     * IndexBuffer stores indices for indexed rendering, reducing vertex
     * duplication and improving rendering performance.
     */
    class IndexBuffer
    {
    public:
        IndexBuffer(uint32_t* indices, uint32_t count);
        ~IndexBuffer();

        void Bind() const;
        void Unbind() const;

        uint32_t GetCount() const { return m_Count; }

    private:
        uint32_t m_RendererID;
        uint32_t m_Count;
    };

}
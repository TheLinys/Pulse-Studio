// Tool.h
#pragma once

#include "pspch.h"

#include "PulseStudio/Events/Event.h"
#include <glm/glm.hpp>

namespace PulseStudio {

    /**
     * @brief Represents the state of a tool in the editor
     *
     * Tools can be in different states that affect their appearance and behavior:
     * - Idle: Default state, waiting for interaction
     * - Hovered: Mouse is over the tool, shows visual feedback
     * - Dragging: Tool is being dragged by the user
     * - Active: Tool is currently selected/active
     */
    enum class ToolState
    {
        Idle,       // Default state, waiting for interaction
        Hovered,    // Mouse is over the tool
        Dragging,   // Tool is being dragged
        Active      // Tool is currently selected
    };

    /**
     * @brief Base class for all editor tools
     *
     * The Tool class provides the foundation for interactive tools in the editor.
     * Each tool can be dragged from the toolbar and executes specific functionality
     * when the drag operation completes. Tools handle their own rendering and
     * event processing within their bounded area.
     */
    class Tool
    {
    public:
        Tool(const std::string& name, const glm::vec4& color = glm::vec4(0.5f, 0.5f, 0.5f, 1.0f));
        virtual ~Tool() = default;

        virtual void OnAttach() {}

        virtual void OnDetach() {}

        virtual void OnUpdate(float deltaTime);

        virtual void OnRender();

        virtual void OnEvent(Event& event);

        virtual void OnDragStart(const glm::vec2& mousePos);

        virtual void OnDragUpdate(const glm::vec2& mousePos);

        virtual void OnDragEnd(const glm::vec2& mousePos);

        virtual void Execute() = 0;

        // ===== Getters =====

        const std::string& GetName() const { return m_Name; }
        ToolState GetState() const { return m_State; }
        const glm::vec2& GetPosition() const { return m_Position; }
        const glm::vec2& GetSize() const { return m_Size; }
        const glm::vec4& GetColor() const { return m_Color; }

        // ===== Setters =====

        void SetPosition(const glm::vec2& position) { m_Position = position; }
        void SetSize(const glm::vec2& size) { m_Size = size; }
        void SetColor(const glm::vec4& color) { m_Color = color; }
        void SetState(ToolState state) { m_State = state; }

        // ===== Utility Methods =====

        bool ContainsPoint(const glm::vec2& point) const;

        glm::vec2 GetCenter() const { return m_Position + m_Size * 0.5f; }

    protected:
        std::string m_Name;           // Display name of the tool
        ToolState m_State;            // Current state of the tool
        glm::vec2 m_Position;         // Position in screen coordinates
        glm::vec2 m_Size;             // Size of the tool visual
        glm::vec4 m_Color;            // Base color of the tool

        // Drag state tracking
        bool m_IsDragging = false;           // Whether tool is currently being dragged
        glm::vec2 m_DragStartPosition;       // Position where drag started
        glm::vec2 m_DragStartOffset;         // Offset from mouse to tool position
    };

}

// Tool.cpp
#include "pspch.h"
#include "../Renderer/Renderer.h"
#include "Tool.h"
#include <PulseStudio/Events/Event.h>
#include <PulseStudio/Log.h>
#include <string>

namespace PulseStudio {

    Tool::Tool(const std::string& name, const glm::vec4& color)
        : m_Name(name), m_Color(color), m_State(ToolState::Idle)
    {
        // Default tool size - can be customized by derived classes
        m_Size = glm::vec2(50.0f, 50.0f);
    }

    void Tool::OnUpdate(float deltaTime)
    {
        // Base implementation does nothing
        // Derived classes can override to add custom update logic
    }

    void Tool::OnRender() 
    {
        // Calculate visual properties based on current state
        glm::vec4 renderColor = m_Color;
        float borderThickness = 1.0f;

        // Modify appearance based on tool state
        switch (m_State) 
        {
        case ToolState::Hovered:
            // Brighten color when hovered
            renderColor.r *= 1.2f;
            renderColor.g *= 1.2f;
            renderColor.b *= 1.2f;
            borderThickness = 2.0f;
            break;

        case ToolState::Dragging:
            // Semi-transparent when dragging
            renderColor.a = 0.7f;
            borderThickness = 2.0f;
            break;

        case ToolState::Active:
            // Yellow tint for active tools
            renderColor = glm::vec4(1.0f, 1.0f, 0.3f, 1.0f);
            borderThickness = 3.0f;
            break;

        case ToolState::Idle:
        default:
            // Use base color for idle state
            break;
        }

        // Render tool background (requires Renderer::DrawQuad implementation)
        Renderer::DrawQuad(m_Position, m_Size, renderColor);

        // Render border (optional - can be implemented later)
        // Renderer::DrawQuadBorder(m_Position, m_Size, borderThickness, glm::vec4(1.0f));
    }

    void Tool::OnEvent(Event& event)
    {
        EventDispatcher dispatcher(event);

        // Handle mouse moved events for hover detection
        dispatcher.Dispatch<MouseMovedEvent>([this](MouseMovedEvent& e)
        {
            glm::vec2 mousePos(e.GetX(), e.GetY());

            // Update hover state
            if (ContainsPoint(mousePos))
            {
                if (m_State != ToolState::Dragging)
                {
                    m_State = ToolState::Hovered;
                }
            }
            else
            {
                if (m_State != ToolState::Dragging)
                {
                    m_State = ToolState::Idle;
                }
            }
            return false; // Event not fully handled
        });

        // Handle mouse button press for drag start
        dispatcher.Dispatch<MouseButtonPressedEvent>([this](MouseButtonPressedEvent& e)
        {
            if (e.GetMouseButton() == GLFW_MOUSE_BUTTON_LEFT)
            {
                glm::vec2 mousePos(e.GetX(), e.GetY());
                if (ContainsPoint(mousePos))
                {
                    OnDragStart(mousePos);
                    return true; // Event handled
                }
            }
            return false;
        });

        // Handle mouse button release for drag end
        dispatcher.Dispatch<MouseButtonReleasedEvent>([this](MouseButtonReleasedEvent& e)
        {
            if (e.GetMouseButton() == GLFW_MOUSE_BUTTON_LEFT && m_IsDragging)
            {
                OnDragEnd(glm::vec2(e.GetX(), e.GetY()));
                return true; // Event handled
            }
            return false;
        });
    }

    void Tool::OnDragStart(const glm::vec2& mousePos) 
    {
        m_IsDragging = true;
        m_State = ToolState::Dragging;
        m_DragStartPosition = m_Position;
        m_DragStartOffset = mousePos - m_Position;

        LOG_TRACE(std::format("Tool '{0}' drag started at ({1}, {2})",
            m_Name, mousePos.x, mousePos.y));
    }

    void Tool::OnDragUpdate(const glm::vec2& mousePos) 
    {
        if (m_IsDragging) 
        {
            // Update tool position to follow mouse with offset
            m_Position = mousePos - m_DragStartOffset;
        }
    }

    void Tool::OnDragEnd(const glm::vec2& mousePos)
    {
        if (m_IsDragging)
        {
            m_IsDragging = false;

            // Execute tool functionality when drag completes
            Execute();

            // Return to appropriate state
            if (ContainsPoint(mousePos))
            {
                m_State = ToolState::Hovered;
            }
            else
            {
                m_State = ToolState::Idle;
            }

            LOG_TRACE(std::format("Tool '{0}' drag ended at ({1}, {2})",
                m_Name, mousePos.x, mousePos.y));
        }
    }

    bool Tool::ContainsPoint(const glm::vec2& point) const 
    {
        return point.x >= m_Position.x &&
            point.x <= m_Position.x + m_Size.x &&
            point.y >= m_Position.y &&
            point.y <= m_Position.y + m_Size.y;
    }

}
// Toolbar.cpp
#include "pspch.h"
#include "Toolbar.h"
#include "../Renderer/Renderer.h"

namespace PulseStudio {

    Toolbar::Toolbar(const glm::vec2& position, bool vertical)
        : m_Position(position), m_Vertical(vertical), m_Spacing(5.0f)
    {
        // Initial size will be calculated when tools are added
        m_Size = glm::vec2(60.0f, 60.0f);
    }

    void Toolbar::OnAttach()
    {
        LOG_TRACE(std::format("Toolbar attached at position ({0}, {1})", m_Position.x, m_Position.y));

        // Notify all tools that they're being attached to this toolbar
        for (auto& tool : m_Tools)
        {
            tool->OnAttach();
        }

        // Ensure proper layout
        UpdateLayout();
    }

    void Toolbar::OnDetach()
    {
        LOG_TRACE("Toolbar detached.");

        // Notify all tools that they're being detached
        for (auto& tool : m_Tools)
        {
            tool->OnDetach();
        }

        // Clear drag state
        m_DraggedTool = nullptr;
        m_IsDragInProgress = false;
    }

    void Toolbar::OnUpdate(float deltaTime) 
    {
        // Update all tools in this toolbar
        for (auto& tool : m_Tools)
        {
            tool->OnUpdate(deltaTime);
        }
    }

    void Toolbar::OnRender()
    {
        // Render toolbar background
        Renderer::DrawQuad(m_Position, m_Size, m_BackgroundColor);

        // Render toolbar border (optional)
        // Renderer::DrawQuadBorder(m_Position, m_Size, m_BorderThickness, m_BorderColor);

        // Render all tools in this toolbar
        for (auto& tool : m_Tools) 
        {
            tool->OnRender();
        }
    }

    void Toolbar::OnEvent(Event& event)
    {
        // First, let individual tools process the event
        for (auto& tool : m_Tools)
        {
            // Skip the tool if it's currently being dragged (it will handle its own events)
            if (tool == m_DraggedTool) continue;

            tool->OnEvent(event);

            // If event was handled, we can stop propagation
            if (event.Handled) break;
        }

        // Then handle toolbar-specific events
        EventDispatcher dispatcher(event);

        // Track tool drag operations that start from this toolbar
        dispatcher.Dispatch<MouseButtonPressedEvent>([this](MouseButtonPressedEvent& e)
        {
            if (e.GetMouseButton() == GLFW_MOUSE_BUTTON_LEFT)
            {
                glm::vec2 mousePos(e.GetX(), e.GetY());
                m_DraggedTool = GetToolAtPosition(mousePos);
                if (m_DraggedTool)
                {
                    m_IsDragInProgress = true;
                    PS_TRACE("Tool '{0}' started drag from toolbar", m_DraggedTool->GetName());
                }
            }
            return false; // Let the tool handle the actual drag start
        });

        // Handle drag completion
        dispatcher.Dispatch<MouseButtonReleasedEvent>([this](MouseButtonReleasedEvent& e)
        {
            if (e.GetMouseButton() == GLFW_MOUSE_BUTTON_LEFT && m_IsDragInProgress)
            {
                glm::vec2 releasePos(e.GetX(), e.GetY());

                // Check if tool was released outside the toolbar
                if (!ContainsPoint(releasePos) && m_DraggedTool)
                {
                    LOG_INFO(std::format("Tool '{0}' released outside toolbar - ready for action",
                        m_DraggedTool->GetName()));
                    // This is where we would trigger window creation or other actions
                }

                m_DraggedTool = nullptr;
                m_IsDragInProgress = false;
            }
            return false;
        });
    }

    void Toolbar::AddTool(std::shared_ptr<Tool> tool)
    {
        if (!tool)
        {
            LOG_WARN("Attempted to add null tool to toolbar.");
            return;
        }

        m_Tools.push_back(tool);
        LOG_TRACE(std::format("Added tool '{0}' to toolbar.", tool->GetName()));

        // Update layout to accommodate new tool
        UpdateLayout();
    }

    bool Toolbar::RemoveTool(const std::string& toolName)
    {
        for (auto it = m_Tools.begin(); it != m_Tools.end(); ++it)
        {
            if ((*it)->GetName() == toolName)
            {
                // Notify tool it's being detached
                (*it)->OnDetach();

                // Remove from collection
                m_Tools.erase(it);

                LOG_TRACE(std::format("Removed tool '{0}' from toolbar.", toolName));
                UpdateLayout();
                return true;
            }
        }

        LOG_WARN(std::format("Tool '{0}' not found in toolbar.", toolName));
        return false;
    }

    std::shared_ptr<Tool> Toolbar::GetTool(const std::string& name) 
    {
        for (auto& tool : m_Tools)
        {
            if (tool->GetName() == name)
            {
                return tool;
            }
        }
        return nullptr;
    }

    void Toolbar::UpdateLayout()
    {
        if (m_Tools.empty())
        {
            m_Size = glm::vec2(60.0f, 60.0f); // Default empty size
            return;
        }

        float currentOffset = 0.0f;
        glm::vec2 maxToolSize(0.0f);

        // Position each tool based on orientation
        for (auto& tool : m_Tools)
        {
            if (m_Vertical)
            {
                // Vertical layout: tools stack from top to bottom
                tool->SetPosition(m_Position + glm::vec2(0.0f, currentOffset));
                currentOffset += tool->GetSize().y + m_Spacing;
                maxToolSize.x = glm::max(maxToolSize.x, tool->GetSize().x);
            }
            else
            {
                // Horizontal layout: tools arrange from left to right
                tool->SetPosition(m_Position + glm::vec2(currentOffset, 0.0f));
                currentOffset += tool->GetSize().x + m_Spacing;
                maxToolSize.y = glm::max(maxToolSize.y, tool->GetSize().y);
            }
        }

        // Calculate total toolbar size
        if (m_Vertical)
        {
            m_Size.x = maxToolSize.x;
            m_Size.y = currentOffset - m_Spacing; // Remove last spacing
        }
        else
        {
            m_Size.x = currentOffset - m_Spacing; // Remove last spacing
            m_Size.y = maxToolSize.y;
        }

        // Ensure minimum size
        m_Size.x = glm::max(m_Size.x, 60.0f);
        m_Size.y = glm::max(m_Size.y, 60.0f);

        LOG_TRACE(std::format("Toolbar layout updated: size ({0}, {1})", m_Size.x, m_Size.y));
    }

    void Toolbar::SetPosition(const glm::vec2& position)
    {
        m_Position = position;
        UpdateLayout(); // Reposition all tools
    }

    void Toolbar::SetOrientation(bool vertical)
    {
        if (m_Vertical != vertical)
        {
            m_Vertical = vertical;
            UpdateLayout(); // Recalculate layout with new orientation
        }
    }

    std::shared_ptr<Tool> Toolbar::GetToolAtPosition(const glm::vec2& position)
    {
        for (auto& tool : m_Tools)
        {
            if (tool->ContainsPoint(position))
            {
                return tool;
            }
        }
        return nullptr;
    }

    bool Toolbar::ContainsPoint(const glm::vec2& point) const
    {
        return point.x >= m_Position.x &&
            point.x <= m_Position.x + m_Size.x &&
            point.y >= m_Position.y &&
            point.y <= m_Position.y + m_Size.y;
    }

}

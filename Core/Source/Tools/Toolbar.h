// Toolbar.h
#pragma once

#include "pspch.h"

#include "PulseStudio/Layer.h"
#include "Tool.h"

namespace PulseStudio {

    /**
     * @brief A container that manages and displays a collection of tools
     *
     * The Toolbar class is responsible for:
     * - Arranging tools in a logical layout (vertical or horizontal)
     * - Managing tool visibility and interaction
     * - Providing visual feedback for the toolbar itself
     * - Handling tool drag operations that start from the toolbar
     *
     * Toolbars can be positioned anywhere in the editor and can be configured
     * to display tools in different orientations.
     */
    class Toolbar : public Layer
    {
    public:
        /**
         * @brief Construct a new Toolbar
         * @param position The screen position of the toolbar
         * @param vertical Whether tools should be arranged vertically (true) or horizontally (false)
         */
        Toolbar(const glm::vec2& position = { 10.0f, 10.0f }, bool vertical = true);
        virtual ~Toolbar() = default;

        // ===== Layer Interface Implementation =====

        void OnAttach() override;
        void OnDetach() override;
        void OnUpdate(float deltaTime) override;
        void OnRender();
        void OnEvent(Event& event) override;

        // ===== Tool Management Methods =====

        void AddTool(std::shared_ptr<Tool> tool);

        bool RemoveTool(const std::string& toolName);

        std::shared_ptr<Tool> GetTool(const std::string& name);

        const std::vector<std::shared_ptr<Tool>>& GetTools() const { return m_Tools; }

        // ===== Layout and Configuration Methods =====

        void UpdateLayout();

        void SetPosition(const glm::vec2& position);

        void SetOrientation(bool vertical);

        void SetSpacing(float spacing) { m_Spacing = spacing; UpdateLayout(); }

        // ===== Interaction Methods =====

        std::shared_ptr<Tool> GetToolAtPosition(const glm::vec2& position);

        bool ContainsPoint(const glm::vec2& point) const;

        // ===== Getters =====

        const glm::vec2& GetPosition() const { return m_Position; }
        const glm::vec2& GetSize() const { return m_Size; }
        bool IsVertical() const { return m_Vertical; }
        float GetSpacing() const { return m_Spacing; }
        size_t GetToolCount() const { return m_Tools.size(); }

    private:
        std::vector<std::shared_ptr<Tool>> m_Tools;  // Collection of tools in this toolbar
        glm::vec2 m_Position;                        // Position of the toolbar
        glm::vec2 m_Size;                            // Total size of the toolbar
        bool m_Vertical;                             // Layout orientation
        float m_Spacing;                             // Space between tools

        // Visual properties
        glm::vec4 m_BackgroundColor = glm::vec4(0.1f, 0.1f, 0.1f, 0.8f);
        glm::vec4 m_BorderColor = glm::vec4(0.3f, 0.3f, 0.3f, 1.0f);
        float m_BorderThickness = 1.0f;

        // Drag state tracking
        std::shared_ptr<Tool> m_DraggedTool = nullptr;  // Tool currently being dragged
        bool m_IsDragInProgress = false;                // Whether a drag operation is active
    };

}

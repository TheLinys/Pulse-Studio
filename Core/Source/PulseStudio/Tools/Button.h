#pragma once

#include <glm/glm.hpp>
#include <functional>
#include <string>

namespace PulseStudio {

    class Button
    {
    public:
        using ClickCallback = std::function<void()>;

        Button(const glm::vec2& position, const glm::vec2& size, const std::string& label = "");
        ~Button();

        void SetPosition(const glm::vec2& position);
        void SetSize(const glm::vec2& size);
        void SetLabel(const std::string& label);
        void SetColors(const glm::vec4& normal, const glm::vec4& hover, const glm::vec4& active);
        void SetClickCallback(ClickCallback callback);

        void Render();
        void Update(const glm::vec2& mousePos, bool mousePressed);

        bool Contains(const glm::vec2& point) const;
        const glm::vec2& GetPosition() const { return m_Position; }
        const glm::vec2& GetSize() const { return m_Size; }

    private:
        glm::vec2 m_Position;
        glm::vec2 m_Size;
        std::string m_Label;

        glm::vec4 m_NormalColor;
        glm::vec4 m_HoverColor;
        glm::vec4 m_ActiveColor;
        glm::vec4 m_CurrentColor;

        bool m_IsHovered = false;
        bool m_IsActive = false;

        ClickCallback m_ClickCallback;

        unsigned int m_TextTextureID = 0;
        glm::vec2 m_TextSize;
    };
}
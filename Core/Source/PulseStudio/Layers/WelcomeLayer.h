#pragma once
#include "../Layer.h"
#include <glm/glm.hpp>

namespace PulseStudio {

    class WelcomeLayer : public Layer
    {
    public:
        WelcomeLayer();

        void OnAttach() override;
        void OnDetach() override;
        void OnUpdate(float deltaTime) override;
        void OnEvent(Event& event) override;

    private:
        void RenderWelcomeScreen();
        void OnStartButtonClicked();
        void OnOpenProjectClicked();
        void OnExitClicked();

		// UI state
        glm::vec2 m_StartButtonPos = { 600, 400 };
        glm::vec2 m_StartButtonSize = { 200, 50 };
        glm::vec2 m_OpenProjectButtonPos = { 600, 300 };
        glm::vec2 m_OpenProjectButtonSize = { 200, 50 };

        bool m_StartButtonHovered = false;
        bool m_OpenProjectButtonHovered = false;
    };

}
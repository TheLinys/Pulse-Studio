#include "pspch.h"
#include "WelcomeLayer.h"
#include "../AppState.h"
#include "../Input.h"
#include "PulseStudio/Events/Event.h"
#include "PulseStudio/Events/ApplicationEvent.h"
#include "PulseStudio/Events/KeyEvent.h"
#include "PulseStudio/Events/MouseEvent.h"

namespace PulseStudio {

    WelcomeLayer::WelcomeLayer()
        : Layer("WelcomeLayer")
    {
    }

    void WelcomeLayer::OnAttach()
    {
        PS_INFO("WelcomeLayer attached");
    }

    void WelcomeLayer::OnDetach()
    {
        PS_INFO("WelcomeLayer detached");
    }

    void WelcomeLayer::OnUpdate(float deltaTime) 
    {
        RenderWelcomeScreen();
    }

    void WelcomeLayer::OnEvent(Event& event)
    {
        EventDispatcher dispatcher(event);

		// Dispatch mouse moved events
        dispatcher.Dispatch<MouseMovedEvent>([this](MouseMovedEvent& e)
        {
            auto [mouseX, mouseY] = Input::GetMousePosition();

			// Check if mouse is over the start button
            m_StartButtonHovered =
                mouseX >= m_StartButtonPos.x &&
                mouseX <= m_StartButtonPos.x + m_StartButtonSize.x &&
                mouseY >= m_StartButtonPos.y &&
                mouseY <= m_StartButtonPos.y + m_StartButtonSize.y;

			// Check if mouse is over the open project button
            m_OpenProjectButtonHovered =
                mouseX >= m_OpenProjectButtonPos.x &&
                mouseX <= m_OpenProjectButtonPos.x + m_OpenProjectButtonSize.x &&
                mouseY >= m_OpenProjectButtonPos.y &&
                mouseY <= m_OpenProjectButtonPos.y + m_OpenProjectButtonSize.y;

            return false;
        });

		// Dispatch mouse button pressed events
        dispatcher.Dispatch<MouseButtonPressedEvent>([this](MouseButtonPressedEvent& e)
        {
            if (e.GetMouseButton() == PS_MOUSE_BUTTON_LEFT)
            {
                auto [mouseX, mouseY] = Input::GetMousePosition();

				// Check if start button was clicked
                if (m_StartButtonHovered) {
                    OnStartButtonClicked();
                    return true;
                }

				// Check if open project button was clicked
                if (m_OpenProjectButtonHovered)
                {
                    OnOpenProjectClicked();
                    return true;
                }
            }
            return false;
        });
    }

    void WelcomeLayer::RenderWelcomeScreen()
    {
		PS_INFO("Rendering Welcome Screen");
    }

    void WelcomeLayer::OnStartButtonClicked() {
        PS_INFO("Start button clicked - switching to Dashboard");
        AppStateManager::getInstance().SetState(AppState::Dashboard);
    }

    void WelcomeLayer::OnOpenProjectClicked()
    {
        PS_INFO("Open project button clicked");
        // TODO: project open logic
        AppStateManager::getInstance().SetCurrentProject("New Project");
        AppStateManager::getInstance().SetState(AppState::Workspace);
    }

    void WelcomeLayer::OnExitClicked()
    {
		// TODO: Exit application logic
        PS_INFO("Exit button clicked");
    }

}
// WorkspaceLayer.cpp
#include "pspch.h"
#include "WorkspaceLayer.h"
#include "../AppState.h"
#include "../Input.h"
#include "PulseStudio/Events/Event.h"
#include "PulseStudio/Events/ApplicationEvent.h"
#include "PulseStudio/Events/KeyEvent.h"
#include "PulseStudio/Events/MouseEvent.h"

namespace PulseStudio {

    WorkspaceLayer::WorkspaceLayer()
        : Layer("WorkspaceLayer")
    {
    }

    void WorkspaceLayer::OnAttach()
    {
        m_CurrentProject = AppStateManager::getInstance().GetCurrentProject();
        PS_INFO(std::format("WorkspaceLayer attached for project: {0}", m_CurrentProject));
    }

    void WorkspaceLayer::OnDetach()
    {
        PS_INFO("WorkspaceLayer detached.");
    }

    void WorkspaceLayer::OnUpdate(float deltaTime)
    {
        RenderWorkspace();
    }

    void WorkspaceLayer::OnEvent(Event& event)
    {
        EventDispatcher dispatcher(event);

        // 处理工作区的事件
        dispatcher.Dispatch<KeyPressedEvent>([this](KeyPressedEvent& e)
        {
            if (e.GetKeyCode() == PS_KEY_ESCAPE)
            {
                PS_INFO("Escape pressed - returning to Dashboard");
                AppStateManager::getInstance().SetState(AppState::Dashboard);
                return true;
            }
            return false;
        });

        dispatcher.Dispatch<MouseButtonPressedEvent>([this](MouseButtonPressedEvent& e)
        {
            if (e.GetMouseButton() == PS_MOUSE_BUTTON_LEFT)
            {
                auto [mouseX, mouseY] = Input::GetMousePosition();

				//Check back button
                if (mouseX > 50 && mouseX < 150 && mouseY > 50 && mouseY < 100) {
                    PS_INFO("Back to dashboard clicked");
                    AppStateManager::getInstance().SetState(AppState::Dashboard);
                    return true;
                }
            }
            return false;
        });
    }

    void WorkspaceLayer::RenderWorkspace()
    {
        PS_TRACE(std::format("Workspace rendered for project: {0}", m_CurrentProject));
    }

}
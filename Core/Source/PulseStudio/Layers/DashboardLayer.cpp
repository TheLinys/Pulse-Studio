#include "pspch.h"
#include "DashboardLayer.h"
#include "../AppState.h"
#include "PulseStudio/Input.h"
#include "PulseStudio/Events/Event.h"
#include "PulseStudio/Events/ApplicationEvent.h"
#include "PulseStudio/Events/KeyEvent.h"
#include "PulseStudio/Events/MouseEvent.h"

namespace PulseStudio {

    DashboardLayer::DashboardLayer()
        : Layer("DashboardLayer")
    {
    }

    void DashboardLayer::OnAttach()
    {
        PS_INFO("DashboardLayer attached");
    }

    void DashboardLayer::OnDetach()
    {
        PS_INFO("DashboardLayer detached");
    }

    void DashboardLayer::OnUpdate(float deltaTime)
    {
        RenderDashboard();
    }

    void DashboardLayer::OnEvent(Event& event)
    {
        EventDispatcher dispatcher(event);

		// Dispatch mouse button pressed events
        dispatcher.Dispatch<MouseButtonPressedEvent>([this](MouseButtonPressedEvent& e)
        {
            if (e.GetMouseButton() == PS_MOUSE_BUTTON_LEFT) {
                auto [mouseX, mouseY] = Input::GetMousePosition();

				// Example: Check if a project is selected (placeholder logic)
                if (mouseX > 100 && mouseX < 400 && mouseY > 200 && mouseY < 300) {
                    OnProjectSelected("Example Project");
                    return true;
                }

				// Check create new project button
                if (mouseX > 100 && mouseX < 400 && mouseY > 350 && mouseY < 450) {
                    OnNewProjectClicked();
                    return true;
                }
            }
            return false;
        });
    }

    void DashboardLayer::RenderDashboard()
    {
        PS_TRACE("Dashboard rendered");
    }

    void DashboardLayer::OnProjectSelected(const std::string& projectPath) 
    {
        PS_INFO(std::format("Project selected: {0}", projectPath));
        AppStateManager::getInstance().SetCurrentProject(projectPath);
        AppStateManager::getInstance().SetState(AppState::Workspace);
    }

    void DashboardLayer::OnNewProjectClicked() {
        PS_INFO("New project button clicked");
		// TODO: Mew project creation logic
        AppStateManager::getInstance().SetCurrentProject("New Project");
        AppStateManager::getInstance().SetState(AppState::Workspace);
    }

}
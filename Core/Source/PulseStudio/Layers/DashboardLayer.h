#pragma once
#include "../Layer.h"

namespace PulseStudio {

    class DashboardLayer : public Layer
    {
    public:
        DashboardLayer();

        void OnAttach() override;
        void OnDetach() override;
        void OnUpdate(float deltaTime) override;
        void OnEvent(Event& event) override;

    private:
        void RenderDashboard();
        void OnProjectSelected(const std::string& projectPath);
        void OnNewProjectClicked();
        void OnBackClicked();
    };

}
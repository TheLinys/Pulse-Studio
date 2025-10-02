#pragma once
#include "../Layer.h"

namespace PulseStudio {

    class WorkspaceLayer : public Layer 
    {
    public:
        WorkspaceLayer();

        void OnAttach() override;
        void OnDetach() override;
        void OnUpdate(float deltaTime) override;
        void OnEvent(Event& event) override;

    private:
        void RenderWorkspace();
        std::string m_CurrentProject;
    };

}
#pragma once
#include "PulseStudio/Tools/Tool.h"

namespace PulseStudio {

    class WindowsTool : public Tool
    {
    public:
        WindowsTool(const ToolProps& props);
        virtual ~WindowsTool();

		// Tool interface implementations
        void OnAttach() override;
        void OnDetach() override;
        void OnUpdate() override;
        void OnUIRender() override;

        const std::string& GetName() const override;
        ToolType GetType() const override;

		bool IsOpen() const;
		void SetOpen(bool open);

        void OnEvent(Event& event) override;

    private:
        std::string m_Name;
        bool m_IsOpen;
        ToolState m_State;
        unsigned int m_Width, m_Height;
        ToolType m_Type;

		// Example internal state
        float m_ExampleFloatValue = 0.0f;
        int m_ExampleIntValue = 0;
        bool m_ExampleBoolValue = false;
    };
}
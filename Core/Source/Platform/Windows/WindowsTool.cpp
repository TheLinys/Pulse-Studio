#include "pspch.h"
#include "WindowsTool.h"

#include "PulseStudio/Log.h"
#include "PulseStudio/Events/ApplicationEvent.h"
#include "PulseStudio/Events/KeyEvent.h"
#include "PulseStudio/Events/MouseEvent.h"

namespace PulseStudio {

    WindowsTool::WindowsTool(const ToolProps& props)
        : m_Name(props.Title), m_IsOpen(props.IsActive), m_State(props.State), m_Width(props.Width), m_Height(props.Height)
    {
        LOG_INFO("WindowsTool created: \"" + m_Name + "\"");
    }

    WindowsTool::~WindowsTool()
    {
        LOG_INFO("WindowsTool destroyed: " + m_Name);
    }

    void WindowsTool::OnAttach()
    {
        LOG_INFO("Tool attached: " + m_Name);
    }

    void WindowsTool::OnDetach()
    {
        LOG_INFO("Tool detached: " + m_Name);
    }

    void WindowsTool::OnUpdate()
    {
        static float time = 0.0f;
        time += 0.016f;
        m_ExampleFloatValue = (sinf(time) + 1.0f) * 0.5f;
    }

    void WindowsTool::OnUIRender()
    {
        PS_TRACE("Rendering tool: " + m_Name);
    }

    const std::string& WindowsTool::GetName() const
    {
        return m_Name;
    }

    ToolType WindowsTool::GetType() const
    {
        return m_Type;
    }

    bool WindowsTool::IsOpen() const
    {
        return m_IsOpen;
    }

    void WindowsTool::SetOpen(bool open)
    {
        m_IsOpen = open;
        if (open)
        {
            LOG_INFO("Tool opened: " + m_Name);
        }
        else
        {
            LOG_INFO("Tool closed: " + m_Name);
        }
    }

    void WindowsTool::OnEvent(Event& event)
    {
        EventDispatcher dispatcher(event);

        if (!event.m_Handled)
        {
            PS_TRACE("Tool received event: " + event.ToString());
        }
    }
}
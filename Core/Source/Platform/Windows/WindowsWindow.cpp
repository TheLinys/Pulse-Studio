#include "pspch.h"
#include "WindowsWindow.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>

#include "PulseStudio/Log.h"

namespace PulseStudio {

    WindowsWindow::WindowsWindow(const WindowProps& props) 
    {
        // Initialized GLFW
        int success = glfwInit();
        PS_CORE_ASSERT(success, "Could not initialize GLFW!");

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        // Create GLFW window
        m_Window = glfwCreateWindow(props.Width, props.Height, props.Title.c_str(), nullptr, nullptr);

        glfwMakeContextCurrent(m_Window);
        int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		PS_CORE_ASSERT(status, "Could not initialize Glad!");
        glfwSetWindowUserPointer(m_Window, this);

        // initialize m_Data
        m_Data.Title = props.Title;
        m_Data.Width = props.Width;
        m_Data.Height = props.Height;
        m_Data.VSync = true;
    }

    void WindowsWindow::OnUpdate() 
    {
        glfwPollEvents();
        glfwSwapBuffers(m_Window);
    }

    WindowsWindow::~WindowsWindow()
    {
        glfwDestroyWindow(m_Window);
        glfwTerminate();
    }

    unsigned int WindowsWindow::GetWidth() const
    {
        return m_Data.Width;
    }

    unsigned int WindowsWindow::GetHeight() const
    {
        return m_Data.Height;
    }

    void WindowsWindow::SetEventCallback(const EventCallbackFn& callback)
    {
		// TODO: Set event callback
    }

    void WindowsWindow::SetVSync(bool enabled)
    {
        m_Data.VSync = enabled;
        glfwSwapInterval(enabled ? 1 : 0);
    }

    bool WindowsWindow::IsVSync() const
    {
        return m_Data.VSync;
    }
}
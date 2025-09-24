#include "pspch.h"

#include "Application.h"
#include "Events/ApplicationEvent.h"
#include "Log.h"
#include "Window.h"

#include <glad/glad.h>

namespace PulseStudio {

	Application::Application()
    {
        // Initialize the logger in the constructor
        Logger::getInstance().init("PulseStudioLog.log", LogLevel::Debug, LogLevel::Debug);
        LOG_INFO("Application constructor called.");
        WindowProps props("Pulse Studio", 1700, 1000);
        m_MainWindow = std::unique_ptr<Window>(Window::Create(props));
    }

    Application::~Application()
    {
        LOG_INFO("Application destructor called.");
		LOG_CORE_DEBUG("Shutting down Pulse Studio...");
        // Shutdown the logger when the application is destroyed
        Logger::getInstance().shutdown();
    }

    void Application::PushLayer(Layer* layer)
    {
        m_LayerStack.PushLayer(layer);
        layer->OnAttach();
	}

    void Application::PushOverlay(Layer* overlay)
    {
        m_LayerStack.PushOverlay(overlay);
		overlay->OnAttach();
	}

    void Application::OnEvent(Event& e)
    {
        EventDispatcher dispatcher(e);
        dispatcher.Dispatch<WindowCloseEvent>(std::bind(&Application::OnWindowClose, this, std::placeholders::_1));
        for (auto it = m_LayerStack.end(); it != m_LayerStack.begin(); )
        {
            (*--it)->OnEvent(e);
            if (e.m_Handled)
                break;
        }
	}

    void Application::Run()
    {
        LOG_TRACE("Pulse Studio initialized and running.");


        do {
            glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT);

            for (Layer* layer : m_LayerStack)
				layer->OnUpdate(0.0f); // TODO: Replace 0.0f with actual delta time
        } while (m_Running);
    }

    bool Application::OnWindowClose(WindowCloseEvent& e) {
        m_Running = false;
        return true;
    }

}

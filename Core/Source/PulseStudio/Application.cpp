#include "pspch.h"

#include "Application.h"
#include "Events/ApplicationEvent.h"
#include "Log.h"
#include "Window.h"

#include <glad/glad.h>

#include "Input.h"

#include "Layers/WelcomeLayer.h"
#include "Layers/DashboardLayer.h"
#include "Layers/WorkspaceLayer.h"

namespace PulseStudio {

#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)

	Application* Application::s_Instance = nullptr;

    bool createDirectoryIfNotExists(const std::string& path)
    {
        namespace fs = std::filesystem;

        try 
        {
            if (!fs::exists(path))
            {
                return fs::create_directories(path);
            }
            return true;
        }
        catch (const fs::filesystem_error& ex)
        {
            std::cerr << ex.what() << std::endl;
            return false;
        }
    }

	Application::Application()
    {
		PS_CORE_ASSERT(!s_Instance, "Application already exists!");
		s_Instance = this;

        // Initialize the logger in the constructor
        if (createDirectoryIfNotExists("Logs"))
        {
            Logger::getInstance().init("Logs/PulseStudioLog.log", LogLevel::Debug, LogLevel::Debug);
        }
        LOG_INFO("Application constructor called.");

        WindowProps props("Pulse Studio", 1700, 1000);
        m_MainWindow = std::unique_ptr<Window>(Window::Create(props));
		m_MainWindow->SetEventCallback(BIND_EVENT_FN(OnEvent));

		// Set state change callback
        AppStateManager::getInstance().SetStateChangeCallback([this](AppState newState)
        {
            this->SwitchToState(newState);
        });

		// initial state
        SwitchToState(AppState::Welcome);

        Input::Init();
        LOG_INFO("Input system initialized");
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
		LOG_CORE_INFO(e.ToString());
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

        do 
        {
            glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT);

            for (Layer* layer : m_LayerStack)
            {
                layer->OnUpdate(0.0f); // TODO: Replace 0.0f with actual delta time
            }

			m_MainWindow->OnUpdate();
        } while (m_Running);
    }

    bool Application::OnWindowClose(WindowCloseEvent& e) 
    {
		LOG_TRACE("Window close event received. Shutting down Application...");
        m_Running = false;
        return true;
    }

    void Application::SwitchToState(AppState newState)
    {
		// Clear existing layers
        m_LayerStack.Clear();

		// Add layers based on the new state
        switch (newState)
        {
        case AppState::Welcome:
            PushLayer(new WelcomeLayer());
            break;

        case AppState::Dashboard:
            PushLayer(new DashboardLayer());
            break;

        case AppState::Workspace:
            PushLayer(new WorkspaceLayer());
            break;
        }

        m_CurrentState = newState;
        PS_INFO(std::format("Switched to state: {0}", static_cast<int>(newState)));
    }

}

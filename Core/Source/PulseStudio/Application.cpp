#include "pspch.h"

#include "Application.h"
#include "Log.h"

namespace PulseStudio {

	Application::Application()
    {
        // Initialize the logger in the constructor
        Logger::getInstance().init("PulseStudioLog.log", LogLevel::Debug, LogLevel::Debug);
        LOG_INFO("Application constructor called");
    }

    Application::~Application()
    {
        LOG_INFO("Application destructor called");
        // Shutdown the logger when the application is destroyed
        Logger::getInstance().shutdown();
    }

    void Application::Run()
    {
        LOG_INFO("Pulse Studio initialized and running.");
        LOG_DEBUG("Hello from Pulse Studio!");

        while (true);
    }

}

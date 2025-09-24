#include "pspch.h"

#include "Window.h"
#include "Platform/Windows/WindowsWindow.h"

#include "Log.h"

namespace PulseStudio {

    Window* Window::Create(const WindowProps& props)
    {
#ifdef PS_PLATFORM_WINDOWS
        LOG_TRACE("Creating window...");
        return new WindowsWindow(props);
#else
        PS_CORE_ERROR("Pulse Studio IDE unsupported the platform!");
        return nullptr;
#endif
    }

}
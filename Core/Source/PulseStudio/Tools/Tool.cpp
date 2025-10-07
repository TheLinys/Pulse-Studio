#include "pspch.h"
#include "Tool.h"
#include "Platform/Windows/WindowsTool.h"
#include "../Log.h"

namespace PulseStudio {

    Tool* Tool::Create(const ToolProps& props)
    {
#ifdef PS_PLATFORM_WINDOWS
        LOG_TRACE("Creating Tool: " + props.Title);
        return new WindowsTool(props);
#else
        PS_CORE_ERROR("Pulse Studio IDE unsupported the platform!");
        return nullptr;
#endif
    }
}
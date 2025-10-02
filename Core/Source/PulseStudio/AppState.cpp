#include "pspch.h"
#include "AppState.h"

namespace PulseStudio {

	AppStateManager& AppStateManager::getInstance()
	{
		static AppStateManager instance;
		return instance;
	}

	void AppStateManager::SetState(AppState newState)
	{
		if (m_CurrentState != newState)
		{
			m_CurrentState = newState;
			if (m_StateChangeCallback)
			{
				m_StateChangeCallback(newState);
			}
		}
	}

	void AppStateManager::SetCurrentProject(const std::string& projectPath)
	{
		m_CurrentProject = projectPath;
	}

}

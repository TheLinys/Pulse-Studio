#pragma once
#include "pspch.h"

namespace PulseStudio {

	enum class AppState
	{
		Welcome,
		Dashboard,
		Workspace
	};

	class AppStateManager
	{
	public:
		static AppStateManager& getInstance();

		// State management
		void SetState(AppState newState);
		AppState GetCurrentState() const { return m_CurrentState; }

		// Project management
		void SetCurrentProject(const std::string& projectPath);
		const std::string& GetCurrentProject() const { return m_CurrentProject; }
		bool HasProject() const { return !m_CurrentProject.empty(); }

		// State change callback
		using StateChangeCallback = std::function<void(AppState)>;
		void SetStateChangeCallback(StateChangeCallback callback) { m_StateChangeCallback = callback; }
	private:
		AppStateManager() = default;

		AppState m_CurrentState = AppState::Welcome;
		std::string m_CurrentProject;
		StateChangeCallback m_StateChangeCallback;
	};

}

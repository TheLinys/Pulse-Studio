#pragma once

#include "Events/Event.h"
#include "Events/ApplicationEvent.h"
#include "Window.h"
#include "LayerStack.h"
#include "AppState.h"

namespace PulseStudio {

	class Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();

		void OnEvent(Event& e);

		void PushLayer(class Layer* layer);
		void PushOverlay(class Layer* overlay);

		// State Management
		void SwitchToState(AppState newState);

		inline static Application& Get() { return *s_Instance; }
		inline Window& GetWindow() { return *m_MainWindow; }
	private:
		bool OnWindowClose(WindowCloseEvent& e);

		std::unique_ptr<class Window> m_MainWindow;
		bool m_Running = true;
		LayerStack m_LayerStack;
		static Application* s_Instance;

		AppState m_CurrentState = AppState::Welcome;
	};

	// To be defined in CLIENT 
	PulseStudio::Application* CreateApplication();

}

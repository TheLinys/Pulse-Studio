#pragma once

#include "Events/Event.h"
#include "Events/ApplicationEvent.h"
#include "Window.h"
#include "LayerStack.h"

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
	private:
		bool OnWindowClose(WindowCloseEvent& e);

		std::unique_ptr<class Window> m_MainWindow;
		bool m_Running = true;
		LayerStack m_LayerStack;
		Window* m_Window;
	};

	PulseStudio::Application* CreateApplication();

}

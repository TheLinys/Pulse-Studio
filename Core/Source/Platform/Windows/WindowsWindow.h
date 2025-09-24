#pragma once
#include "PulseStudio/Window.h"

struct GLFWwindow;

namespace PulseStudio {

	class WindowsWindow : public Window
	{
	public:
		using EventCallbackFn = std::function<void(Event&)>;

		WindowsWindow(const WindowProps& props);
		virtual ~WindowsWindow();

		void OnUpdate() override;

		// Window attributes
		void SetEventCallback(const EventCallbackFn& callback) override;
		void SetVSync(bool enabled) override;
		bool IsVSync() const override;

		unsigned int GetWidth() const override;
		unsigned int GetHeight() const override;

		static Window* Create(const WindowProps& props = WindowProps());
	private:
		GLFWwindow* m_Window;

		struct WindowData
		{
			std::string Title;
			uint32_t Width, Height;
			bool VSync;
		};

		WindowData m_Data;
	};

}

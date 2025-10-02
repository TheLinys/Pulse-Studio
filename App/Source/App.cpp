#include <Pulse.h>
#include <iostream>

#include "PulseStudio/Events/KeyEvent.h"

class ExampleLayer : public PulseStudio::Layer
{
public:
	ExampleLayer()
		: Layer("Example")
	{
	}

	void OnUpdate(float deltaTime) override
	{
		if (PulseStudio::Input::IsKeyPressed(PS_KEY_TAB))
			PS_TRACE("Tab key is pressed (polling).");
	}

	void OnEvent(PulseStudio::Event& event) override
	{
		if (event.GetEventType() == PulseStudio::EventType::KeyPressed)
		{
			PulseStudio::KeyPressedEvent& e = (PulseStudio::KeyPressedEvent&)event;
			PS_TRACE(std::format("{0}", (char)e.GetKeyCode()));
		}
	}
};

class SandboxApp : public PulseStudio::Application
{
public:
	SandboxApp()
	{
	}
	~SandboxApp()
	{
	}
};

PulseStudio::Application* PulseStudio::CreateApplication()
{
	return new SandboxApp();
}

static void ChangeConsoelStatus(bool Isshow)
{
	HWND hwnd = GetConsoleWindow();
	if (Isshow)
	{
		ShowWindow(hwnd, SW_SHOW); // Show Console
		PS_INFO("Console is Showed.");
	}
	else
	{
		ShowWindow(hwnd, SW_HIDE); // Hide Console
		PS_INFO("Console is Hided.");
	}
}

int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	ChangeConsoelStatus(true);

	PulseStudio::Application* app = PulseStudio::CreateApplication();

	std::cout.setf(std::ios::unitbuf);

	app->Run();

	delete app;
	return 0;
}

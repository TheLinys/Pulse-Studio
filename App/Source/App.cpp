#include <Pulse.h>
#include <iostream>

class ImGuiLayer : public PulseStudio::Layer
{
public:
	ImGuiLayer()
		: Layer("ImGuiLayer")
	{
	}
	~ImGuiLayer()
	{
	}
	void OnAttach() override
	{
		PulseStudio::Layer::OnAttach();
	}
	void OnDetach() override
	{
	}
	void OnUpdate(float deltaTime) override
	{
		LOG_CORE_DEBUG("ExampleLayer::Update");
	}
	void OnEvent(PulseStudio::Event& event) override
	{
		LOG_TRACE(event.ToString());
	}
};

class SandboxApp : public PulseStudio::Application
{
public:
	SandboxApp()
	{
		/*PushLayer(new PulseStudio::ImGuiLayer());
		PushOverlay(new PulseStudio::ImGuiLayer());*/
	}
	~SandboxApp()
	{
	}
};

PulseStudio::Application* PulseStudio::CreateApplication()
{
	return new SandboxApp();
}

static void ChangeConsoelStatus(bool show)
{
	HWND hwnd = GetConsoleWindow();
	if (show)
	{
		ShowWindow(hwnd, SW_SHOW); // Show Console
	}
	else
	{
		ShowWindow(hwnd, SW_HIDE); // Hide Console
	}
}

int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	ChangeConsoelStatus(false);

	PulseStudio::Application* app = PulseStudio::CreateApplication();

	std::cout.setf(std::ios::unitbuf);

	app->Run();

	delete app;
	return 0;
}

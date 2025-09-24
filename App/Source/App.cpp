#include <Pulse.h>
#include <iostream>

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

enum ConsoleMode
{
	Hide,
	Show
};

void ChangeConsoleStatus(ConsoleMode mode)
{
	HWND hwnd = GetConsoleWindow();

	if (hwnd != NULL)
	{
		if (mode == Show)
		{
			ShowWindow(hwnd, SW_SHOW);
			LOG_INFO("Console window show.");
		}
		else
		{
			ShowWindow(hwnd, SW_HIDE);
			LOG_INFO("Console window hide.");
		}
	}
}

int main()
{
	ChangeConsoleStatus(Hide);

	PulseStudio::Application* app = PulseStudio::CreateApplication();

	std::cout.setf(std::ios::unitbuf);

	app->Run();

	delete app;
	return 0;
}

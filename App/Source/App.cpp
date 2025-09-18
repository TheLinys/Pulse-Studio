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

int main()
{
	PulseStudio::Application* app = PulseStudio::CreateApplication();

	std::cout.setf(std::ios::unitbuf);

	app->Run();

	delete app;

	return 0;
}

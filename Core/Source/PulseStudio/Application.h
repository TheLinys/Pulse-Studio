#pragma once
#include "Core.h"

namespace PulseStudio {

	class Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();
	};

	PulseStudio::Application* CreateApplication();

}

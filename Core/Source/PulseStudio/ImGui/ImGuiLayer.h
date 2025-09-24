#pragma once

#include "PulseStudio/Layer.h"

namespace PulseStudio {

	class ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer();

		void OnAttach();
		void OnDetach();
		void OnUpdate(float deltaTime);
		void OnEvent(Event& event);
	};

}
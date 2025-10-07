#pragma once

#include "../Core.h"
#include "PulseStudio/Events/Event.h"

namespace PulseStudio {

	enum class ToolType 
	{
		PropertyEditor,
		AssetBrowser,
		Console,
		Hierarchy
	};

	enum ToolState
	{
		Left = 0, Right, Top, Bottom, Center,
		LeftTop, LeftBottom, LeftCenter,
		RightTop, RightBottom, RightCenter,
		TopLeft, TopRight, TopCenter,
		BottomLeft, BottomRight, BottomCenter,
		Floating
	};

	struct ToolProps
	{
		std::string Title;
		unsigned int Width, Height;
		bool IsActive;
		ToolState State;
		ToolProps(const std::string& name = "Tool", bool isActive = true, ToolState state = Floating, unsigned int wigth = 300, unsigned int height = 400)
			: Title(name), IsActive(isActive), State(state), Width(wigth), Height(height)
		{
		}
	};

	class Tool
	{
	public:
		using EventCallbackFn = std::function<void(Event&)>;

		virtual ~Tool() {}

		virtual void OnAttach() = 0;
		virtual void OnDetach() = 0;
		virtual void OnUpdate() = 0;
		virtual void OnUIRender() = 0;

		virtual const std::string& GetName() const = 0;
		virtual ToolType GetType() const = 0;

		virtual bool IsOpen() const = 0;
		virtual void SetOpen(bool open) = 0;

		virtual void OnEvent(Event& event) = 0;

		static Tool* Create(const ToolProps& props = ToolProps());
	protected:
		bool m_IsOpen = true;
	};

}

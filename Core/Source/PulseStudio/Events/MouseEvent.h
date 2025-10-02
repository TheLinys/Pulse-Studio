#pragma once
#include "pspch.h"
#include "Event.h"
#include "PulseStudio/Input.h"

#include <glm/glm.hpp>

namespace PulseStudio {

	class MouseMovedEvent : public Event
	{
	public:
		MouseMovedEvent(float x, float y)
			: m_MouseX(x), m_MouseY(y) {}
		inline float GetX() const { return m_MouseX; }
		inline float GetY() const { return m_MouseY; }
		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseMovedEvent: " << m_MouseX << ", " << m_MouseY;
			return ss.str();
		}
		EVENT_CLASS_TYPE(MouseMoved)
		EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)
	private:
		float m_MouseX, m_MouseY;
	};

	class MouseScrolledEvent : public Event
	{
	public:
		MouseScrolledEvent(float xOffset, float yOffset)
			: m_XOffset(xOffset), m_YOffset(yOffset) {}
		inline float GetXOffset() const { return m_XOffset; }
		inline float GetYOffset() const { return m_YOffset; }
		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseScrolledEvent: " << GetXOffset() << ", " << GetYOffset();
			return ss.str();
		}
		EVENT_CLASS_TYPE(MouseScrolled)
		EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)
	private:
		float m_XOffset, m_YOffset;
	};

	class MouseButtonEvent : public Event
	{
	public:
		inline int GetMouseButton() const { return m_Button; }
		inline const glm::vec2& GetMousePosition() const { return m_MousePosition; }
		float GetMouseX() const { return m_MouseX; }
		float GetMouseY() const { return m_MouseY; }

		EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput | EventCategoryMouseButton)
	protected:
		MouseButtonEvent(int button, float mouseX, float mouseY)
			: m_Button(button), m_MousePosition(mouseX, mouseY) {}

		int m_Button;
		glm::vec2 m_MousePosition;
		float m_MouseX = 0.0f;
		float m_MouseY = 0.0f;
	};

	class MouseButtonPressedEvent : public MouseButtonEvent
	{
	public:
		MouseButtonPressedEvent(int button, float mouseX = 0.0f, float mouseY = 0.0f)
			: MouseButtonEvent(button, mouseX, mouseY) {}
		float GetMouseX() const { return m_MouseX; }
		float GetMouseY() const { return m_MouseY; }

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseButtonPressedEvent: " << m_Button << " (" << m_MousePosition.x << ", " << m_MousePosition.y << ")";
			return ss.str();
		}

		EVENT_CLASS_TYPE(MouseButtonPressed)
	private:
		float m_MouseX = 0.0f;
		float m_MouseY = 0.0f;
	};

	class MouseButtonReleasedEvent : public MouseButtonEvent
	{
	public:
		MouseButtonReleasedEvent(int button, float mouseX = 0.0f, float mouseY = 0.0f)
			: MouseButtonEvent(button, mouseX, mouseY) {}

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseButtonReleasedEvent: " << m_Button << " (" << m_MousePosition.x << ", " << m_MousePosition.y << ")";
			return ss.str();
		}

		EVENT_CLASS_TYPE(MouseButtonReleased)
	};

}
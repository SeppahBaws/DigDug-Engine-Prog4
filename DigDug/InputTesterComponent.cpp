#include "pch.h"
#include "InputTesterComponent.h"
#include "GameObject.h"
#include "InputManager.h"
#include "TextComponent.h"
#include <string>

#pragma warning(push)
#pragma warning (disable:4201)
#include <glm/vec2.hpp>
#pragma warning(pop)

namespace dae
{
	void InputTesterComponent::Update()
	{
		std::vector<std::shared_ptr<TextComponent>> textComponents = GetGameObject()->GetComponents<TextComponent>();

		UpdateButtons(textComponents[0]);
		UpdateTriggers(textComponents[1]);
		UpdateJoysticks(textComponents[2]);
	}

	void InputTesterComponent::UpdateButtons(std::shared_ptr<TextComponent> pText)
	{
		// ------------------------------------
		// ABXY buttons
		// ------------------------------------
		if (InputManager::GetInstance().IsDown(GamepadButton::ButtonA))
		{
			pText->SetText("Button A Pressed!");
		}
		else if (InputManager::GetInstance().IsDown(GamepadButton::ButtonB))
		{
			pText->SetText("Button B Pressed!");
		}
		else if (InputManager::GetInstance().IsDown(GamepadButton::ButtonX))
		{
			pText->SetText("Button X Pressed!");
		}
		else if (InputManager::GetInstance().IsDown(GamepadButton::ButtonY))
		{
			pText->SetText("Button Y Pressed!");
		}

		// ------------------------------------
		// DPad buttons
		// ------------------------------------
		else if (InputManager::GetInstance().IsDown(GamepadButton::DPadUp))
		{
			pText->SetText("DPad Up Pressed!");
		}
		else if (InputManager::GetInstance().IsDown(GamepadButton::DPadDown))
		{
			pText->SetText("DPad Down Pressed!");
		}
		else if (InputManager::GetInstance().IsDown(GamepadButton::DPadLeft))
		{
			pText->SetText("DPad Left Pressed!");
		}
		else if (InputManager::GetInstance().IsDown(GamepadButton::DPadRight))
		{
			pText->SetText("DPad Right Pressed!");
		}

		// ------------------------------------
		// Thumbstick buttons
		// ------------------------------------
		else if (InputManager::GetInstance().IsDown(GamepadButton::LeftThumb))
		{
			pText->SetText("Left Thumbstick Pressed!");
		}
		else if (InputManager::GetInstance().IsDown(GamepadButton::RightThumb))
		{
			pText->SetText("Right Thumbstick Pressed!");
		}

		// ------------------------------------
		// Shoulder buttons
		// ------------------------------------
		else if (InputManager::GetInstance().IsDown(GamepadButton::LeftShoulder))
		{
			pText->SetText("Left Shoulder Button Pressed!");
		}
		else if (InputManager::GetInstance().IsDown(GamepadButton::RightShoulder))
		{
			pText->SetText("Right Shoulder Button Pressed!");
		}

		// ------------------------------------
		// Special buttons
		// ------------------------------------
		else if (InputManager::GetInstance().IsDown(GamepadButton::Start))
		{
			pText->SetText("Start Button Pressed!");
		}
		else if (InputManager::GetInstance().IsDown(GamepadButton::Back))
		{
			pText->SetText("Back Button Pressed!");
		}


		// No buttons pressed
		else
		{
			pText->SetText("No buttons are pressed!");
		}
	}

	void InputTesterComponent::UpdateTriggers(std::shared_ptr<TextComponent> pText)
	{
		std::string text = "Left trigger: 0, Right trigger: 0";

		const float leftTrigger = InputManager::GetInstance().GetAxis(GamepadAxis::LeftTrigger);
		const float rightTrigger = InputManager::GetInstance().GetAxis(GamepadAxis::RightTrigger);

		std::stringstream ss;
		ss << "Left trigger: " << leftTrigger << ", Right trigger: " << rightTrigger;
		text = ss.str();
		pText->SetText(text);
	}

	void InputTesterComponent::UpdateJoysticks(std::shared_ptr<TextComponent> pText)
	{
		std::string text = "Left thumbstick: (0,0), Right thumbstick: (0,0)";

		const glm::vec2 left = InputManager::GetInstance().GetThumbstick(GamepadAxis::LeftThumbstick);
		const glm::vec2 right = InputManager::GetInstance().GetThumbstick(GamepadAxis::RightThumbstick);

		std::stringstream ss;
		ss << "Left thumbstick: (" << left.x << "," << left.y << "), ";
		ss << "Right thumbstick: (" << right.x << "," << right.y << ")";
		text = ss.str();
		pText->SetText(text);
	}
}

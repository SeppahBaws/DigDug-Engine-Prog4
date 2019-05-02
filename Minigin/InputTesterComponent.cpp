#include "MiniginPCH.h"
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
		if (InputManager::GetInstance().IsPressed(ControllerButton::ButtonA))
		{
			pText->SetText("Button A Pressed!");
		}
		else if (InputManager::GetInstance().IsPressed(ControllerButton::ButtonB))
		{
			pText->SetText("Button B Pressed!");
		}
		else if (InputManager::GetInstance().IsPressed(ControllerButton::ButtonX))
		{
			pText->SetText("Button X Pressed!");
		}
		else if (InputManager::GetInstance().IsPressed(ControllerButton::ButtonY))
		{
			pText->SetText("Button Y Pressed!");
		}

		// ------------------------------------
		// DPad buttons
		// ------------------------------------
		else if (InputManager::GetInstance().IsPressed(ControllerButton::DPadUp))
		{
			pText->SetText("DPad Up Pressed!");
		}
		else if (InputManager::GetInstance().IsPressed(ControllerButton::DPadDown))
		{
			pText->SetText("DPad Down Pressed!");
		}
		else if (InputManager::GetInstance().IsPressed(ControllerButton::DPadLeft))
		{
			pText->SetText("DPad Left Pressed!");
		}
		else if (InputManager::GetInstance().IsPressed(ControllerButton::DPadRight))
		{
			pText->SetText("DPad Right Pressed!");
		}

		// ------------------------------------
		// Thumbstick buttons
		// ------------------------------------
		else if (InputManager::GetInstance().IsPressed(ControllerButton::LeftThumb))
		{
			pText->SetText("Left Thumbstick Pressed!");
		}
		else if (InputManager::GetInstance().IsPressed(ControllerButton::RightThumb))
		{
			pText->SetText("Right Thumbstick Pressed!");
		}

		// ------------------------------------
		// Shoulder buttons
		// ------------------------------------
		else if (InputManager::GetInstance().IsPressed(ControllerButton::LeftShoulder))
		{
			pText->SetText("Left Shoulder Button Pressed!");
		}
		else if (InputManager::GetInstance().IsPressed(ControllerButton::RightShoulder))
		{
			pText->SetText("Right Shoulder Button Pressed!");
		}

		// ------------------------------------
		// Special buttons
		// ------------------------------------
		else if (InputManager::GetInstance().IsPressed(ControllerButton::Start))
		{
			pText->SetText("Start Button Pressed!");
		}
		else if (InputManager::GetInstance().IsPressed(ControllerButton::Back))
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

		const float leftTrigger = InputManager::GetInstance().GetAxis(ControllerAxis::LeftTrigger);
		const float rightTrigger = InputManager::GetInstance().GetAxis(ControllerAxis::RightTrigger);

		std::stringstream ss;
		ss << "Left trigger: " << leftTrigger << ", Right trigger: " << rightTrigger;
		text = ss.str();
		pText->SetText(text);
	}

	void InputTesterComponent::UpdateJoysticks(std::shared_ptr<TextComponent> pText)
	{
		std::string text = "Left thumbstick: (0,0), Right thumbstick: (0,0)";

		const glm::vec2 left = InputManager::GetInstance().GetThumbstick(ControllerAxis::LeftThumbstick);
		const glm::vec2 right = InputManager::GetInstance().GetThumbstick(ControllerAxis::RightThumbstick);

		std::stringstream ss;
		ss << "Left thumbstick: (" << left.x << "," << left.y << "), ";
		ss << "Right thumbstick: (" << right.x << "," << right.y << ")";
		text = ss.str();
		pText->SetText(text);
	}
}

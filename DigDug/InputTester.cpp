#include "pch.h"
#include "InputTester.h"
#include "InputManager.h"
#include "TextComponent.h"
#include "ResourceManager.h"

namespace dae
{
	InputTester::InputTester()
	{
		std::shared_ptr<Font> pFont = ResourceManager::GetInstance().LoadFont("Lingua.otf", 25);
		AddComponent(std::make_shared<TextComponent>("No buttons pressed", pFont));
	}

	void InputTester::Update()
	{
		std::shared_ptr<TextComponent> pText = GetComponent<TextComponent>();

		// ------------------------------------
		// ABXY buttons
		// ------------------------------------
		if (InputManager::GetInstance().IsPressed(ControllerButton::ButtonA))
		{
			// pText->SetText("Button A Pressed!");
		}
		else if (InputManager::GetInstance().IsPressed(ControllerButton::ButtonB))
		{
			// pText->SetText("Button B Pressed!");
		}
		else if (InputManager::GetInstance().IsPressed(ControllerButton::ButtonX))
		{
			// pText->SetText("Button X Pressed!");
		}
		else if (InputManager::GetInstance().IsPressed(ControllerButton::ButtonY))
		{
			// pText->SetText("Button Y Pressed!");
		}

		// ------------------------------------
		// DPad buttons
		// ------------------------------------
		else if (InputManager::GetInstance().IsPressed(ControllerButton::DPadUp))
		{
			// pText->SetText("DPad Up Pressed!");
		}
		else if (InputManager::GetInstance().IsPressed(ControllerButton::DPadDown))
		{
			// pText->SetText("DPad Down Pressed!");
		}
		else if (InputManager::GetInstance().IsPressed(ControllerButton::DPadLeft))
		{
			// pText->SetText("DPad Left Pressed!");
		}
		else if (InputManager::GetInstance().IsPressed(ControllerButton::DPadRight))
		{
			// pText->SetText("DPad Right Pressed!");
		}

		// ------------------------------------
		// Thumbstick buttons
		// ------------------------------------
		else if (InputManager::GetInstance().IsPressed(ControllerButton::LeftThumb))
		{
			// pText->SetText("Left Thumbstick Pressed!");
		}
		else if (InputManager::GetInstance().IsPressed(ControllerButton::RightThumb))
		{
			// pText->SetText("Right Thumbstick Pressed!");
		}

		// ------------------------------------
		// Shoulder buttons
		// ------------------------------------
		else if (InputManager::GetInstance().IsPressed(ControllerButton::LeftShoulder))
		{
			// pText->SetText("Left Shoulder Button Pressed!");
		}
		else if (InputManager::GetInstance().IsPressed(ControllerButton::RightShoulder))
		{
			// pText->SetText("Right Shoulder Button Pressed!");
		}

		// ------------------------------------
		// Special buttons
		// ------------------------------------
		else if (InputManager::GetInstance().IsPressed(ControllerButton::Start))
		{
			// pText->SetText("Start Button Pressed!");
		}
		else if (InputManager::GetInstance().IsPressed(ControllerButton::Back))
		{
			// pText->SetText("Back Button Pressed!");
		}
	}
}

#include "MiniginPCH.h"
#include "InputTesterComponent.h"
#include "GameObject.h"
#include "InputManager.h"

namespace dae
{
	void InputTesterComponent::Update()
	{
		std::shared_ptr<TextComponent> pTextComp = GetGameObject()->GetComponent<TextComponent>();

		// ------------------------------------
		// ABXY buttons
		// ------------------------------------
		if (InputManager::GetInstance().IsPressed(ControllerButton::ButtonA))
		{
			pTextComp->SetText("Button A Pressed!");
		}
		else if (InputManager::GetInstance().IsPressed(ControllerButton::ButtonB))
		{
			pTextComp->SetText("Button B Pressed!");
		}
		else if (InputManager::GetInstance().IsPressed(ControllerButton::ButtonX))
		{
			pTextComp->SetText("Button X Pressed!");
		}
		else if (InputManager::GetInstance().IsPressed(ControllerButton::ButtonY))
		{
			pTextComp->SetText("Button Y Pressed!");
		}

		// ------------------------------------
		// DPad buttons
		// ------------------------------------
		else if (InputManager::GetInstance().IsPressed(ControllerButton::DPadUp))
		{
			pTextComp->SetText("DPad Up Pressed!");
		}
		else if (InputManager::GetInstance().IsPressed(ControllerButton::DPadDown))
		{
			pTextComp->SetText("DPad Down Pressed!");
		}
		else if (InputManager::GetInstance().IsPressed(ControllerButton::DPadLeft))
		{
			pTextComp->SetText("DPad Left Pressed!");
		}
		else if (InputManager::GetInstance().IsPressed(ControllerButton::DPadRight))
		{
			pTextComp->SetText("DPad Right Pressed!");
		}

		// ------------------------------------
		// Thumbstick buttons
		// ------------------------------------
		else if (InputManager::GetInstance().IsPressed(ControllerButton::LeftThumb))
		{
			pTextComp->SetText("Left Thumbstick Pressed!");
		}
		else if (InputManager::GetInstance().IsPressed(ControllerButton::RightThumb))
		{
			pTextComp->SetText("Right Thumbstick Pressed!");
		}

		// ------------------------------------
		// Shoulder buttons
		// ------------------------------------
		else if (InputManager::GetInstance().IsPressed(ControllerButton::LeftShoulder))
		{
			pTextComp->SetText("Left Shoulder Button Pressed!");
		}
		else if (InputManager::GetInstance().IsPressed(ControllerButton::RightShoulder))
		{
			pTextComp->SetText("Right Shoulder Button Pressed!");
		}

		// ------------------------------------
		// Special buttons
		// ------------------------------------
		else if (InputManager::GetInstance().IsPressed(ControllerButton::Start))
		{
			pTextComp->SetText("Start Button Pressed!");
		}
		else if (InputManager::GetInstance().IsPressed(ControllerButton::Back))
		{
			pTextComp->SetText("Back Button Pressed!");
		}


		// No buttons pressed
		else
		{
			pTextComp->SetText("No buttons are pressed!");
		}
	}
}

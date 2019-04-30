#include "MiniginPCH.h"
#include "InputTester.h"
#include "InputManager.h"
#include "Log.h"

namespace dae
{
	void InputTester::Update()
	{
		if (InputManager::GetInstance().IsPressed(ControllerButton::ButtonA))
		{
			std::cout << "Button A Pressed!" << std::endl;
		}
		else if (InputManager::GetInstance().IsPressed(ControllerButton::ButtonB))
		{
			std::cout << "Button B Pressed!" << std::endl;
		}
		else if (InputManager::GetInstance().IsPressed(ControllerButton::ButtonX))
		{
			std::cout << "Button X Pressed!" << std::endl;
		}
		else if (InputManager::GetInstance().IsPressed(ControllerButton::ButtonY))
		{
			std::cout << "Button Y Pressed!" << std::endl;
		}

	}
}

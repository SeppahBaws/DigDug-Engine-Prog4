#include "MiniginPCH.h"
#include "InputManager.h"
#include <SDL.h>


bool dae::InputManager::ProcessInput()
{
	ZeroMemory(&m_CurrentState, sizeof(XINPUT_STATE));
	XInputGetState(0, &m_CurrentState);

	SDL_Event e;
	while (SDL_PollEvent(&e)) {
		if (e.type == SDL_QUIT) {
			return false;
		}
		if (e.type == SDL_KEYDOWN) {
			
		}
		if (e.type == SDL_MOUSEBUTTONDOWN) {
			
		}
	}

	return true;
}

bool dae::InputManager::IsPressed(ControllerButton button) const
{
	switch (button)
	{
	case ControllerButton::ButtonA:
		return m_CurrentState.Gamepad.wButtons & XINPUT_GAMEPAD_A;
	case ControllerButton::ButtonB:
		return m_CurrentState.Gamepad.wButtons & XINPUT_GAMEPAD_B;
	case ControllerButton::ButtonX:
		return m_CurrentState.Gamepad.wButtons & XINPUT_GAMEPAD_X;
	case ControllerButton::ButtonY:
		return m_CurrentState.Gamepad.wButtons & XINPUT_GAMEPAD_Y;
	case ControllerButton::DPadUp:
		return m_CurrentState.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_UP;
	case ControllerButton::DPadDown:
		return m_CurrentState.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_DOWN;
	case ControllerButton::DPadLeft:
		return m_CurrentState.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_LEFT;
	case ControllerButton::DPadRight:
		return m_CurrentState.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_RIGHT;
	case ControllerButton::Start:
		return m_CurrentState.Gamepad.wButtons & XINPUT_GAMEPAD_START;
	case ControllerButton::Back:
		return m_CurrentState.Gamepad.wButtons & XINPUT_GAMEPAD_BACK;
	case ControllerButton::LeftThumb:
		return m_CurrentState.Gamepad.wButtons & XINPUT_GAMEPAD_LEFT_THUMB;
	case ControllerButton::RightThumb:
		return m_CurrentState.Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_THUMB;
	case ControllerButton::LeftShoulder:
		return m_CurrentState.Gamepad.wButtons & XINPUT_GAMEPAD_LEFT_SHOULDER;
	case ControllerButton::RightShoulder:
		return m_CurrentState.Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_SHOULDER;
	default: return false;
	}
}


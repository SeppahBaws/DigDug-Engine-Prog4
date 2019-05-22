#include "MiniginPCH.h"
#include "InputManager.h"
#include "Command.h"
#include <SDL.h>

#pragma warning(push)
#pragma warning (disable:4201)
#include <glm/glm.hpp>
#pragma warning(pop)

namespace dae
{
	bool InputManager::ProcessInput()
	{
		// Set the State
		m_PreviousState = m_CurrentState;
		ZeroMemory(&m_CurrentState, sizeof(XINPUT_STATE));
		XInputGetState(0, &m_CurrentState);

		// Handle commands
		for (unsigned int i = 0; i < m_pInputCommands.size(); i++)
		{
			switch (m_pInputCommands[i]->GetStatus())
			{
			case ControllerButtonState::Pressed:
				if (IsPressed(m_pInputCommands[i]->GetButton()))
					m_pInputCommands[i]->Execute();
				break;

			case ControllerButtonState::Released:
				if (IsReleased(m_pInputCommands[i]->GetButton()))
					m_pInputCommands[i]->Execute();
				break;

			case ControllerButtonState::Down:
				if (IsDown(m_pInputCommands[i]->GetButton()))
					m_pInputCommands[i]->Execute();
				break;
			}
		}

		// Handle Events
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

	void InputManager::RegisterCommand(std::unique_ptr<Command>&& command)
	{
		m_pInputCommands.push_back(std::move(command));
	}

	bool InputManager::IsDown(ControllerButton button) const
	{
		return m_CurrentState.Gamepad.wButtons & (WORD)button;
	}

	bool InputManager::IsPressed(ControllerButton button) const
	{
		return m_CurrentState.Gamepad.wButtons & (WORD)button && 
			!(m_PreviousState.Gamepad.wButtons & (WORD)button);
	}

	bool InputManager::IsReleased(ControllerButton button) const
	{
		return !(m_CurrentState.Gamepad.wButtons & (WORD)button) &&
			m_PreviousState.Gamepad.wButtons & (WORD)button;
	}

	float InputManager::GetAxis(ControllerAxis axis) const
	{
		switch (axis)
		{
			// Triggers
		case ControllerAxis::LeftTrigger:
			return NormalizeTriggerValue(m_CurrentState.Gamepad.bLeftTrigger, 255.0f, XINPUT_GAMEPAD_TRIGGER_THRESHOLD);
		case ControllerAxis::RightTrigger:
			return NormalizeTriggerValue(m_CurrentState.Gamepad.bRightTrigger, 255.0f, XINPUT_GAMEPAD_TRIGGER_THRESHOLD);
		default:
			return 0.0f;
		}
	}

	float InputManager::GetAxisRaw(ControllerAxis axis) const
	{
		switch (axis)
		{
			// Triggers
		case ControllerAxis::LeftTrigger:
			return m_CurrentState.Gamepad.bLeftTrigger;
		case ControllerAxis::RightTrigger:
			return m_CurrentState.Gamepad.bRightTrigger;
		default:
			return 0.0f;
		}
	}

	glm::vec2 InputManager::GetThumbstick(ControllerAxis axis) const
	{
		switch (axis)
		{
		case ControllerAxis::LeftThumbstick:
		{
			glm::vec2 axisValue{ m_CurrentState.Gamepad.sThumbLX, m_CurrentState.Gamepad.sThumbLY };
			axisValue.y *= -1;
			return NormalizeJoystickValue(axisValue, 32767, XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE);
		}
		case ControllerAxis::RightThumbstick:
		{
			glm::vec2 axisValue{ m_CurrentState.Gamepad.sThumbRX, m_CurrentState.Gamepad.sThumbRY };
			axisValue.y *= -1;
			return NormalizeJoystickValue(axisValue, 32767, XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE);
		}
		default:
			return glm::vec2{ 0 };
		}
	}

	float InputManager::NormalizeTriggerValue(float value, float max, float deadzone) const
	{
		// If value is in the deadzone, return 0;
		if (abs(value) < deadzone)
			return 0;

		// Return normalized value with deadzone in mind
		// see https://bell0bytes.eu/xinput-and-gamepads/#analoginput for more information
		return (value - deadzone) / (max - deadzone);
	}

	glm::vec2 InputManager::NormalizeJoystickValue(glm::vec2 value, float max, float deadzone) const
	{
		// If value is in deadzone, return 0
		if (glm::length(value) < deadzone)
			return glm::vec2{ 0 };

		// Return normalized value with deadzone in mind
		float percentage = (glm::length(value) - deadzone) / (max - deadzone);
		return glm::normalize(value) * percentage;
	}
}

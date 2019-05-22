#pragma once
#include <XInput.h>
#include "Command.h"
#include "Singleton.h"

#pragma warning(push)
#pragma warning (disable:4201)
#include <glm/vec2.hpp>
#pragma warning(pop)

namespace dae
{
	class InputManager final : public Singleton<InputManager>
	{
	public:
		bool ProcessInput();

		void RegisterCommand(std::unique_ptr<Command>&& command);

		bool IsDown(ControllerButton button) const;  // Checks if a button is held down
		bool IsPressed(ControllerButton button) const; // Checks if a button just got pressed this frame
		bool IsReleased(ControllerButton button) const; // Checks if a button just got released this frame
		float GetAxis(ControllerAxis axis) const;
		float GetAxisRaw(ControllerAxis axis) const;
		glm::vec2 GetThumbstick(ControllerAxis axis) const;

	private:
		float NormalizeTriggerValue(float value, float max, float deadzone) const;
		glm::vec2 NormalizeJoystickValue(glm::vec2 value, float max, float deadzone) const;

	private:
		XINPUT_STATE m_PreviousState{};
		XINPUT_STATE m_CurrentState{};
		std::vector<std::unique_ptr<Command>> m_pInputCommands;
	};

}

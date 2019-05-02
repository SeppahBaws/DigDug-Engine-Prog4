#pragma once
#include <XInput.h>
#include "Singleton.h"

#pragma warning(push)
#pragma warning (disable:4201)
#include <glm/vec2.hpp>
#pragma warning(pop)

namespace dae
{
	enum class ControllerButton
	{
		ButtonA,
		ButtonB,
		ButtonX,
		ButtonY,
		DPadUp,
		DPadDown,
		DPadLeft,
		DPadRight,
		Start,
		Back,
		LeftThumb,
		RightThumb,
		LeftShoulder,
		RightShoulder
	};

	enum class ControllerAxis
	{
		LeftTrigger,
		RightTrigger,
		LeftThumbstick,
		RightThumbstick
	};

	class InputManager final : public Singleton<InputManager>
	{
	public:
		bool ProcessInput();
		bool IsPressed(ControllerButton button) const;
		float GetAxis(ControllerAxis axis) const;
		float GetAxisRaw(ControllerAxis axis) const;
		glm::vec2 GetThumbstick(ControllerAxis axis) const;

	private:
		float NormalizeTriggerValue(float value, float max, float deadzone) const;
		glm::vec2 NormalizeJoystickValue(glm::vec2 value, float max, float deadzone) const;

	private:
		XINPUT_STATE m_CurrentState{};
	};

}

#pragma once
#include <XInput.h>
#include "Singleton.h"

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
		LeftThumbstickX,
		LeftThumbstickY,
		RightThumbstickX,
		RightThumbstickY
	};

	class InputManager final : public Singleton<InputManager>
	{
	public:
		bool ProcessInput();
		bool IsPressed(ControllerButton button) const;
	private:
		XINPUT_STATE m_CurrentState{};
	};

}

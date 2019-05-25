#pragma once

namespace dae
{
	enum class GamepadButton
	{
		ButtonA			= XINPUT_GAMEPAD_A,
		ButtonB			= XINPUT_GAMEPAD_B,
		ButtonX			= XINPUT_GAMEPAD_X,
		ButtonY			= XINPUT_GAMEPAD_Y,
		DPadUp			= XINPUT_GAMEPAD_DPAD_UP,
		DPadDown		= XINPUT_GAMEPAD_DPAD_DOWN,
		DPadLeft		= XINPUT_GAMEPAD_DPAD_LEFT,
		DPadRight		= XINPUT_GAMEPAD_DPAD_RIGHT,
		Start			= XINPUT_GAMEPAD_START,
		Back			= XINPUT_GAMEPAD_BACK,
		LeftThumb		= XINPUT_GAMEPAD_LEFT_THUMB,
		RightThumb		= XINPUT_GAMEPAD_RIGHT_THUMB,
		LeftShoulder	= XINPUT_GAMEPAD_LEFT_SHOULDER,
		RightShoulder	= XINPUT_GAMEPAD_RIGHT_SHOULDER
	};

	enum class GamepadButtonState
	{
		Pressed,
		Released,
		Down
	};

	enum class GamepadAxis
	{
		LeftTrigger,
		RightTrigger,
		LeftThumbstick,
		RightThumbstick
	};

	class Command
	{
	public:
		Command(GamepadButton button, GamepadButtonState status)
			: m_Button(button)
			, m_Status(status)
		{}
		virtual ~Command() = default;
		virtual void Execute() = 0;

		GamepadButton GetButton() const { return m_Button; }
		GamepadButtonState GetStatus() const { return m_Status; }

	private:
		GamepadButton m_Button;
		GamepadButtonState m_Status;
	};
}
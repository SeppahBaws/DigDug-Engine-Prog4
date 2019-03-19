#pragma once
#include "Singleton.h"
#include <chrono>

namespace dae
{
	class Time final : public Singleton<Time>
	{
	public:
		static std::chrono::high_resolution_clock::time_point GetTime();

		static float GetDeltaTime();
		static void SetDeltaTime(float deltaTime);

	private:
		static float mDeltaTime;
		static std::chrono::high_resolution_clock::time_point mStartTime;
	};
}

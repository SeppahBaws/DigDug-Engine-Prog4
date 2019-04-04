﻿#include "MiniginPCH.h"
#include "Time.h"

namespace dae
{
	// Static member initialization
	float Time::mDeltaTime = 0.0f;
	std::chrono::high_resolution_clock::time_point Time::mStartTime;

	std::chrono::high_resolution_clock::time_point Time::GetTime()
	{
		return std::chrono::high_resolution_clock::now();
	}

	float Time::GetDeltaTime()
	{
		return mDeltaTime;
	}

	void Time::SetDeltaTime(float deltaTime)
	{
		mDeltaTime = deltaTime;
	}

	void Time::Update(std::chrono::high_resolution_clock::time_point lastTime)
	{
		const auto currentTime = std::chrono::high_resolution_clock::now();
		mDeltaTime = std::chrono::duration<float>(currentTime - lastTime).count();
	}
}

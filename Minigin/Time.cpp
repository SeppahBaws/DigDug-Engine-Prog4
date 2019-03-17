#include "MiniginPCH.h"
#include "Time.h"

namespace dae
{
	// Static member initialization
	float Time::m_DeltaTime = 0.0f;
	std::chrono::high_resolution_clock::time_point Time::m_StartTime;

	std::chrono::high_resolution_clock::time_point Time::GetTime()
	{
		return std::chrono::high_resolution_clock::now();
	}

	float Time::GetDeltaTime()
	{
		return m_DeltaTime;
	}

	void Time::SetDeltaTime(float deltaTime)
	{
		m_DeltaTime = deltaTime;
	}
}

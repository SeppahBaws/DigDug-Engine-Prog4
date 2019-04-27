#include "MiniginPCH.h"
#include <SDL.h>

#include "SceneSwitcherComponent.h"
#include "SceneManager.h"
#include "Scene.h"
#include "Time.h"

namespace dae
{
	void SceneSwitcherComponent::Update()
	{
		mAccumulatedTime += Time::GetDeltaTime();


		if (mAccumulatedTime > 2.0f)
		{
			mAccumulatedTime = 0.0f;

			if (SceneManager::GetInstance().GetActiveScene().GetName() == "Demo")
			{
				SceneManager::GetInstance().SetActiveScene("Demo2");
			}
			else
			{
				SceneManager::GetInstance().SetActiveScene("Demo");
			}
		}
	}
}

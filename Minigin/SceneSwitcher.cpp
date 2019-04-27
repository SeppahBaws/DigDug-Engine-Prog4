#include "MiniginPCH.h"
#include "SceneSwitcher.h"

#include "Time.h"
#include "SceneManager.h"
#include "Scene.h"

namespace dae
{
	void SceneSwitcher::Update()
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

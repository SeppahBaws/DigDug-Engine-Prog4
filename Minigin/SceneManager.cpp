#include "MiniginPCH.h"
#include "SceneManager.h"
#include "Scene.h"

namespace dae
{
	void SceneManager::Update()
	{
		mActiveScene->Update();
	}

	void SceneManager::Render()
	{
		mActiveScene->Render();
	}

	Scene& SceneManager::CreateScene(const std::string& name)
	{
		const auto scene = std::shared_ptr<Scene>(new Scene(name));
		mScenes.push_back(scene);
		return *scene;
	}


	void SceneManager::SetActiveScene(const std::string& name)
	{
		for (auto pScene : mScenes)
		{
			if (pScene->GetName() == name)
			{
				mActiveScene = pScene;
				break;
			}
		}
	}
}

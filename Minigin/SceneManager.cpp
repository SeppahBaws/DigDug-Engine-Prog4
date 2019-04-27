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
		const std::shared_ptr<Scene> scene = std::shared_ptr<Scene>(new Scene(name));
		mScenes.push_back(scene);
		return *scene;
	}

	void SceneManager::SetActiveScene(const std::string& name)
	{
		for (const std::shared_ptr<Scene> pScene : mScenes)
		{
			if (pScene->GetName() == name)
			{
				mActiveScene = pScene;

				// The newly added scene needs to be updated here before we continue
				// Because otherwise the textures will be invalid once we try to render that scene
				mActiveScene->Update();
				break;
			}
		}
	}

	const Scene& SceneManager::GetActiveScene() const
	{
		return *mActiveScene;
	}
}

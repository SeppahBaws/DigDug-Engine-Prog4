#include "MiniginPCH.h"
#include "SceneManager.h"
#include "Scene.h"

namespace dae
{
	void SceneManager::Start()
	{
		for (const std::shared_ptr<Scene> pScene : m_Scenes)
		{
			pScene->Start();
		}
	}

	void SceneManager::Update()
	{
		m_ActiveScene->Update();
	}

	void SceneManager::Render()
	{
		m_ActiveScene->Render();
	}

	Scene& SceneManager::CreateScene(const std::string& name, bool setActive)
	{
		const std::shared_ptr<Scene> scene = std::shared_ptr<Scene>(new Scene(name));
		m_Scenes.push_back(scene);

		if (setActive)
		{
			SetActiveScene(name);
		}

		return *scene;
	}

	void SceneManager::SetActiveScene(const std::string& name)
	{
		for (const std::shared_ptr<Scene> pScene : m_Scenes)
		{
			if (pScene->GetName() == name)
			{
				m_ActiveScene = pScene;

				// The newly added scene needs to be updated here before we continue
				// Because otherwise the textures will be invalid once we try to render that scene
				m_ActiveScene->Update();
				break;
			}
		}
	}

	const Scene& SceneManager::GetActiveScene() const
	{
		return *m_ActiveScene;
	}
}

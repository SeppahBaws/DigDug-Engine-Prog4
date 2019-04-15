#pragma once
#include "Singleton.h"

namespace dae
{
	class Scene;
	class SceneManager final : public Singleton<SceneManager>
	{
	public:
		Scene & CreateScene(const std::string& name);

		void Update();
		void Render();

		void SetActiveScene(const std::string& name);

	private:
		std::vector<std::shared_ptr<Scene>> mScenes;
		std::shared_ptr<Scene> mActiveScene;
	};

}

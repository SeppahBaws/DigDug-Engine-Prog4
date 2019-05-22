#pragma once
#include "Singleton.h"

namespace dae
{
	class Scene;
	class SceneManager final : public Singleton<SceneManager>
	{
	public:
		Scene & CreateScene(const std::string& name, bool setActive = false);

		void Start();
		void Update();
		void Render();

		void SetActiveScene(const std::string& name);
		const Scene& GetActiveScene() const;

	private:
		std::vector<std::shared_ptr<Scene>> m_Scenes;
		std::shared_ptr<Scene> m_ActiveScene;
	};

}

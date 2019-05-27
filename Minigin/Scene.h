#pragma once
#include "SceneManager.h"

namespace dae
{
	class GameObject;

	class Scene
	{
		friend Scene& SceneManager::CreateScene(const std::string& name, bool setActive);
	public:
		void Add(const std::shared_ptr<GameObject>& object);
		void Destroy(const std::shared_ptr<GameObject>& object);

		void Start();
		void Update();
		void PhysicsUpdate(); // Handles all the collisions
		void Render() const;

		inline std::string GetName() const { return m_Name; }

		~Scene();
		Scene(const Scene& other) = delete;
		Scene(Scene&& other) = delete;
		Scene& operator=(const Scene& other) = delete;
		Scene& operator=(Scene&& other) = delete;

	private:
		explicit Scene(const std::string& name);

		std::string m_Name{};
		std::vector<std::shared_ptr<GameObject>> m_Objects{};

		static unsigned int m_IdCounter;
	};
}

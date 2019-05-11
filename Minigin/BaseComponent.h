#pragma once

namespace dae
{
	class GameObject;

	class BaseComponent
	{
	public:
		BaseComponent() = default;
		virtual ~BaseComponent() = default;
		BaseComponent(const BaseComponent& other) = delete;
		BaseComponent(BaseComponent&& other) noexcept = delete;
		BaseComponent& operator=(const BaseComponent& other) = delete;
		BaseComponent& operator=(BaseComponent&& other) noexcept = delete;

		virtual void Update();
		virtual void Render();

		std::shared_ptr<GameObject> GetGameObject() const
		{
			if (std::shared_ptr<GameObject> sp = m_pGameObject.lock())
			{
				return sp;
			}
			return nullptr;
		}

	private:
		friend class GameObject;

		std::weak_ptr<GameObject> m_pGameObject;
	};
}

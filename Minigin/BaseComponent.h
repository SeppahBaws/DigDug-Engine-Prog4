#pragma once

namespace dae
{
	class GameObject;
	class TransformComponent;

	class BaseComponent
	{
	public:
		BaseComponent();
		virtual ~BaseComponent();
		BaseComponent(const BaseComponent& other) = delete;
		BaseComponent(BaseComponent&& other) noexcept = delete;
		BaseComponent& operator=(const BaseComponent& other) = delete;
		BaseComponent& operator=(BaseComponent&& other) noexcept = delete;

		virtual void Start() {}
		virtual void Update() {}
		virtual void Render() {}
		virtual void OnEnable() {}
		virtual void OnDisable() {}

		GameObject* GetGameObject() const { return m_pGameObject; }
		std::shared_ptr<TransformComponent> GetTransform() const;

	private:
		friend class GameObject;

		GameObject* m_pGameObject;
	};
}

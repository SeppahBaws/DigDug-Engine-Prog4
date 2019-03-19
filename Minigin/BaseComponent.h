#pragma once

namespace dae
{
	class GameObject;

	class BaseComponent
	{
	public:
		BaseComponent();
		virtual ~BaseComponent();
		BaseComponent(const BaseComponent& other) = delete;
		BaseComponent(BaseComponent&& other) noexcept = delete;
		BaseComponent& operator=(const BaseComponent& other) = delete;
		BaseComponent& operator=(BaseComponent&& other) noexcept = delete;

		virtual void Update() = 0;
		virtual void Render() const = 0;

		GameObject* GetGameObject() const { return mpGameObject; }

	private:
		friend class GameObject;

		GameObject* mpGameObject;
	};
}

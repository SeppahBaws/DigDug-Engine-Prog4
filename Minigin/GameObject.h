#pragma once
#include <memory>

#include "SceneObject.h"
#include "BaseComponent.h"

namespace dae
{
	class GameObject final : public SceneObject
	{
	public:
		void Update() override;
		void Render() const override;

		void AddComponent(std::shared_ptr<BaseComponent> component);

		template<class T>
		std::shared_ptr<T> GetComponent()
		{
			const type_info& ti = typeid(T);
			for (auto component : mComponents)
			{
				if (component && typeid(*component) == ti)
				{
					return std::dynamic_pointer_cast<T>(component);
				}
			}

			return nullptr;
		}

		GameObject() = default;
		virtual ~GameObject();
		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;

	private:
		std::vector<std::shared_ptr<BaseComponent>> mComponents;
	};
}

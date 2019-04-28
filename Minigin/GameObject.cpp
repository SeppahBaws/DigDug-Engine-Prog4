#include "MiniginPCH.h"
#include "GameObject.h"
#include "TransformComponent.h"

namespace dae
{
	GameObject::GameObject()
	{
		const auto transformComponent = std::make_shared<TransformComponent>();
		mComponents.push_back(transformComponent);
	}

	void GameObject::Update()
	{
		for (auto component : mComponents)
		{
			component->Update();
		}
	}

	void GameObject::Render() const
	{
		for (auto component : mComponents)
		{
			component->Render();
		}
	}

	void GameObject::AddComponent(std::shared_ptr<BaseComponent> component)
	{
		

		mComponents.push_back(component);
		component->mpGameObject = this;
	}

	void GameObject::RemoveComponent(std::shared_ptr<BaseComponent> pComponent)
	{
		const auto it = std::find(mComponents.begin(), mComponents.end(), pComponent);

		mComponents.erase(it);
		pComponent = nullptr;  // Set pComponent to nullptr since it doesn't exist anymore
	}
}

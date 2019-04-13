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
}

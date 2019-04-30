#include "MiniginPCH.h"
#include "GameObject.h"
#include "TransformComponent.h"

namespace dae
{
	GameObject::GameObject()
	{
		const auto transformComponent = std::make_shared<TransformComponent>();
		m_Components.push_back(transformComponent);
	}

	void GameObject::Update()
	{
		for (auto component : m_Components)
		{
			component->Update();
		}
	}

	void GameObject::Render() const
	{
		for (auto component : m_Components)
		{
			component->Render();
		}
	}

	void GameObject::AddComponent(std::shared_ptr<BaseComponent> component)
	{
		m_Components.push_back(component);
		component->mpGameObject = this;
	}

	void GameObject::RemoveComponent(std::shared_ptr<BaseComponent> pComponent)
	{
		const auto it = std::find(m_Components.begin(), m_Components.end(), pComponent);

		m_Components.erase(it);
		pComponent = nullptr;  // Set pComponent to nullptr since it doesn't exist anymore
	}
}

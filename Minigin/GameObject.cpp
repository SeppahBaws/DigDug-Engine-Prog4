#include "MiniginPCH.h"
#include "GameObject.h"
#include "TransformComponent.h"

namespace dae
{
	GameObject::GameObject()
	{
		m_Components.push_back(std::make_shared<TransformComponent>());
	}

	void GameObject::Start()
	{
		if (!m_Active) return;

		for (auto component : m_Components)
		{
			component->Start();
		}
	}

	void GameObject::Update()
	{
		if (!m_Active) return;

		for (auto component : m_Components)
		{
			component->Update();
		}
	}

	void GameObject::Render() const
	{
		if (!m_Active) return;

		for (auto component : m_Components)
		{
			component->Render();
		}
	}

	void GameObject::AddComponent(std::shared_ptr<BaseComponent> component)
	{
		m_Components.push_back(component);
		component->m_pGameObject = this;
	}

	void GameObject::RemoveComponent(std::shared_ptr<BaseComponent> pComponent)
	{
		const auto it = std::find(m_Components.begin(), m_Components.end(), pComponent);

		m_Components.erase(it);
		pComponent = nullptr;  // Set pComponent to nullptr since it doesn't exist anymore
	}

	void GameObject::SetActive(bool value)
	{
		m_Active = value;

		if (value)
		{
			for (auto component : m_Components)
			{
				component->OnEnable();
			}
		}
		else
		{
			for (auto component : m_Components)
			{
				component->OnDisable();
			}
		}
	}

	std::shared_ptr<TransformComponent> GameObject::GetTransform()
	{
		return GetComponent<TransformComponent>();
	}
}

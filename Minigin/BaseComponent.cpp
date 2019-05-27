#include "MiniginPCH.h"
#include "BaseComponent.h"
#include "GameObject.h"

namespace dae
{
	BaseComponent::BaseComponent()
		: m_pGameObject(nullptr)
	{
	}

	BaseComponent::~BaseComponent()
	{
		m_pGameObject = nullptr;
	}

	std::shared_ptr<TransformComponent> BaseComponent::GetTransform() const
	{
		return m_pGameObject->GetComponent<TransformComponent>();
	}
}

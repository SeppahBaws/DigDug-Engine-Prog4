#include "MiniginPCH.h"
#include "BaseComponent.h"

dae::BaseComponent::BaseComponent()
{
}

dae::BaseComponent::~BaseComponent()
{
	m_pGameObject = nullptr;
}

void dae::BaseComponent::Update()
{
}

void dae::BaseComponent::Render()
{
}

#include "MiniginPCH.h"
#include "BaseComponent.h"

dae::BaseComponent::BaseComponent()
	: m_pGameObject(nullptr)
{
}

dae::BaseComponent::~BaseComponent()
{
	m_pGameObject = nullptr;
}

void dae::BaseComponent::Start()
{
}

void dae::BaseComponent::Update()
{
}

void dae::BaseComponent::Render()
{
}

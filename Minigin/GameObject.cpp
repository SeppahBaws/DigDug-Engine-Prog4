#include "MiniginPCH.h"
#include "GameObject.h"

dae::GameObject::~GameObject() = default;

void dae::GameObject::Update()
{
	for (auto component : mComponents)
	{
		component->Update();
	}
}

void dae::GameObject::Render() const
{
	for (auto component : mComponents)
	{
		component->Render();
	}
}

void dae::GameObject::AddComponent(std::shared_ptr<BaseComponent> component)
{
	mComponents.push_back(component);
	component->mpGameObject = this;
}

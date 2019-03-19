#include "MiniginPCH.h"
#include "RenderComponent.h"
#include "ResourceManager.h"
#include "Renderer.h"
#include "GameObject.h"
#include "TransformComponent.h"

dae::RenderComponent::RenderComponent(const std::string& file)
{
	SetTexture(file);
}

void dae::RenderComponent::Update()
{
}

void dae::RenderComponent::Render() const
{
	const auto pos = GetGameObject()->GetComponent<TransformComponent>()->GetPosition();
	Renderer::GetInstance().RenderTexture(*mTexture, pos.x, pos.y);
}

void dae::RenderComponent::SetTexture(const std::string& file)
{
	mTexture = ResourceManager::GetInstance().LoadTexture(file);
}

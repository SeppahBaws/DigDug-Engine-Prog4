#include "MiniginPCH.h"
#include "TransformComponent.h"


dae::TransformComponent::TransformComponent()
	: TransformComponent({ 0, 0, 0 })
{
}

dae::TransformComponent::TransformComponent(const glm::vec3& pos)
	: mPosition(pos)
{
}

void dae::TransformComponent::SetPosition(float x, float y, float z)
{
	mPosition.x = x;
	mPosition.y = y;
	mPosition.z = z;
}

void dae::TransformComponent::SetPosition(const glm::vec3& vec)
{
	mPosition.x = vec.x;
	mPosition.y = vec.y;
	mPosition.z = vec.z;
}

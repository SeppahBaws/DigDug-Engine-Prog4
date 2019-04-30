#include "MiniginPCH.h"
#include "TransformComponent.h"


dae::TransformComponent::TransformComponent()
	: TransformComponent({ 0, 0, 0 })
{
}

dae::TransformComponent::TransformComponent(const glm::vec3& pos)
	: m_Position(pos)
{
}

void dae::TransformComponent::SetPosition(float x, float y, float z)
{
	m_Position.x = x;
	m_Position.y = y;
	m_Position.z = z;
}

void dae::TransformComponent::SetPosition(const glm::vec3& vec)
{
	m_Position.x = vec.x;
	m_Position.y = vec.y;
	m_Position.z = vec.z;
}

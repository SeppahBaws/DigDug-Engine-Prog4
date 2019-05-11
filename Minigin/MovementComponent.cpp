#include "MiniginPCH.h"
#include "MovementComponent.h"
#include "GameObject.h"
#include "TransformComponent.h"
#include "InputManager.h"
#include "Time.h"

namespace dae
{
	MovementComponent::MovementComponent()
		: m_MoveSpeed{ 500 }
	{
	}

	void MovementComponent::Update()
	{
		std::shared_ptr<TransformComponent> transform = GetGameObject()->GetComponent<TransformComponent>();

		glm::vec2 move = InputManager::GetInstance().GetThumbstick(ControllerAxis::LeftThumbstick);
		move *= Time::GetDeltaTime() * m_MoveSpeed;
		transform->SetPosition(transform->GetPosition() + glm::vec3(move.x, move.y, 0));
	}
}

#include "MiniginPCH.h"
#include "BoxColliderComponent.h"
#include "GameObject.h"
#include "TransformComponent.h"
#include "Renderer.h"
#include <SDL.h>

namespace dae
{
	BoxColliderComponent::BoxColliderComponent(const glm::vec2& center, const glm::vec2& extents)
		: m_CenterOffset(center), m_Extents(extents)
	{
	}

	void BoxColliderComponent::Render()
	{
		DrawDebug();
	}

	bool BoxColliderComponent::IsColliding(std::shared_ptr<BoxColliderComponent> other)
	{
		glm::vec2 otherPosition = glm::vec2(other->GetTransform()->GetPosition()) + other->m_CenterOffset;
		glm::vec2 myPosition = glm::vec2(GetTransform()->GetPosition()) + m_CenterOffset;

		RECT otherRect =  {
			LONG(otherPosition.x - other->m_Extents.x),
			LONG(otherPosition.y - other->m_Extents.y),
			LONG(otherPosition.x + other->m_Extents.x),
			LONG(otherPosition.y + other->m_Extents.y)
		};

		RECT myRect = {
			LONG(myPosition.x - m_Extents.x),
			LONG(myPosition.y - m_Extents.y),
			LONG(myPosition.x + m_Extents.x),
			LONG(myPosition.y + m_Extents.y)
		};

		if (otherRect.left < myRect.right && otherRect.right > myRect.left)
		{
			if (otherRect.top < myRect.bottom && otherRect.bottom > myRect.top)
			{
				return true;
			}
		}

		return false;
	}

	void BoxColliderComponent::SetCenterOffset(const glm::vec2& offset)
	{
		m_CenterOffset = offset;
	}

	void BoxColliderComponent::SetExtents(const glm::vec2& extents)
	{
		m_Extents = extents;
	}

	void BoxColliderComponent::DrawDebug() const
	{
#ifdef _DEBUG
		glm::vec2 pos = glm::vec2(GetTransform()->GetPosition()) + m_CenterOffset;

		RECT boxRect = {
			LONG(pos.x - m_Extents.x),
			LONG(pos.y - m_Extents.y),
			LONG(pos.x + m_Extents.x),
			LONG(pos.y + m_Extents.y)
		};

		SDL_Point lines[] =
		{
			{ boxRect.left, boxRect.top },
			{ boxRect.left, boxRect.bottom },
			{ boxRect.right, boxRect.bottom },
			{ boxRect.right, boxRect.top },
			{ boxRect.left, boxRect.top },
		};

		Uint8 r, g, b, a;
		SDL_GetRenderDrawColor(Renderer::GetInstance().GetSDLRenderer(), &r, &g, &b, &a);
		SDL_SetRenderDrawColor(Renderer::GetInstance().GetSDLRenderer(), 255, 0, 0, 255);
		SDL_RenderDrawLines(Renderer::GetInstance().GetSDLRenderer(), lines, 5);
		SDL_SetRenderDrawColor(Renderer::GetInstance().GetSDLRenderer(), r, g, b, a);

#endif
	}
}

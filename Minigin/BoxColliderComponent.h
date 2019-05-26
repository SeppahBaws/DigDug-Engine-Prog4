#pragma once
#include "BaseComponent.h"

#pragma warning(push)
#pragma warning (disable:4201)
#include <glm/vec2.hpp>
#pragma warning(pop)

namespace dae
{
	// Simple collider component. Uses AABB for collision detection.
	class BoxColliderComponent : public BaseComponent
	{
	public:
		BoxColliderComponent() = default;
		BoxColliderComponent(const glm::vec2& center, const glm::vec2& extents);

		void Render() override;

		bool IsColliding();
		void CheckColliding(std::shared_ptr<BoxColliderComponent> other);

		void SetCenterOffset(const glm::vec2& offset);
		void SetExtents(const glm::vec2& extents);

		// Draws four lines on the edges of the collider, only works in DEBUG mode
		void DrawDebug() const;

	private:
		glm::vec2 m_CenterOffset;
		glm::vec2 m_Extents;

		bool m_IsColliding = false;
	};
}

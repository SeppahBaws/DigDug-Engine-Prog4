#pragma once
#include "BaseComponent.h"
#include <glm/detail/type_vec2.hpp>

namespace dae
{
	class BoxColliderComponent : public BaseComponent
	{
	public:
		BoxColliderComponent() = default;
		BoxColliderComponent(const glm::vec2& center, const glm::vec2& extents)
			: m_Center(center)
			, m_Extents(extents)
		{}

	private:
		glm::vec2 m_Center;
		glm::vec2 m_Extents;
	};
}

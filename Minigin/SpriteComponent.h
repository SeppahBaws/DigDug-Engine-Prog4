#pragma once
#include "BaseComponent.h"

namespace dae
{
	// Forward declarations
	class Texture2D;

	class SpriteComponent final : public BaseComponent
	{
	public:
		SpriteComponent() = default;

	private:
		std::vector<Texture2D> m_Textures;
	};
}

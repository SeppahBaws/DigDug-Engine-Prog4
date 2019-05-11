#pragma once
#include "BaseComponent.h"

namespace dae
{
	// Forward declarations
	class Sprite;

	class SpriteRenderComponent final : public BaseComponent
	{
	public:
		SpriteRenderComponent() = default;

		void AddSprite(std::unique_ptr<Sprite> pSprite);
		void SelectSprite(const std::string& name);

		void Update() override;
		void Render() override;

	private:
		std::vector<std::unique_ptr<Sprite>> m_pSprites{};
		std::weak_ptr<Sprite> m_pCurrentSprite{};
		int m_CurrentSpriteIdx{};
	};
}

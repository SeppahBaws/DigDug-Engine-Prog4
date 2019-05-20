#pragma once
#include "BaseComponent.h"

namespace dae
{
	// Forward declarations
	class Sprite;

	struct SpriteRenderConfig
	{
		std::string defaultSprite;
		int scale;
	};

	// TODO: add support for sprite playback speed
	class SpriteRenderComponent final : public BaseComponent
	{
	public:
		SpriteRenderComponent();

		void AddSprite(std::unique_ptr<Sprite> pSprite);
		void SelectSprite(const std::string& name);
		void ResetSprite() const;
		void ResetSprite(const std::string& name) const;
		void SetScale(int scale);

		void Update() override;
		void Render() override;

	private:
		std::vector<std::unique_ptr<Sprite>> m_pSprites{};
		std::weak_ptr<Sprite> m_pCurrentSprite{};
		int m_CurrentSpriteIdx{};
		int m_Scale;
	};
}

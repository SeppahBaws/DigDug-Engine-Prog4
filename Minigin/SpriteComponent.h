#pragma once
#include "BaseComponent.h"

namespace dae
{
	// Forward declarations
	class Texture2D;

	struct SpriteProps
	{
		int cols = 1;
		int rows = 1;
		float framerate = 1;
		int scale = 1;
	};

	class SpriteComponent final : public BaseComponent
	{
	public:
		SpriteComponent(const std::string& filename, const SpriteProps& props);

		void SetTexture(const std::string& file);

		void Update() override;
		void Render() override;

	private:
		int GetFrameWidth() const;
		int GetFrameHeight() const;

	private:
		std::shared_ptr<Texture2D> m_pSpriteSheet;

		SpriteProps m_Props;
		int m_TextureWidth{};
		int m_TextureHeight{};

		float m_Accuframes;
		int m_CurrentFrame;
	};
}

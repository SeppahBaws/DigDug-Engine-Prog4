#pragma once
#include "BaseComponent.h"
#include "Font.h"
#include "Texture2D.h"

namespace dae
{
	class TextComponent final : public BaseComponent
	{
	public:
		TextComponent(const std::string& text, std::shared_ptr<Font> font);
		TextComponent(const std::string& text, std::shared_ptr<Font> font, const SDL_Color& color);
		virtual ~TextComponent() = default;

		TextComponent(const TextComponent& other) = delete;
		TextComponent(TextComponent&& other) noexcept = delete;
		TextComponent& operator=(const TextComponent& other) = delete;
		TextComponent& operator=(TextComponent&& other) noexcept = delete;

		virtual void Update() override;
		virtual void Render() override;

		void SetText(const std::string& text);
		void SetFont(std::shared_ptr<Font> font);

	private:
		std::string mText;
		std::shared_ptr<Font> mFont;
		SDL_Color mColor;
		std::shared_ptr<Texture2D> mTexture;
	};
}

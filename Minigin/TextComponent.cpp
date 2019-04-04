#include "MiniginPCH.h"
#include "TextComponent.h"
#include "Renderer.h"
#include "GameObject.h"
#include "TransformComponent.h"

namespace dae
{
	TextComponent::TextComponent(const std::string& text, std::shared_ptr<Font> font)
		: TextComponent(text, font, {255, 255, 255})
	{
	}

	TextComponent::TextComponent(const std::string& text, std::shared_ptr<Font> font, const SDL_Color& color)
		: mText(text), mFont(font), mColor(color), mTexture(nullptr)
	{
	}

	void TextComponent::Update()
	{
		const auto surf = TTF_RenderText_Blended(mFont->GetFont(), mText.c_str(), mColor);
		if (surf == nullptr)
		{
			throw std::runtime_error(std::string("Render text failed: ") + SDL_GetError());
		}
		auto texture = SDL_CreateTextureFromSurface(Renderer::GetInstance().GetSDLRenderer(), surf);
		if (texture == nullptr)
		{
			throw std::runtime_error(std::string("Create texture from surface failed: ") + SDL_GetError());
		}
		SDL_FreeSurface(surf);
		mTexture = std::make_shared<Texture2D>(texture);
	}

	void TextComponent::Render()
	{
		const auto pos = GetGameObject()->GetComponent<TransformComponent>()->GetPosition();
		Renderer::GetInstance().RenderTexture(*mTexture, pos.x, pos.y);
	}

	void TextComponent::SetText(const std::string& text)
	{
		mText = text;
	}

	void TextComponent::SetFont(std::shared_ptr<Font> font)
	{
		mFont = font;
	}
}

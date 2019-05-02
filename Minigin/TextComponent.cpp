#include "MiniginPCH.h"
#include "TextComponent.h"
#include "Renderer.h"
#include "GameObject.h"
#include "TransformComponent.h"

namespace dae
{
	TextComponent::TextComponent(const std::string& text, std::shared_ptr<Font> font)
		: TextComponent(text, font, {255, 255, 255}, {0, 0, 0})
	{
	}

	TextComponent::TextComponent(const std::string& text, std::shared_ptr<Font> font, const SDL_Color& color)
		: TextComponent(text, font, color, { 0, 0, 0 })
	{
	}

	TextComponent::TextComponent(const std::string& text, std::shared_ptr<Font> font, const SDL_Color& color, const glm::vec3& offsetPos)
		: m_Text(text), m_Font(font), m_Color(color)
		, m_Texture(nullptr), m_OffsetPos(offsetPos)
	{
	}

	void TextComponent::Update()
	{
		SDL_Surface* pSurf = TTF_RenderText_Blended(m_Font->GetFont(), m_Text.c_str(), m_Color);
		if (pSurf == nullptr)
		{
			throw std::runtime_error(std::string("Render text failed: ") + SDL_GetError());
		}
		SDL_Texture* pTexture = SDL_CreateTextureFromSurface(Renderer::GetInstance().GetSDLRenderer(), pSurf);
		if (pTexture == nullptr)
		{
			throw std::runtime_error(std::string("Create texture from surface failed: ") + SDL_GetError());
		}
		SDL_FreeSurface(pSurf);
		m_Texture = std::make_shared<Texture2D>(pTexture);
	}

	void TextComponent::Render()
	{
		glm::vec3 pos = GetGameObject()->GetComponent<TransformComponent>()->GetPosition();
		pos += m_OffsetPos;
		Renderer::GetInstance().RenderTexture(*m_Texture, pos.x, pos.y);
	}

	void TextComponent::SetText(const std::string& text)
	{
		m_Text = text;
	}

	void TextComponent::SetFont(std::shared_ptr<Font> font)
	{
		m_Font = font;
	}

	void TextComponent::SetOffset(const glm::vec3& offsetPos)
	{
		m_OffsetPos = offsetPos;
	}
}

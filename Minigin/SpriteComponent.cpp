#include "MiniginPCH.h"
#include "SpriteComponent.h"

#include <SDL.h>

#include "Renderer.h"
#include "Time.h"
#include "Texture2D.h"
#include "GameObject.h"
#include "TransformComponent.h"
#include "ResourceManager.h"

namespace dae
{
	SpriteComponent::SpriteComponent(const std::string& filename, const SpriteProps& props)
		: m_pSpriteSheet{ nullptr }, m_Props{ props }
		, m_Accuframes{0}, m_CurrentFrame{0}
	{
		SetTexture(filename);
	}

	void SpriteComponent::SetTexture(const std::string& file)
	{
		m_pSpriteSheet = ResourceManager::GetInstance().LoadTexture(file);

		// Query and store texture dimensions
		SDL_QueryTexture(m_pSpriteSheet->GetSDLTexture(), nullptr, nullptr, &m_TextureWidth, &m_TextureHeight);
	}

	void SpriteComponent::Update()
	{
		m_Accuframes += Time::GetDeltaTime();
		
		if (m_Accuframes >= 1 / m_Props.framerate)
		{
			m_CurrentFrame++;
			
			// Loop back the current frame if we're out of bounds
			if (m_CurrentFrame >= m_Props.cols * m_Props.rows)
			{
				m_CurrentFrame = 0;
			}

			m_Accuframes -= 1 / m_Props.framerate;
		}
	}

	void SpriteComponent::Render()
	{
		// Calculate source and destination rects
		SDL_Rect srcRect = SDL_Rect{
			GetFrameWidth() * (m_CurrentFrame % m_Props.cols),	// calculate the column
			GetFrameHeight() * (m_CurrentFrame / m_Props.cols),	// calculate the row
			GetFrameWidth(),
			GetFrameHeight()
		};
		SDL_Rect destRect = SDL_Rect{
			(int)GetGameObject()->GetComponent<TransformComponent>()->GetPosition().x,
			(int)GetGameObject()->GetComponent<TransformComponent>()->GetPosition().y,
			GetFrameWidth() * m_Props.scale,
			GetFrameHeight() * m_Props.scale
		};

		Renderer::GetInstance().RenderTexture(*m_pSpriteSheet, srcRect, destRect);
	}

	int SpriteComponent::GetFrameWidth() const
	{
		return m_TextureWidth / m_Props.cols;
	}

	int SpriteComponent::GetFrameHeight() const
	{
		return m_TextureHeight / m_Props.rows;
	}
}

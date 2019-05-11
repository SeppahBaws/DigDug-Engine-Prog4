#include "MiniginPCH.h"
#include "Sprite.h"

#include <SDL.h>
#include "ResourceManager.h"
#include "Texture2D.h"
#include "Time.h"
#include "TransformComponent.h"
#include "Renderer.h"

namespace dae
{
	Sprite::Sprite(const SpriteProps& props)
		: m_pSpriteSheet(nullptr), m_Props(props)
		, m_TextureWidth(0), m_TextureHeight(0)
		, m_AccuFrames(0), m_CurrentFrame(0)
	{
		
		LoadTexture(props.filename);
	}

	void Sprite::LoadTexture(const std::string& filename)
	{
		m_pSpriteSheet = ResourceManager::GetInstance().LoadTexture(filename);

		// Query and store texture dimensions
		SDL_QueryTexture(m_pSpriteSheet->GetSDLTexture(), nullptr, nullptr, &m_TextureWidth, &m_TextureHeight);
	}

	void Sprite::Update()
	{
		m_AccuFrames += Time::GetDeltaTime();

		if (m_AccuFrames >= 1 / m_Props.framerate)
		{
			m_CurrentFrame++;

			// Loop back the current frame if we're out of bounds
			if (m_CurrentFrame >= m_Props.cols * m_Props.rows)
			{
				m_CurrentFrame = 0;
			}

			m_AccuFrames -= 1 / m_Props.framerate;
		}
	}

	void Sprite::Render(const glm::vec3& pos, int scale)
	{
		// Calculate source and destination rects
		const SDL_Rect srcRect = SDL_Rect{
			GetFrameWidth() * (m_CurrentFrame % m_Props.cols),	// calculate the column
			GetFrameHeight() * (m_CurrentFrame / m_Props.cols),	// calculate the row
			GetFrameWidth(),
			GetFrameHeight()
		};
		const SDL_Rect destRect = SDL_Rect{
			int(pos.x),
			int(pos.y),
			GetFrameWidth() * scale,
			GetFrameHeight() * scale
		};

		Renderer::GetInstance().RenderTexture(*m_pSpriteSheet, srcRect, destRect);
	}

	void Sprite::Reset()
	{
		m_AccuFrames = 0;
	}

	int Sprite::GetFrameWidth() const
	{
		return m_TextureWidth / m_Props.cols;
	}

	int Sprite::GetFrameHeight() const
	{
		return m_TextureHeight / m_Props.rows;
	}
}

#include "MiniginPCH.h"
#include "SpriteRenderComponent.h"
#include "TransformComponent.h"
#include "GameObject.h"
#include "Sprite.h"

namespace dae
{
	SpriteRenderComponent::SpriteRenderComponent()
		: m_pSprites()
		, m_pCurrentSprite()
		, m_CurrentSpriteIdx(0)
		, m_Scale(1)
	{
	}

	void SpriteRenderComponent::AddSprite(std::unique_ptr<Sprite> pSprite)
	{
		m_pSprites.push_back(std::move(pSprite));

		//TODO:
		// Set this sprite the default one if it's the first one
		// if (m_pSprites.size() == 1)
		// {
		// 	m_pCurrentSprite = std::make_shared<Sprite>(*m_pSprites[0]);
		// }
	}


	void SpriteRenderComponent::SelectSprite(const std::string& name)
	{
		for (int i = 0; i < m_pSprites.size(); i++)
		{
			if (m_pSprites[i]->GetName() == name)
			{
				m_CurrentSpriteIdx = i;
				return;
			}
		}
	}

	void SpriteRenderComponent::ResetSprite() const
	{
		m_pCurrentSprite.lock()->Reset();
	}

	void SpriteRenderComponent::ResetSprite(const std::string& name) const
	{
		for (int i = 0; i < m_pSprites.size(); i++)
		{
			if (m_pSprites[i]->GetName() == name)
			{
				m_pSprites[i]->Reset();
			}
		}
	}

	void SpriteRenderComponent::SetScale(int scale)
	{
		m_Scale = scale;
	}

	void SpriteRenderComponent::Update()
	{
		m_pSprites[m_CurrentSpriteIdx]->Update();
	}

	void SpriteRenderComponent::Render()
	{
		m_pSprites[m_CurrentSpriteIdx]->Render(GetGameObject()->GetComponent<TransformComponent>()->GetPosition(), m_Scale);
	}
}

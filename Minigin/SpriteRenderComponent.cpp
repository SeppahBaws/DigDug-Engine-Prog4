#include "MiniginPCH.h"
#include "SpriteRenderComponent.h"
#include "TransformComponent.h"
#include "GameObject.h"
#include "Sprite.h"

namespace dae
{
	void SpriteRenderComponent::AddSprite(std::unique_ptr<Sprite> pSprite)
	{
		m_pSprites.push_back(std::move(pSprite));

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

		// for (auto& sprite : m_pSprites)
		// {
		// 	if (sprite->GetName() == name)
		// 	{
		// 		m_pCurrentSprite = std::make_shared<Sprite>(*sprite);
		// 	}
		// }

		// const auto it = std::find_if(m_pSprites.begin(), m_pSprites.end(),
		// 	[name](std::unique_ptr<Sprite>& pSprite){ return pSprite->GetName() == name; });
		//
		// if (it != m_pSprites.end())
		// {
		// 	m_pCurrentSprite = std::make_shared<Sprite>(**it);
		// }
	}

	void SpriteRenderComponent::Update()
	{
		// m_pCurrentSprite.lock()->Update();
		m_pSprites[m_CurrentSpriteIdx]->Update();
	}

	void SpriteRenderComponent::Render()
	{
		// m_pCurrentSprite.lock()->Render(GetGameObject()->GetComponent<TransformComponent>()->GetPosition());
		m_pSprites[m_CurrentSpriteIdx]->Render(GetGameObject()->GetComponent<TransformComponent>()->GetPosition());
	}
}

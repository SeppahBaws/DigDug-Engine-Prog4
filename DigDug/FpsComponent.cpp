#include "pch.h"
#include "FpsComponent.h"
#include "Time.h"
#include "GameObject.h"
#include "TextComponent.h"

namespace dae
{
	FpsComponent::FpsComponent()
		: m_AccumulatedTime(0)
	{
	}

	void FpsComponent::Update()
	{
		m_AccumulatedTime += Time::GetDeltaTime();

		// Update the fps text
		if (m_AccumulatedTime > 0.5f)
		{
			m_AccumulatedTime -= 0.5f;
			const float fps = 1 / Time::GetDeltaTime();

			std::stringstream ss;
			ss << int(fps) << " fps";
			m_FpsText = ss.str();
			GetGameObject()->GetComponent<TextComponent>()->SetText(m_FpsText);
		}
	}
}

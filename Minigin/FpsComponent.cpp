#include "MiniginPCH.h"
#include "FpsComponent.h"
#include "Time.h"
#include "GameObject.h"
#include "TextComponent.h"

namespace dae
{
	FpsComponent::FpsComponent()
		: mAccumulatedTime(0)
	{
	}

	void FpsComponent::Update()
	{
		mAccumulatedTime += Time::GetDeltaTime();

		// Update the fps text
		if (mAccumulatedTime > 0.5f)
		{
			mAccumulatedTime -= 0.5f;
			const float fps = 1 / Time::GetDeltaTime();

			std::stringstream ss;
			ss << int(fps) << " fps";
			mFpsText = ss.str();
			GetGameObject()->GetComponent<TextComponent>()->SetText(mFpsText);
		}
	}
}

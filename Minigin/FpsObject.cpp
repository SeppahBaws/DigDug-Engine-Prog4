#include "MiniginPCH.h"
#include <SDL_pixels.h>

#include "FpsObject.h"
#include "Font.h"
#include "Time.h"

namespace dae
{
	FpsObject::FpsObject(std::shared_ptr<Font> font)
		: m_Text(std::make_shared<TextObject>("0 fps", font, SDL_Color{255, 255, 0}))
		, m_AccumulatedTime(0.0f)
	{
	}

	void FpsObject::Update()
	{
		m_AccumulatedTime += Time::GetDeltaTime();

		// Update the fps text
		if (m_AccumulatedTime > 1.0f)
		{
			m_AccumulatedTime -= 1.0f;
			const float fps = 1 / Time::GetDeltaTime();

			std::stringstream ss;
			ss << int(fps) << " fps";
			m_Text->SetText(ss.str());
			m_Text->Update();
		}
	}

	void FpsObject::Render() const
	{
		m_Text->Render();
	}

	void FpsObject::SetPosition(float x, float y)
	{
		m_Transform.SetPosition(x, y, 0.0f);
		m_Text->SetPosition(x, y);
	}
}

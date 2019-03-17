#pragma once
#include "SceneObject.h"
#include "Transform.h"
#include "TextObject.h"

namespace dae
{
	class Font;

	class FpsObject final : public SceneObject
	{
	public:
		explicit FpsObject(std::shared_ptr<Font> font);
		virtual ~FpsObject() = default;
		FpsObject(const FpsObject& other) = delete;
		FpsObject(FpsObject&& other) = delete;
		FpsObject& operator=(const FpsObject& other) = delete;
		FpsObject& operator=(FpsObject&& other) = delete;

		void Update() override;
		void Render() const override;

		void SetPosition(float x, float y);

	private:
		Transform m_Transform;
		std::shared_ptr<TextObject> m_Text;
		float m_AccumulatedTime;
	};
}

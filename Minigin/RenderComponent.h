#pragma once
#include "BaseComponent.h"
#include "Texture2D.h"

namespace dae
{
	class RenderComponent final : public BaseComponent
	{
	public:
		RenderComponent(const std::string& file);
		virtual ~RenderComponent() = default;

		RenderComponent(const RenderComponent& other) = delete;
		RenderComponent(RenderComponent&& other) noexcept = delete;
		RenderComponent& operator=(const RenderComponent& other) = delete;
		RenderComponent& operator=(RenderComponent&& other) noexcept = delete;

		void Update() override;
		void Render() const override;

		void SetTexture(const std::string& file);

	private:
		std::shared_ptr<Texture2D> mTexture;
	};
}

#pragma once
#include "BaseComponent.h"

namespace dae
{
	class FpsComponent final : public BaseComponent
	{
	public:
		FpsComponent();
		virtual ~FpsComponent() = default;

		FpsComponent(const FpsComponent& other) = delete;
		FpsComponent(FpsComponent&& other) noexcept = delete;
		FpsComponent& operator=(const FpsComponent& other) = delete;
		FpsComponent& operator=(FpsComponent&& other) noexcept = delete;

		virtual void Update() override;

	private:
		std::string mFpsText;
		float mAccumulatedTime;
	};
}

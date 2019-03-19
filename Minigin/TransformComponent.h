#pragma once
#include "BaseComponent.h"

#pragma warning(push)
#pragma warning (disable:4201)
#include <glm/vec3.hpp>
#pragma warning(pop)

namespace dae
{
	class TransformComponent final : public BaseComponent
	{
	public:
		TransformComponent();
		TransformComponent(const glm::vec3& pos);
		virtual ~TransformComponent() = default;

		virtual void Update() override {}
		virtual void Render() const override {}

		const glm::vec3& GetPosition() const { return mPosition; }
		void SetPosition(float x, float y, float z);
		void SetPosition(const glm::vec3& vec);

	private:
		glm::vec3 mPosition;
	};
}

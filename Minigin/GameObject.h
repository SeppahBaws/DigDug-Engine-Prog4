#pragma once
#include <memory>

#include "BaseComponent.h"
#include "TransformComponent.h"

namespace dae
{
	class GameObject final
	{
	public:
		GameObject();

		void Start();
		void Update();
		void Render() const;

		void AddComponent(std::shared_ptr<BaseComponent> component);
		void RemoveComponent(std::shared_ptr<BaseComponent> component);

		void SetActive(bool value);
		bool IsActive() const { return m_Active; }

		std::shared_ptr<TransformComponent> GetTransform();

#pragma region Templated Functions

		template<class T>
		bool HasComponent()
		{
			const type_info& ti = typeid(T);
			for (const std::shared_ptr<BaseComponent> pComponent : m_Components)
			{
				if (typeid(*pComponent) == ti)
				{
					// Current component matches requested type
					return true;
				}
			}

			// No components of requested type
			return false;
		}

		// Returns the first component of given type
		template<class T>
		std::shared_ptr<T> GetComponent()
		{
			const type_info& ti = typeid(T);
			for (const std::shared_ptr<BaseComponent> component : m_Components)
			{
				if (component && typeid(*component) == ti)
				{
					return std::dynamic_pointer_cast<T>(component);
				}
			}

			return nullptr;
		}

		// Returns all the components of given type
		template<class T>
		std::vector<std::shared_ptr<T>> GetComponents()
		{
			std::vector<std::shared_ptr<T>> matchingComponents = {};

			const type_info& ti = typeid(T);
			for (const std::shared_ptr<BaseComponent> component : m_Components)
			{
				if (component && typeid(*component) == ti)
				{
					matchingComponents.push_back(std::dynamic_pointer_cast<T>(component));
				}
			}

			return matchingComponents;
		}

#pragma endregion Templated Functions

	private:
		std::vector<std::shared_ptr<BaseComponent>> m_Components;
		bool m_Active = true;
	};
}

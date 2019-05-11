#pragma once
#include <memory>

#include "BaseComponent.h"

namespace dae
{
	class GameObject
	{
	public:
		GameObject();
		virtual ~GameObject() = default;

		virtual void Update();
		virtual void Render() const;

		void AddComponent(std::shared_ptr<BaseComponent> component);
		void RemoveComponent(std::shared_ptr<BaseComponent> component);

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
		T& GetComponent()
		{
			const type_info& ti = typeid(T);

			// Old code for reference
			// for (const std::unique_ptr<BaseComponent>& component : m_Components)
			// {
			// 	if (component && typeid(*component) == ti)
			// 	{
			// 		return std::dynamic_pointer_cast<T>(component);
			// 	}
			// }

			for (auto it = m_Components.begin(); it != m_Components.end(); ++it)
			{
				if (*it && typeid(*&it) == ti)
				{
					return **it;
				}
			}

			return nullptr;
		}

#if 0 // temporarily disable this as I figure out how to do all this stuff
		// Returns all the components of given type
		template<class T>
		std::vector<std::shared_ptr<T>> GetComponents()
		{
			std::vector<std::shared_ptr<T>> matchingComponents = {};
			
			const type_info& ti = typeid(T);
			// for (int i = 0; i < m_Components.size(); i++)
			// {
			// 	if (m_Components[i] && typeid(*m_Components[i]) == ti)
			// 	{
			// 		matchingComponents.push_back(std::dynamic_pointer_cast<>())
			// 	}
			// }
			for (const std::unique_ptr<BaseComponent>& component : m_Components)
			{
				if (component && typeid(*component) == ti)
				{
					matchingComponents.push_back(std::dynamic_pointer_cast<T>(component));
				}
			}

			return matchingComponents;
		}
#endif

#pragma endregion Templated Functions

	private:
		std::vector<std::unique_ptr<BaseComponent>> m_Components;
	};
}

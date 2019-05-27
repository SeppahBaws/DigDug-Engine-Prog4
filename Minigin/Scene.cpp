#include "MiniginPCH.h"
#include "Scene.h"
#include "GameObject.h"
#include "BoxColliderComponent.h"

unsigned int dae::Scene::m_IdCounter = 0;

dae::Scene::Scene(const std::string& name) : m_Name(name) {}

dae::Scene::~Scene() = default;

void dae::Scene::Add(const std::shared_ptr<GameObject>& object)
{
	m_Objects.push_back(object);
}

void dae::Scene::Destroy(const std::shared_ptr<GameObject>& object)
{
	m_Objects.erase(std::remove(m_Objects.begin(), m_Objects.end(), object));
}

void dae::Scene::Start()
{
	for (auto gameObject : m_Objects)
	{
		gameObject->Start();
	}
}

void dae::Scene::Update()
{
	PhysicsUpdate();

	for(auto gameObject : m_Objects)
	{
		gameObject->Update();
	}
}

// Dirty loop to check collisions on all box colliders in the scene
// This could get way more improved by for example holding a list of all the pairs
// that have been checked already, or by using a physics library like Box2D for example.
void dae::Scene::PhysicsUpdate()
{
	for (auto gameObject : m_Objects)
	{
		for (auto otherObj : m_Objects)
		{
			if (otherObj == gameObject)
				continue;

			auto coll = gameObject->GetComponent<BoxColliderComponent>();
			auto otherColl = otherObj->GetComponent<BoxColliderComponent>();
			
			if (coll && otherColl)
			{
				coll->CheckColliding(otherColl);
			}
		}
	}
}

void dae::Scene::Render() const
{
	for (const auto gameObject : m_Objects)
	{
		gameObject->Render();
	}
}


#include "MiniginPCH.h"
#include "Scene.h"
#include "GameObject.h"

unsigned int dae::Scene::m_IdCounter = 0;

dae::Scene::Scene(const std::string& name) : m_Name(name) {}

dae::Scene::~Scene() = default;

void dae::Scene::Add(const std::shared_ptr<GameObject>& object)
{
	m_Objects.push_back(object);
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
	for(auto gameObject : m_Objects)
	{
		gameObject->Update();
	}
}

void dae::Scene::Render() const
{
	for (const auto gameObject : m_Objects)
	{
		gameObject->Render();
	}
}


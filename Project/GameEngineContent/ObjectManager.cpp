#include "PrecompileHeader.h"
#include "ObjectManager.h"
#include <GameEngineCore/GameEngineLevel.h>

ObjectManager::ObjectManager()
{
}

ObjectManager::~ObjectManager()
{
}

void ObjectManager::CreateStaticObject(const SObject_DESC& _Desc)
{
	std::shared_ptr<StaticObject> CreatePtr = GetLevel()->CreateActor<StaticObject>();
	CreatePtr->GetTransform()->SetParent(this->GetTransform());
	CreatePtr->Init(_Desc);
	StaticObjectActors.push_back(CreatePtr);
}

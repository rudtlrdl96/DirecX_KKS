#include "PrecompileHeader.h"
#include "ObjectManager.h"
#include <GameEngineCore/GameEngineLevel.h>

ObjectManager::ObjectManager()
{
	StaticObjectActors.reserve(32);
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

void ObjectManager::SaveBin(GameEngineSerializer& _SaveSerializer) const
{
	_SaveSerializer.Write(static_cast<int>(StaticObjectActors.size()));

	for (const std::shared_ptr<StaticObject>& LoopRef : StaticObjectActors)
	{ 
		LoopRef->SaveBin(_SaveSerializer);
	}	

	_SaveSerializer.Write(static_cast<int>(BrokenObjectActors.size()));

	for (const std::shared_ptr<BrokenObject>& LoopRef : BrokenObjectActors)
	{
		//LoopRef->SaveBin(_SaveSerializer);
	}
}

void ObjectManager::LoadBin(GameEngineSerializer& _LoadSerializer)
{
	for (size_t i = 0; i < StaticObjectActors.size(); i++)
	{
		if (nullptr == StaticObjectActors[i])
		{
			continue;
		}

		StaticObjectActors[i]->Death();
		StaticObjectActors[i] = nullptr;
	}

	StaticObjectActors.clear();

	int StaticObjectCount = 0;
	_LoadSerializer.Read(StaticObjectCount);

	StaticObjectActors.reserve(StaticObjectCount);

	for (int i = 0; i < StaticObjectCount; i++)
	{
		SObject_DESC LoadDesc = StaticObject::LoadBin(_LoadSerializer);
		CreateStaticObject(LoadDesc);
	}

	int BrokenObjectCount = 0;
	_LoadSerializer.Read(BrokenObjectCount);

	for (int i = 0; i < BrokenObjectCount; i++)
	{
	}
}

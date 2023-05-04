#pragma once
#include "BaseContentActor.h"
#include "StaticObject.h"
#include "BrokenObject.h"

class ObjectManager : public BaseContentActor
{
public:
	ObjectManager();
	~ObjectManager();

	ObjectManager(const ObjectManager& _Other) = delete;
	ObjectManager(ObjectManager&& _Other) noexcept = delete;
	ObjectManager& operator=(const ObjectManager& _Other) = delete;
	ObjectManager& operator=(ObjectManager&& _Other) noexcept = delete;

	void CreateStaticObject(const SObject_DESC& _Desc);

	void SaveBin(GameEngineSerializer& _SaveSerializer) const;
	void LoadBin(GameEngineSerializer& _LoadSerializer);

protected:
	
private:
	std::vector<std::shared_ptr<StaticObject>> StaticObjectActors;
	std::vector<std::shared_ptr<BrokenObject>> BrokenObjectActors;
};


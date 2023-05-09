#pragma once
#include "BaseContentActor.h"
#include "StaticObject.h"
#include "BrokenObject.h"
#include "MapCollision.h"

class ObjectManager : public BaseContentActor
{
public:
	ObjectManager();
	~ObjectManager();

	ObjectManager(const ObjectManager& _Other) = delete;
	ObjectManager(ObjectManager&& _Other) noexcept = delete;
	ObjectManager& operator=(const ObjectManager& _Other) = delete;
	ObjectManager& operator=(ObjectManager&& _Other) noexcept = delete;

	std::shared_ptr<StaticObject> CreateStaticObject(const SObject_DESC& _Desc);

	void SaveBin(GameEngineSerializer& _SaveSerializer) const;
	void LoadBin(GameEngineSerializer& _LoadSerializer);

	void ShowGUI() override;
	
	inline std::shared_ptr<BaseContentActor> GetSelectSObject() const
	{
		if (CurrentStaticObjectIndex < 0 || CurrentStaticObjectIndex >= StaticObjectActors.size())
		{
			return nullptr;
		}

		return StaticObjectActors[CurrentStaticObjectIndex];
	}

protected:

private:
	std::vector<std::shared_ptr<StaticObject>> StaticObjectActors;
	std::vector<std::shared_ptr<BrokenObject>> BrokenObjectActors;
	std::vector<std::shared_ptr<MapCollision>> MapCollisionActors;

	int CurrentStaticObjectIndex = -1;
};


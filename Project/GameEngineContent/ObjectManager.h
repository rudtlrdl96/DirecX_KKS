#pragma once
#include "BaseContentActor.h"
#include "StaticObject.h"
#include "BrokenObject.h"
#include "MapPlatform.h"

class ObjectManager : public BaseContentActor
{
public:
	enum class GuiType
	{
		None,
		SObject,
		BObject,
		Platform
	};

public:
	ObjectManager();
	~ObjectManager();

	ObjectManager(const ObjectManager& _Other) = delete;
	ObjectManager(ObjectManager&& _Other) noexcept = delete;
	ObjectManager& operator=(const ObjectManager& _Other) = delete;
	ObjectManager& operator=(ObjectManager&& _Other) noexcept = delete;

	std::shared_ptr<StaticObject> CreateStaticObject(const SObject_DESC& _Desc);
	std::shared_ptr<MapPlatform> CreatePaltform(const MapPlatform::Platform_DESC& _Desc);

	void SaveBin(GameEngineSerializer& _SaveSerializer) const;
	void LoadBin(GameEngineSerializer& _LoadSerializer);

	void ShowGUI() override;
	
	inline void SetGuiType(GuiType _ShowGuiType)
	{
		ShowGuiType = _ShowGuiType;
	}

	inline std::shared_ptr<BaseContentActor> GetSelectSObject() const
	{
		if (CurrentStaticObjectIndex < 0 || CurrentStaticObjectIndex >= StaticObjectActors.size())
		{
			return nullptr;
		}

		return StaticObjectActors[CurrentStaticObjectIndex];
	}

	void PlatformDebugOn();
	void PlatformDebugOff();

protected:

private:
	std::vector<std::shared_ptr<StaticObject>> StaticObjectActors;
	std::vector<std::shared_ptr<BrokenObject>> BrokenObjectActors;
	std::vector<std::shared_ptr<MapPlatform>> MapPlatformActors;

	int CurrentStaticObjectIndex = -1;
	int CurrentPlatformIndex = -1;

	bool IsPlatformDebug = false;

	GuiType ShowGuiType = GuiType::None;

	void Draw_SObject_GUI();
	void Draw_BObject_GUI();
	void Draw_Platform_GUI();
};


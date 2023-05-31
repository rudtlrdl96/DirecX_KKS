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
		Platform,
	};

public:
	ObjectManager();
	~ObjectManager();

	ObjectManager(const ObjectManager& _Other) = delete;
	ObjectManager(ObjectManager&& _Other) noexcept = delete;
	ObjectManager& operator=(const ObjectManager& _Other) = delete;
	ObjectManager& operator=(ObjectManager&& _Other) noexcept = delete;

	std::shared_ptr<StaticObject> CreateStaticObject(const SObjectMetaData& _MetaData);
	std::shared_ptr<MapPlatform> CreatePaltform(const MapPlatform::PlatformMetaData& _MetaData);

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

	void SelectLastStaticObject();
	void SelectLastPlatform();

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	std::vector<std::shared_ptr<StaticObject>> StaticObjectActors;
	std::vector<std::shared_ptr<BrokenObject>> BrokenObjectActors;
	std::vector<std::shared_ptr<MapPlatform>> MapPlatformActors;
	
	/// <summary>
	/// ImGUI
	/// </summary>

	std::shared_ptr<MapPlatform> CurrentEmphasizePlatform = nullptr;

	int CurrentStaticObjectIndex = -1;
	int CurrentPlatformIndex = -1;

	bool IsPlatformDebug = false;

	std::shared_ptr<ContentSpriteRenderer> OutlineRender = nullptr;
	CaptureBuffer Buffer;

	GuiType ShowGuiType = GuiType::None;

	void PushAllStaticObject(const float4& _AddPos);
	void PushAllPlatform(const float4& _AddPos);

	void Draw_SObject_GUI();
	void Draw_BObject_GUI();
	void Draw_Platform_GUI();

	void EmphasizeCurrentPlatform();
};


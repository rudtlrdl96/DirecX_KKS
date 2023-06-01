#pragma once
#include "BaseContentActor.h"
#include "MapObject.h"
#include "BrokenObject.h"
#include "MapPlatform.h"

class ObjectManager : public BaseContentActor
{
public:
	enum class GuiType
	{
		None,
		Object,
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

	std::shared_ptr<MapObject> CreateObject(const ObjectMetaData& _MetaData);
	std::shared_ptr<MapPlatform> CreatePaltform(const MapPlatform::PlatformMetaData& _MetaData);

	void SaveBin(GameEngineSerializer& _SaveSerializer) const;
	void LoadBin(GameEngineSerializer& _LoadSerializer);

	void ShowGUI() override;
	
	inline void SetGuiType(GuiType _ShowGuiType)
	{
		ShowGuiType = _ShowGuiType;
	}

	inline std::shared_ptr<BaseContentActor> GetSelectObject() const
	{
		if (CurrentObjectIndex < 0 || CurrentObjectIndex >= ObjectActors.size())
		{
			return nullptr;
		}

		return ObjectActors[CurrentObjectIndex];
	}

	void PlatformDebugOn();
	void PlatformDebugOff();

	void SelectLastObject();
	void SelectLastPlatform();

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	std::vector<std::shared_ptr<MapObject>> ObjectActors;
	std::vector<std::shared_ptr<BrokenObject>> BrokenObjectActors;
	std::vector<std::shared_ptr<MapPlatform>> MapPlatformActors;
	
	/// <summary>
	/// ImGUI
	/// </summary>

	std::shared_ptr<MapPlatform> CurrentEmphasizePlatform = nullptr;

	int CurrentObjectIndex = -1;
	int CurrentPlatformIndex = -1;

	bool IsPlatformDebug = false;

	std::shared_ptr<ContentSpriteRenderer> OutlineRender = nullptr;
	CaptureBuffer Buffer;

	GuiType ShowGuiType = GuiType::None;

	void PushAllObject(const float4& _AddPos);
	void PushAllPlatform(const float4& _AddPos);

	void Draw_Object_GUI();
	void Draw_BObject_GUI();
	void Draw_Platform_GUI();

	void EmphasizeCurrentPlatform();
};


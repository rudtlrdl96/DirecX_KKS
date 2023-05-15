#pragma once
#include <GameEngineCore/GameEngineCoreWindow.h>
#include "TileMetaData.h"
#include "MapToolLevel.h"
#include "ObjectManager.h"
#include "ParticleManager.h"

class MapToolGUI : public GameEngineCoreWindow
{
private:
	class MapTool_TilemapData
	{
	public:
		TileMetaData Data;
		std::shared_ptr<class GameEngineTexture> TexturePtr = nullptr; 

		MapTool_TilemapData(const TileMetaData& _Data, const std::shared_ptr<class GameEngineTexture> _TexturePtr) :
			Data(_Data),
			TexturePtr(_TexturePtr)
		{		
		}
	};

	class MapTool_SObjectData
	{
	public:
		SObjectMetaData Data;
		std::shared_ptr<class GameEngineTexture> TexturePtr = nullptr;

		MapTool_SObjectData(const SObjectMetaData& _Data, const std::shared_ptr<class GameEngineTexture> _TexturePtr) :
			Data(_Data),
			TexturePtr(_TexturePtr)
		{
		}
	};
public:
	MapToolGUI();
	~MapToolGUI();

	MapToolGUI(const MapToolGUI& _Other) = delete;
	MapToolGUI(MapToolGUI&& _Other) noexcept = delete;
	MapToolGUI& operator=(const MapToolGUI& _Other) = delete;
	MapToolGUI& operator=(MapToolGUI&& _Other) noexcept = delete;

	inline UINT GetSelectTileIndex() const
	{
		return SelectTileIndex;
	}

	inline SObjectMetaData GetSelectSObject() const
	{
		return SelectSObjectMetaData;
	}

	inline ParticleAreaMetaData GetNewParticleMetaData() const
	{
		return ParticleAreaMapMetaData;
	}

	inline MapToolLevel::MapToolState GetMapToolState() const
	{
		return MapToolType;
	}

	inline MapPlatform::PlatformType GetPlatformType() const
	{
		return BasePlatformType;
	}

	inline void Pushback_TilemapCallback(std::function<void()> _FunctionPtr)
	{
		TilemapCallback.push_back(_FunctionPtr);
	}

	inline void Pushback_ObjectManagerCallback(std::function<void()> _FunctionPtr)
	{
		ObjectManagerCallback.push_back(_FunctionPtr);
	}

	inline void Pushback_EventManagerCallback(std::function<void()> _FunctionPtr)
	{
		EventManagerCallback.push_back(_FunctionPtr);
	}

	inline void Pushback_ParticleManagerCallback(std::function<void()> _FunctionPtr)
	{
		ParticleManagerCallback.push_back(_FunctionPtr);
	}

	bool CheckSaveTrigger();
	bool CheckLoadTrigger();

protected:
	
private:
	std::map<LevelArea, std::vector<MapTool_TilemapData>> TileTexDatas;
	std::map<LevelArea, std::vector<MapTool_SObjectData>> SObjectTexDatas;

	LevelArea CurShowAreaTile = LevelArea::None;
	MapToolLevel::MapToolState MapToolType = MapToolLevel::MapToolState::Tilemap;
	MapPlatform::PlatformType BasePlatformType = MapPlatform::PlatformType::Normal;

	std::vector<std::function<void()>> TilemapCallback;
	std::vector<std::function<void()>> ObjectManagerCallback;
	std::vector<std::function<void()>> EventManagerCallback;
	std::vector<std::function<void()>> ParticleManagerCallback;

	const char* AreaComboText[7] = {"None" ,"Opening", "Castle", "ForestOfHarmony", "GrandHall", "HolyCourtyard", "Shop"};
	const char* MapToolComboText[7] = {"Tilemap" ,"SObject", "BObject", "Platform", "Event", "Particle", "Light"};
	const char* PlatformTypeCombo[2] = {"Normal" ,"Half"};
	
	float4 TileSize = float4::Zero;

	UINT SelectTileIndex = 0;
	SObjectMetaData SelectSObjectMetaData;

	ParticleAreaMetaData ParticleAreaMapMetaData;
	
	bool IsSaveTrigger = false;
	bool IsLoadTrigger = false;

	bool IsTilemapClearTrigger = false;
	bool IsDepthResizeTrigger = false;

	void Start() override;
	void OnGUI(std::shared_ptr<class GameEngineLevel>, float _DeltaTime) override;

	void TileDatasLoad(LevelArea _Area);
	void SObjectDatasLoad(LevelArea _Area);
	
	void DrawGui_Tilemap();
	void DrawGui_SObject();
	void DrawGui_BObject();
	void DrawGui_Platform();
	void DrawGui_Event();
	void DrawGui_Particle();
	void DrawGui_Light();

	void Callback_Object();
	void Callback_Event();
	void Callback_Particle();
};


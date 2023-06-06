#pragma once
#include <GameEngineCore/GameEngineCoreWindow.h>
#include "TileMetaData.h"
#include "MonsterData.h"
#include "MapToolLevel.h"
#include "ObjectManager.h"
#include "ParticleManager.h"
#include "BaseNPC.h"

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

	class MapTool_ObjectData
	{
	public:
		ObjectMetaData Data;
		std::shared_ptr<class GameEngineTexture> TexturePtr = nullptr;

		MapTool_ObjectData(const ObjectMetaData& _Data, const std::shared_ptr<class GameEngineTexture> _TexturePtr) :
			Data(_Data),
			TexturePtr(_TexturePtr)
		{
		}
	};

	class MapTool_BehaviorObjectData
	{
	public:
		BehaviorObjectMetaData Data;
		std::shared_ptr<class GameEngineTexture> TexturePtr = nullptr;

		MapTool_BehaviorObjectData(const BehaviorObjectMetaData& _Data, const std::shared_ptr<class GameEngineTexture> _TexturePtr) :
			Data(_Data),
			TexturePtr(_TexturePtr)
		{
		}
	};

	class MapTool_MonsterData
	{
	public:
		MonsterData Data;
		std::shared_ptr<class GameEngineTexture> TexturePtr = nullptr;

		MapTool_MonsterData(const MonsterData& _Data, const std::shared_ptr<class GameEngineTexture> _TexturePtr) :
			Data(_Data),
			TexturePtr(_TexturePtr)
		{
		}
	};

	class MapTool_NPCData
	{
	public:
		NPCMetaData Data;
		std::shared_ptr<class GameEngineTexture> TexturePtr = nullptr;

		MapTool_NPCData(const NPCMetaData& _Data, const std::shared_ptr<class GameEngineTexture> _TexturePtr) :
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

	inline ObjectMetaData GetSelectObject() const
	{
		return SelectObjectMetaData;
	}

	inline BehaviorObjectMetaData GetSelectBehaviorObject() const
	{
		return SelectBehaviorObjectMetaData;
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

	inline const MonsterData& GetMonsterData() const
	{
		return SelectMonsterMetaData;
	}

	inline const NPCMetaData& GetNPCData() const
	{
		return SelectNPCMetaData;
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

	inline void Pushback_MonsterManagerCallback(std::function<void()> _FunctionPtr)
	{
		MonsterManagerCallback.push_back(_FunctionPtr);
	}

	inline void Pushback_NPCManagerCallback(std::function<void()> _FunctionPtr)
	{
		NPCManagerCallback.push_back(_FunctionPtr);
	}

	bool CheckSaveTrigger();
	bool CheckLoadTrigger();

protected:
	
private:
	std::map<LevelArea, std::vector<MapTool_TilemapData>> TileTexDatas;
	std::map<LevelArea, std::vector<MapTool_ObjectData>> ObjectTexDatas;
	std::map<LevelArea, std::vector<MapTool_BehaviorObjectData>> BehaviorObjectTexDatas;
	std::map<LevelArea, std::vector<MapTool_MonsterData>> MonsterTexDatas;
	std::map<LevelArea, std::vector<MapTool_NPCData>> NPCTexDatas;

	LevelArea CurShowAreaTile = LevelArea::None;

	MapToolLevel::MapToolState MapToolType = MapToolLevel::MapToolState::Tilemap;
	MapPlatform::PlatformType BasePlatformType = MapPlatform::PlatformType::Normal;

	std::vector<std::function<void()>> TilemapCallback;
	std::vector<std::function<void()>> ObjectManagerCallback;
	std::vector<std::function<void()>> EventManagerCallback;
	std::vector<std::function<void()>> ParticleManagerCallback;
	std::vector<std::function<void()>> MonsterManagerCallback;
	std::vector<std::function<void()>> NPCManagerCallback;

	const char* AreaComboText[7] = {"None" ,"Opening", "Castle", "ForestOfHarmony", "GrandHall", "HolyCourtyard", "Shop"};
	const char* MapToolComboText[9] = { "Tilemap" ,"Object", "BObject", "Platform", "Event", "Particle", "Light", "Monster", "NPC" };
	const char* PlatformTypeCombo[2] = {"Normal" ,"Half"};
	
	float4 TileSize = float4::Zero;

	UINT SelectTileIndex = 0;
	ObjectMetaData SelectObjectMetaData;
	BehaviorObjectMetaData SelectBehaviorObjectMetaData;
	MonsterData SelectMonsterMetaData;
	NPCMetaData SelectNPCMetaData;

	ParticleAreaMetaData ParticleAreaMapMetaData;
	
	bool IsSaveTrigger = false;
	bool IsLoadTrigger = false;

	bool IsTilemapClearTrigger = false;
	bool IsDepthResizeTrigger = false;

	void Start() override;
	void OnGUI(std::shared_ptr<class GameEngineLevel>, float _DeltaTime) override;

	void TileDatasLoad(LevelArea _Area);
	void ObjectDatasLoad(LevelArea _Area);
	void BehaviorObjectDatasLoad(LevelArea _Area);
	void MonsterDatasLoad(LevelArea _Area);
	void NPCDatasLoad(LevelArea _Area);
	
	void DrawGui_Tilemap();
	void DrawGui_Object();
	void DrawGui_BObject();
	void DrawGui_Platform();
	void DrawGui_Event();
	void DrawGui_Particle();
	void DrawGui_Light();
	void DrawGui_Monster();
	void DrawGui_NPC();

	void Callback_Object();
	void Callback_Event();
	void Callback_Particle();
	void Callback_Monster();
	void Callback_NPC();
};


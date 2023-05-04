#pragma once
#include <GameEngineCore/GameEngineCoreWindow.h>
#include "TilemapData.h"
#include "MapToolLevel.h"
#include "ObjectManager.h"

class MapToolGUI : public GameEngineCoreWindow
{
private:
	class MapTool_TilemapData
	{
	public:
		TilemapData Data;
		std::shared_ptr<class GameEngineTexture> TexturePtr = nullptr; 

		MapTool_TilemapData(const TilemapData& _Data, const std::shared_ptr<class GameEngineTexture> _TexturePtr) :
			Data(_Data),
			TexturePtr(_TexturePtr)
		{		
		}
	};

	class MapTool_SObjectData
	{
	public:
		SObject_DESC Data;
		std::shared_ptr<class GameEngineTexture> TexturePtr = nullptr;

		MapTool_SObjectData(const SObject_DESC& _Data, const std::shared_ptr<class GameEngineTexture> _TexturePtr) :
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

	void Start() override;
	void OnGUI(std::shared_ptr<class GameEngineLevel>, float _DeltaTime) override;

	inline UINT GetSelectTileIndex() const
	{
		return SelectTileIndex;
	}

	inline SObject_DESC GetSelectSObject() const
	{
		return SelectSObject_Desc;
	}

	inline MapToolLevel::MapToolState GetMapToolState() const
	{
		return MapToolType;
	}

	bool CheckSaveTrigger();
	bool CheckLoadTrigger();

protected:
	
private:
	std::map<LevelArea, std::vector<MapTool_TilemapData>> TileTexDatas;
	std::map<LevelArea, std::vector<MapTool_SObjectData>> SObjectTexDatas;

	std::shared_ptr<class ObjectManager> ObjectMgrPtr = nullptr;

	LevelArea CurShowAreaTile = LevelArea::None;
	MapToolLevel::MapToolState MapToolType = MapToolLevel::MapToolState::Tilemap;

	const char* AreaComboText[6] = {"None" ,"Opening", "Castle", "ForestOfHarmony", "GrandHall", "HolyCourtyard"};
	const char* MapToolComboText[3] = {"Tilemap" ,"Object", "Light"};

	float4 TileSize = float4::Zero;

	UINT SelectTileIndex = 0;
	SObject_DESC SelectSObject_Desc;
	
	float MinWidth = 0.0f;
	float MaxWitdh = 0.0f;

	bool IsSaveTrigger = false;
	bool IsLoadTrigger = false;

	void TileDatasLoad(LevelArea _Area);
	void SObjectDatasLoad(LevelArea _Area);
	
	void DrawGui_Tilemap();
	void DrawGui_Object();
	void DrawGui_Light();
};


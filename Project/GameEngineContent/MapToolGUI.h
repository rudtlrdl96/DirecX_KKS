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

	inline void SetDepthCount(UINT _DepthCount)
	{
		TilemapDepthCount = _DepthCount;
	}

	inline void SetCurDepth(UINT _CurDepth)
	{
		TilemapCurDepth = _CurDepth;
	}

	inline UINT GetDepthCount() const
	{
		return TilemapDepthCount;
	}

	inline UINT GetCurDepth() const
	{
		return TilemapCurDepth;
	}

	inline void Pushback_SObjectCallbackFunc(std::function<void()> _FunctionPtr)
	{
		SObjectCallback.push_back(_FunctionPtr);
	}

	inline void SetTilemapSize(int2 _Size)
	{
		TilemapSize = _Size;
	}

	inline int2 GetTilemapSize() const
	{
		return TilemapSize;
	}

	bool CheckSaveTrigger();
	bool CheckLoadTrigger();
	bool CheckTilemapReSizeTrigger();
	bool CheckDepthResizeTrigger();

protected:
	
private:
	std::map<LevelArea, std::vector<MapTool_TilemapData>> TileTexDatas;
	std::map<LevelArea, std::vector<MapTool_SObjectData>> SObjectTexDatas;

	LevelArea CurShowAreaTile = LevelArea::None;
	MapToolLevel::MapToolState MapToolType = MapToolLevel::MapToolState::Tilemap;

	std::vector<std::function<void()>> SObjectCallback;

	const char* AreaComboText[6] = {"None" ,"Opening", "Castle", "ForestOfHarmony", "GrandHall", "HolyCourtyard"};
	const char* MapToolComboText[3] = {"Tilemap" ,"Object", "Light"};

	UINT TilemapDepthCount = 0;
	UINT TilemapCurDepth = 0;

	float4 TileSize = float4::Zero;
	int2 TilemapSize = int2::Zero;

	UINT SelectTileIndex = 0;
	SObject_DESC SelectSObject_Desc;
	
	float MinWidth = 0.0f;
	float MaxWitdh = 0.0f;

	bool IsSaveTrigger = false;
	bool IsLoadTrigger = false;
	bool IsTilemapReSizeTrigger = false;
	bool IsDepthResizeTrigger = false;

	void TileDatasLoad(LevelArea _Area);
	void SObjectDatasLoad(LevelArea _Area);
	
	void DrawGui_Tilemap();
	void DrawGui_Object();
	void DrawGui_Light();
};


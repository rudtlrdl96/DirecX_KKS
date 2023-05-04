#include "PrecompileHeader.h"
#include "MapToolGUI.h"

#include <GameEngineCore/GameEngineTexture.h>

#include "TilemapData.h"
#include "StaticObject.h"
#include "ObjectManager.h"

MapToolGUI::MapToolGUI() :
	CurShowAreaTile(LevelArea::Opening)
{
}

MapToolGUI::~MapToolGUI()
{
}

void MapToolGUI::Start()
{
	ImGui::SetWindowSize(GetName().data(), ImVec2(150, 500));

	TileSize = ContentConst::TileSize;

	for (LevelArea LoadLevel = LevelArea::None; LoadLevel <= LevelArea::Shop;)
	{
		TileDatasLoad(LoadLevel);
		SObjectDatasLoad(LoadLevel);

		int NextLevel = static_cast<int>(LoadLevel) + 1;
		LoadLevel = static_cast<LevelArea>(NextLevel);
	}
}

void MapToolGUI::OnGUI(std::shared_ptr<class GameEngineLevel>, float _DeltaTime)
{
	std::shared_ptr<GameEngineTexture> FindTex = GameEngineTexture::Find("DebugBoxTexture.png");

	if (nullptr == FindTex)
	{
		MsgAssert_Rtti<MapToolGUI>(" - 텍스쳐를 찾을 수 없습니다.");
		return;
	}

	if (true == ImGui::Button("Save", ImVec2(60, 20)))
	{
		IsSaveTrigger = true;
		return;
	}

	ImGui::SameLine();

	if (true == ImGui::Button("Load", ImVec2(60, 20)))
	{
		IsLoadTrigger = true;
		return;
	}
		
	ImGui::Spacing();
	ImGui::Spacing();
	ImGui::Spacing();

	static int CurrentAreaIndex = 0;
	ImGui::Combo("Area", &CurrentAreaIndex, AreaComboText, IM_ARRAYSIZE(AreaComboText));

	CurShowAreaTile = (LevelArea)CurrentAreaIndex;

	if (CurShowAreaTile < LevelArea::None || CurShowAreaTile > LevelArea::Shop)
	{
		MsgAssert_Rtti<MapToolGUI>(" - 잘못된 Area 타입이 입력되었습니다");
	}

	ImGui::Spacing();

	static int CurrentMapToolStateIndex = 0;
	ImGui::Combo("MapToolType", &CurrentMapToolStateIndex, MapToolComboText, IM_ARRAYSIZE(MapToolComboText));

	MapToolType = (MapToolLevel::MapToolState)CurrentMapToolStateIndex;

	if (MapToolType < MapToolLevel::MapToolState::Tilemap || MapToolType > MapToolLevel::MapToolState::Light)
	{
		MsgAssert_Rtti<MapToolGUI>(" - 잘못된 MappTool 타입이 입력되었습니다");
	}
	
	switch (MapToolType)
	{
	case MapToolLevel::MapToolState::Tilemap:
		DrawGui_Tilemap();
		break;
	case MapToolLevel::MapToolState::Object:
		DrawGui_Object();
		break;
	case MapToolLevel::MapToolState::Light:
		DrawGui_Light();
		break;
	default:
		break;
	}


}

bool MapToolGUI::CheckSaveTrigger()
{
	bool ReturnValue = IsSaveTrigger;

	IsSaveTrigger = false;

	return ReturnValue;
}

bool MapToolGUI::CheckLoadTrigger()
{
	bool ReturnValue = IsLoadTrigger;

	IsLoadTrigger = false;

	return ReturnValue;
}

void MapToolGUI::DrawGui_Tilemap()
{
	const std::vector<MapTool_TilemapData>& BufferTextureDatas = TileTexDatas[CurShowAreaTile];

	ImGui::Spacing();

	for (size_t i = 0; i < BufferTextureDatas.size(); i++)
	{
		if (0 != i % 4)
		{
			ImGui::SameLine();
		}

		if (true == ImGui::ImageButton((void*)BufferTextureDatas[i].TexturePtr->GetSRV(), ImVec2(TileSize.x, TileSize.y)))
		{
			SelectTileIndex = BufferTextureDatas[i].Data.Index;
		}
	}
}

void MapToolGUI::DrawGui_Object()
{
	const std::vector<MapTool_SObjectData>& BufferTextureDatas = SObjectTexDatas[CurShowAreaTile];

	ImGui::Spacing();

	for (size_t i = 0; i < BufferTextureDatas.size(); i++)
	{
		if (0 != i % 4)
		{
			ImGui::SameLine();
		}

		if (true == ImGui::ImageButton((void*)BufferTextureDatas[i].TexturePtr->GetSRV(), ImVec2(TileSize.x, TileSize.y)))
		{
			SelectSObject_Desc = BufferTextureDatas[i].Data;
		}
	}
}

void MapToolGUI::DrawGui_Light()
{
}

void MapToolGUI::TileDatasLoad(LevelArea _Area)
{
	std::vector<MapTool_TilemapData>& BufferTextureDatas = TileTexDatas[_Area];

	std::vector<TilemapData> CopyDatas;
	ContentDatabase<TilemapData, LevelArea>::CopyGradeDatas(_Area, CopyDatas);

	BufferTextureDatas.reserve(CopyDatas.size());

	for (size_t i = 0; i < CopyDatas.size(); i++)
	{
		std::shared_ptr<GameEngineTexture> FindTex = GameEngineTexture::Find(CopyDatas[i].Name);

		if (nullptr == FindTex)
		{
			MsgAssert_Rtti<MapToolGUI>(" - 타일 데이터의 텍스쳐를 찾을 수 없습니다");
		}
		
		BufferTextureDatas.push_back(MapTool_TilemapData(CopyDatas[i], FindTex));
	}
}

void MapToolGUI::SObjectDatasLoad(LevelArea _Area)
{
	std::vector<MapTool_SObjectData>& BufferTextureDatas = SObjectTexDatas[_Area];

	std::vector<SObject_DESC> CopyDatas;
	ContentDatabase<SObject_DESC, LevelArea>::CopyGradeDatas(_Area, CopyDatas);

	BufferTextureDatas.reserve(CopyDatas.size());

	for (size_t i = 0; i < CopyDatas.size(); i++)
	{
		std::shared_ptr<GameEngineTexture> FindTex = GameEngineTexture::Find(CopyDatas[i].Name);

		if (nullptr == FindTex)
		{
			MsgAssert_Rtti<MapToolGUI>(" - 타일 데이터의 텍스쳐를 찾을 수 없습니다");
		}

		BufferTextureDatas.push_back(MapTool_SObjectData(CopyDatas[i], FindTex));
	}

	if (nullptr == ObjectMgrPtr)
	{
		return;
	}

	if (true == ObjectMgrPtr->IsDeath())
	{
		ObjectMgrPtr = nullptr;
		return;
	}


}

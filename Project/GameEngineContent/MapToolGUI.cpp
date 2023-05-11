#include "PrecompileHeader.h"
#include "MapToolGUI.h"

#include <GameEngineCore/GameEngineTexture.h>

#include "TileMetaData.h"
#include "StaticObject.h"
#include "ObjectManager.h"

MapToolGUI::MapToolGUI() :
	CurShowAreaTile(LevelArea::Opening)
{
}

MapToolGUI::~MapToolGUI()
{
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
	for (size_t i = 0; i < TilemapCallback.size(); i++)
	{
		if (nullptr != TilemapCallback[i])
		{
			TilemapCallback[i]();
		}
	}

	ImGui::Spacing();

	const std::vector<MapTool_TilemapData>& BufferTextureDatas = TileTexDatas[CurShowAreaTile];

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

void MapToolGUI::DrawGui_SObject()
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
			SelectSObjectMetaData = BufferTextureDatas[i].Data;
		}
	}
}

void MapToolGUI::DrawGui_BObject()
{

}

void MapToolGUI::DrawGui_Platform()
{
	static int CurrentPlatformTypeIndex = 0;
	ImGui::Combo("Default New Platform Type", &CurrentPlatformTypeIndex, PlatformTypeCombo, IM_ARRAYSIZE(PlatformTypeCombo));

	BasePlatformType = static_cast<MapPlatform::PlatformType>(CurrentPlatformTypeIndex);

	if (BasePlatformType < MapPlatform::PlatformType::Normal || BasePlatformType > MapPlatform::PlatformType::Half)
	{
		MsgAssert_Rtti<MapToolGUI>(" - 잘못된 Platform 타입이 입력되었습니다");
	}

	ImGui::Spacing();
}

void MapToolGUI::DrawGui_Event()
{
}

void MapToolGUI::DrawGui_Light()
{
}

void MapToolGUI::Callback_Object()
{

	for (size_t i = 0; i < ObjectManagerCallback.size(); i++)
	{
		if (nullptr != ObjectManagerCallback[i])
		{
			ObjectManagerCallback[i]();
		}
	}
}

void MapToolGUI::Callback_Event()
{
	for (size_t i = 0; i < EventManagerCallback.size(); i++)
	{
		if (nullptr != EventManagerCallback[i])
		{
			EventManagerCallback[i]();
		}
	}
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
	if (true == ImGui::Button("Save", ImVec2(60, 25)))
	{
		IsSaveTrigger = true;
		return;
	}

	ImGui::SameLine();

	if (true == ImGui::Button("Load", ImVec2(60, 25)))
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
	case MapToolLevel::MapToolState::SObject:
		Callback_Object();
		DrawGui_SObject();
		break;
	case MapToolLevel::MapToolState::BObject:
		Callback_Object();
		DrawGui_BObject();
		break;
	case MapToolLevel::MapToolState::Platform:
		Callback_Object();
		DrawGui_Platform();
		break;
	case MapToolLevel::MapToolState::Event:
		Callback_Event();
		DrawGui_Event();
		break;
	case MapToolLevel::MapToolState::Light:
		DrawGui_Light();
		break;
	default:
		break;
	}
}

void MapToolGUI::TileDatasLoad(LevelArea _Area)
{
	std::vector<MapTool_TilemapData>& BufferTextureDatas = TileTexDatas[_Area];

	std::vector<TileMetaData> CopyDatas;
	ContentDatabase<TileMetaData, LevelArea>::CopyGradeDatas(_Area, CopyDatas);

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

	std::vector<SObjectMetaData> CopyDatas;
	ContentDatabase<SObjectMetaData, LevelArea>::CopyGradeDatas(_Area, CopyDatas);

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
}

#include "PrecompileHeader.h"
#include "MapToolGUI.h"

#include <GameEngineCore/GameEngineTexture.h>

#include "TileMetaData.h"
#include "MapObject.h"
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

		if (true == ImGui::IsItemHovered())
		{
			ImGui::BeginTooltip();
			ImGui::PushTextWrapPos(ImGui::GetFontSize() * 35.0f);
			ImGui::TextUnformatted(BufferTextureDatas[i].Data.Name.c_str());
			ImGui::PopTextWrapPos();
			ImGui::EndTooltip();
		}
	}
}

void MapToolGUI::DrawGui_Object()
{
	const std::vector<MapTool_ObjectData>& BufferTextureDatas = ObjectTexDatas[CurShowAreaTile];

	ImGui::Spacing();

	for (size_t i = 0; i < BufferTextureDatas.size(); i++)
	{
		if (0 != i % 4)
		{
			ImGui::SameLine();
		}

		if (true == ImGui::ImageButton((void*)BufferTextureDatas[i].TexturePtr->GetSRV(), ImVec2(TileSize.x, TileSize.y)))
		{
			SelectObjectMetaData = BufferTextureDatas[i].Data;
		}

		if (true == ImGui::IsItemHovered())
		{
			ImGui::BeginTooltip();
			ImGui::PushTextWrapPos(ImGui::GetFontSize() * 35.0f);
			ImGui::TextUnformatted(BufferTextureDatas[i].Data.Name.c_str());
			ImGui::PopTextWrapPos();
			ImGui::EndTooltip();
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

void MapToolGUI::DrawGui_Particle()
{
	ImGui::Spacing();
	ImGui::Text("New Create Particle Parameter");

	const char* AreaComboText[5] = { "Opening", "Castle", "ForestOfHarmony", "ForestOfHarmony_Blue", "GrandHall"};
	
	int SelectIndex = static_cast<int>(ParticleAreaMapMetaData.Type);

	ImGui::Combo("New Particle Type", &SelectIndex, AreaComboText, IM_ARRAYSIZE(AreaComboText));
	
	ParticleAreaType InputType = static_cast<ParticleAreaType>(SelectIndex);

	if (InputType != ParticleAreaMapMetaData.Type)
	{
		ParticleAreaMapMetaData.Type = InputType;
	}

	ImGui::Checkbox("New Is Top Spawn", &ParticleAreaMapMetaData.IsTopSpawn);

	float4 MinWind = ParticleAreaMapMetaData.MinWindDir;
	float InputMinWind[4] = { MinWind.x, MinWind.y, MinWind.z, MinWind.w };

	ImGui::DragFloat4("New Min Wind", InputMinWind);

	ParticleAreaMapMetaData.MinWindDir.x = InputMinWind[0];
	ParticleAreaMapMetaData.MinWindDir.y = InputMinWind[1];
	ParticleAreaMapMetaData.MinWindDir.z = InputMinWind[2];
	ParticleAreaMapMetaData.MinWindDir.w = InputMinWind[3];


	float4 MaxWind = ParticleAreaMapMetaData.MaxWindDir;
	float InputMaxWind[4] = { MaxWind.x, MaxWind.y, MaxWind.z, MaxWind.w };

	ImGui::DragFloat4("New Max Wind", InputMaxWind);

	ParticleAreaMapMetaData.MaxWindDir.x = InputMaxWind[0];
	ParticleAreaMapMetaData.MaxWindDir.y = InputMaxWind[1];
	ParticleAreaMapMetaData.MaxWindDir.z = InputMaxWind[2];
	ParticleAreaMapMetaData.MaxWindDir.w = InputMaxWind[3];


	float4 MinRandRot = ParticleAreaMapMetaData.MinRandRot;
	float InputMinRandrot[4] = { MinRandRot.x, MinRandRot.y, MinRandRot.z, MinRandRot.w };

	ImGui::DragFloat4("New Min RandRot", InputMinRandrot);

	ParticleAreaMapMetaData.MinRandRot.x = InputMinRandrot[0];
	ParticleAreaMapMetaData.MinRandRot.y = InputMinRandrot[1];
	ParticleAreaMapMetaData.MinRandRot.z = InputMinRandrot[2];
	ParticleAreaMapMetaData.MinRandRot.w = InputMinRandrot[3];


	float4 MaxRandRot = ParticleAreaMapMetaData.MaxRandRot;
	float InputMaxRandrot[4] = { MaxRandRot.x, MaxRandRot.y, MaxRandRot.z, MaxRandRot.w };

	ImGui::DragFloat4("New Max RandRot", InputMaxRandrot);

	ParticleAreaMapMetaData.MaxRandRot.x = InputMaxRandrot[0];
	ParticleAreaMapMetaData.MaxRandRot.y = InputMaxRandrot[1];
	ParticleAreaMapMetaData.MaxRandRot.z = InputMaxRandrot[2];
	ParticleAreaMapMetaData.MaxRandRot.w = InputMaxRandrot[3];

	ImGui::DragFloat("New Create MinTime", &ParticleAreaMapMetaData.CreateMinTime);
	ImGui::DragFloat("New Create MaxTime", &ParticleAreaMapMetaData.CreateMaxTime);
}

void MapToolGUI::DrawGui_Light()
{
}

void MapToolGUI::DrawGui_Monster()
{
	const std::vector<MapTool_MonsterData>& BufferTextureDatas = MonsterTexDatas[CurShowAreaTile];
	
	ImGui::Spacing();
	
	for (size_t i = 0; i < BufferTextureDatas.size(); i++)
	{
		if (0 != i % 4)
		{
			ImGui::SameLine();
		}
	
		if (true == ImGui::ImageButton((void*)BufferTextureDatas[i].TexturePtr->GetSRV(), ImVec2(TileSize.x, TileSize.y)))
		{
			SelectMonsterMetaData = BufferTextureDatas[i].Data;
		}
	
		if (true == ImGui::IsItemHovered())
		{
			ImGui::BeginTooltip();
			ImGui::PushTextWrapPos(ImGui::GetFontSize() * 35.0f);
			ImGui::TextUnformatted(GameEngineString::AnsiToUTF8(BufferTextureDatas[i].Data.Name).c_str());
			ImGui::PopTextWrapPos();
			ImGui::EndTooltip();
		}
	}
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

void MapToolGUI::Callback_Particle()
{
	for (size_t i = 0; i < ParticleManagerCallback.size(); i++)
	{
		if (nullptr != ParticleManagerCallback[i])
		{
			ParticleManagerCallback[i]();
		}
	}
}

void MapToolGUI::Callback_Monster()
{
	for (size_t i = 0; i < MonsterManagerCallback.size(); i++)
	{
		if (nullptr != MonsterManagerCallback[i])
		{
			MonsterManagerCallback[i]();
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
		ObjectDatasLoad(LoadLevel);
		MonsterDatasLoad(LoadLevel);

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

	if (MapToolType < MapToolLevel::MapToolState::Tilemap || MapToolType > MapToolLevel::MapToolState::Monster)
	{
		MsgAssert_Rtti<MapToolGUI>(" - 잘못된 MapTool 타입이 입력되었습니다");
	}

	switch (MapToolType)
	{
	case MapToolLevel::MapToolState::Tilemap:
		DrawGui_Tilemap();
		break;
	case MapToolLevel::MapToolState::Object:
		Callback_Object();
		DrawGui_Object();
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
	case MapToolLevel::MapToolState::Particle:
		Callback_Particle();
		DrawGui_Particle();
		break;
	case MapToolLevel::MapToolState::Light:
		DrawGui_Light();
		break;
	case MapToolLevel::MapToolState::Monster:
		Callback_Monster();
		DrawGui_Monster();
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

void MapToolGUI::ObjectDatasLoad(LevelArea _Area)
{
	std::vector<MapTool_ObjectData>& BufferTextureDatas = ObjectTexDatas[_Area];

	std::vector<ObjectMetaData> CopyDatas;
	ContentDatabase<ObjectMetaData, LevelArea>::CopyGradeDatas(_Area, CopyDatas);

	BufferTextureDatas.reserve(CopyDatas.size());

	for (size_t i = 0; i < CopyDatas.size(); i++)
	{
		std::shared_ptr<GameEngineTexture> FindTex = GameEngineTexture::Find(CopyDatas[i].Name);

		if (nullptr == FindTex)
		{
			MsgAssert_Rtti<MapToolGUI>(" - 타일 데이터의 텍스쳐를 찾을 수 없습니다");
		}

		BufferTextureDatas.push_back(MapTool_ObjectData(CopyDatas[i], FindTex));
	}
}

void MapToolGUI::MonsterDatasLoad(LevelArea _Area)
{
	std::vector<MapTool_MonsterData>& BufferTextureDatas = MonsterTexDatas[_Area];

	std::vector<MonsterData> CopyDatas;
	ContentDatabase<MonsterData, LevelArea>::CopyGradeDatas(_Area, CopyDatas);

	BufferTextureDatas.reserve(CopyDatas.size());

	for (size_t i = 0; i < CopyDatas.size(); i++)
	{
		std::shared_ptr<GameEngineTexture> FindTex = GameEngineTexture::Find(CopyDatas[i].ImageName);

		if (nullptr == FindTex)
		{
			MsgAssert_Rtti<MapToolGUI>(" - 타일 데이터의 텍스쳐를 찾을 수 없습니다");
		}

		BufferTextureDatas.push_back(MapTool_MonsterData(CopyDatas[i], FindTex));
	}
}

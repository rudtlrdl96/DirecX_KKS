#include "PrecompileHeader.h"
#include "MapToolLevel.h"
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineCamera.h>
#include <GameEngineCore/imgui.h>
#include <GameEngineCore/GameEngineGUI.h>
#include <GameEngineCore/GameEngineSpriteRenderer.h>


#include "Tilemap.h"
#include "ObjectManager.h"
#include "GameEventManager.h"

#include "TilemapPallet.h"
#include "TilemapHoverRenderActor.h"
#include "TilemapOutlineRenderActor.h"
#include "PlayerSpawnPointRenderer.h"

#include "GameEngineActorGUI.h"
#include "MapToolGUI.h"

MapToolLevel::MapToolLevel()
{
}

MapToolLevel::~MapToolLevel()
{
}

void MapToolLevel::Start()
{
	ContentLevel::Start();

	if (false == GameEngineInput::IsKey("ToolActive"))
	{
		GameEngineInput::CreateKey("ToolActive", VK_LBUTTON);
		GameEngineInput::CreateKey("ToolDisable", VK_RBUTTON);


		GameEngineInput::CreateKey("TempSizeUp", VK_OEM_PLUS);
		GameEngineInput::CreateKey("TempSizeDown", VK_OEM_MINUS);

		GameEngineInput::CreateKey("CameraMoveUp", 'W');
		GameEngineInput::CreateKey("CameraMoveDown", 'S');
		GameEngineInput::CreateKey("CameraMoveLeft", 'A');
		GameEngineInput::CreateKey("CameraMoveRight", 'D');

		GameEngineInput::CreateKey("CameraMoveBoost", VK_LSHIFT);
	}

	TilemapOutLinePtr = CreateActor<TilemapOutlineRenderActor>();
	TilemapPtr = CreateActor<Tilemap>();

	TilemapPtr->SetDepth(2);
	TilemapPtr->ResizeTilemap(20, 20);

	ObjectMgrPtr = CreateActor<ObjectManager>();
	ObjectMgrPtr->PlatformDebugOn();

	EventMgrPtr = CreateActor<GameEventManager>();

	TilePalletPtr = CreateActor<TilemapPallet>();
	TilePalletPtr->SetPencleIndex(1000);

	MapToolGuiPtr = GameEngineGUI::FindGUIWindowConvert<MapToolGUI>("MapToolGUI");
	
	if (nullptr == MapToolGuiPtr)
	{
		MsgAssert_Rtti<MapToolLevel>(" - 맵툴 Gui가 생성되지 않았습니다.");
	}

	MapToolGuiPtr->Pushback_ObjectManagerCallback(std::bind(&ObjectManager::ShowGUI, ObjectMgrPtr));
	MapToolGuiPtr->Pushback_TilemapCallback(std::bind(&Tilemap::ShowGUI, TilemapPtr));
	MapToolGuiPtr->Pushback_EventManagerCallback(std::bind(&GameEventManager::ShowGUI, EventMgrPtr));

	ActorGUIPtr = GameEngineGUI::FindGUIWindowConvert<GameEngineActorGUI>("GameEngineActorGUI");

	if (nullptr == ActorGUIPtr)
	{
		MsgAssert_Rtti<MapToolLevel>(" - GameEngineActor Gui가 생성되지 않았습니다.");
	}

	TilemapHoverPtr = CreateActor<TilemapHoverRenderActor>();
	TilemapOutLinePtr->SetSize(TilemapPtr->GetSize() * ContentConst::TileSize);

	PlayerSpawnRender = CreateActor<PlayerSpawnPointRenderer>();
}

void MapToolLevel::Update(float _DeltaTime)
{
	ContentLevel::Update(_DeltaTime);

	MapToolType = MapToolGuiPtr->GetMapToolState();

	TilePalletPtr->SetActiveCursor(false);
	TilemapHoverPtr->HoverOff();

	float4 SpawnPos = EventMgrPtr->GetSpawnPoint();
	PlayerSpawnRender->GetTransform()->SetWorldPosition(SpawnPos);

	switch (MapToolType)
	{
	case MapToolState::Tilemap:
	{
		Update_Tilemap(_DeltaTime);
		break;
	}
	case MapToolState::SObject:
	{
		Update_SObject(_DeltaTime);		
		break;
	}

	case MapToolState::BObject:
	{
		Update_BObject(_DeltaTime);
		break;
	}
	case MapToolState::Platform:
	{
		Update_Platfrom(_DeltaTime);	
		break;
	}
	case MapToolState::Event:
		Update_Event(_DeltaTime);
		break;
	case MapToolState::Light:
		break;
	default:
		break;
	}

	if (true == MapToolGuiPtr->CheckSaveTrigger())
	{
		Save();
	}

	if (true == MapToolGuiPtr->CheckLoadTrigger())
	{
		Load();
	}


	CameraMoveFunction(_DeltaTime);
}

void MapToolLevel::LevelChangeStart()
{
	if (nullptr == MapToolGuiPtr)
	{
		MsgAssert_Rtti<MapToolLevel>(" - MapTool Gui를 찾을 수 없습니다");
		return;
	}

	MapToolGuiPtr->On();

	if (nullptr == ActorGUIPtr)
	{
		MsgAssert_Rtti<MapToolLevel>(" - GameEngineActor Gui를 찾을 수 없습니다");
		return;
	}

	ActorGUIPtr->On();
}

void MapToolLevel::LevelChangeEnd()
{
	if (nullptr == MapToolGuiPtr)
	{
		MsgAssert_Rtti<MapToolLevel>(" - MapTool Gui를 찾을 수 없습니다");
		return;
	}

	MapToolGuiPtr->Off();

	if (nullptr == ActorGUIPtr)
	{
		MsgAssert_Rtti<MapToolLevel>(" - GameEngineActor Gui를 찾을 수 없습니다");
		return;
	}

	ActorGUIPtr->SetTarget(nullptr);
	ActorGUIPtr->Off();
}

void MapToolLevel::Save()
{
	std::string Path = ContentFunc::GetSaveFilePath();

	if ("" == Path)
	{
		return;
	}

	GameEngineSerializer SaveSerializer;
	SaveSerializer.BufferResize(2^17);

	TilemapPtr->SaveBin(SaveSerializer);
	ObjectMgrPtr->SaveBin(SaveSerializer);
	EventMgrPtr->SaveBin(SaveSerializer);

	GameEngineFile SaveFile = GameEngineFile(Path);
	SaveFile.SaveBin(SaveSerializer);
}

void MapToolLevel::Load()
{
	std::string Path = ContentFunc::GetOpenFilePath();

	if ("" == Path)
	{
		return;
	}

	GameEngineFile LoadFile = GameEngineFile(Path);

	GameEngineSerializer SaveSerializer;
	SaveSerializer.BufferResize(131072);
	LoadFile.LoadBin(SaveSerializer);

	TilemapPtr->LoadBin(SaveSerializer);
	ObjectMgrPtr->LoadBin(SaveSerializer);
	EventMgrPtr->LoadBin(SaveSerializer);

	TilemapOutLinePtr->SetSize(TilemapPtr->GetSize() * ContentConst::TileSize);
}


void MapToolLevel::CameraMoveFunction(float _DeltaTime)
{

	float CurFrameCameraSpeed = CameraSpeed * _DeltaTime;

	if (GameEngineInput::IsPress("CameraMoveBoost"))
	{
		CurFrameCameraSpeed *= 2.0f;
	}

	if (GameEngineInput::IsDown("TempSizeUp"))
	{
		TilemapPtr->ResizeTilemap(TilemapPtr->SizeX() + 1, TilemapPtr->SizeY() + 1);
	}

	if (GameEngineInput::IsDown("TempSizeDown"))
	{
		TilemapPtr->ResizeTilemap(TilemapPtr->SizeX() - 1, TilemapPtr->SizeY() - 1);
	}

	if (GameEngineInput::IsPress("CameraMoveUp"))
	{
		GetMainCamera()->GetTransform()->AddLocalPosition(float4::Up * CurFrameCameraSpeed);
	}
	else if (GameEngineInput::IsPress("CameraMoveDown"))
	{
		GetMainCamera()->GetTransform()->AddLocalPosition(float4::Down * CurFrameCameraSpeed);
	}
	if (GameEngineInput::IsPress("CameraMoveLeft"))
	{
		GetMainCamera()->GetTransform()->AddLocalPosition(float4::Left * CurFrameCameraSpeed);
	}
	else if (GameEngineInput::IsPress("CameraMoveRight"))
	{
		GetMainCamera()->GetTransform()->AddLocalPosition(float4::Right * CurFrameCameraSpeed);
	}
}


void MapToolLevel::Update_Tilemap(float _DeltaTime)
{
	ActorGUIPtr->SetTarget(nullptr);
	TilePalletPtr->SetActiveCursor(true);
	TilePalletPtr->On();

	TilemapOutLinePtr->SetSize(TilemapPtr->GetSize() * ContentConst::TileSize);

	float4 WorldMousePos = GetMousePos();
	WorldMousePos.z = 0.0f;

	int2 MouseIndex = TilemapPtr->GetTileIndex(WorldMousePos);

	UINT CastingIndexX = static_cast<UINT>(MouseIndex.x);
	UINT CastingIndexY = static_cast<UINT>(MouseIndex.y);

	TilePalletPtr->GetTransform()->SetWorldPosition(WorldMousePos);

	if (MouseIndex.x >= 0 && MouseIndex.y >= 0 && false == TilemapPtr->IsOver(MouseIndex.x, MouseIndex.y))
	{
		float4 TileIndexPos = TilemapPtr->GetTilePos(CastingIndexX, CastingIndexY);
		TileIndexPos.z = -50;

		TilemapHoverPtr->HoverOn();
		TilemapHoverPtr->GetTransform()->SetWorldPosition(TileIndexPos);
	}
	else
	{
		return;
	}

	if (false == ImGui::GetIO().WantCaptureMouse &&
		(true == GameEngineInput::IsPress("ToolActive") ||
			true == GameEngineInput::IsPress("ToolDisable")))
	{
		UINT TilemapCurDepthCount = TilemapPtr->GetCurDepth();

		if (true == GameEngineInput::IsPress("ToolActive"))
		{
			TilemapPtr->ChangeData(TilemapCurDepthCount, MouseIndex.x, MouseIndex.y, TilePalletPtr->GetPencleIndex());
		}
		else if (true == GameEngineInput::IsPress("ToolDisable"))
		{
			TilemapPtr->ChangeData(TilemapCurDepthCount, MouseIndex.x, MouseIndex.y, 0);
		}
	}
}

void MapToolLevel::Update_SObject(float _DeltaTime)
{
	ObjectMgrPtr->SetGuiType(ObjectManager::GuiType::SObject);

	std::shared_ptr<BaseContentActor> GetActorPtr = ObjectMgrPtr->GetSelectSObject();

	if (nullptr == GetActorPtr)
	{
		ActorGUIPtr->SetTarget(nullptr);
	}
	else
	{
		ActorGUIPtr->SetTarget(GetActorPtr->GetTransform(), { std::bind(&BaseContentActor::ShowGUI, GetActorPtr) });
	}


	if (false == ImGui::GetIO().WantCaptureMouse && true == GameEngineInput::IsDown("ToolActive"))
	{
		float4 TestMousePos = GetMousePos();
		TestMousePos.z = 0;

		SObjectMetaData NewObjectMetaData = MapToolGuiPtr->GetSelectSObject();
		NewObjectMetaData.Pos = TestMousePos;

		ObjectMgrPtr->CreateStaticObject(NewObjectMetaData);
	}
}

void MapToolLevel::Update_BObject(float _DeltaTime)
{

	ObjectMgrPtr->SetGuiType(ObjectManager::GuiType::BObject);
}

void MapToolLevel::Update_Platfrom(float _DeltaTime)
{
	ObjectMgrPtr->SetGuiType(ObjectManager::GuiType::Platform);

	static float4 PlatformStartPos = float4::Zero;
	static float4 PlatformEndPos = float4::Zero;

	if (false == ImGui::GetIO().WantCaptureMouse)
	{
		if (true == GameEngineInput::IsDown("ToolActive"))
		{
			PlatformStartPos = GetMousePos();
		}
		else if (true == GameEngineInput::IsUp("ToolActive"))
		{
			PlatformEndPos = GetMousePos();
			MapPlatform::PlatformMetaData NewMetaData;

			NewMetaData.Type = MapToolGuiPtr->GetPlatformType();
			NewMetaData.Pos = (PlatformStartPos + PlatformEndPos) * 0.5f;
			NewMetaData.Pos.z = -100;
			NewMetaData.Rot = float4::Zero;
			NewMetaData.Scale = float4(
				std::abs(PlatformStartPos.x - PlatformEndPos.x),
				std::abs(PlatformStartPos.y - PlatformEndPos.y),
				1,
				1);

			ObjectMgrPtr->CreatePaltform(NewMetaData);
		}	
	}
}

void MapToolLevel::Update_Event(float _DeltaTime)
{

}

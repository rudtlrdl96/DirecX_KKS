#include "PrecompileHeader.h"
#include "BattleDebugLevel.h"
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineCamera.h>
#include "DebugSpriteActor.h"
#include "Tilemap.h"
#include "MultiBackground.h"
#include "ObjectManager.h"
#include "GameEngineActorGUI.h"

BattleDebugLevel::BattleDebugLevel()
{

}

BattleDebugLevel::~BattleDebugLevel()
{
}

void BattleDebugLevel::Start()
{
	ContentLevel::Start();

	GameEngineActorGUIPtr = GameEngineGUI::FindGUIWindowConvert<GameEngineActorGUI>("GameEngineActorGUI");

	if (false == GameEngineInput::IsKey("CameraShake"))
	{
		GameEngineInput::CreateKey("CameraShake", VK_SPACE);		
	}
		
	DebugBackground = CreateActor<MultiBackground>();

	DeubgObject = CreateActor<ObjectManager>();

	DebugTilemap = CreateActor<Tilemap>();
	DebugTilemap->SetDepth(1); 
	DebugTilemap->ResizeTilemap(80, 12);

	DebugTilemap->ChangeData(0, 0, 79, 0, 11, 0);
	DebugTilemap->ChangeData(0, 0, 79, 0, 0, 2);

	TilemapMetaData TilemapMeta = DebugTilemap->GetTilemapMetaData();

	MainCamCtrl.SetMinHeight(TilemapMeta.Bottom);
	MainCamCtrl.SetMaxHeight(TilemapMeta.Top);

	MainCamCtrl.SetMinWidth(TilemapMeta.Left);

	float4 CenterPos = float4((TilemapMeta.Left + TilemapMeta.Right) * 0.5f,
		(TilemapMeta.Top + TilemapMeta.Bottom) * 0.5f);

	DebugBackground->GetTransform()->SetWorldPosition(CenterPos);
	DeubgObject->GetTransform()->SetWorldPosition(CenterPos);

	DeubgActor = CreateActor<DebugSpriteActor>();
	DeubgActor->GetTransform()->SetWorldPosition(float4(100, 0 , 0));
	DeubgActor->UnMove = true;

	DeubgChildActor = CreateActor<DebugSpriteActor>();
	DeubgChildActor->GetTransform()->SetParent(DeubgActor->GetTransform());
	DeubgChildActor->GetTransform()->SetLocalPosition(float4(100, 0, 0));

	MainCamCtrl.SetLookatTarget(DeubgActor);

	//
	//	GameEngineDirectory Directory;
	//	Directory.MoveParentToDirectory("Resources");
	//	Directory.Move("Resources");
	//	Directory.Move("Data");
	//	Directory.Move("Map");
	//	Directory.Move("Castle");
	//
	//	GameEnginePath Path = Directory.GetPlusFileName("TilemapData.txt");
	//
	//	GameEngineFile SaveFile = GameEngineFile(Path.GetFullPath());
	//	GameEngineSerializer SaveSer = GameEngineSerializer();
	//	SaveSer.BufferResize(51200);
	//
	//	//DebugTilemap->SaveBin(SaveSer);
	//	//SaveFile.SaveBin(SaveSer);
	//
	//	//SaveFile.LoadBin(SaveSer);
	//	//DebugTilemap->LoadBin(SaveSer);
	//
}

void BattleDebugLevel::Update(float _DeltaTime)
{
	ContentLevel::Update(_DeltaTime);

	if (true == GameEngineInput::IsPress("CameraShake"))
	{
		MainCamCtrl.CameraShake( 4.0f, 30.0f, 40);
	}

	DebugBackground->UpdateTargetPos(_DeltaTime, MainCamCtrl.GetCameraPos());	
}

void BattleDebugLevel::LevelChangeStart()
{
	if (nullptr == GameEngineActorGUIPtr)
	{
		MsgAssert_Rtti<BattleDebugLevel>(" - GameEngineActor GUI를 찾을 수 없습니다");
	}

	GameEngineActorGUIPtr->On();
	GameEngineActorGUIPtr->SetTarget(DeubgChildActor->GetTransform());
}

void BattleDebugLevel::LevelChangeEnd()
{
	if (nullptr == GameEngineActorGUIPtr)
	{
		MsgAssert_Rtti<BattleDebugLevel>(" - GameEngineActor GUI를 찾을 수 없습니다");
	}

	GameEngineActorGUIPtr->Off();
	GameEngineActorGUIPtr->SetTarget(nullptr);
}

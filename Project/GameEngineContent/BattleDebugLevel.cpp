#include "PrecompileHeader.h"
#include "BattleDebugLevel.h"
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineCamera.h>

#include "BoneSkull.h"
#include "Tilemap.h"
#include "MultiBackground.h"
#include "ObjectManager.h"
#include "ParticleManager.h"

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

	TilemapMeta.Top = GameEngineWindow::GetScreenSize().y;
	TilemapMeta.Bottom = 0;
	TilemapMeta.Left = 0;
	TilemapMeta.Right = GameEngineWindow::GetScreenSize().x;

	DebugParticleMgr = CreateActor<ParticleManager>();

	DebugParticleMgr->CreateMapParticleArea({
	.Type = ParticleAreaType::Opening,
	.Center = GameEngineWindow::GetScreenSize().half(),
	.Size = GameEngineWindow::GetScreenSize(),
	.IsTopSpawn = true,
	.MinWindDir = float4(-30.0f, -10.0f, 0.0f),
	.MaxWindDir = float4(30.0f, -20.0f, 0.0f),
	.MinRandRot = float4::Zero,
	.MaxRandRot = float4(100.0f, 100.0f, 100.0f),
	.CreateMinTime = 2.0f,
	.CreateMaxTime = 3.5f });

	DebugParticleMgr->CreateMapParticleArea({
		.Type = ParticleAreaType::Opening,
		.Center = GameEngineWindow::GetScreenSize().half(),
		.Size = GameEngineWindow::GetScreenSize(),
		.IsTopSpawn = false,
		.MinWindDir = float4(-30.0f, 10.0f, 0.0f),
		.MaxWindDir = float4(30.0f, 30.0f, 0.0f),
		.MinRandRot = float4::Zero,
		.MaxRandRot = float4(100.0f, 100.0f, 100.0f),
		.CreateMinTime = 0.4f, 
		.CreateMaxTime = 1.0f});

	MainCamCtrl.SetMinHeight(TilemapMeta.Bottom);
	MainCamCtrl.SetMaxHeight(TilemapMeta.Top);

	MainCamCtrl.SetMinWidth(TilemapMeta.Left);
	MainCamCtrl.SetMaxWidth(TilemapMeta.Right);

	DebugSkull = CreateActor<BoneSkull>();
	DebugSkull->GetTransform()->SetLocalPosition(float4(128, 128 , 0));


	MainCamCtrl.SetLookatTarget(DebugSkull);

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
	GameEngineActorGUIPtr->SetTarget(DebugSkull->GetTransform());
	GameEngineActorGUIPtr->EditorGui(std::bind(&Rigidbody2D::ShowGUI, DebugSkull->GetDashRigidbody()));
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

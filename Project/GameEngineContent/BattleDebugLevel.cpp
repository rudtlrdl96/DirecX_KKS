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

	//{
	//	Background::BG_DESC BgDesc;
	//
	//	BgDesc.TextureName = "Castle_BackImage_InSky.png";
	//	BgDesc.Center = { 0.0f, 0.0f, 0, 0 };
	//	BgDesc.Ratio = 0.0f;
	//	BgDesc.Size = float4(960.0f, 350.0f, 0, 0);
	//	BgDesc.Size *= 4.0f;
	//	BgDesc.Animation = false;
	//	BgDesc.AnimationSpeed = 0.0f;
	//	BgDesc.Color = float4(0.03f, 0, 0.2f, 1.0f);
	//
	//	DebugBackground->CreateBackground(BgDesc, 11);
	//}
	//
	//{
	//	Background::BG_DESC BgDesc;
	//
	//	BgDesc.TextureName = "Castle_BackImage_Star.png";
	//	BgDesc.Center = { 0.0f, 0.0f, 0, 0 };
	//	BgDesc.Ratio = 0.2f;
	//	BgDesc.Size = float4(927.0f, 347.0f, 0, 0);
	//	BgDesc.Size *= 2.5f;
	//	BgDesc.Animation = false;
	//	BgDesc.AnimationSpeed = 0.0f;
	//
	//	DebugBackground->CreateBackground(BgDesc, 10);
	//}
	//
	//{
	//	Background::BG_DESC BgDesc;
	//
	//	BgDesc.TextureName = "Castle_BackImage_InSmallCloud.png";
	//	BgDesc.Center = { 0.0f, 100.0f, 0, 0 };
	//	BgDesc.Ratio = 0.2f;
	//	BgDesc.Size = float4(1521.6f, 552.0f, 0, 0);
	//	BgDesc.Animation = true;
	//	BgDesc.AnimationSpeed = 25.0f;
	//
	//	DebugBackground->CreateBackground(BgDesc, 9);
	//}
	//
	//{
	//	Background::BG_DESC BgDesc;
	//
	//	BgDesc.TextureName = "Castle_BackImage_InBigCloud.png";
	//	BgDesc.Center = { 500.0f, 20.0f, 0, 0 };
	//	BgDesc.Ratio = 0.1f;
	//	BgDesc.Size = float4(2110.0f, 422.5f, 0, 0);
	//	BgDesc.Animation = false;
	//	BgDesc.AnimationSpeed = 0.0f;
	//
	//	DebugBackground->CreateBackground(BgDesc, 8);
	//}
	//
	//{
	//	Background::BG_DESC BgDesc;
	//
	//	BgDesc.TextureName = "Castle_BackImage_CastleWall.png";
	//	BgDesc.Center = { 700.0f, 50.0f, 0, 0 };
	//	BgDesc.Ratio = 0.3f;
	//	BgDesc.Size = float4(2400.0f, 875.0f, 0, 0);
	//	BgDesc.Animation = false;
	//	BgDesc.AnimationSpeed = 0.0f;
	//	BgDesc.Color = -float4(0.1f, 0.1f, 0.1f, 1.0f);
	//
	//	DebugBackground->CreateBackground(BgDesc, 7);
	//}
	//
	//{
	//	Background::BG_DESC BgDesc;
	//
	//	BgDesc.TextureName = "Castle_BackImage_Chandelier.png";
	//	BgDesc.Center = {780.0f, 220.0f, 0, 0 };
	//	BgDesc.Ratio = 0.35f;
	//	BgDesc.Size = float4(1050.0f, 304.0f, 0, 0);
	//	BgDesc.Size *= 2.0f;
	//	BgDesc.Animation = false;
	//	BgDesc.AnimationSpeed = 0.0f;
	//	BgDesc.Color = float4(0.07f, 0.05f, 0.12f, 1.0f);
	//
	//	DebugBackground->CreateBackground(BgDesc, 6);
	//}

	DeubgObject = CreateActor<ObjectManager>();

	{
		SObject_DESC Desc = ContentDatabase<SObject_DESC, LevelArea>::GetData(
			GameEngineString::ToUpper("Castle_StaticObject_Wall00.png"));
		
		Desc.Pos = float4(-1900.0f, 0, 0, 0);
		Desc.Size *= 2.5f;
		Desc.Size.z = 1;
		Desc.Color = float4(0, 0, 0.05f, 1.0f);

		DeubgObject->CreateStaticObject(Desc);
	}

	{
		SObject_DESC Desc = ContentDatabase<SObject_DESC, LevelArea>::GetData(
			GameEngineString::ToUpper("Castle_StaticObject_Wall01.png"));

		Desc.Pos = float4(-2160, 0, 0, 0);
		Desc.Size *= 2.5f;
		Desc.Size.z = 1;
		Desc.Color = float4(0, 0, 0.05f, 1.0f);

		DeubgObject->CreateStaticObject(Desc);
	}	

	{
		SObject_DESC Desc = ContentDatabase<SObject_DESC, LevelArea>::GetData(
			GameEngineString::ToUpper("Castle_StaticObject_Wall04.png"));
		
		Desc.Pos = float4(-2420, 0, 0, 0);
		Desc.Size *= 2.5f;
		Desc.Size.z = 1;
		Desc.Color = float4(0, 0, 0.05f, 1.0f);

		DeubgObject->CreateStaticObject(Desc);
	}

	DebugTilemap = CreateActor<Tilemap>();
	DebugTilemap->SetDepth(1); 
	DebugTilemap->ResizeTilemap(80, 12);

	DebugTilemap->ChangeData(0, 0, 79, 0, 11, 0);
	DebugTilemap->ChangeData(0, 0, 79, 0, 0, 2);

	Tilemap_Meta TilemapDESC = DebugTilemap->GetTilemap_DESC();

	MainCamCtrl.SetMinHeight(TilemapDESC.Bottom);
	MainCamCtrl.SetMaxHeight(TilemapDESC.Top);

	MainCamCtrl.SetMinWidth(TilemapDESC.Left);

	float4 CenterPos = float4((TilemapDESC.Left + TilemapDESC.Right) * 0.5f,
		(TilemapDESC.Top + TilemapDESC.Bottom) * 0.5f);

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

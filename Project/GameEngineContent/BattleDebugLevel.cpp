#include "PrecompileHeader.h"
#include "BattleDebugLevel.h"
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineCamera.h>
#include "DebugSpriteActor.h"
#include "Tilemap.h"
#include "MultiBackground.h"
#include "ObjectManager.h"

BattleDebugLevel::BattleDebugLevel()
{

}

BattleDebugLevel::~BattleDebugLevel()
{
}

void BattleDebugLevel::Start()
{
	ContentLevel::Start();

	if (false == GameEngineInput::IsKey("CameraMoveX++"))
	{
		GameEngineInput::CreateKey("CameraMoveX++", 'L');
		GameEngineInput::CreateKey("CameraMoveY++", 'I');
		GameEngineInput::CreateKey("CameraMoveX--", 'J');
		GameEngineInput::CreateKey("CameraMoveY--", 'K');
		GameEngineInput::CreateKey("CameraShake", VK_SPACE);		
	}
		
	DebugBackground = CreateActor<MultiBackground>();

	{
		Background::BG_DESC BgDesc;

		BgDesc.TextureName = "Castle_BackImage_InSky.png";
		BgDesc.Center = { 0.0f, 0.0f, 0, 0 };
		BgDesc.Ratio = 0.0f;
		BgDesc.Size = float4(960.0f, 350.0f, 0, 0);
		BgDesc.Size *= 4.0f;
		BgDesc.Animation = false;
		BgDesc.AnimationSpeed = 0.0f;
		BgDesc.Color = float4(0.03f, 0, 0.2f, 0);

		DebugBackground->CreateBackground(BgDesc, 9);
	}

	{
		Background::BG_DESC BgDesc;

		BgDesc.TextureName = "Castle_BackImage_Star.png";
		BgDesc.Center = { 0.0f, 0.0f, 0, 0 };
		BgDesc.Ratio = 0.2f;
		BgDesc.Size = float4(927.0f, 347.0f, 0, 0);
		BgDesc.Size *= 2.5f;
		BgDesc.Animation = false;
		BgDesc.AnimationSpeed = 0.0f;

		DebugBackground->CreateBackground(BgDesc, 8);
	}

	{
		Background::BG_DESC BgDesc;

		BgDesc.TextureName = "Castle_BackImage_InSmallCloud.png";
		BgDesc.Center = { 0.0f, 100.0f, 0, 0 };
		BgDesc.Ratio = 0.2f;
		BgDesc.Size = float4(1521.6f, 552.0f, 0, 0);
		BgDesc.Animation = true;
		BgDesc.AnimationSpeed = 25.0f;

		DebugBackground->CreateBackground(BgDesc, 7);
	}

	{
		Background::BG_DESC BgDesc;

		BgDesc.TextureName = "Castle_BackImage_InBigCloud.png";
		BgDesc.Center = { 500.0f, 20.0f, 0, 0 };
		BgDesc.Ratio = 0.1f;
		BgDesc.Size = float4(2110.0f, 422.5f, 0, 0);
		BgDesc.Animation = false;
		BgDesc.AnimationSpeed = 0.0f;

		DebugBackground->CreateBackground(BgDesc, 6);
	}
	
	{
		Background::BG_DESC BgDesc;

		BgDesc.TextureName = "Castle_BackImage_CastleWall.png";
		BgDesc.Center = { 700.0f, 50.0f, 0, 0 };
		BgDesc.Ratio = 0.3f;
		BgDesc.Size = float4(2400.0f, 875.0f, 0, 0);
		BgDesc.Animation = false;
		BgDesc.AnimationSpeed = 0.0f;
		BgDesc.Color = -float4(0.1f, 0.1f, 0.1f, 0);

		DebugBackground->CreateBackground(BgDesc, 5);
	}

	{
		Background::BG_DESC BgDesc;

		BgDesc.TextureName = "Castle_BackImage_Chandelier.png";
		BgDesc.Center = {780.0f, 220.0f, 0, 0 };
		BgDesc.Ratio = 0.35f;
		BgDesc.Size = float4(1050.0f, 304.0f, 0, 0);
		BgDesc.Size *= 2.0f;
		BgDesc.Animation = false;
		BgDesc.AnimationSpeed = 0.0f;
		BgDesc.Color = float4(0.07f, 0.05f, 0.12f, 0);

		DebugBackground->CreateBackground(BgDesc, 4);
	}

	DeubgObject = CreateActor<ObjectManager>();

	{
		SObject_DESC Desc = ContentDatabase<SObject_DESC, LevelType>::GetData(
			GameEngineString::ToUpper("Castle_StaticObject_Wall00.png"));
		
		Desc.Pos = float4(-1900.0f, 0, 0, 0);
		Desc.Size *= 2.5f;
		Desc.Size.z = 1;
		Desc.Color = float4(0, 0, 0.05f, 0);

		DeubgObject->CreateStaticObject(Desc);
	}

	{
		SObject_DESC Desc = ContentDatabase<SObject_DESC, LevelType>::GetData(
			GameEngineString::ToUpper("Castle_StaticObject_Wall01.png"));

		Desc.Pos = float4(-2160, 0, 0, 0);
		Desc.Size *= 2.5f;
		Desc.Size.z = 1;
		Desc.Color = float4(0, 0, 0.05f, 0);

		DeubgObject->CreateStaticObject(Desc);
	}	
	{
		SObject_DESC Desc = ContentDatabase<SObject_DESC, LevelType>::GetData(
			GameEngineString::ToUpper("Castle_StaticObject_Wall04.png"));
		
		Desc.Pos = float4(-2420, 0, 0, 0);
		Desc.Size *= 2.5f;
		Desc.Size.z = 1;
		Desc.Color = float4(0, 0, 0.05f, 0);

		DeubgObject->CreateStaticObject(Desc);
	}

	DebugTilemap = CreateActor<Tilemap>();
	DebugTilemap->ResizeTilemap(80, 12, 0);

	DebugTilemap->ChangeData(0, 0, 79, 0, 11, 0);
	DebugTilemap->ChangeData(0, 0, 79, 0, 0, 2);

	Tilemap_DESC TilemapDESC = DebugTilemap->GetTilemap_DESC(0);

	MainCamCtrl.SetMinHeight(TilemapDESC.Bottom);
	MainCamCtrl.SetMaxHeight(TilemapDESC.Top);

	MainCamCtrl.SetMinWidth(TilemapDESC.Left);

	float4 CenterPos = float4((TilemapDESC.Left + TilemapDESC.Right) * 0.5f,
		(TilemapDESC.Top + TilemapDESC.Bottom) * 0.5f);

	DebugBackground->GetTransform()->SetWorldPosition(CenterPos);
	DeubgObject->GetTransform()->SetWorldPosition(CenterPos);

	DeubgActor = CreateActor<DebugSpriteActor>();
	MainCamCtrl.SetLookatTarget(DeubgActor);
}

void BattleDebugLevel::Update(float _DeltaTime)
{
	ContentLevel::Update(_DeltaTime);

	if (true == GameEngineInput::IsPress("CameraMoveX++"))
	{
		MainCamCtrl.AddCamPos({_DeltaTime * CameraSpeed, 0, 0, 0});
	}
	else if (true == GameEngineInput::IsPress("CameraMoveX--"))
	{
		MainCamCtrl.AddCamPos({-_DeltaTime * CameraSpeed, 0, 0, 0});
	}
	else if (true == GameEngineInput::IsPress("CameraMoveY++"))
	{
		MainCamCtrl.AddCamPos({0,_DeltaTime * CameraSpeed, 0, 0});
	}
	else if (true == GameEngineInput::IsPress("CameraMoveY--"))
	{
		MainCamCtrl.AddCamPos({0, -_DeltaTime * CameraSpeed, 0, 0});
	}
	else if (true == GameEngineInput::IsPress("CameraShake"))
	{
		MainCamCtrl.CameraShake( 4.0f, 30.0f, 40);
	}

	DebugBackground->UpdateTargetPos(_DeltaTime, MainCamCtrl.GetCameraPos());
}
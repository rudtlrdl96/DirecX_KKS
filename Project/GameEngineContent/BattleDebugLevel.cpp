#include "PrecompileHeader.h"
#include "BattleDebugLevel.h"
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineCamera.h>
#include "DebugSpriteActor.h"
#include "Tilemap.h"
#include "MultiBackground.h"

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
		BgDesc.Center = { 1280.0f, 384.0f, 0, 0 };
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
		BgDesc.Center = { 1280.0f, 384.0f, 0, 0 };
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
		BgDesc.Center = { 1280.0f, 684.0f, 0, 0 };
		BgDesc.Ratio = 0.2f;
		BgDesc.Size = float4(1521.6f, 552.0f, 0, 0);
		BgDesc.Animation = true;
		BgDesc.AnimationSpeed = 25.0f;

		DebugBackground->CreateBackground(BgDesc, 7);
	}

	{
		Background::BG_DESC BgDesc;

		BgDesc.TextureName = "Castle_BackImage_InBigCloud.png";
		BgDesc.Center = { 1280.0f, -700.0f, 0, 0 };
		BgDesc.Ratio = 0.1f;
		BgDesc.Size = float4(2110.0f, 422.5f, 0, 0);
		BgDesc.Animation = false;
		BgDesc.AnimationSpeed = 0.0f;

		DebugBackground->CreateBackground(BgDesc, 6);
	}
	
	{
		Background::BG_DESC BgDesc;

		BgDesc.TextureName = "Castle_BackImage_CastleWall.png";
		BgDesc.Center = { 1680.0f, 200.0f, 0, 0 };
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
		BgDesc.Center = {1280.0f, 550.0f, 0, 0 };
		BgDesc.Ratio = 0.5f;
		BgDesc.Size = float4(1050.0f, 238.6f, 0, 0);
		BgDesc.Size *= 2.0f;
		BgDesc.Animation = false;
		BgDesc.AnimationSpeed = 0.0f;
		BgDesc.Color = float4(0.07f, 0.05f, 0.12f, 0);

		DebugBackground->CreateBackground(BgDesc, 4);
	}

	DebugTilemap = CreateActor<Tilemap>();
	DebugTilemap->ResizeTilemap(40, 12, 0);

	DebugTilemap->ChangeData(0, 0, 39, 0, 11, 0);
	DebugTilemap->ChangeData(0, 0, 39, 0, 0, 2);

	Tilemap_DESC TilemapDESC = DebugTilemap->GetTilemap_DESC(0);

	MainCamCtrl.SetMinHeight(TilemapDESC.Bottom);
	MainCamCtrl.SetMaxHeight(TilemapDESC.Top);

	MainCamCtrl.SetMinWidth(TilemapDESC.Left);
	MainCamCtrl.SetMaxWidth(TilemapDESC.Right);

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
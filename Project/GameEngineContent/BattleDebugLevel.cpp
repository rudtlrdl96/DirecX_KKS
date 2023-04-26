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

	DebugTilemap = CreateActor<Tilemap>();
	DebugTilemap->ResizeTilemap(40, 12, 0);

	DebugTilemap->ChangeData(0, 0, 39, 0, 11, 1);
	DebugTilemap->ChangeData(0, 0, 39, 0, 0, 2);

	Tilemap_DESC TilemapDESC = DebugTilemap->GetTilemap_DESC(0);

	MainCamCtrl.SetMinHeight(TilemapDESC.Bottom);
	MainCamCtrl.SetMaxHeight(TilemapDESC.Top);

	MainCamCtrl.SetMinWidth(TilemapDESC.Left);
	MainCamCtrl.SetMaxWidth(TilemapDESC.Right);

	DebugBackground = CreateActor<MultiBackground>();

	{
		Background::BG_DESC BgDesc;

		std::shared_ptr<GameEngineTexture> Tex = GameEngineTexture::Find("Castle_BackImage_InSmallCloud");

		BgDesc.TextureName = "Castle_BackImage_InSmallCloud.png";
		BgDesc.Center = { (TilemapDESC.Left + TilemapDESC.Right) * 0.5f, (TilemapDESC.Top + TilemapDESC.Bottom) * 0.5f, 0, 0 };
		BgDesc.Ratio = 0.2f;
		BgDesc.Size = float4(3804.0f, 1380.0f, 0, 0);
		BgDesc.Animation = true;
		BgDesc.AnimationSpeed = 50.0f;

		DebugBackground->CreateBackground(BgDesc, 7);
	}

	{
		Background::BG_DESC BgDesc;

		std::shared_ptr<GameEngineTexture> Tex = GameEngineTexture::Find("Castle_BackImage_InSmallCloud");

		BgDesc.TextureName = "Castle_BackImage_InBigCloud.png";
		BgDesc.Center = { (TilemapDESC.Left + TilemapDESC.Right) * 0.5f, (TilemapDESC.Top + TilemapDESC.Bottom) * 0.5f, 0, 0 };
		BgDesc.Ratio = 0.1f;
		BgDesc.Size = float4(2110.0f, 422.5f, 0, 0);
		BgDesc.Animation = false;
		BgDesc.AnimationSpeed = 0.0f;

		DebugBackground->CreateBackground(BgDesc, 6);
	}
	
	{
		Background::BG_DESC BgDesc;

		std::shared_ptr<GameEngineTexture> Tex = GameEngineTexture::Find("Castle_BackImage_InSmallCloud");

		BgDesc.TextureName = "Castle_BackImage_CastleWall.png";
		BgDesc.Center = { 400.0f + (TilemapDESC.Left + TilemapDESC.Right) * 0.5f, (TilemapDESC.Top + TilemapDESC.Bottom) * 0.5f, 0, 0 };
		BgDesc.Ratio = 0.5f;
		BgDesc.Size = float4(2400.0f, 875.0f, 0, 0);
		BgDesc.Animation = false;
		BgDesc.AnimationSpeed = 0.0f;

		DebugBackground->CreateBackground(BgDesc, 5);
	}

	{
		Background::BG_DESC BgDesc;

		std::shared_ptr<GameEngineTexture> Tex = GameEngineTexture::Find("Castle_BackImage_InSmallCloud");

		BgDesc.TextureName = "Castle_BackImage_Chandelier.png";
		BgDesc.Center = {(TilemapDESC.Left + TilemapDESC.Right) * 0.5f, 100.0f + (TilemapDESC.Top + TilemapDESC.Bottom) * 0.5f, 0, 0 };
		BgDesc.Ratio = 0.75f;
		BgDesc.Size = float4(1718.2f, 523.6f, 0, 0);
		BgDesc.Animation = false;
		BgDesc.AnimationSpeed = 0.0f;

		DebugBackground->CreateBackground(BgDesc, 4);
	}

	DeubgActor = CreateActor<DebugSpriteActor>();
	DeubgActor->Off();

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
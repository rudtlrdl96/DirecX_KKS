#include "PrecompileHeader.h"
#include "CastleLevel.h"
#include <GameEngineCore/GameEngineTexture.h>
#include "MultiBackground.h"

CastleLevel::CastleLevel()
{
}

CastleLevel::~CastleLevel()
{
}

void CastleLevel::Start()
{
	BattleLevel::Start();

	{
		BG_DESC BgDesc;

		BgDesc.Name = "Castle_BackImage_InSky.png";
		BgDesc.Center = { 0.0f, 0.0f, 1100.0f, 0 };
		BgDesc.MoveRatio = 0.0f;
		BgDesc.TextureSize  = float4(960.0f, 350.0f, 0, 0);
		BgDesc.TextureScale = 4.0f;
		BgDesc.Animation = false;
		BgDesc.AnimationSpeed = 0.0f;
		BgDesc.Color = float4(-0.062f, -0.076f, -0.053f, 1.0f);

		MBackgroundPtr->CreateBackground(BgDesc);
	}

	{
		BG_DESC BgDesc;

		BgDesc.Name = "Castle_BackImage_Star.png";
		BgDesc.Center = { 0.0f, 0.0f, 1000.0f, 0 };
		BgDesc.MoveRatio = 0.2f;
		BgDesc.TextureSize  = float4(927.0f, 347.0f, 0, 0);
		BgDesc.TextureScale *= 2.5f;
		BgDesc.Animation = false;
		BgDesc.AnimationSpeed = 0.0f;
		BgDesc.Color = float4(-0.051f, -0.101f, -0.051f, 1.0f);

		MBackgroundPtr->CreateBackground(BgDesc);
	}

	{
		BG_DESC BgDesc;

		BgDesc.Name = "Castle_BackImage_InSmallCloud.png";
		BgDesc.Center = { 400.0f, 100.0f, 900.0f, 0 };
		BgDesc.MoveRatio = 0.2f;
		BgDesc.TextureSize  = float4(1521.6f, 552.0f, 0, 0);
		BgDesc.TextureScale = 1.0f;
		BgDesc.Animation = true;
		BgDesc.AnimationSpeed = 0.016f;
		BgDesc.Color = float4(-0.05f, -0.05f, -0.05f, 1.0f);

		MBackgroundPtr->CreateBackground(BgDesc);
	}

	{
		BG_DESC BgDesc;

		BgDesc.Name = "Castle_BackImage_InBigCloud.png";
		BgDesc.Center = { 500.0f, 20.0f, 800.0f, 0 };
		BgDesc.MoveRatio = 0.1f;
		BgDesc.TextureSize = float4(2110.0f, 422.5f, 0, 0);
		BgDesc.TextureScale = 1.0f;
		BgDesc.Animation = false;
		BgDesc.AnimationSpeed = 0.0f;
		BgDesc.Color = float4(-0.05f, -0.05f, -0.05f, 1.0f);

		MBackgroundPtr->CreateBackground(BgDesc);
	}

	{
		BG_DESC BgDesc;

		BgDesc.Name = "Castle_BackImage_CastleWall.png";
		BgDesc.Center = { 700.0f, 50.0f, 700.0f, 0 };
		BgDesc.MoveRatio = 0.5f;
		BgDesc.TextureSize  = float4(2400.0f, 875.0f, 0, 0);
		BgDesc.TextureScale = 1.0f;
		BgDesc.Animation = false;
		BgDesc.AnimationSpeed = 0.0f;
		BgDesc.Color = float4(-0.2f, -0.2f, -0.25f, 1.0f);

		MBackgroundPtr->CreateBackground(BgDesc);
	}

	{
		BG_DESC BgDesc;

		BgDesc.Name = "Castle_BackImage_Chandelier.png";
		BgDesc.Center = { 780.0f, 100.0f, 600.0f, 0 };
		BgDesc.MoveRatio = 0.7f;
		BgDesc.TextureSize  = float4(1050.0f, 304.0f, 0, 0);
		BgDesc.TextureScale = 2.0f;
		BgDesc.Animation = false;
		BgDesc.AnimationSpeed = 0.0f;
		BgDesc.Color = float4(-0.05f, -0.05f, -0.05f, 1.0f);

		MBackgroundPtr->CreateBackground(BgDesc);
	}

}

void CastleLevel::Update(float _DeltaTime)
{
	BattleLevel::Update(_DeltaTime);
}

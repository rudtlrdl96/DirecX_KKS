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
	TextureLoad();

	{
		Background::BG_DESC BgDesc;

		BgDesc.TextureName = "Castle_BackImage_InSky.png";
		BgDesc.Center = { 0.0f, 0.0f, 0, 0 };
		BgDesc.Ratio = 0.0f;
		BgDesc.Size = float4(960.0f, 350.0f, 0, 0);
		BgDesc.Size *= 4.0f;
		BgDesc.Animation = false;
		BgDesc.AnimationSpeed = 0.0f;
		BgDesc.Color = float4(-0.062f, -0.076f, -0.053f, 1.0f);

		MBackgroundPtr->CreateBackground(BgDesc, 11);
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
		BgDesc.Color = float4(-0.051f, -0.101f, -0.051f, 1.0f);

		MBackgroundPtr->CreateBackground(BgDesc, 10);
	}

	{
		Background::BG_DESC BgDesc;

		BgDesc.TextureName = "Castle_BackImage_InSmallCloud.png";
		BgDesc.Center = { 400.0f, 100.0f, 0, 0 };
		BgDesc.Ratio = 0.2f;
		BgDesc.Size = float4(1521.6f, 552.0f, 0, 0);
		BgDesc.Animation = true;
		BgDesc.AnimationSpeed = 25.0f;
		BgDesc.Color = float4(-0.05f, -0.05f, -0.05f, 1.0f);

		MBackgroundPtr->CreateBackground(BgDesc, 9);
	}

	{
		Background::BG_DESC BgDesc;

		BgDesc.TextureName = "Castle_BackImage_InBigCloud.png";
		BgDesc.Center = { 500.0f, 20.0f, 0, 0 };
		BgDesc.Ratio = 0.1f;
		BgDesc.Size = float4(2110.0f, 422.5f, 0, 0);
		BgDesc.Animation = false;
		BgDesc.AnimationSpeed = 0.0f;
		BgDesc.Color = float4(-0.05f, -0.05f, -0.05f, 1.0f);

		MBackgroundPtr->CreateBackground(BgDesc, 8);
	}

	{
		Background::BG_DESC BgDesc;

		BgDesc.TextureName = "Castle_BackImage_CastleWall.png";
		BgDesc.Center = { 700.0f, 50.0f, 0, 0 };
		BgDesc.Ratio = 0.5f;
		BgDesc.Size = float4(2400.0f, 875.0f, 0, 0);
		BgDesc.Animation = false;
		BgDesc.AnimationSpeed = 0.0f;
		BgDesc.Color = float4(-0.2f, -0.2f, -0.25f, 1.0f);

		MBackgroundPtr->CreateBackground(BgDesc, 7);
	}

	{
		Background::BG_DESC BgDesc;

		BgDesc.TextureName = "Castle_BackImage_Chandelier.png";
		BgDesc.Center = { 780.0f, 100.0f, 0, 0 };
		BgDesc.Ratio = 0.7f;
		BgDesc.Size = float4(1050.0f, 304.0f, 0, 0);
		BgDesc.Size *= 2.0f;
		BgDesc.Animation = false;
		BgDesc.AnimationSpeed = 0.0f;
		BgDesc.Color = float4(-0.05f, -0.05f, -0.05f, 1.0f);

		MBackgroundPtr->CreateBackground(BgDesc, 6);
	}

}

void CastleLevel::Update(float _DeltaTime)
{
	BattleLevel::Update(_DeltaTime);
}

void CastleLevel::TextureLoad()
{
	GameEngineDirectory Path;
	Path.MoveParentToDirectory("Resources");
	Path.Move("Resources");
	Path.Move("Texture");
	Path.Move("Map");

	{
		Path.Move("Background");
		Path.Move("Castle");

		std::vector<GameEngineFile> Files = Path.GetAllFile({ ".png" });

		for (size_t i = 0; i < Files.size(); i++)
		{
			GameEngineTexture::Load(Files[i].GetFullPath());
		}

		Path.MoveParent();
		Path.MoveParent();
	}

	{
		Path.Move("FrontImage");
		Path.Move("Castle");

		std::vector<GameEngineFile> Files = Path.GetAllFile({ ".png" });

		for (size_t i = 0; i < Files.size(); i++)
		{
			GameEngineTexture::Load(Files[i].GetFullPath());
		}

		Path.MoveParent();
		Path.MoveParent();
	}
}

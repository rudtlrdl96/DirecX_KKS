#include "PrecompileHeader.h"
#include "OpeningLevel.h"
#include "MultiBackground.h"

OpeningLevel::OpeningLevel()
{
}

OpeningLevel::~OpeningLevel()
{
}

void OpeningLevel::Start()
{
	BattleLevel::Start();
	TextureLoad();

	{
		Background::BG_DESC BgDesc;

		BgDesc.TextureName = "Opening_BackImage_0.png";
		BgDesc.Center = { 0.0f, 400.0f, 0, 0 };
		BgDesc.Ratio = 0.0f;
		BgDesc.Size = float4(962.0f, 802.0f, 0, 0);
		BgDesc.Size *= 2.0f;
		//BgDesc.Color = float4(0, 0, 0, 1.1f);

		MBackgroundPtr->CreateBackground(BgDesc, 11);
	}

	{
		Background::BG_DESC BgDesc;

		BgDesc.TextureName = "Opening_BackImage_1.png";
		BgDesc.Center = { 0.0f, 450.0f, 0, 0 };
		BgDesc.Ratio = 0.1f;
		BgDesc.Size = float4(969.0f, 811.0f, 0, 0);
		BgDesc.Size *= 2.0f;
		//BgDesc.Color = float4(0, 0, 0, 1.1f);

		MBackgroundPtr->CreateBackground(BgDesc, 10);
	}

	{
		Background::BG_DESC BgDesc;

		BgDesc.TextureName = "Opening_BackImage_2.png";
		BgDesc.Center = { 0.0f, 400.0f, 0, 0 };
		BgDesc.Ratio = 0.2f;
		BgDesc.Size = float4(971.0f, 811.0f, 0, 0);
		BgDesc.Size *= 2.0f;
		//BgDesc.Color = float4(0, 0, 0, 1.1f);

		MBackgroundPtr->CreateBackground(BgDesc, 9);
	}

	{
		Background::BG_DESC BgDesc;

		BgDesc.TextureName = "Opening_BackImage_3.png";
		BgDesc.Center = { 0.0f, 300.0f, 0, 0 };
		BgDesc.Ratio = 0.4f;
		BgDesc.Size = float4(970.0f, 801.0f, 0, 0);
		BgDesc.Size *= 2.0f;
		//BgDesc.Color = float4(0, 0, 0, 1.1f);

		MBackgroundPtr->CreateBackground(BgDesc, 8);
	}
}

void OpeningLevel::Update(float _DeltaTime)
{
	BattleLevel::Update(_DeltaTime);
}

void OpeningLevel::TextureLoad()
{
	GameEngineDirectory Path;
	Path.MoveParentToDirectory("Resources");
	Path.Move("Resources");
	Path.Move("Texture");
	Path.Move("Map");

	{
		Path.Move("Background");
		Path.Move("Opening");

		std::vector<GameEngineFile> Files = Path.GetAllFile({ ".png" });

		for (size_t i = 0; i < Files.size(); i++)
		{
			GameEngineTexture::Load(Files[i].GetFullPath());
		}

		Path.MoveParent();
		Path.MoveParent();
	}
}

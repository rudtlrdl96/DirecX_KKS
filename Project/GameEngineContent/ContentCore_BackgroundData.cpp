#include "PrecompileHeader.h"
#include "ContentCore.h"

#include <GameEngineCore/GameEngineTexture.h>

#include "Background.h"
#include "ContentDatabase.h"


void ContentCore::BackgroundDataLoad()
{
	GameEngineDirectory Path;
	Path.MoveParentToDirectory("Resources");
	Path.Move("Resources");
	Path.Move("Texture");


	{	
		Path.Move("1_Opening");	
		Path.Move("Background");

		std::vector<GameEngineFile> Files = Path.GetAllFile({ ".png" });

		for (UINT i = 0; i < Files.size(); i++)
		{
			std::shared_ptr<GameEngineTexture> LoadTex = GameEngineTexture::Load(Files[i].GetFullPath());

			float4 TexSize = { (float)LoadTex->GetWidth(), (float)LoadTex->GetHeight() };

			ContentDatabase<BG_DESC, LevelArea>::InsertData({
			.Name = LoadTex->GetNameToString(), .Index = 100 + i, .Grade = LevelArea::Opening , .TextureSize = TexSize });
		}

		Path.MoveParent();
		Path.MoveParent();
	}

	{
		Path.Move("2_Castle");
		Path.Move("Background");

		std::vector<GameEngineFile> Files = Path.GetAllFile({ ".png" });

		for (UINT i = 0; i < Files.size(); i++)
		{
			std::shared_ptr<GameEngineTexture> LoadTex = GameEngineTexture::Load(Files[i].GetFullPath());

			float4 TexSize = { (float)LoadTex->GetWidth(), (float)LoadTex->GetHeight() };

			ContentDatabase<BG_DESC, LevelArea>::InsertData({
			.Name = LoadTex->GetNameToString(), .Index = 200 + i, .Grade = LevelArea::Castle, .TextureSize = TexSize });
		}

		Path.MoveParent();
		Path.MoveParent();
	}

	{
		Path.Move("3_ForestOfHarmony");
		Path.Move("Background");

		std::vector<GameEngineFile> Files = Path.GetAllFile({ ".png" });

		for (UINT i = 0; i < Files.size(); i++)
		{
			std::shared_ptr<GameEngineTexture> LoadTex = GameEngineTexture::Load(Files[i].GetFullPath());

			float4 TexSize = { (float)LoadTex->GetWidth(), (float)LoadTex->GetHeight() };

			ContentDatabase<BG_DESC, LevelArea>::InsertData({
			.Name = LoadTex->GetNameToString(), .Index = 300 + i, .Grade = LevelArea::ForestOfHamory, .TextureSize = TexSize });
		}

		Path.MoveParent();
		Path.MoveParent();
	}

	{
		Path.Move("4_GrandHall");
		Path.Move("Background");

		std::vector<GameEngineFile> Files = Path.GetAllFile({ ".png" });

		for (UINT i = 0; i < Files.size(); i++)
		{
			std::shared_ptr<GameEngineTexture> LoadTex = GameEngineTexture::Load(Files[i].GetFullPath());

			float4 TexSize = { (float)LoadTex->GetWidth(), (float)LoadTex->GetHeight() };

			ContentDatabase<BG_DESC, LevelArea>::InsertData({
			.Name = LoadTex->GetNameToString(), .Index = 400 + i, .Grade = LevelArea::GrandHall , .TextureSize = TexSize });
		}

		Path.MoveParent();
		Path.MoveParent();
	}

	{
		Path.Move("5_HolyCourtyard");
		Path.Move("Background");

		std::vector<GameEngineFile> Files = Path.GetAllFile({ ".png" });

		for (UINT i = 0; i < Files.size(); i++)
		{
			std::shared_ptr<GameEngineTexture> LoadTex = GameEngineTexture::Load(Files[i].GetFullPath());

			float4 TexSize = { (float)LoadTex->GetWidth(), (float)LoadTex->GetHeight() };

			ContentDatabase<BG_DESC, LevelArea>::InsertData({
			.Name = LoadTex->GetNameToString(), .Index = 500 + i, .Grade = LevelArea::HolyCourtyard, .TextureSize = TexSize });
		}

		Path.MoveParent();
		Path.MoveParent();
	}

	{
		Path.Move("7_Shop");
		Path.Move("Background");

		std::vector<GameEngineFile> Files = Path.GetAllFile({ ".png" });

		for (UINT i = 0; i < Files.size(); i++)
		{
			std::shared_ptr<GameEngineTexture> LoadTex = GameEngineTexture::Load(Files[i].GetFullPath());

			float4 TexSize = { (float)LoadTex->GetWidth(), (float)LoadTex->GetHeight() };

			ContentDatabase<BG_DESC, LevelArea>::InsertData({
			.Name = LoadTex->GetNameToString(), .Index = 600 + i, .Grade = LevelArea::Shop , .TextureSize = TexSize });
		}

		Path.MoveParent();
		Path.MoveParent();
	}

	std::vector<BG_DESC> OpeningDatas;
	ContentDatabase<BG_DESC, LevelArea>::CopyGradeDatas(LevelArea::Opening, OpeningDatas);

	std::vector<BG_DESC> CastleDatas;
	ContentDatabase<BG_DESC, LevelArea>::CopyGradeDatas(LevelArea::Castle, CastleDatas);

	std::vector<BG_DESC> ForestOfHarmonyDatas;
	ContentDatabase<BG_DESC, LevelArea>::CopyGradeDatas(LevelArea::ForestOfHamory, ForestOfHarmonyDatas);

	std::vector<BG_DESC> GrandHallDatas;
	ContentDatabase<BG_DESC, LevelArea>::CopyGradeDatas(LevelArea::GrandHall, GrandHallDatas);

	std::vector<BG_DESC> HoluCourtyardDatas;
	ContentDatabase<BG_DESC, LevelArea>::CopyGradeDatas(LevelArea::HolyCourtyard, HoluCourtyardDatas);

	std::vector<BG_DESC> ShopDatas;
	ContentDatabase<BG_DESC, LevelArea>::CopyGradeDatas(LevelArea::Shop, ShopDatas);

	int a = 0;
}
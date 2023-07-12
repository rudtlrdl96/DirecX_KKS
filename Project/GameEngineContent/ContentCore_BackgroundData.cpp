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

			ContentDatabase<BackgroundMetaData, LevelArea>::InsertData({
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

			ContentDatabase<BackgroundMetaData, LevelArea>::InsertData({
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

			ContentDatabase<BackgroundMetaData, LevelArea>::InsertData({
			.Name = LoadTex->GetNameToString(), .Index = 300 + i, .Grade = LevelArea::ForestOfHarmory, .TextureSize = TexSize });
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

			ContentDatabase<BackgroundMetaData, LevelArea>::InsertData({
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

			ContentDatabase<BackgroundMetaData, LevelArea>::InsertData({
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

			ContentDatabase<BackgroundMetaData, LevelArea>::InsertData({
			.Name = LoadTex->GetNameToString(), .Index = 600 + i, .Grade = LevelArea::Shop , .TextureSize = TexSize });
		}

		Path.MoveParent();
		Path.MoveParent();
	}

	std::vector<BackgroundMetaData> OpeningDatas;
	ContentDatabase<BackgroundMetaData, LevelArea>::CopyGradeDatas(LevelArea::Opening, OpeningDatas);

	std::vector<BackgroundMetaData> CastleDatas;
	ContentDatabase<BackgroundMetaData, LevelArea>::CopyGradeDatas(LevelArea::Castle, CastleDatas);

	std::vector<BackgroundMetaData> ForestOfHarmonyDatas;
	ContentDatabase<BackgroundMetaData, LevelArea>::CopyGradeDatas(LevelArea::ForestOfHarmory, ForestOfHarmonyDatas);

	std::vector<BackgroundMetaData> GrandHallDatas;
	ContentDatabase<BackgroundMetaData, LevelArea>::CopyGradeDatas(LevelArea::GrandHall, GrandHallDatas);

	std::vector<BackgroundMetaData> HoluCourtyardDatas;
	ContentDatabase<BackgroundMetaData, LevelArea>::CopyGradeDatas(LevelArea::HolyCourtyard, HoluCourtyardDatas);

	std::vector<BackgroundMetaData> ShopDatas;
	ContentDatabase<BackgroundMetaData, LevelArea>::CopyGradeDatas(LevelArea::Shop, ShopDatas);

	int a = 0;
}
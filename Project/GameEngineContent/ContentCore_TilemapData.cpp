#include "PrecompileHeader.h"
#include "ContentCore.h"
#include <GameEngineCore/GameEngineTexture.h>
#include "TilemapData.h"

void TileLoad(const TilemapData& _Data)
{
	ContentDatabase<TilemapData, LevelArea>::InsertData(_Data);
}

void ContentCore::TileDataLoad()
{
	GameEngineDirectory Path;
	Path.MoveParentToDirectory("Resources");
	Path.Move("Resources");
	Path.Move("Texture");

	{
		Path.Move("12_Debug");
		Path.Move("Tile");

		std::vector<GameEngineFile> Files = Path.GetAllFile({ ".png" });

		for (UINT i = 0; i < Files.size(); i++)
		{
			std::shared_ptr<GameEngineTexture> Tex = GameEngineTexture::Load(Files[i].GetFullPath());
			std::string Name = Tex->GetNameToString();
			TileLoad({ .Name = Name, .Index = i, .Grade = LevelArea::None });
		}

		Path.MoveParent();
		Path.MoveParent();
	}

	{
		Path.Move("1_Opening");
		Path.Move("Tile");

		std::vector<GameEngineFile> Files = Path.GetAllFile({ ".png" });

		for (UINT i = 0; i < Files.size(); i++)
		{
			std::shared_ptr<GameEngineTexture> Tex = GameEngineTexture::Load(Files[i].GetFullPath());
			std::string Name = Tex->GetNameToString();
			TileLoad({ .Name = Name, .Index = 1000 + i, .Grade = LevelArea::Opening });
		}

		Path.MoveParent();
		Path.MoveParent();
	}

	{
		Path.Move("2_Castle");
		Path.Move("Tile");

		std::vector<GameEngineFile> Files = Path.GetAllFile({ ".png" });

		for (UINT i = 0; i < Files.size(); i++)
		{
			std::shared_ptr<GameEngineTexture> Tex = GameEngineTexture::Load(Files[i].GetFullPath());
			std::string Name = Tex->GetNameToString();
			TileLoad({ .Name = Name, .Index = 2000 + i, .Grade = LevelArea::Castle});
		}

		Path.MoveParent();
		Path.MoveParent();
	}
	{
		Path.Move("3_ForestOfHarmony");
		Path.Move("Tile");

		std::vector<GameEngineFile> Files = Path.GetAllFile({ ".png" });
	
		for (UINT i = 0; i < Files.size(); i++)
		{
			std::shared_ptr<GameEngineTexture> Tex = GameEngineTexture::Load(Files[i].GetFullPath());
			std::string Name = Tex->GetNameToString();
			TileLoad({ .Name = Name, .Index = 3000 + i, .Grade = LevelArea::ForestOfHamory });
		}

		Path.MoveParent();
		Path.MoveParent();
	}
	{
		Path.Move("4_GrandHall");
		Path.Move("Tile");

		std::vector<GameEngineFile> Files = Path.GetAllFile({ ".png" });
	
		for (UINT i = 0; i < Files.size(); i++)
		{
			std::shared_ptr<GameEngineTexture> Tex = GameEngineTexture::Load(Files[i].GetFullPath());
			std::string Name = Tex->GetNameToString();
			TileLoad({ .Name = Name, .Index = 4000 + i, .Grade = LevelArea::GrandHall });
		}

		Path.MoveParent();
		Path.MoveParent();
	}
	{
		Path.Move("5_HolyCourtyard");
		Path.Move("Tile");

		std::vector<GameEngineFile> Files = Path.GetAllFile({ ".png" });

		for (UINT i = 0; i < Files.size(); i++)
		{
			std::shared_ptr<GameEngineTexture> Tex = GameEngineTexture::Load(Files[i].GetFullPath());
			std::string Name = Tex->GetNameToString();
			TileLoad({ .Name = Name, .Index = 5000 + i, .Grade = LevelArea::HolyCourtyard });
		}

		Path.MoveParent();
		Path.MoveParent();
	}

	{
		Path.Move("7_Shop");
		Path.Move("Tile");

		std::vector<GameEngineFile> Files = Path.GetAllFile({ ".png" });

		for (UINT i = 0; i < Files.size(); i++)
		{
			std::shared_ptr<GameEngineTexture> Tex = GameEngineTexture::Load(Files[i].GetFullPath());
			std::string Name = Tex->GetNameToString();
			TileLoad({ .Name = Name, .Index = 6000 + i, .Grade = LevelArea::Shop });
		}

		Path.MoveParent();
		Path.MoveParent();
	}

	std::vector<TilemapData> NoneDatas;
	ContentDatabase<TilemapData, LevelArea>::CopyGradeDatas(LevelArea::None, NoneDatas);

	std::vector<TilemapData> OpeningDatas;
	ContentDatabase<TilemapData, LevelArea>::CopyGradeDatas(LevelArea::Opening, OpeningDatas);

	std::vector<TilemapData> CastleDatas;
	ContentDatabase<TilemapData, LevelArea>::CopyGradeDatas(LevelArea::Castle, CastleDatas);

	std::vector<TilemapData> ForestDatas;
	ContentDatabase<TilemapData, LevelArea>::CopyGradeDatas(LevelArea::ForestOfHamory, ForestDatas);

	std::vector<TilemapData> GrandHallDatas;
	ContentDatabase<TilemapData, LevelArea>::CopyGradeDatas(LevelArea::GrandHall, GrandHallDatas);

	std::vector<TilemapData> SacredGroundsDatas;
	ContentDatabase<TilemapData, LevelArea>::CopyGradeDatas(LevelArea::HolyCourtyard, SacredGroundsDatas);
		
	std::vector<TilemapData> ShopDatas;
	ContentDatabase<TilemapData, LevelArea>::CopyGradeDatas(LevelArea::Shop, ShopDatas);

	int a = 0;
}
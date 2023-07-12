#include "PrecompileHeader.h"
#include "ContentCore.h"
#include <GameEngineCore/GameEngineTexture.h>
#include "TileMetaData.h"

void TileLoad(const TileMetaData& _Data)
{
	ContentDatabase<TileMetaData, LevelArea>::InsertData(_Data);
}

void ContentCore::TileDataLoad()
{
	GameEngineDirectory Path;
	Path.MoveParentToDirectory("Resources");
	Path.Move("Resources");
	Path.Move("Texture");

	{
		Path.Move("0_Common");
		Path.Move("Door");
		Path.Move("ForestOfHarmony");

		GameEngineSprite::LoadSheet(Path.GetPlusFileName("ForestOfHarmony_BossIntroDoor_Active.png").GetFullPath(), 4, 2);
		GameEngineSprite::LoadSheet(Path.GetPlusFileName("ForestOfHarmony_BossIntroDoor_Disable.png").GetFullPath(), 1, 1);

		GameEngineSprite::LoadSheet(Path.GetPlusFileName("ForestOfHarmony_EquipDoor_Active.png").GetFullPath(), 4, 2);
		GameEngineSprite::LoadSheet(Path.GetPlusFileName("ForestOfHarmony_EquipDoor_Disable.png").GetFullPath(), 1, 1);

		GameEngineSprite::LoadSheet(Path.GetPlusFileName("ForestOfHarmony_MiddleBossDoor_Active.png").GetFullPath(), 4, 2);
		GameEngineSprite::LoadSheet(Path.GetPlusFileName("ForestOfHarmony_MiddleBossDoor_Disable.png").GetFullPath(), 1, 1);

		GameEngineSprite::LoadSheet(Path.GetPlusFileName("ForestOfHarmony_NormalDoor_Active.png").GetFullPath(), 4, 2);
		GameEngineSprite::LoadSheet(Path.GetPlusFileName("ForestOfHarmony_NormalDoor_Disable.png").GetFullPath(), 1, 1);

		GameEngineSprite::LoadSheet(Path.GetPlusFileName("ForestOfHarmony_ShopDoor_Active.png").GetFullPath(), 4, 2);
		GameEngineSprite::LoadSheet(Path.GetPlusFileName("ForestOfHarmony_ShopDoor_Disable.png").GetFullPath(), 1, 1);
		
		GameEngineSprite::LoadSheet(Path.GetPlusFileName("ForestOfHarmony_SkullDoor_Active.png").GetFullPath(), 4, 2);
		GameEngineSprite::LoadSheet(Path.GetPlusFileName("ForestOfHarmony_SkullDoor_Disable.png").GetFullPath(), 1, 1);

		GameEngineSprite::LoadSheet(Path.GetPlusFileName("ForestOfHarmony_MainBossDoor.png").GetFullPath(), 4, 2);		
		GameEngineSprite::LoadSheet(Path.GetPlusFileName("ForestOfHarmony_BrokenDoor.png").GetFullPath(), 1, 1);
		

		Path.MoveParent();
		Path.MoveParent();
		Path.MoveParent();
	}

	{
		Path.Move("12_Debug");
		Path.Move("Tile");

		std::vector<GameEngineFile> Files = Path.GetAllFile({ ".png" });

		for (UINT i = 0; i < Files.size(); i++)
		{
			std::shared_ptr<GameEngineSprite> Tex = GameEngineSprite::LoadSheet(Files[i].GetFullPath(), 1, 1);
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
			std::shared_ptr<GameEngineSprite> Tex = GameEngineSprite::LoadSheet(Files[i].GetFullPath(), 1, 1);
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
			std::shared_ptr<GameEngineSprite> Tex = GameEngineSprite::LoadSheet(Files[i].GetFullPath(), 1, 1);
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
			std::shared_ptr<GameEngineSprite> Tex = GameEngineSprite::LoadSheet(Files[i].GetFullPath(), 1, 1);
			std::string Name = Tex->GetNameToString();
			TileLoad({ .Name = Name, .Index = 3000 + i, .Grade = LevelArea::ForestOfHarmory });
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
			std::shared_ptr<GameEngineSprite> Tex = GameEngineSprite::LoadSheet(Files[i].GetFullPath(), 1, 1);
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
			std::shared_ptr<GameEngineSprite> Tex = GameEngineSprite::LoadSheet(Files[i].GetFullPath(), 1, 1);
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
			std::shared_ptr<GameEngineSprite> Tex = GameEngineSprite::LoadSheet(Files[i].GetFullPath(), 1, 1);
			std::string Name = Tex->GetNameToString();
			TileLoad({ .Name = Name, .Index = 6000 + i, .Grade = LevelArea::Shop });
		}

		Path.MoveParent();
		Path.MoveParent();
	}

	std::vector<TileMetaData> NoneDatas;
	ContentDatabase<TileMetaData, LevelArea>::CopyGradeDatas(LevelArea::None, NoneDatas);

	std::vector<TileMetaData> OpeningDatas;
	ContentDatabase<TileMetaData, LevelArea>::CopyGradeDatas(LevelArea::Opening, OpeningDatas);

	std::vector<TileMetaData> CastleDatas;
	ContentDatabase<TileMetaData, LevelArea>::CopyGradeDatas(LevelArea::Castle, CastleDatas);

	std::vector<TileMetaData> ForestDatas;
	ContentDatabase<TileMetaData, LevelArea>::CopyGradeDatas(LevelArea::ForestOfHarmory, ForestDatas);

	std::vector<TileMetaData> GrandHallDatas;
	ContentDatabase<TileMetaData, LevelArea>::CopyGradeDatas(LevelArea::GrandHall, GrandHallDatas);

	std::vector<TileMetaData> SacredGroundsDatas;
	ContentDatabase<TileMetaData, LevelArea>::CopyGradeDatas(LevelArea::HolyCourtyard, SacredGroundsDatas);
		
	std::vector<TileMetaData> ShopDatas;
	ContentDatabase<TileMetaData, LevelArea>::CopyGradeDatas(LevelArea::Shop, ShopDatas);

	int a = 0;
}
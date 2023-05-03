#include "PrecompileHeader.h"
#include "ContentCore.h"
#include <GameEngineCore/GameEngineTexture.h>
#include "TilemapData.h"

void TileLoad(const TilemapData& _Data)
{
	ContentDatabase<TilemapData, TileArea>::InsertData(_Data);
}

void ContentCore::TileDataLoad()
{
	GameEngineDirectory Path;
	Path.MoveParentToDirectory("Resources");
	Path.Move("Resources");
	Path.Move("Texture");
	Path.Move("Map");
	Path.Move("Tile");

	{
		Path.Move("DebugTile");
		std::vector<GameEngineFile> Files = Path.GetAllFile({ ".png" });

		for (UINT i = 0; i < Files.size(); i++)
		{
			std::shared_ptr<GameEngineTexture> Tex = GameEngineTexture::Load(Files[i].GetFullPath());
			std::string Name = Tex->GetNameToString();
			TileLoad({ .Name = Name, .Index = i, .Grade = TileArea::Castle });
		}
	}

	{
		Path.MoveParent();
		Path.Move("Castle");
		std::vector<GameEngineFile> Files = Path.GetAllFile({ ".png" });

		for (UINT i = 0; i < Files.size(); i++)
		{
			std::shared_ptr<GameEngineTexture> Tex = GameEngineTexture::Load(Files[i].GetFullPath());
			std::string Name = Tex->GetNameToString();
			TileLoad({ .Name = Name, .Index = 1000 + i, .Grade = TileArea::Castle});
		}
	}
	{
		Path.MoveParent();
		Path.Move("ForestOfHarmony");
		std::vector<GameEngineFile> Files = Path.GetAllFile({ ".png" });
	
		for (UINT i = 0; i < Files.size(); i++)
		{
			std::shared_ptr<GameEngineTexture> Tex = GameEngineTexture::Load(Files[i].GetFullPath());
			std::string Name = Tex->GetNameToString();
			TileLoad({ .Name = Name, .Index = 2000 + i, .Grade = TileArea::ForestOfHamory });
		}
	}
	{
		Path.MoveParent();
		Path.Move("GrandHall");
		std::vector<GameEngineFile> Files = Path.GetAllFile({ ".png" });
	
		for (UINT i = 0; i < Files.size(); i++)
		{
			std::shared_ptr<GameEngineTexture> Tex = GameEngineTexture::Load(Files[i].GetFullPath());
			std::string Name = Tex->GetNameToString();
			TileLoad({ .Name = Name, .Index = 3000 + i, .Grade = TileArea::GrandHall });
		}
	}
	{
		Path.MoveParent();
		Path.Move("HolyCourtyard");
		std::vector<GameEngineFile> Files = Path.GetAllFile({ ".png" });

		for (UINT i = 0; i < Files.size(); i++)
		{
			std::shared_ptr<GameEngineTexture> Tex = GameEngineTexture::Load(Files[i].GetFullPath());
			std::string Name = Tex->GetNameToString();
			TileLoad({ .Name = Name, .Index = 4000 + i, .Grade = TileArea::SacredGrounds });
		}
	}

	std::vector<TilemapData> CastleDatas;
	ContentDatabase<TilemapData, TileArea>::CopyGradeDatas(TileArea::Castle, CastleDatas);

	std::vector<TilemapData> ForestDatas;
	ContentDatabase<TilemapData, TileArea>::CopyGradeDatas(TileArea::ForestOfHamory, ForestDatas);

	std::vector<TilemapData> GrandHallDatas;
	ContentDatabase<TilemapData, TileArea>::CopyGradeDatas(TileArea::GrandHall, GrandHallDatas);

	std::vector<TilemapData> SacredGroundsDatas;
	ContentDatabase<TilemapData, TileArea>::CopyGradeDatas(TileArea::SacredGrounds, SacredGroundsDatas);

	int a = 0;
}
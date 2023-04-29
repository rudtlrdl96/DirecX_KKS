#include "PrecompileHeader.h"
#include "ContentCore.h"
#include "StaticObject.h"

void ContentCore::StaticObjectLoad()
{
	GameEngineDirectory Path;
	Path.MoveParentToDirectory("Resources");
	Path.Move("Resources");
	Path.Move("Texture");
	Path.Move("Map");
	Path.Move("Object");
	Path.Move("StaticObject");

	{
		Path.Move("Castle");

		std::vector<GameEngineFile> Files = Path.GetAllFile({ ".png" });

		for (size_t i = 0; i < Files.size(); i++)
		{
			std::shared_ptr<GameEngineTexture> Tex = GameEngineTexture::Load(Files[i].GetFullPath());
			std::string Name = Tex->GetNameToString();
			ContentDatabase<SObject_DESC, LevelType>::InsertData(
				{.Name = Name, .Index = i, .Grade = LevelType::Castle, .Size = float4(Tex->GetWidth(), Tex->GetHeight())});
		}

		Path.MoveParent();
	}

	{
		Path.Move("ForestOfHarmony");

		std::vector<GameEngineFile> Files = Path.GetAllFile({ ".png" });

		for (size_t i = 0; i < Files.size(); i++)
		{
			std::shared_ptr<GameEngineTexture> Tex = GameEngineTexture::Load(Files[i].GetFullPath());
			std::string Name = Tex->GetNameToString();
			ContentDatabase<SObject_DESC, LevelType>::InsertData(
				{ .Name = Name, .Index = 1000 + i, .Grade = LevelType::ForestOfHarmony, .Size = float4(Tex->GetWidth(), Tex->GetHeight()) });
		}

		Path.MoveParent();
	}

	{
		Path.Move("GrandHall");

		std::vector<GameEngineFile> Files = Path.GetAllFile({ ".png" });

		for (size_t i = 0; i < Files.size(); i++)
		{
			std::shared_ptr<GameEngineTexture> Tex = GameEngineTexture::Load(Files[i].GetFullPath());
			std::string Name = Tex->GetNameToString();
			ContentDatabase<SObject_DESC, LevelType>::InsertData(
				{ .Name = Name, .Index = 2000 + i, .Grade = LevelType::Grandhall, .Size = float4(Tex->GetWidth(), Tex->GetHeight()) });
		}

		Path.MoveParent();
	}

	{
		Path.Move("HolyCourtyard");

		std::vector<GameEngineFile> Files = Path.GetAllFile({ ".png" });

		for (size_t i = 0; i < Files.size(); i++)
		{
			std::shared_ptr<GameEngineTexture> Tex = GameEngineTexture::Load(Files[i].GetFullPath());
			std::string Name = Tex->GetNameToString();
			ContentDatabase<SObject_DESC, LevelType>::InsertData(
				{ .Name = Name, .Index = 3000 + i, .Grade = LevelType::HolyCourtyard, .Size = float4(Tex->GetWidth(), Tex->GetHeight()) });
		}

		Path.MoveParent();
	}

	{
		Path.Move("Opening");

		std::vector<GameEngineFile> Files = Path.GetAllFile({ ".png" });

		for (size_t i = 0; i < Files.size(); i++)
		{
			std::shared_ptr<GameEngineTexture> Tex = GameEngineTexture::Load(Files[i].GetFullPath());
			std::string Name = Tex->GetNameToString();
			ContentDatabase<SObject_DESC, LevelType>::InsertData(
				{ .Name = Name, .Index = 4000 + i, .Grade = LevelType::Opening, .Size = float4(Tex->GetWidth(), Tex->GetHeight()) });
		}

		Path.MoveParent();
	}

	{
		Path.Move("Shop");

		std::vector<GameEngineFile> Files = Path.GetAllFile({ ".png" });

		for (size_t i = 0; i < Files.size(); i++)
		{
			std::shared_ptr<GameEngineTexture> Tex = GameEngineTexture::Load(Files[i].GetFullPath());
			std::string Name = Tex->GetNameToString();
			ContentDatabase<SObject_DESC, LevelType>::InsertData(
				{ .Name = Name, .Index = 5000 + i, .Grade = LevelType::Shop, .Size = float4(Tex->GetWidth(), Tex->GetHeight()) });
		}

		Path.MoveParent();
	}

	std::vector<SObject_DESC> Castle_SObject_Datas;
	ContentDatabase<SObject_DESC, LevelType>::CopyGradeDatas(LevelType::Castle , Castle_SObject_Datas);

	std::vector<SObject_DESC> Opening_SObject_Datas;
	ContentDatabase<SObject_DESC, LevelType>::CopyGradeDatas(LevelType::Opening, Opening_SObject_Datas);

	std::vector<SObject_DESC> ForestOfHarmony_SObject_Datas;
	ContentDatabase<SObject_DESC, LevelType>::CopyGradeDatas(LevelType::ForestOfHarmony, ForestOfHarmony_SObject_Datas);

	std::vector<SObject_DESC> GranHall_SObject_Datas;
	ContentDatabase<SObject_DESC, LevelType>::CopyGradeDatas(LevelType::Grandhall, GranHall_SObject_Datas);

	std::vector<SObject_DESC> HolyCourtyard_SObject_Datas;
	ContentDatabase<SObject_DESC, LevelType>::CopyGradeDatas(LevelType::HolyCourtyard, HolyCourtyard_SObject_Datas);

	std::vector<SObject_DESC> Shop_SObject_Datas;
	ContentDatabase<SObject_DESC, LevelType>::CopyGradeDatas(LevelType::Shop, Shop_SObject_Datas);

	int a = 0;
}

void ContentCore::CommonTextureLoad()
{
	GameEngineDirectory Path;
	Path.MoveParentToDirectory("Resources");
	Path.Move("Resources");
	Path.Move("Texture");
	Path.Move("UI");
	Path.Move("Common");
	{
		std::vector<GameEngineFile> Files = Path.GetAllFile({ ".png" });

		for (size_t i = 0; i < Files.size(); i++)
		{
			std::shared_ptr<GameEngineTexture> Tex = GameEngineTexture::Load(Files[i].GetFullPath());
		}
	}
}

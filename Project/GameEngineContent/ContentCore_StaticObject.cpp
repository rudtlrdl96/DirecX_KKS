#include "PrecompileHeader.h"
#include "ContentCore.h"
#include "StaticObject.h"

void ContentCore::StaticObjectLoad()
{
	GameEngineDirectory Path;
	Path.MoveParentToDirectory("Resources");
	Path.Move("Resources");
	Path.Move("Texture");

	{
		Path.Move("2_Castle");
		Path.Move("StaticObject");

		std::vector<GameEngineFile> Files = Path.GetAllFile({ ".png" });

		for (size_t i = 0; i < Files.size(); i++)
		{
			std::shared_ptr<GameEngineTexture> Tex = GameEngineTexture::Load(Files[i].GetFullPath());

			if (nullptr == Tex)
			{
				MsgAssert_Rtti<ContentCore>(" - 알 수 없는 이유로 텍스쳐 로드에 실패했습니다");
				continue;
			}

			std::string Name = Tex->GetNameToString();
			ContentDatabase<SObjectMetaData, LevelArea>::InsertData(
				{.Name = Name, .Index = i, .Grade = LevelArea::Castle, .Size = float4(Tex->GetWidth(), Tex->GetHeight())});
		}

		Path.MoveParent();
		Path.MoveParent();
	}

	{
		Path.Move("3_ForestOfHarmony");
		Path.Move("StaticObject");

		std::vector<GameEngineFile> Files = Path.GetAllFile({ ".png" });

		for (size_t i = 0; i < Files.size(); i++)
		{
			std::shared_ptr<GameEngineTexture> Tex = GameEngineTexture::Load(Files[i].GetFullPath());
			

			if (nullptr == Tex)
			{
				MsgAssert_Rtti<ContentCore>(" - 알 수 없는 이유로 텍스쳐 로드에 실패했습니다");
				continue;
			}

			std::string Name = Tex->GetNameToString();
			ContentDatabase<SObjectMetaData, LevelArea>::InsertData(
				{ .Name = Name, .Index = 1000 + i, .Grade = LevelArea::ForestOfHamory, .Size = float4(Tex->GetWidth(), Tex->GetHeight()) });
		}

		Path.MoveParent();
		Path.MoveParent();
	}

	{
		Path.Move("4_GrandHall");
		Path.Move("StaticObject");

		std::vector<GameEngineFile> Files = Path.GetAllFile({ ".png" });

		for (size_t i = 0; i < Files.size(); i++)
		{
			std::shared_ptr<GameEngineTexture> Tex = GameEngineTexture::Load(Files[i].GetFullPath());


			if (nullptr == Tex)
			{
				MsgAssert_Rtti<ContentCore>(" - 알 수 없는 이유로 텍스쳐 로드에 실패했습니다");
				continue;
			}


			std::string Name = Tex->GetNameToString();
			ContentDatabase<SObjectMetaData, LevelArea>::InsertData(
				{ .Name = Name, .Index = 2000 + i, .Grade = LevelArea::GrandHall, .Size = float4(Tex->GetWidth(), Tex->GetHeight()) });
		}

		Path.MoveParent();
		Path.MoveParent();
	}

	{
		Path.Move("5_HolyCourtyard");
		Path.Move("StaticObject");

		std::vector<GameEngineFile> Files = Path.GetAllFile({ ".png" });

		for (size_t i = 0; i < Files.size(); i++)
		{
			std::shared_ptr<GameEngineTexture> Tex = GameEngineTexture::Load(Files[i].GetFullPath());

			if (nullptr == Tex)
			{
				MsgAssert_Rtti<ContentCore>(" - 알 수 없는 이유로 텍스쳐 로드에 실패했습니다");
				continue;
			}

			std::string Name = Tex->GetNameToString();
			ContentDatabase<SObjectMetaData, LevelArea>::InsertData(
				{ .Name = Name, .Index = 3000 + i, .Grade = LevelArea::HolyCourtyard, .Size = float4(Tex->GetWidth(), Tex->GetHeight()) });
		}

		Path.MoveParent();
		Path.MoveParent();
	}

	{
		Path.Move("1_Opening");
		Path.Move("StaticObject");

		std::vector<GameEngineFile> Files = Path.GetAllFile({ ".png" });

		for (size_t i = 0; i < Files.size(); i++)
		{
			std::shared_ptr<GameEngineTexture> Tex = GameEngineTexture::Load(Files[i].GetFullPath());

			if (nullptr == Tex)
			{
				MsgAssert_Rtti<ContentCore>(" - 알 수 없는 이유로 텍스쳐 로드에 실패했습니다");
				continue;
			}

			std::string Name = Tex->GetNameToString();
			ContentDatabase<SObjectMetaData, LevelArea>::InsertData(
				{ .Name = Name, .Index = 4000 + i, .Grade = LevelArea::Opening, .Size = float4(Tex->GetWidth(), Tex->GetHeight()) });
		}

		Path.MoveParent();
		Path.MoveParent();
	}

	{
		Path.Move("7_Shop");
		Path.Move("StaticObject");

		std::vector<GameEngineFile> Files = Path.GetAllFile({ ".png" });

		for (size_t i = 0; i < Files.size(); i++)
		{
			std::shared_ptr<GameEngineTexture> Tex = GameEngineTexture::Load(Files[i].GetFullPath());

			if (nullptr == Tex)
			{
				MsgAssert_Rtti<ContentCore>(" - 알 수 없는 이유로 텍스쳐 로드에 실패했습니다");
				continue;
			}

			std::string Name = Tex->GetNameToString();
			ContentDatabase<SObjectMetaData, LevelArea>::InsertData(
				{ .Name = Name, .Index = 5000 + i, .Grade = LevelArea::Shop, .Size = float4(Tex->GetWidth(), Tex->GetHeight()) });
		}

		Path.MoveParent();
		Path.MoveParent();
	}

	std::vector<SObjectMetaData> Castle_SObject_Datas;
	ContentDatabase<SObjectMetaData, LevelArea>::CopyGradeDatas(LevelArea::Castle , Castle_SObject_Datas);

	std::vector<SObjectMetaData> Opening_SObject_Datas;
	ContentDatabase<SObjectMetaData, LevelArea>::CopyGradeDatas(LevelArea::Opening, Opening_SObject_Datas);

	std::vector<SObjectMetaData> ForestOfHarmony_SObject_Datas;
	ContentDatabase<SObjectMetaData, LevelArea>::CopyGradeDatas(LevelArea::ForestOfHamory, ForestOfHarmony_SObject_Datas);

	std::vector<SObjectMetaData> GranHall_SObject_Datas;
	ContentDatabase<SObjectMetaData, LevelArea>::CopyGradeDatas(LevelArea::GrandHall, GranHall_SObject_Datas);

	std::vector<SObjectMetaData> HolyCourtyard_SObject_Datas;
	ContentDatabase<SObjectMetaData, LevelArea>::CopyGradeDatas(LevelArea::HolyCourtyard, HolyCourtyard_SObject_Datas);

	std::vector<SObjectMetaData> Shop_SObject_Datas;
	ContentDatabase<SObjectMetaData, LevelArea>::CopyGradeDatas(LevelArea::Shop, Shop_SObject_Datas);

	int a = 0;
}

void ContentCore::CommonTextureLoad()
{
	GameEngineDirectory Path;
	Path.MoveParentToDirectory("Resources");
	Path.Move("Resources");
	Path.Move("Texture");
	Path.Move("0_Common");
	Path.Move("UI");

	{
		std::vector<GameEngineFile> Files = Path.GetAllFile({ ".png" });

		for (size_t i = 0; i < Files.size(); i++)
		{
			std::shared_ptr<GameEngineTexture> Tex = GameEngineTexture::Load(Files[i].GetFullPath());
		}

		Path.MoveParent();
	}

	{
		Path.Move("Inventory");

		std::vector<GameEngineFile> Files = Path.GetAllFile({ ".png" });

		for (size_t i = 0; i < Files.size(); i++)
		{
			std::shared_ptr<GameEngineTexture> Tex = GameEngineTexture::Load(Files[i].GetFullPath());
		}
	}
}

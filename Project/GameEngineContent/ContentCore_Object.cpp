#include "PrecompileHeader.h"
#include "ContentCore.h"
#include "MapObject.h"

void ContentCore::ObjectLoad()
{
	GameEngineDirectory Path;
	Path.MoveParentToDirectory("Resources");
	Path.Move("Resources");
	Path.Move("Texture");

	{
		Path.Move("2_Castle");
		Path.Move("Object");

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
			ContentDatabase<ObjectMetaData, LevelArea>::InsertData(
				{.Name = Name, .Index = i, .Grade = LevelArea::Castle, .Size = float4(Tex->GetWidth(), Tex->GetHeight())});
		}

		Path.MoveParent();
		Path.MoveParent();
	}

	{
		Path.Move("3_ForestOfHarmony");
		Path.Move("Object");

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
			ContentDatabase<ObjectMetaData, LevelArea>::InsertData(
				{ .Name = Name, .Index = 1000 + i, .Grade = LevelArea::ForestOfHamory, .Size = float4(Tex->GetWidth(), Tex->GetHeight()) });
		}

		Path.MoveParent();
		Path.MoveParent();
	}

	{
		Path.Move("4_GrandHall");
		Path.Move("Object");

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
			ContentDatabase<ObjectMetaData, LevelArea>::InsertData(
				{ .Name = Name, .Index = 2000 + i, .Grade = LevelArea::GrandHall, .Size = float4(Tex->GetWidth(), Tex->GetHeight()) });
		}

		Path.MoveParent();
		Path.MoveParent();
	}

	{
		Path.Move("5_HolyCourtyard");
		Path.Move("Object");

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
			ContentDatabase<ObjectMetaData, LevelArea>::InsertData(
				{ .Name = Name, .Index = 3000 + i, .Grade = LevelArea::HolyCourtyard, .Size = float4(Tex->GetWidth(), Tex->GetHeight()) });
		}

		Path.MoveParent();
		Path.MoveParent();
	}

	{
		Path.Move("1_Opening");
		Path.Move("Object");

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
			ContentDatabase<ObjectMetaData, LevelArea>::InsertData(
				{ .Name = Name, .Index = 4000 + i, .Grade = LevelArea::Opening, .Size = float4(Tex->GetWidth(), Tex->GetHeight()) });
		}

		Path.MoveParent();
		Path.MoveParent();
	}

	{
		Path.Move("7_Shop");
		Path.Move("Object");

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
			ContentDatabase<ObjectMetaData, LevelArea>::InsertData(
				{ .Name = Name, .Index = 5000 + i, .Grade = LevelArea::Shop, .Size = float4(Tex->GetWidth(), Tex->GetHeight()) });
		}

		Path.MoveParent();
		Path.MoveParent();
	}

	std::vector<ObjectMetaData> Castle_Object_Datas;
	ContentDatabase<ObjectMetaData, LevelArea>::CopyGradeDatas(LevelArea::Castle , Castle_Object_Datas);

	std::vector<ObjectMetaData> Opening_Object_Datas;
	ContentDatabase<ObjectMetaData, LevelArea>::CopyGradeDatas(LevelArea::Opening, Opening_Object_Datas);

	std::vector<ObjectMetaData> ForestOfHarmony_Object_Datas;
	ContentDatabase<ObjectMetaData, LevelArea>::CopyGradeDatas(LevelArea::ForestOfHamory, ForestOfHarmony_Object_Datas);

	std::vector<ObjectMetaData> GranHall_Object_Datas;
	ContentDatabase<ObjectMetaData, LevelArea>::CopyGradeDatas(LevelArea::GrandHall, GranHall_Object_Datas);

	std::vector<ObjectMetaData> HolyCourtyard_Object_Datas;
	ContentDatabase<ObjectMetaData, LevelArea>::CopyGradeDatas(LevelArea::HolyCourtyard, HolyCourtyard_Object_Datas);

	std::vector<ObjectMetaData> Shop_Object_Datas;
	ContentDatabase<ObjectMetaData, LevelArea>::CopyGradeDatas(LevelArea::Shop, Shop_Object_Datas);

	int a = 0;
}

void ContentCore::CommonTextureLoad()
{
	GameEngineDirectory Path;
	Path.MoveParentToDirectory("Resources");
	Path.Move("Resources");
	Path.Move("Texture");
	Path.Move("0_Common");

	{
		Path.Move("DebugTex");
		GameEngineTexture::Load(Path.GetPlusFileName("BoxCol.png").GetFullPath());
		GameEngineTexture::Load(Path.GetPlusFileName("ScaleCol.png").GetFullPath());
		GameEngineTexture::Load(Path.GetPlusFileName("SphereCol.png").GetFullPath());
		GameEngineTexture::Load(Path.GetPlusFileName("EventCol.png").GetFullPath());
		Path.MoveParent();
	}

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

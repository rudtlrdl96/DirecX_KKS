#include "PrecompileHeader.h"
#include "ContentCore.h"
#include "MonsterData.h"

static void LoadMonster(const MonsterData& _Data)
{
	ContentDatabase<MonsterData, MonsterArea>::InsertData(_Data);
}

void ContentCore::MonsterDataLoad()
{
	LoadMonster({ .Name = "칼레온 신병", .ImageName = "CarleonRecruit", .Index = 0, .Grade = MonsterArea::Opning,
	.HP = 40, .Attack = 6 });
	LoadMonster({ .Name = "칼레온 궁수", .ImageName = "CarleonArcher", .Index = 1, .Grade = MonsterArea::Opning,
		.HP = 35, .Attack = 8 });

	LoadMonster({ .Name = "몬갈", .ImageName = "Mongal", .Index = 90, .Grade = MonsterArea::MianBoss });

	LoadMonster({ .Name = "엔트", .ImageName = "Ent", .Index = 100, .Grade = MonsterArea::ForestOfHamory,
		.HP = 55, .Attack = 6});
	LoadMonster({ .Name = "꽃 엔트", .ImageName = "BlossomEnt", .Index = 101, .Grade = MonsterArea::ForestOfHamory,
		.HP = 55, .Attack = 3});
	LoadMonster({ .Name = "뿌리 엔트", .ImageName = "RootEnt", .Index = 102, .Grade = MonsterArea::ForestOfHamory,
		.HP = 45, .Attack = 5});
	LoadMonster({ .Name = "숲지기", .ImageName = "GiganticEnt", .Index = 103, .Grade = MonsterArea::ForestOfHamory,
		.HP = 200, .Attack = 7});

	LoadMonster({ .Name = "칼레온 중보병", .ImageName = "CarleonManAtArms", .Index = 106, .Grade = MonsterArea::ForestOfHamory,
		.HP = 150, .Attack = 7});
	LoadMonster({ .Name = "칼레온 암살자", .ImageName = "CarleonAssassin", .Index = 107, .Grade = MonsterArea::ForestOfHamory,
		.HP = 55, .Attack = 6});
	LoadMonster({ .Name = "화염 마도사", .ImageName = "FlameWizard", .Index = 108, .Grade = MonsterArea::ForestOfHamory,
		.HP = 45, .Attack = 7});
	LoadMonster({ .Name = "빙결 마도사", .ImageName = "GlacialWizard", .Index = 109, .Grade = MonsterArea::ForestOfHamory,
		.HP = 45, .Attack = 7});

	LoadMonster({ .Name = "견습 용사", .ImageName = "RookieHero", .Index = 180, .Grade = MonsterArea::SubBoss
		,.HP = 1200, .Attack = 6});
	LoadMonster({ .Name = "각성 용사", .ImageName = "RookieHero", .Index = 190, .Grade = MonsterArea::MianBoss,
		.HP = 2150, .Attack = 12});

	//LoadMonster({ .Name = "빛나는 신병", .ImageName = "GoldCarleonRecruit", .Index = 200, .Grade = MonsterArea::GrandHall,
	//	.HP = 75, .Attack = 7});
	//LoadMonster({ .Name = "황금갈기 기사", .ImageName = "GoldManeRecruit", .Index = 201, .Grade = MonsterArea::GrandHall,
	//	.HP = 115, .Attack = 9});
	//LoadMonster({ .Name = "황금갈기 창기사", .ImageName = "GoldManeSpearman", .Index = 202, .Grade = MonsterArea::GrandHall,
	//	.HP = 165, .Attack = 11});
	//LoadMonster({ .Name = "황금갈기 궁수", .ImageName = "GoldManeArcher", .Index = 203, .Grade = MonsterArea::GrandHall,
	//	.HP = 85, .Attack = 7});
	//LoadMonster({ .Name = "황금갈기 중보병", .ImageName = "GoldManeManAtArms", .Index = 204, .Grade = MonsterArea::GrandHall,
	//	.HP = 370, .Attack = 11});
	//LoadMonster({ .Name = "황금갈기 마법사", .ImageName = "GoldManeWizard", .Index = 205, .Grade = MonsterArea::GrandHall,
	//	.HP = 110, .Attack = 6});
	//LoadMonster({ .Name = "황금갈기 사제", .ImageName = "GoldManePriest", .Index = 206, .Grade = MonsterArea::GrandHall,
	//.HP = 150, .Attack = 6 });
	//LoadMonster({ .Name = "화염 마도사_그랜드 홀", .ImageName = "FlameWizard", .Index = 207, .Grade = MonsterArea::GrandHall,
	//	.HP = 70, .Attack = 8});
	//LoadMonster({ .Name = "빙결 마도사_그랜드 홀", .ImageName = "GlacialWizard", .Index = 208, .Grade = MonsterArea::GrandHall,
	//	.HP = 70, .Attack = 8});
	//
	//LoadMonster({ .Name = "하녀장", .ImageName = "ChiefMaid", .Index = 209, .Grade = MonsterArea::GrandHall,
	//.HP = 310, .Attack = 8 });
	//LoadMonster({ .Name = "빗자루 메이드", .ImageName = "MaidMelee", .Index = 210, .Grade = MonsterArea::GrandHall,
	//.HP = 65, .Attack = 6 });
	//LoadMonster({ .Name = "그릇 메이드", .ImageName = "MaidRanged", .Index = 211, .Grade = MonsterArea::GrandHall,
	//.HP = 70, .Attack = 7 });
	//LoadMonster({ .Name = "말썽쟁이 하인", .ImageName = "Servant", .Index = 212, .Grade = MonsterArea::GrandHall,
	//.HP = 45, .Attack = 4 });
	//
	//LoadMonster({ .Name = "마법사", .ImageName = "Mage", .Index = 280, .Grade = MonsterArea::SubBoss,
	//	.HP = 1250, .Attack = 7});
	//LoadMonster({ .Name = "사제", .ImageName = "Cleric", .Index = 290, .Grade = MonsterArea::SubBoss,
	//	.HP = 1600, .Attack = 12});

	LoadMonster({ .Name = "레이아나 자매_흑", .ImageName = "LeianaSistersA", .Index = 291, .Grade = MonsterArea::MianBoss,
		.HP = 2800, .Attack = 9});
	LoadMonster({ .Name = "레이아나 자매_백", .ImageName = "LeianaSistersB", .Index = 292, .Grade = MonsterArea::MianBoss,
		.HP = 2800, .Attack = 9 });
	LoadMonster({ .Name = "레이아나 자매_각성", .ImageName = "LeianaSistersDark", .Index = 293, .Grade = MonsterArea::MianBoss,
	.HP = 3650, .Attack = 12 });

	LoadMonster({ .Name = "초대용사_페이즈1", .ImageName = "FirstHero_P1", .Index = 391, .Grade = MonsterArea::MianBoss,
	.HP = 10500, .Attack = 20 });
	LoadMonster({ .Name = "초대용사_페이즈2", .ImageName = "FirstHero_P2", .Index = 392, .Grade = MonsterArea::MianBoss,
		.HP = 15500, .Attack = 25 });
	LoadMonster({ .Name = "초대용사_페이즈3", .ImageName = "FirstHero_P3", .Index = 393, .Grade = MonsterArea::MianBoss,
	.HP = 5500, .Attack = 15});

	std::vector<MonsterData> OpeningDatas;
	ContentDatabase<MonsterData, MonsterArea>::CopyGradeDatas(MonsterArea::Opning, OpeningDatas);

	std::vector<MonsterData> ForestDatas;
	ContentDatabase<MonsterData, MonsterArea>::CopyGradeDatas(MonsterArea::ForestOfHamory, ForestDatas);

	std::vector<MonsterData> GrandHallDatas;
	ContentDatabase<MonsterData, MonsterArea>::CopyGradeDatas(MonsterArea::GrandHall, GrandHallDatas);

	std::vector<MonsterData> MainBossDatas;
	ContentDatabase<MonsterData, MonsterArea>::CopyGradeDatas(MonsterArea::MianBoss, MainBossDatas);

	std::vector<MonsterData> SubBossDatas;
	ContentDatabase<MonsterData, MonsterArea>::CopyGradeDatas(MonsterArea::SubBoss, SubBossDatas);

	GameEngineDirectory Path;
	Path.MoveParentToDirectory("Resources");
	Path.Move("Resources");
	Path.Move("Texture");

	{
		Path.Move("1_Opening");
		Path.Move("Monster");

		// 칼레온 신병
		{
			Path.Move("CarleonRecruit");
			Path.Move("Sheet");

			GameEngineSprite::LoadSheet(Path.GetPlusFileName("CarleonRecruit_Attack.png").GetFullPath(), 5, 1);
			GameEngineSprite::LoadSheet(Path.GetPlusFileName("CarleonRecruit_Dead.png").GetFullPath(), 1, 1);
			GameEngineSprite::LoadSheet(Path.GetPlusFileName("CarleonRecruit_Hit1.png").GetFullPath(), 1, 1);
			GameEngineSprite::LoadSheet(Path.GetPlusFileName("CarleonRecruit_Hit2.png").GetFullPath(), 1, 1);
			GameEngineSprite::LoadSheet(Path.GetPlusFileName("CarleonRecruit_Idle.png").GetFullPath(), 6, 1);
			GameEngineSprite::LoadSheet(Path.GetPlusFileName("CarleonRecruit_Walk.png").GetFullPath(), 8, 1);

			Path.MoveParent();
			Path.MoveParent();
		}

		// 칼레온 궁수
		{
			Path.Move("CarleonArcher");
			Path.Move("Sheet");

			GameEngineSprite::LoadSheet(Path.GetPlusFileName("CarleonArcher_Attack.png").GetFullPath(), 4, 1);
			GameEngineSprite::LoadSheet(Path.GetPlusFileName("CarleonArcher_Dead.png").GetFullPath(), 1, 1);
			GameEngineSprite::LoadSheet(Path.GetPlusFileName("CarleonArcher_Hit1.png").GetFullPath(), 1, 1);
			GameEngineSprite::LoadSheet(Path.GetPlusFileName("CarleonArcher_Hit2.png").GetFullPath(), 1, 1);
			GameEngineSprite::LoadSheet(Path.GetPlusFileName("CarleonArcher_Idle.png").GetFullPath(), 5, 1);
			GameEngineSprite::LoadSheet(Path.GetPlusFileName("CarleonArcher_Walk.png").GetFullPath(), 6, 1);

			Path.MoveParent();
			Path.MoveParent();
		}
	}

	{
	
	}

	int a = 0;
}
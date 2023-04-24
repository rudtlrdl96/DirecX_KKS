#include "PrecompileHeader.h"
#include "ContentCore.h"
#include "MonsterData.h"

static void LoadMonster(const MonsterData& _Data)
{
	ContentDatabase<MonsterData, MonsterArea>::InsertData(_Data);
}

void ContentCore::MonsterDataLoad()
{
	LoadMonster({ .Name = "Į���� �ź�_������", .ImageName = "CarleonRecruit", .Index = 0, .Grade = MonsterArea::Opning});
	LoadMonster({ .Name = "Į���� �ü�_������", .ImageName = "CarleonArcher", .Index = 1, .Grade = MonsterArea::Opning });
	LoadMonster({ .Name = "��", .ImageName = "Mongal", .Index = 90, .Grade = MonsterArea::MianBoss });

	LoadMonster({ .Name = "��Ʈ", .ImageName = "Ent", .Index = 100, .Grade = MonsterArea::ForestOfHamory,
		.HP = 55, .Attack = 6});
	LoadMonster({ .Name = "�� ��Ʈ", .ImageName = "BlossomEnt", .Index = 101, .Grade = MonsterArea::ForestOfHamory,
		.HP = 55, .Attack = 3});
	LoadMonster({ .Name = "�Ѹ� ��Ʈ", .ImageName = "RootEnt", .Index = 102, .Grade = MonsterArea::ForestOfHamory,
		.HP = 45, .Attack = 5});
	LoadMonster({ .Name = "������", .ImageName = "GiganticEnt", .Index = 103, .Grade = MonsterArea::ForestOfHamory,
		.HP = 200, .Attack = 7});
	LoadMonster({ .Name = "Į���� �ź�", .ImageName = "CarleonRecruit", .Index = 104, .Grade = MonsterArea::ForestOfHamory,
		.HP = 40, .Attack = 6});
	LoadMonster({ .Name = "Į���� �ü�", .ImageName = "CarleonArcher", .Index = 105, .Grade = MonsterArea::ForestOfHamory,
		.HP = 35, .Attack = 8});
	LoadMonster({ .Name = "Į���� �ߺ���", .ImageName = "CarleonManAtArms", .Index = 106, .Grade = MonsterArea::ForestOfHamory,
		.HP = 150, .Attack = 7});
	LoadMonster({ .Name = "Į���� �ϻ���", .ImageName = "CarleonAssassin", .Index = 107, .Grade = MonsterArea::ForestOfHamory,
		.HP = 55, .Attack = 6});
	LoadMonster({ .Name = "ȭ�� ������_��ȭ�� ��", .ImageName = "FlameWizard", .Index = 108, .Grade = MonsterArea::ForestOfHamory,
		.HP = 45, .Attack = 7});
	LoadMonster({ .Name = "���� ������_��ȭ�� ��", .ImageName = "GlacialWizard", .Index = 109, .Grade = MonsterArea::ForestOfHamory,
		.HP = 45, .Attack = 7});

	LoadMonster({ .Name = "�߽� ���", .ImageName = "RookieHero", .Index = 180, .Grade = MonsterArea::SubBoss
		,.HP = 1200, .Attack = 6});
	LoadMonster({ .Name = "���� ���", .ImageName = "RookieHero", .Index = 190, .Grade = MonsterArea::MianBoss,
		.HP = 2150, .Attack = 12});

	LoadMonster({ .Name = "������ �ź�", .ImageName = "GoldCarleonRecruit", .Index = 200, .Grade = MonsterArea::GrandHall,
		.HP = 75, .Attack = 7});
	LoadMonster({ .Name = "Ȳ�ݰ��� ���", .ImageName = "GoldManeRecruit", .Index = 201, .Grade = MonsterArea::GrandHall,
		.HP = 115, .Attack = 9});
	LoadMonster({ .Name = "Ȳ�ݰ��� â���", .ImageName = "GoldManeSpearman", .Index = 202, .Grade = MonsterArea::GrandHall,
		.HP = 165, .Attack = 11});
	LoadMonster({ .Name = "Ȳ�ݰ��� �ü�", .ImageName = "GoldManeArcher", .Index = 203, .Grade = MonsterArea::GrandHall,
		.HP = 85, .Attack = 7});
	LoadMonster({ .Name = "Ȳ�ݰ��� �ߺ���", .ImageName = "GoldManeManAtArms", .Index = 204, .Grade = MonsterArea::GrandHall,
		.HP = 370, .Attack = 11});
	LoadMonster({ .Name = "Ȳ�ݰ��� ������", .ImageName = "GoldManeWizard", .Index = 205, .Grade = MonsterArea::GrandHall,
		.HP = 110, .Attack = 6});
	LoadMonster({ .Name = "Ȳ�ݰ��� ����", .ImageName = "GoldManePriest", .Index = 206, .Grade = MonsterArea::GrandHall,
	.HP = 150, .Attack = 6 });
	LoadMonster({ .Name = "ȭ�� ������_�׷��� Ȧ", .ImageName = "FlameWizard", .Index = 207, .Grade = MonsterArea::GrandHall,
		.HP = 70, .Attack = 8});
	LoadMonster({ .Name = "���� ������_�׷��� Ȧ", .ImageName = "GlacialWizard", .Index = 208, .Grade = MonsterArea::GrandHall,
		.HP = 70, .Attack = 8});

	LoadMonster({ .Name = "�ϳ���", .ImageName = "ChiefMaid", .Index = 209, .Grade = MonsterArea::GrandHall,
	.HP = 310, .Attack = 8 });
	LoadMonster({ .Name = "���ڷ� ���̵�", .ImageName = "MaidMelee", .Index = 210, .Grade = MonsterArea::GrandHall,
	.HP = 65, .Attack = 6 });
	LoadMonster({ .Name = "�׸� ���̵�", .ImageName = "MaidRanged", .Index = 211, .Grade = MonsterArea::GrandHall,
	.HP = 70, .Attack = 7 });
	LoadMonster({ .Name = "�������� ����", .ImageName = "Servant", .Index = 212, .Grade = MonsterArea::GrandHall,
	.HP = 45, .Attack = 4 });

	LoadMonster({ .Name = "������", .ImageName = "Mage", .Index = 280, .Grade = MonsterArea::SubBoss,
		.HP = 1250, .Attack = 7});
	LoadMonster({ .Name = "����", .ImageName = "Cleric", .Index = 290, .Grade = MonsterArea::SubBoss,
		.HP = 1600, .Attack = 12});
	LoadMonster({ .Name = "���̾Ƴ� �ڸ�_��", .ImageName = "LeianaSistersA", .Index = 291, .Grade = MonsterArea::MianBoss,
		.HP = 2800, .Attack = 9});
	LoadMonster({ .Name = "���̾Ƴ� �ڸ�_��", .ImageName = "LeianaSistersB", .Index = 292, .Grade = MonsterArea::MianBoss,
		.HP = 2800, .Attack = 9 });
	LoadMonster({ .Name = "���̾Ƴ� �ڸ�_����", .ImageName = "LeianaSistersDark", .Index = 293, .Grade = MonsterArea::MianBoss,
	.HP = 3650, .Attack = 12 });

	LoadMonster({ .Name = "�ʴ���_������1", .ImageName = "FirstHero_P1", .Index = 391, .Grade = MonsterArea::MianBoss,
	.HP = 10500, .Attack = 20 });
	LoadMonster({ .Name = "�ʴ���_������2", .ImageName = "FirstHero_P2", .Index = 392, .Grade = MonsterArea::MianBoss,
		.HP = 15500, .Attack = 25 });
	LoadMonster({ .Name = "�ʴ���_������3", .ImageName = "FirstHero_P3", .Index = 393, .Grade = MonsterArea::MianBoss,
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

	int a = 0;
}
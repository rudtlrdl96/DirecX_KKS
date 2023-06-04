#include "PrecompileHeader.h"
#include "ContentCore.h"
#include "MonsterData.h"

static void LoadMonster(const MonsterData& _Data)
{
	ContentDatabase<MonsterData, LevelArea>::InsertData(_Data);
}

void ContentCore::MonsterDataLoad()
{
	LoadMonster({ .Name = "Į���� �ź�", .ImageName = "Preview_CarleonRecruit.png", .Index = 0, .Grade = LevelArea::Opening,
	.HP = 40, .Attack = 6 });
	LoadMonster({ .Name = "Į���� �ü�", .ImageName = "Preview_CarleonArcher.png", .Index = 1, .Grade = LevelArea::Opening,
		.HP = 35, .Attack = 8 });

	LoadMonster({ .Name = "��", .ImageName = "Preview_Mongal.png", .Index = 90, .Grade = LevelArea::Opening,
		.HP = 500, .Attack = 12});
	
	LoadMonster({ .Name = "��Ʈ", .ImageName = "Preview_Ent.png", .Index = 100, .Grade = LevelArea::ForestOfHamory,
		.HP = 55, .Attack = 6});
	LoadMonster({ .Name = "�� ��Ʈ", .ImageName = "Preview_BlossomEnt.png", .Index = 101, .Grade = LevelArea::ForestOfHamory,
		.HP = 55, .Attack = 3});
	LoadMonster({ .Name = "�Ѹ� ��Ʈ", .ImageName = "Preview_RootEnt.png", .Index = 102, .Grade = LevelArea::ForestOfHamory,
		.HP = 45, .Attack = 5});
	LoadMonster({ .Name = "������", .ImageName = "Preview_GiganticEnt.png", .Index = 103, .Grade = LevelArea::ForestOfHamory,
		.HP = 200, .Attack = 7});

	LoadMonster({ .Name = "Į���� �ߺ���", .ImageName = "Preview_CarleonManAtArms.png", .Index = 106, .Grade = LevelArea::ForestOfHamory,
		.HP = 150, .Attack = 7});
	//LoadMonster({ .Name = "Į���� �ϻ���", .ImageName = "Preview_CarleonRecruit.png", .Index = 107, .Grade = LevelArea::ForestOfHamory,
	//	.HP = 55, .Attack = 6});
	LoadMonster({ .Name = "ȭ�� ������", .ImageName = "Preview_FireFlower.png", .Index = 108, .Grade = LevelArea::ForestOfHamory,
		.HP = 45, .Attack = 7});
	LoadMonster({ .Name = "���� ������", .ImageName = "Preview_GlacialWizard.png", .Index = 109, .Grade = LevelArea::ForestOfHamory,
		.HP = 45, .Attack = 7});

	//LoadMonster({ .Name = "�߽� ���", .ImageName = "Preview_CarleonRecruit.png", .Index = 180, .Grade = LevelArea::ForestOfHamory
	//	,.HP = 1200, .Attack = 6});
	//LoadMonster({ .Name = "���� ���", .ImageName = "Preview_CarleonRecruit.png", .Index = 190, .Grade = LevelArea::ForestOfHamory,
	//	.HP = 2150, .Attack = 12});

	//LoadMonster({ .Name = "������ �ź�", .ImageName = "GoldCarleonRecruit", .Index = 200, .Grade = LevelArea::GrandHall,
	//	.HP = 75, .Attack = 7});
	//LoadMonster({ .Name = "Ȳ�ݰ��� ���", .ImageName = "GoldManeRecruit", .Index = 201, .Grade = LevelArea::GrandHall,
	//	.HP = 115, .Attack = 9});
	//LoadMonster({ .Name = "Ȳ�ݰ��� â���", .ImageName = "GoldManeSpearman", .Index = 202, .Grade = LevelArea::GrandHall,
	//	.HP = 165, .Attack = 11});
	//LoadMonster({ .Name = "Ȳ�ݰ��� �ü�", .ImageName = "GoldManeArcher", .Index = 203, .Grade = LevelArea::GrandHall,
	//	.HP = 85, .Attack = 7});
	//LoadMonster({ .Name = "Ȳ�ݰ��� �ߺ���", .ImageName = "GoldManeManAtArms", .Index = 204, .Grade = LevelArea::GrandHall,
	//	.HP = 370, .Attack = 11});
	//LoadMonster({ .Name = "Ȳ�ݰ��� ������", .ImageName = "GoldManeWizard", .Index = 205, .Grade = LevelArea::GrandHall,
	//	.HP = 110, .Attack = 6});
	//LoadMonster({ .Name = "Ȳ�ݰ��� ����", .ImageName = "GoldManePriest", .Index = 206, .Grade = LevelArea::GrandHall,
	//.HP = 150, .Attack = 6 });
	//LoadMonster({ .Name = "ȭ�� ������_�׷��� Ȧ", .ImageName = "FlameWizard", .Index = 207, .Grade = LevelArea::GrandHall,
	//	.HP = 70, .Attack = 8});
	//LoadMonster({ .Name = "���� ������_�׷��� Ȧ", .ImageName = "GlacialWizard", .Index = 208, .Grade = LevelArea::GrandHall,
	//	.HP = 70, .Attack = 8});
	//
	//LoadMonster({ .Name = "�ϳ���", .ImageName = "ChiefMaid", .Index = 209, .Grade = LevelArea::GrandHall,
	//.HP = 310, .Attack = 8 });
	//LoadMonster({ .Name = "���ڷ� ���̵�", .ImageName = "MaidMelee", .Index = 210, .Grade = LevelArea::GrandHall,
	//.HP = 65, .Attack = 6 });
	//LoadMonster({ .Name = "�׸� ���̵�", .ImageName = "MaidRanged", .Index = 211, .Grade = LevelArea::GrandHall,
	//.HP = 70, .Attack = 7 });
	//LoadMonster({ .Name = "�������� ����", .ImageName = "Servant", .Index = 212, .Grade = LevelArea::GrandHall,
	//.HP = 45, .Attack = 4 });
	//
	//LoadMonster({ .Name = "������", .ImageName = "Mage", .Index = 280, .Grade = LevelArea::GrandHall,
	//	.HP = 1250, .Attack = 7});
	//LoadMonster({ .Name = "����", .ImageName = "Cleric", .Index = 290, .Grade = LevelArea::GrandHall,
	//	.HP = 1600, .Attack = 12});

	//LoadMonster({ .Name = "���̾Ƴ� �ڸ�_��", .ImageName = "LeianaSistersA", .Index = 291, .Grade = LevelArea::GrandHall,
	//	.HP = 2800, .Attack = 9});
	//LoadMonster({ .Name = "���̾Ƴ� �ڸ�_��", .ImageName = "LeianaSistersB", .Index = 292, .Grade = LevelArea::GrandHall,
	//	.HP = 2800, .Attack = 9 });
	//LoadMonster({ .Name = "���̾Ƴ� �ڸ�_����", .ImageName = "LeianaSistersDark", .Index = 293, .Grade = LevelArea::GrandHall,
	//.HP = 3650, .Attack = 12 });
	//
	//LoadMonster({ .Name = "�ʴ���_������1", .ImageName = "FirstHero_P1", .Index = 391, .Grade = LevelArea::HolyCourtyard,
	//.HP = 10500, .Attack = 20 });
	//LoadMonster({ .Name = "�ʴ���_������2", .ImageName = "FirstHero_P2", .Index = 392, .Grade = LevelArea::HolyCourtyard,
	//	.HP = 15500, .Attack = 25 });
	//LoadMonster({ .Name = "�ʴ���_������3", .ImageName = "FirstHero_P3", .Index = 393, .Grade = LevelArea::HolyCourtyard,
	//.HP = 5500, .Attack = 15});

	std::vector<MonsterData> OpeningDatas;
	ContentDatabase<MonsterData, LevelArea>::CopyGradeDatas(LevelArea::Opening, OpeningDatas);

	std::vector<MonsterData> ForestDatas;
	ContentDatabase<MonsterData, LevelArea>::CopyGradeDatas(LevelArea::ForestOfHamory, ForestDatas);

	std::vector<MonsterData> GrandHallDatas;
	ContentDatabase<MonsterData, LevelArea>::CopyGradeDatas(LevelArea::GrandHall, GrandHallDatas);

	std::vector<MonsterData> HolyCourtyardDatas;
	ContentDatabase<MonsterData, LevelArea>::CopyGradeDatas(LevelArea::HolyCourtyard, HolyCourtyardDatas);

	GameEngineDirectory Path;
	Path.MoveParentToDirectory("Resources");
	Path.Move("Resources");
	Path.Move("Texture");

	{
		Path.Move("0_Common");
		Path.Move("Monster");
		Path.Move("Preview");

		std::vector<GameEngineFile> Files = Path.GetAllFile({ ".png" });

		for (UINT i = 0; i < Files.size(); i++)
		{
			std::shared_ptr<GameEngineTexture> Tex = GameEngineTexture::Load(Files[i].GetFullPath());
		}

		Path.MoveParent();
		Path.MoveParent();
		Path.MoveParent();
	}

	{
		Path.Move("1_Opening");
		Path.Move("Monster");

		// Į���� �ź�
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

		// Į���� �ü�
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

		// ��
		{
			Path.Move("Mongal");
			Path.Move("Sheet");

			GameEngineSprite::LoadSheet(Path.GetPlusFileName("Mongal_Attack.png").GetFullPath(), 7, 1);
			GameEngineSprite::LoadSheet(Path.GetPlusFileName("Mongal_BattleDead.png").GetFullPath(), 7, 2);
			GameEngineSprite::LoadSheet(Path.GetPlusFileName("Mongal_BattleHit1.png").GetFullPath(), 1, 1);
			GameEngineSprite::LoadSheet(Path.GetPlusFileName("Mongal_BattleHit2.png").GetFullPath(), 1, 1);
			GameEngineSprite::LoadSheet(Path.GetPlusFileName("Mongal_Death.png").GetFullPath(), 1, 1);
			GameEngineSprite::LoadSheet(Path.GetPlusFileName("Mongal_BattleIdle.png").GetFullPath(), 6, 1);
			GameEngineSprite::LoadSheet(Path.GetPlusFileName("Mongal_BattleWalk.png").GetFullPath(), 4, 2);
			GameEngineSprite::LoadSheet(Path.GetPlusFileName("Mongal_Idle.png").GetFullPath(), 6, 1);
			GameEngineSprite::LoadSheet(Path.GetPlusFileName("Mongal_Laugh.png").GetFullPath(), 3, 1);
			GameEngineSprite::LoadSheet(Path.GetPlusFileName("Mongal_WakeUp.png").GetFullPath(), 7, 3);
			GameEngineSprite::LoadSheet(Path.GetPlusFileName("Mongal_Walk.png").GetFullPath(), 4, 2);

			Path.MoveParent();
			Path.MoveParent();
		}
	
		Path.MoveParent();
		Path.MoveParent();
	}

	{
		Path.Move("3_ForestOfHarmony");
		Path.Move("Monster");

		// Į���� �ߺ���
		{
			Path.Move("CarleonManAtArms");
			Path.Move("Sheet");

			GameEngineSprite::LoadSheet(Path.GetPlusFileName("CarleonManAtArms_Attack.png").GetFullPath(), 8, 1);
			GameEngineSprite::LoadSheet(Path.GetPlusFileName("CarleonManAtArms_Tackle.png").GetFullPath(), 3, 1);
			GameEngineSprite::LoadSheet(Path.GetPlusFileName("CarleonManAtArms_Dead.png").GetFullPath(), 1, 1);
			GameEngineSprite::LoadSheet(Path.GetPlusFileName("CarleonManAtArms_Idle.png").GetFullPath(), 5, 1);
			GameEngineSprite::LoadSheet(Path.GetPlusFileName("CarleonManAtArms_Walk.png").GetFullPath(), 8, 1);

			Path.MoveParent();
			Path.MoveParent();
		}

		// ��Ʈ
		{
			Path.Move("Ent");
			Path.Move("Sheet");

			GameEngineSprite::LoadSheet(Path.GetPlusFileName("Ent_Attack.png").GetFullPath(), 4, 1);
			GameEngineSprite::LoadSheet(Path.GetPlusFileName("Ent_Dead.png").GetFullPath(), 1, 1);
			GameEngineSprite::LoadSheet(Path.GetPlusFileName("Ent_Hit1.png").GetFullPath(), 1, 1);
			GameEngineSprite::LoadSheet(Path.GetPlusFileName("Ent_Hit2.png").GetFullPath(), 1, 1);
			GameEngineSprite::LoadSheet(Path.GetPlusFileName("Ent_Idle.png").GetFullPath(), 5, 1);
			GameEngineSprite::LoadSheet(Path.GetPlusFileName("Ent_Walk.png").GetFullPath(), 6, 1);

			Path.MoveParent();
			Path.MoveParent();
		}

		// �Ѹ� ��Ʈ
		{
			Path.Move("RootEnt");
			Path.Move("Sheet");

			GameEngineSprite::LoadSheet(Path.GetPlusFileName("RootEnt_Attack.png").GetFullPath(), 8, 1);
			GameEngineSprite::LoadSheet(Path.GetPlusFileName("RootEnt_Dead.png").GetFullPath(), 1, 1);
			GameEngineSprite::LoadSheet(Path.GetPlusFileName("RootEnt_Hit1.png").GetFullPath(), 1, 1);
			GameEngineSprite::LoadSheet(Path.GetPlusFileName("RootEnt_Hit2.png").GetFullPath(), 1, 1);
			GameEngineSprite::LoadSheet(Path.GetPlusFileName("RootEnt_Idle.png").GetFullPath(), 5, 1);
			GameEngineSprite::LoadSheet(Path.GetPlusFileName("RootEnt_Walk.png").GetFullPath(), 6, 1);

			Path.MoveParent();
			Path.MoveParent();
		}

		// �� ��Ʈ
		{
			Path.Move("BlossomEnt");
			Path.Move("Sheet");

			GameEngineSprite::LoadSheet(Path.GetPlusFileName("BlossomEnt_Attack.png").GetFullPath(), 10, 1);
			GameEngineSprite::LoadSheet(Path.GetPlusFileName("BlossomEnt_Hit1.png").GetFullPath(), 1, 1);
			GameEngineSprite::LoadSheet(Path.GetPlusFileName("BlossomEnt_Hit2.png").GetFullPath(), 1, 1);
			GameEngineSprite::LoadSheet(Path.GetPlusFileName("BlossomEnt_Idle.png").GetFullPath(), 5, 1);
			GameEngineSprite::LoadSheet(Path.GetPlusFileName("BlossomEnt_Walk.png").GetFullPath(), 6, 1);

			Path.MoveParent();
			Path.MoveParent();
		}

		// ������(���̾�Ʈ ��Ʈ)
		{
			Path.Move("GiganticEnt");
			Path.Move("Sheet");

			GameEngineSprite::LoadSheet(Path.GetPlusFileName("GiganticEnt_Idle.png").GetFullPath(), 5, 1);
			GameEngineSprite::LoadSheet(Path.GetPlusFileName("GiganticEnt_MeleeAttack.png").GetFullPath(), 7, 1);
			GameEngineSprite::LoadSheet(Path.GetPlusFileName("GiganticEnt_RangeAttack.png").GetFullPath(), 4, 1);

			Path.MoveParent();
			Path.MoveParent();
		}


		// ȭ�� ������
		{
			Path.Move("FlameWizard");
			Path.Move("Sheet");

			GameEngineSprite::LoadSheet(Path.GetPlusFileName("FlameWizard_AttackEnter.png").GetFullPath(), 3, 1);
			GameEngineSprite::LoadSheet(Path.GetPlusFileName("FlameWizard_AttackLoop.png").GetFullPath(), 5, 1);
			GameEngineSprite::LoadSheet(Path.GetPlusFileName("FlameWizard_Hit1.png").GetFullPath(), 1, 1);
			GameEngineSprite::LoadSheet(Path.GetPlusFileName("FlameWizard_Hit2.png").GetFullPath(), 1, 1);
			GameEngineSprite::LoadSheet(Path.GetPlusFileName("FlameWizard_Idle.png").GetFullPath(), 5, 1);
			GameEngineSprite::LoadSheet(Path.GetPlusFileName("FlameWizard_TeleportIn.png").GetFullPath(), 8, 1);
			GameEngineSprite::LoadSheet(Path.GetPlusFileName("FlameWizard_TeleportOut.png").GetFullPath(), 5, 1);

			Path.MoveParent();
			Path.MoveParent();
		}

		// ���� ������
		{
			Path.Move("GlacialWizard");
			Path.Move("Sheet");

			GameEngineSprite::LoadSheet(Path.GetPlusFileName("GlacialWizard_Attack.png").GetFullPath(), 8, 1);
			GameEngineSprite::LoadSheet(Path.GetPlusFileName("GlacialWizard_Hit1.png").GetFullPath(), 1, 1);
			GameEngineSprite::LoadSheet(Path.GetPlusFileName("GlacialWizard_Hit2.png").GetFullPath(), 1, 1);
			GameEngineSprite::LoadSheet(Path.GetPlusFileName("GlacialWizard_Idle.png").GetFullPath(), 5, 1);
			GameEngineSprite::LoadSheet(Path.GetPlusFileName("GlacialWizard_TeleportIn.png").GetFullPath(), 8, 1);
			GameEngineSprite::LoadSheet(Path.GetPlusFileName("GlacialWizard_TeleportOut.png").GetFullPath(), 5, 1);

			Path.MoveParent();
			Path.MoveParent();
		}
	}

	int a = 0;
}
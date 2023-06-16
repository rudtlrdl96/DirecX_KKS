#include "PrecompileHeader.h"
#include "ContentCore.h"
#include "MonsterData.h"

static void LoadMonster(const MonsterData& _Data)
{
	ContentDatabase<MonsterData, LevelArea>::InsertData(_Data);
}

void ContentCore::MonsterDataLoad()
{
	LoadMonster({ .Name = "칼레온 신병", .ImageName = "Preview_CarleonRecruit.png", .Index = 0, .Grade = LevelArea::Opening,
	.HP = 40, .Attack = 6 });
	LoadMonster({ .Name = "칼레온 궁수", .ImageName = "Preview_CarleonArcher.png", .Index = 1, .Grade = LevelArea::Opening,
		.HP = 35, .Attack = 8 });

	LoadMonster({ .Name = "몬갈", .ImageName = "Preview_Mongal.png", .Index = 90, .Grade = LevelArea::Opening,
		.HP = 300, .Attack = 12});
	
	LoadMonster({ .Name = "엔트", .ImageName = "Preview_Ent.png", .Index = 100, .Grade = LevelArea::ForestOfHamory,
		.HP = 55, .Attack = 6});
	LoadMonster({ .Name = "꽃 엔트", .ImageName = "Preview_BlossomEnt.png", .Index = 101, .Grade = LevelArea::ForestOfHamory,
		.HP = 55, .Attack = 3});
	LoadMonster({ .Name = "뿌리 엔트", .ImageName = "Preview_RootEnt.png", .Index = 102, .Grade = LevelArea::ForestOfHamory,
		.HP = 45, .Attack = 5});
	LoadMonster({ .Name = "숲지기", .ImageName = "Preview_GiganticEnt.png", .Index = 103, .Grade = LevelArea::ForestOfHamory,
		.HP = 200, .Attack = 7});

	LoadMonster({ .Name = "칼레온 중보병", .ImageName = "Preview_CarleonManAtArms.png", .Index = 106, .Grade = LevelArea::ForestOfHamory,
		.HP = 150, .Attack = 7});
	//LoadMonster({ .Name = "칼레온 암살자", .ImageName = "Preview_CarleonRecruit.png", .Index = 107, .Grade = LevelArea::ForestOfHamory,
	//	.HP = 55, .Attack = 6});
	LoadMonster({ .Name = "화염 마도사", .ImageName = "Preview_FireFlower.png", .Index = 108, .Grade = LevelArea::ForestOfHamory,
		.HP = 45, .Attack = 7});
	LoadMonster({ .Name = "빙결 마도사", .ImageName = "Preview_GlacialWizard.png", .Index = 109, .Grade = LevelArea::ForestOfHamory,
		.HP = 45, .Attack = 7});

	LoadMonster({ .Name = "견습 용사", .ImageName = "Preview_RookieHero.png", .Index = 180, .Grade = LevelArea::ForestOfHamory
		,.HP = 1350, .Attack = 6});
	LoadMonster({ .Name = "각성 용사", .ImageName = "Preview_VeteranHero.png", .Index = 190, .Grade = LevelArea::ForestOfHamory,
		.HP = 2050, .Attack = 12});

	//LoadMonster({ .Name = "빛나는 신병", .ImageName = "GoldCarleonRecruit", .Index = 200, .Grade = LevelArea::GrandHall,
	//	.HP = 75, .Attack = 7});
	//LoadMonster({ .Name = "황금갈기 기사", .ImageName = "GoldManeRecruit", .Index = 201, .Grade = LevelArea::GrandHall,
	//	.HP = 115, .Attack = 9});
	//LoadMonster({ .Name = "황금갈기 창기사", .ImageName = "GoldManeSpearman", .Index = 202, .Grade = LevelArea::GrandHall,
	//	.HP = 165, .Attack = 11});
	//LoadMonster({ .Name = "황금갈기 궁수", .ImageName = "GoldManeArcher", .Index = 203, .Grade = LevelArea::GrandHall,
	//	.HP = 85, .Attack = 7});
	//LoadMonster({ .Name = "황금갈기 중보병", .ImageName = "GoldManeManAtArms", .Index = 204, .Grade = LevelArea::GrandHall,
	//	.HP = 370, .Attack = 11});
	//LoadMonster({ .Name = "황금갈기 마법사", .ImageName = "GoldManeWizard", .Index = 205, .Grade = LevelArea::GrandHall,
	//	.HP = 110, .Attack = 6});
	//LoadMonster({ .Name = "황금갈기 사제", .ImageName = "GoldManePriest", .Index = 206, .Grade = LevelArea::GrandHall,
	//.HP = 150, .Attack = 6 });
	//LoadMonster({ .Name = "화염 마도사_그랜드 홀", .ImageName = "FlameWizard", .Index = 207, .Grade = LevelArea::GrandHall,
	//	.HP = 70, .Attack = 8});
	//LoadMonster({ .Name = "빙결 마도사_그랜드 홀", .ImageName = "GlacialWizard", .Index = 208, .Grade = LevelArea::GrandHall,
	//	.HP = 70, .Attack = 8});
	//
	//LoadMonster({ .Name = "하녀장", .ImageName = "ChiefMaid", .Index = 209, .Grade = LevelArea::GrandHall,
	//.HP = 310, .Attack = 8 });
	//LoadMonster({ .Name = "빗자루 메이드", .ImageName = "MaidMelee", .Index = 210, .Grade = LevelArea::GrandHall,
	//.HP = 65, .Attack = 6 });
	//LoadMonster({ .Name = "그릇 메이드", .ImageName = "MaidRanged", .Index = 211, .Grade = LevelArea::GrandHall,
	//.HP = 70, .Attack = 7 });
	//LoadMonster({ .Name = "말썽쟁이 하인", .ImageName = "Servant", .Index = 212, .Grade = LevelArea::GrandHall,
	//.HP = 45, .Attack = 4 });
	//
	//LoadMonster({ .Name = "마법사", .ImageName = "Mage", .Index = 280, .Grade = LevelArea::GrandHall,
	//	.HP = 1250, .Attack = 7});
	//LoadMonster({ .Name = "사제", .ImageName = "Cleric", .Index = 290, .Grade = LevelArea::GrandHall,
	//	.HP = 1600, .Attack = 12});

	//LoadMonster({ .Name = "레이아나 자매_흑", .ImageName = "LeianaSistersA", .Index = 291, .Grade = LevelArea::GrandHall,
	//	.HP = 2800, .Attack = 9});
	//LoadMonster({ .Name = "레이아나 자매_백", .ImageName = "LeianaSistersB", .Index = 292, .Grade = LevelArea::GrandHall,
	//	.HP = 2800, .Attack = 9 });
	//LoadMonster({ .Name = "레이아나 자매_각성", .ImageName = "LeianaSistersDark", .Index = 293, .Grade = LevelArea::GrandHall,
	//.HP = 3650, .Attack = 12 });
	//
	//LoadMonster({ .Name = "초대용사_페이즈1", .ImageName = "FirstHero_P1", .Index = 391, .Grade = LevelArea::HolyCourtyard,
	//.HP = 10500, .Attack = 20 });
	//LoadMonster({ .Name = "초대용사_페이즈2", .ImageName = "FirstHero_P2", .Index = 392, .Grade = LevelArea::HolyCourtyard,
	//	.HP = 15500, .Attack = 25 });
	//LoadMonster({ .Name = "초대용사_페이즈3", .ImageName = "FirstHero_P3", .Index = 393, .Grade = LevelArea::HolyCourtyard,
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

		// 몬갈
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

		// 칼레온 중보병
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

		// 엔트
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

		// 뿌리 엔트
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

		// 꽃 엔트
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

		// 숲지기(자이언트 엔트)
		{
			Path.Move("GiganticEnt");
			Path.Move("Sheet");

			GameEngineSprite::LoadSheet(Path.GetPlusFileName("GiganticEnt_Idle.png").GetFullPath(), 5, 1);
			GameEngineSprite::LoadSheet(Path.GetPlusFileName("GiganticEnt_MeleeAttack.png").GetFullPath(), 7, 1);
			GameEngineSprite::LoadSheet(Path.GetPlusFileName("GiganticEnt_RangeAttack.png").GetFullPath(), 4, 1);

			Path.MoveParent();
			Path.MoveParent();
		}


		// 화염 마법사
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

		// 빙결 마법사
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

	// 견습용사
	{
		GameEngineDirectory Path;

		Path.MoveParentToDirectory("Resources");
		Path.Move("Resources");
		Path.Move("Texture");
		Path.Move("3_ForestOfHarmony");
		Path.Move("Boss");
		Path.Move("RookieHero");
		Path.Move("Sheet");

		GameEngineSprite::LoadSheet(Path.GetPlusFileName("RookieHero_Idle.png").GetFullPath(), 6, 1);
		GameEngineSprite::LoadSheet(Path.GetPlusFileName("RookieHero_Intro_ComboA.png").GetFullPath(), 8, 6);
		GameEngineSprite::LoadSheet(Path.GetPlusFileName("RookieHero_Intro_ComboB.png").GetFullPath(), 7, 4);
		GameEngineSprite::LoadSheet(Path.GetPlusFileName("RookieHero_Yeah.png").GetFullPath(), 7, 3);
		GameEngineSprite::LoadSheet(Path.GetPlusFileName("RookieHero_lol.png").GetFullPath(), 5, 1);
		GameEngineSprite::LoadSheet(Path.GetPlusFileName("RookieHero_lol_End.png").GetFullPath(), 1, 1);
		GameEngineSprite::LoadSheet(Path.GetPlusFileName("RookieHero_Who.png").GetFullPath(), 6, 1);
		GameEngineSprite::LoadSheet(Path.GetPlusFileName("RookieHero_LandingReady.png").GetFullPath(), 4, 1);
		GameEngineSprite::LoadSheet(Path.GetPlusFileName("RookieHero_LandingIntro.png").GetFullPath(), 9, 3);
		GameEngineSprite::LoadSheet(Path.GetPlusFileName("RookieHero_LandingEnd.png").GetFullPath(), 6, 3);
		GameEngineSprite::LoadSheet(Path.GetPlusFileName("RookieHero_LandingEndWait.png").GetFullPath(), 1, 1);
		GameEngineSprite::LoadSheet(Path.GetPlusFileName("RookieHero_Throwing.png").GetFullPath(), 4, 1);
		GameEngineSprite::LoadSheet(Path.GetPlusFileName("RookieHero_Potion.png").GetFullPath(), 6, 1);
		GameEngineSprite::LoadSheet(Path.GetPlusFileName("RookieHero_Hit.png").GetFullPath(), 3, 1);
		GameEngineSprite::LoadSheet(Path.GetPlusFileName("RookieHero_Dash.png").GetFullPath(), 3, 1);
		GameEngineSprite::LoadSheet(Path.GetPlusFileName("RookieHero_BackDash.png").GetFullPath(), 3, 1);
		GameEngineSprite::LoadSheet(Path.GetPlusFileName("RookieHero_Groggy.png").GetFullPath(), 2, 2);
		GameEngineSprite::LoadSheet(Path.GetPlusFileName("RookieHero_EnergyBallReady.png").GetFullPath(), 9, 1);
		GameEngineSprite::LoadSheet(Path.GetPlusFileName("RookieHero_EnergyBall.png").GetFullPath(), 6, 1);
		GameEngineSprite::LoadSheet(Path.GetPlusFileName("RookieHero_ExplosionReady.png").GetFullPath(), 3, 1);
		GameEngineSprite::LoadSheet(Path.GetPlusFileName("RookieHero_ExplosionLoop.png").GetFullPath(), 6, 1);
		GameEngineSprite::LoadSheet(Path.GetPlusFileName("RookieHero_AttackA.png").GetFullPath(), 9, 1);
		GameEngineSprite::LoadSheet(Path.GetPlusFileName("RookieHero_AttackAReady.png").GetFullPath(), 5, 1);
		GameEngineSprite::LoadSheet(Path.GetPlusFileName("RookieHero_AttackB.png").GetFullPath(), 5, 1);
		GameEngineSprite::LoadSheet(Path.GetPlusFileName("RookieHero_AttackC.png").GetFullPath(), 3, 1);
		GameEngineSprite::LoadSheet(Path.GetPlusFileName("RookieHero_AttackD.png").GetFullPath(), 5, 1);
		GameEngineSprite::LoadSheet(Path.GetPlusFileName("RookieHero_AttackE.png").GetFullPath(), 9, 1);
		GameEngineSprite::LoadSheet(Path.GetPlusFileName("RookieHero_SwordEnergyReady.png").GetFullPath(), 3, 1);
		GameEngineSprite::LoadSheet(Path.GetPlusFileName("RookieHero_SwordEnergy.png").GetFullPath(), 5, 2);
		GameEngineSprite::LoadSheet(Path.GetPlusFileName("RookieHero_DeadIntro.png").GetFullPath(), 5, 1);
		GameEngineSprite::LoadSheet(Path.GetPlusFileName("RookieHero_DeadBody.png").GetFullPath(), 1, 1);
		GameEngineSprite::LoadSheet(Path.GetPlusFileName("RookieHero_StingerReady.png").GetFullPath(), 3, 3);
		GameEngineSprite::LoadSheet(Path.GetPlusFileName("RookieHero_Stinger.png").GetFullPath(), 3, 1);
	
		Path.MoveParent();
		Path.Move("Effect");

		GameEngineSprite::LoadSheet(Path.GetPlusFileName("RookieHero_ExplosionEffect.png").GetFullPath(), 4, 5);
		GameEngineSprite::LoadSheet(Path.GetPlusFileName("RookieHero_EnergyBall_Projectile.png").GetFullPath(), 7, 7);
		GameEngineSprite::LoadSheet(Path.GetPlusFileName("RookieHero_EnergyBallExplosion_Effect.png").GetFullPath(), 5, 4);
		GameEngineSprite::LoadSheet(Path.GetPlusFileName("RookieHero_EnergyBallShot_Effect.png").GetFullPath(), 4, 5);
		GameEngineSprite::LoadSheet(Path.GetPlusFileName("RookieHero_Ultimate_Projectile.png").GetFullPath(), 4, 6);
		GameEngineSprite::LoadSheet(Path.GetPlusFileName("RookieHero_UltimateAura_Effect.png").GetFullPath(), 4, 6);
		GameEngineSprite::LoadSheet(Path.GetPlusFileName("RookieHero_UltimateComplete_Effect.png").GetFullPath(), 4, 4);
		GameEngineSprite::LoadSheet(Path.GetPlusFileName("RookieHero_UltimateFail_Effect.png").GetFullPath(), 4, 5);
		GameEngineSprite::LoadSheet(Path.GetPlusFileName("RookieHero_UltimateSmoke_Effect.png").GetFullPath(), 1, 6);

		GameEngineSprite::LoadSheet(Path.GetPlusFileName("VeteranHero_EnergyBall_Projectile.png").GetFullPath(), 7, 6);
		GameEngineSprite::LoadSheet(Path.GetPlusFileName("VeteranHero_SwordWave_Projectile.png").GetFullPath(), 9, 3);
		GameEngineSprite::LoadSheet(Path.GetPlusFileName("VeteranHero_ComboAttack_Projectile.png").GetFullPath(), 4, 4);
		GameEngineSprite::LoadSheet(Path.GetPlusFileName("VeteranHero_EnergyBlast_Explosion.png").GetFullPath(), 5, 4);
		GameEngineSprite::LoadSheet(Path.GetPlusFileName("VeteranHero_EnergyBlast_Charging.png").GetFullPath(), 6, 8);
		GameEngineSprite::LoadSheet(Path.GetPlusFileName("VeteranHero_EnergyBlastStart_Effect.png").GetFullPath(), 4, 3);
		GameEngineSprite::LoadSheet(Path.GetPlusFileName("VeteranHero_WaveSmoke_Effect.png").GetFullPath(), 4, 4);
		GameEngineSprite::LoadSheet(Path.GetPlusFileName("VeteranHero_Stinger_Effect.png").GetFullPath(), 4, 5);
		GameEngineSprite::LoadSheet(Path.GetPlusFileName("VeteranHero_StingerSlash_Effect.png").GetFullPath(), 3, 4);

		EffectManager::CreateMetaData("RookieHero_Explosion", {
			.SpriteName = "RookieHero_ExplosionEffect.png",
			.AnimStart = 0,
			.AnimEnd = 17,
			.AnimIter = 0.05f,
			.ScaleRatio = 2.0f });

		EffectManager::CreateMetaData("RookieHero_EnergyBall", {
			.SpriteName = "RookieHero_EnergyBall_Projectile.png",
			.AnimStart = 0,
			.AnimEnd = 47,
			.AnimIter = 0.05f,
			.ScaleRatio = 2.0f });

		EffectManager::CreateMetaData("VeteranHero_EnergyBall", {
			.SpriteName = "VeteranHero_EnergyBall_Projectile.png",
			.AnimStart = 0,
			.AnimEnd = 38,
			.AnimIter = 0.05f,
			.ScaleRatio = 2.0f });

		EffectManager::CreateMetaData("RookieHero_EnergyBallExplosion", {
			.SpriteName = "RookieHero_EnergyBallExplosion_Effect.png",
			.AnimStart = 0,
			.AnimEnd = 19,
			.AnimIter = 0.04f,
			.ScaleRatio = 1.0f });


		EffectManager::CreateMetaData("RookieHero_EnergyBallExplosion_Large", {
			.SpriteName = "RookieHero_EnergyBallExplosion_Effect.png",
			.AnimStart = 0,
			.AnimEnd = 19,
			.AnimIter = 0.04f,
			.ScaleRatio = 2.0f });

		EffectManager::CreateMetaData("RookieHero_EnergyBallShot", {
			.SpriteName = "RookieHero_EnergyBallShot_Effect.png",
			.AnimStart = 0,
			.AnimEnd = 18,
			.AnimIter = 0.04f,
			.ScaleRatio = 2.0f });

		EffectManager::CreateMetaData("RookieHero_Ultimate_Projectile", {
			.SpriteName = "RookieHero_Ultimate_Projectile.png",
			.AnimStart = 0,
			.AnimEnd = 23,
			.AnimIter = 0.05f,
			.ScaleRatio = 2.5f });

		EffectManager::CreateMetaData("RookieHero_UltimateAura", {
			.SpriteName = "RookieHero_UltimateAura_Effect.png",
			.AnimStart = 0,
			.AnimEnd = 21,
			.AnimIter = 0.05f,
			.ScaleRatio = 2.0f });

		EffectManager::CreateMetaData("RookieHero_UltimateComplete", {
			.SpriteName = "RookieHero_UltimateComplete_Effect.png",
			.AnimStart = 0,
			.AnimEnd = 13,
			.AnimIter = 0.05f,
			.ScaleRatio = 2.0f });

		EffectManager::CreateMetaData("RookieHero_UltimateFail", {
			.SpriteName = "RookieHero_UltimateFail_Effect.png",
			.AnimStart = 0,
			.AnimEnd = 17,
			.AnimIter = 0.03f,
			.ScaleRatio = 2.0f });

		EffectManager::CreateMetaData("RookieHero_UltimateSmoke", {
			.SpriteName = "RookieHero_UltimateSmoke_Effect.png",
			.AnimStart = 0,
			.AnimEnd = 5,
			.AnimIter = 0.05f,
			.ScaleRatio = 2.0f });

		EffectManager::CreateMetaData("VeteranHero_SwordWave", {
			.SpriteName = "VeteranHero_SwordWave_Projectile.png",
			.AnimStart = 0,
			.AnimEnd = 26,
			.AnimIter = 0.05f,
			.ScaleRatio = 2.0f });		

		EffectManager::CreateMetaData("VeteranHero_ComboWave", {
			.SpriteName = "VeteranHero_ComboAttack_Projectile.png",
			.AnimStart = 0,
			.AnimEnd = 12,
			.AnimIter = 0.05f,
			.ScaleRatio = 2.0f});		
		
		EffectManager::CreateMetaData("VeteranHero_Explosion", {
			.SpriteName = "VeteranHero_EnergyBlast_Explosion.png",
			.AnimStart = 0,
			.AnimEnd = 18,
			.AnimIter = 0.035f,
			.ScaleRatio = 2.0f});		
		
		EffectManager::CreateMetaData("VeteranHero_EnergyCharging", {
			.SpriteName = "VeteranHero_EnergyBlast_Charging.png",
			.AnimStart = 0,
			.AnimEnd = 46,
			.AnimIter = 0.045f,
			.ScaleRatio = 2.0f});		
		
		EffectManager::CreateMetaData("VeteranHero_EnergyBlast", {
			.SpriteName = "VeteranHero_EnergyBlastStart_Effect.png",
			.AnimStart = 0,
			.AnimEnd = 11,
			.AnimIter = 0.045f,
			.ScaleRatio = 2.0f});		
		
		EffectManager::CreateMetaData("VeteranHero_WaveSmoke", {
			.SpriteName = "VeteranHero_WaveSmoke_Effect.png",
			.AnimStart = 0,
			.AnimEnd = 15,
			.AnimIter = 0.04f,
			.ScaleRatio = 2.0f});		
		
		EffectManager::CreateMetaData("VeteranHero_Stinger", {
			.SpriteName = "VeteranHero_Stinger_Effect.png",
			.AnimStart = 0,
			.AnimEnd = 19,
			.AnimIter = 0.05f,
			.ScaleRatio = 2.0f});		
		
		EffectManager::CreateMetaData("VeteranHero_StingerSlash", {
			.SpriteName = "VeteranHero_StingerSlash_Effect.png",
			.AnimStart = 0,
			.AnimEnd = 9,
			.AnimIter = 0.05f,
			.ScaleRatio = 2.0f});

		Path.MoveParent();

		GameEngineTexture::Load(Path.GetPlusFileName("AdventurerHero_Sword.png").GetFullPath());
	}

	// 몬스터 공용 이펙트
	{
		GameEngineDirectory Path;

		Path.MoveParentToDirectory("Resources");
		Path.Move("Resources");
		Path.Move("Texture");
		Path.Move("0_Common");
		Path.Move("Monster");
		Path.Move("Effect");

		GameEngineSprite::LoadSheet(Path.GetPlusFileName("FindPlayerSightEffect.png").GetFullPath(), 5, 3);
		GameEngineSprite::LoadSheet(Path.GetPlusFileName("MonsterDeathEffect.png").GetFullPath(), 3, 2);
		GameEngineSprite::LoadSheet(Path.GetPlusFileName("MonsterAppear.png").GetFullPath(), 11, 1);
		GameEngineSprite::LoadSheet(Path.GetPlusFileName("HitSlashEffect.png").GetFullPath(), 5, 1);
		GameEngineSprite::LoadSheet(Path.GetPlusFileName("Monster_HealEffect.png").GetFullPath(), 4, 5);

		EffectManager::CreateMetaData("FindPlayer", {
			.SpriteName = "FindPlayerSightEffect.png",
			.AnimStart = 0,
			.AnimEnd = 14,
			.AnimIter = 0.025f,
			.ScaleRatio = 2.0f });

		EffectManager::CreateMetaData("HitSlashEffect", {
			.SpriteName = "HitSlashEffect.png",
			.AnimStart = 0,
			.AnimEnd = 4,
			.AnimIter = 0.04f,
			.ScaleRatio = 2.0f,});

		EffectManager::CreateMetaData("MonsterDeath", {
			.SpriteName = "MonsterDeathEffect.png",
			.AnimStart = 0,
			.AnimEnd = 5,
			.AnimIter = 0.04f,
			.ScaleRatio = 2.0f });

		EffectManager::CreateMetaData("MonsterAppear", {
			.SpriteName = "MonsterAppear.png",
			.AnimStart = 0,
			.AnimEnd = 10,
			.AnimIter = 0.04f,
			.ScaleRatio = 2.0f });

		EffectManager::CreateMetaData("MonsterHeal", {
			.SpriteName = "Monster_HealEffect.png",
			.AnimStart = 0,
			.AnimEnd = 17,
			.AnimIter = 0.04f,
			.ScaleRatio = 2.0f });

		Path.MoveParent();
		Path.Move("Particle");

		GameEngineTexture::Load(Path.GetPlusFileName("BaseHitParticle.png").GetFullPath());
	}
}
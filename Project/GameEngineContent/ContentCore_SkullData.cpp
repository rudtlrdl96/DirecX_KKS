#include "PrecompileHeader.h"
#include "ContentCore.h"
#include "SkullData.h"

static void LoadSkull(const SkullData& _Data)
{
	ContentDatabase<SkullData, SkullGrade>::InsertData(_Data);
}

void ContentCore::SkullDataLoad()
{
	LoadSkull({ .Name = "리틀본", .Index = 0, .Grade = SkullGrade::Normal });

	LoadSkull({.Name = "웨어울프", .Index = 1, .Grade = SkullGrade::Normal});
	LoadSkull({.Name = "나이 든 웨어울프", .Index = 100, .Grade = SkullGrade::Rare});
	LoadSkull({ .Name = "미노타우로스", .Index = 101, .Grade = SkullGrade::Rare });
	LoadSkull({ .Name = "연금술사", .Index = 102, .Grade = SkullGrade::Rare });

	LoadSkull({.Name = "우두머리 웨어울프", .Index = 200, .Grade = SkullGrade::Unique});
	LoadSkull({ .Name = "미노타우로스 2세", .Index = 201, .Grade = SkullGrade::Unique });
	LoadSkull({ .Name = "고위 연금술사", .Index = 202, .Grade = SkullGrade::Unique });
	LoadSkull({ .Name = "경비대장", .Index = 203, .Grade = SkullGrade::Unique });
	
	LoadSkull({.Name = "영원의 웨어울프", .Index = 300, .Grade = SkullGrade::Legendary});
	LoadSkull({ .Name = "미노타우로스 3세", .Index = 301, .Grade = SkullGrade::Legendary });
	LoadSkull({ .Name = "검은 연금술사", .Index = 302, .Grade = SkullGrade::Legendary });

	if (nullptr == GameEngineTexture::Find("BoneSkull_Idle.png"))
	{
		GameEngineDirectory Path;

		Path.MoveParentToDirectory("Resources");
		Path.Move("Resources");
		Path.Move("Texture");
		Path.Move("0_Common");
		Path.Move("Player");

		{
			Path.Move("SkullImage");

			std::vector<GameEngineFile> Files = Path.GetAllFile({ ".png" });
		
			for (size_t i = 0; i < Files.size(); i++)
			{
				GameEngineTexture::Load(Files[i].GetFullPath());
			}

			Path.MoveParent();
		}


		{
			Path.Move("Skill");

			std::vector<GameEngineFile> Files = Path.GetAllFile({ ".png" });

			for (size_t i = 0; i < Files.size(); i++)
			{
				GameEngineTexture::Load(Files[i].GetFullPath());
			}

			Path.MoveParent();
		}
	}

	// 리틀본 텍스쳐 로드
	if (nullptr == GameEngineTexture::Find("BoneSkull_Idle.png"))
	{
		GameEngineDirectory Path;

		Path.MoveParentToDirectory("Resources");
		Path.Move("Resources");
		Path.Move("Texture");
		Path.Move("0_Common");
		Path.Move("Player");
		Path.Move("Skull");
		Path.Move("BoneSkull");
		Path.Move("Sheet");

		// Idle Sprite
		GameEngineSprite::LoadSheet(Path.GetPlusFileName("BoneSkull_Idle.png").GetFullPath(), 4, 1);
		GameEngineSprite::LoadSheet(Path.GetPlusFileName("BoneSkull_Idle_NoHead.png").GetFullPath(), 4, 1);
		GameEngineSprite::LoadSheet(Path.GetPlusFileName("BoneSkull_Idle_NoWeapon.png").GetFullPath(), 4, 1);

		// Walk Sprite
		GameEngineSprite::LoadSheet(Path.GetPlusFileName("BoneSkull_Walk.png").GetFullPath(), 8, 1);
		GameEngineSprite::LoadSheet(Path.GetPlusFileName("BoneSkull_Walk_NoHead.png").GetFullPath(), 8, 1);
		GameEngineSprite::LoadSheet(Path.GetPlusFileName("BoneSkull_Walk_NoWeapon.png").GetFullPath(), 8, 1);

		// Dash Sprite
		GameEngineSprite::LoadSheet(Path.GetPlusFileName("BoneSkull_Dash.png").GetFullPath(), 1, 1);
		GameEngineSprite::LoadSheet(Path.GetPlusFileName("BoneSkull_Dash_NoHead.png").GetFullPath(), 1, 1);
		GameEngineSprite::LoadSheet(Path.GetPlusFileName("BoneSkull_Dash_NoWeapon.png").GetFullPath(), 1, 1);

		// FallEnter Sprite
		GameEngineSprite::LoadSheet(Path.GetPlusFileName("BoneSkull_Fall.png").GetFullPath(), 2, 1);
		GameEngineSprite::LoadSheet(Path.GetPlusFileName("BoneSkull_Fall_NoHead.png").GetFullPath(), 2, 1);
		GameEngineSprite::LoadSheet(Path.GetPlusFileName("BoneSkull_Fall_NoWeapon.png").GetFullPath(), 2, 1);

		GameEngineSprite::LoadSheet(Path.GetPlusFileName("BoneSkull_Normal_FallDead.png").GetFullPath(), 3, 1);

		// FallRepeat Sprite
		GameEngineSprite::LoadSheet(Path.GetPlusFileName("BoneSkull_FallRepeat.png").GetFullPath(), 3, 1);
		GameEngineSprite::LoadSheet(Path.GetPlusFileName("BoneSkull_FallRepeat_NoHead.png").GetFullPath(), 3, 1);
		GameEngineSprite::LoadSheet(Path.GetPlusFileName("BoneSkull_FallRepeat_NoWeapon.png").GetFullPath(), 3, 1);

		// Jump Sprite
		GameEngineSprite::LoadSheet(Path.GetPlusFileName("BoneSkull_Jump.png").GetFullPath(), 2, 1);
		GameEngineSprite::LoadSheet(Path.GetPlusFileName("BoneSkull_Jump_NoHead.png").GetFullPath(), 2, 1);
		GameEngineSprite::LoadSheet(Path.GetPlusFileName("BoneSkull_Jump_NoWeapon.png").GetFullPath(), 2, 1);

		// AttackA Sprite
		GameEngineSprite::LoadSheet(Path.GetPlusFileName("BoneSkull_AttackA.png").GetFullPath(), 5, 1);
		GameEngineSprite::LoadSheet(Path.GetPlusFileName("BoneSkull_AttackA_NoHead.png").GetFullPath(), 5, 1);

		// AttackB Sprite
		GameEngineSprite::LoadSheet(Path.GetPlusFileName("BoneSkull_AttackB.png").GetFullPath(), 4, 1);
		GameEngineSprite::LoadSheet(Path.GetPlusFileName("BoneSkull_AttackB_NoHead.png").GetFullPath(), 4, 1);

		// JumpAttack Sprite
		GameEngineSprite::LoadSheet(Path.GetPlusFileName("BoneSkull_JumpAttack.png").GetFullPath(), 4, 1);
		GameEngineSprite::LoadSheet(Path.GetPlusFileName("BoneSkull_JumpAttack_NoHead.png").GetFullPath(), 4, 1);

		// SkillA Sprite
		GameEngineSprite::LoadSheet(Path.GetPlusFileName("BoneSkull_Skill.png").GetFullPath(), 4, 1);

		// SkillB Sprite
		GameEngineSprite::LoadSheet(Path.GetPlusFileName("BoneSkull_SkillReborn.png").GetFullPath(), 9, 1);

		// Skull Switch
		GameEngineSprite::LoadSheet(Path.GetPlusFileName("BoneSkull_Switch.png").GetFullPath(), 7, 1);

		// Reborn
		GameEngineSprite::LoadSheet(Path.GetPlusFileName("BoneSkull_Normal_Reborn2Field.png").GetFullPath(), 22, 1);
		GameEngineSprite::LoadSheet(Path.GetPlusFileName("BoneSkull_Normal_RebornCastle.png").GetFullPath(), 6, 5);

		// Story Animation
		GameEngineSprite::LoadSheet(Path.GetPlusFileName("BoneSkull_Wait.png").GetFullPath(), 8, 6);
		GameEngineSprite::LoadSheet(Path.GetPlusFileName("BoneSkull_Intro_Getbone.png").GetFullPath(), 10, 1);
		GameEngineSprite::LoadSheet(Path.GetPlusFileName("BoneSkull_DeadLoop.png").GetFullPath(), 1, 1);
		GameEngineSprite::LoadSheet(Path.GetPlusFileName("BoneSkull_Getscroll.png").GetFullPath(), 6, 9);
		GameEngineSprite::LoadSheet(Path.GetPlusFileName("BoneSkull_Intro_Idle.png").GetFullPath(), 1, 1);
		GameEngineSprite::LoadSheet(Path.GetPlusFileName("BoneSkull_Intro_0.png").GetFullPath(), 5, 1);
		GameEngineSprite::LoadSheet(Path.GetPlusFileName("BoneSkull_Intro_1.png").GetFullPath(), 5, 11);
		GameEngineSprite::LoadSheet(Path.GetPlusFileName("BoneSkull_Intro_2.png").GetFullPath(), 5, 4);
		GameEngineSprite::LoadSheet(Path.GetPlusFileName("BoneSkull_Normal_Getskull.png").GetFullPath(), 7, 7);
	}

	// 경비대장 텍스쳐 로드
	if (nullptr == GameEngineTexture::Find("ChiefGuard_Unique_Idle.png"))
	{
		GameEngineDirectory Path;

		Path.MoveParentToDirectory("Resources");
		Path.Move("Resources");
		Path.Move("Texture");
		Path.Move("0_Common");
		Path.Move("Player");
		Path.Move("Skull");
		Path.Move("ChiefGuard");
		Path.Move("Sheet");

		// Idle Sprite
		GameEngineSprite::LoadSheet(Path.GetPlusFileName("ChiefGuard_Unique_Idle.png").GetFullPath(), 6, 1);

		// Walk Sprite
		GameEngineSprite::LoadSheet(Path.GetPlusFileName("ChiefGuard_Unique_Walk.png").GetFullPath(), 6, 1);

		// Dash Sprite
		GameEngineSprite::LoadSheet(Path.GetPlusFileName("ChiefGuard_Unique_Dash.png").GetFullPath(), 5, 1);

		// FallEnter Sprite
		GameEngineSprite::LoadSheet(Path.GetPlusFileName("ChiefGuard_Unique_Fall.png").GetFullPath(), 2, 1);

		// FallRepeat Sprite
		GameEngineSprite::LoadSheet(Path.GetPlusFileName("ChiefGuard_Unique_FallRepeat.png").GetFullPath(), 3, 1);

		// Jump Sprite
		GameEngineSprite::LoadSheet(Path.GetPlusFileName("ChiefGuard_Unique_Jump.png").GetFullPath(), 3, 1);

		// AttackA Sprite
		GameEngineSprite::LoadSheet(Path.GetPlusFileName("ChiefGuard_Unique_AttackA.png").GetFullPath(), 5, 1);

		// AttackB Sprite
		GameEngineSprite::LoadSheet(Path.GetPlusFileName("ChiefGuard_Unique_AttackB.png").GetFullPath(), 5, 1);

		// AttackC Sprite
		GameEngineSprite::LoadSheet(Path.GetPlusFileName("ChiefGuard_Unique_AttackC.png").GetFullPath(), 6, 1);

		// JumpAttack Sprite
		GameEngineSprite::LoadSheet(Path.GetPlusFileName("ChiefGuard_Unique_JumpAttack.png").GetFullPath(), 5, 1);

		// SkillA Sprite
		GameEngineSprite::LoadSheet(Path.GetPlusFileName("ChiefGuard_Unique_SkillA.png").GetFullPath(), 22, 1);

		// SkillB Sprite
		GameEngineSprite::LoadSheet(Path.GetPlusFileName("ChiefGuard_Unique_SkillB.png").GetFullPath(), 8, 1);

		// Skull Switch
		GameEngineSprite::LoadSheet(Path.GetPlusFileName("ChiefGuard_Unique_Switch.png").GetFullPath(), 9, 1);
	}

	std::vector<SkullData> NormalDatas;
	ContentDatabase<SkullData, SkullGrade>::CopyGradeDatas(SkullGrade::Normal, NormalDatas);
	std::vector<SkullData> RareDatas;
	ContentDatabase<SkullData, SkullGrade>::CopyGradeDatas(SkullGrade::Rare, RareDatas);
	std::vector<SkullData> UniqueDatas;
	ContentDatabase<SkullData, SkullGrade>::CopyGradeDatas(SkullGrade::Unique, UniqueDatas);
	std::vector<SkullData> LegendaryDatas;
	ContentDatabase<SkullData, SkullGrade>::CopyGradeDatas(SkullGrade::Legendary, LegendaryDatas);

	int a = 0;
}
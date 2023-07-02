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

	LoadSkull({.Name = "웨어울프", .Index = 1, .Grade = SkullGrade::Normal, .MoveSpeed = 440.0f});
	LoadSkull({.Name = "나이 든 웨어울프", .Index = 100, .Grade = SkullGrade::Rare, .MoveSpeed = 440.0f });
	LoadSkull({ .Name = "미노타우로스", .Index = 101, .Grade = SkullGrade::Rare, .MoveSpeed = 440.0f });
	//LoadSkull({ .Name = "연금술사", .Index = 102, .Grade = SkullGrade::Rare, .MoveSpeed = 440.0f });

	LoadSkull({.Name = "우두머리 웨어울프", .Index = 200, .Grade = SkullGrade::Unique});
	LoadSkull({ .Name = "미노타우로스 2세", .Index = 201, .Grade = SkullGrade::Unique });
	//LoadSkull({ .Name = "고위 연금술사", .Index = 202, .Grade = SkullGrade::Unique });
	LoadSkull({ .Name = "경비대장", .Index = 203, .Grade = SkullGrade::Unique });
	
	LoadSkull({.Name = "영원의 웨어울프", .Index = 300, .Grade = SkullGrade::Legendary});
	LoadSkull({ .Name = "미노타우로스 3세", .Index = 301, .Grade = SkullGrade::Legendary });
	//LoadSkull({ .Name = "검은 연금술사", .Index = 302, .Grade = SkullGrade::Legendary });

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

		{
			Path.Move("DeadPart");

			std::vector<GameEngineFile> Files = Path.GetAllFile({ ".png" });

			for (size_t i = 0; i < Files.size(); i++)
			{
				GameEngineTexture::Load(Files[i].GetFullPath());
			}

			Path.MoveParent();
		}
		
		{
			Path.Move("Head");

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
		GameEngineSprite::LoadSheet(Path.GetPlusFileName("BoneSkull_Intro_WlakUp.png").GetFullPath(), 5, 1);
		GameEngineSprite::LoadSheet(Path.GetPlusFileName("BoneSkull_Intro_GetHead.png").GetFullPath(), 5, 11);
		GameEngineSprite::LoadSheet(Path.GetPlusFileName("BoneSkull_Intro_Awkward.png").GetFullPath(), 5, 4);
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

	// 웨어울프 노말
	if (nullptr == GameEngineTexture::Find("Wolf_Normal_Idle.png"))
	{
		GameEngineDirectory Path;

		Path.MoveParentToDirectory("Resources");
		Path.Move("Resources");
		Path.Move("Texture");
		Path.Move("0_Common");
		Path.Move("Player");
		Path.Move("Skull");
		Path.Move("Wolf");
		Path.Move("Normal");

		// Idle Sprite
		GameEngineSprite::LoadSheet(Path.GetPlusFileName("Wolf_Normal_Idle.png").GetFullPath(), 6, 1);

		// Walk Sprite
		GameEngineSprite::LoadSheet(Path.GetPlusFileName("Wolf_Normal_Walk.png").GetFullPath(), 3, 2);

		// Dash Sprite
		GameEngineSprite::LoadSheet(Path.GetPlusFileName("Wolf_Normal_Dash.png").GetFullPath(), 3, 1);

		// FallEnter Sprite
		GameEngineSprite::LoadSheet(Path.GetPlusFileName("Wolf_Normal_Fall.png").GetFullPath(), 2, 1);

		// FallRepeat Sprite
		GameEngineSprite::LoadSheet(Path.GetPlusFileName("Wolf_Normal_FallRepeat.png").GetFullPath(), 3, 1);

		// Jump Sprite
		GameEngineSprite::LoadSheet(Path.GetPlusFileName("Wolf_Normal_Jump.png").GetFullPath(), 3, 1);

		// AttackA Sprite
		GameEngineSprite::LoadSheet(Path.GetPlusFileName("Wolf_Normal_AttackA.png").GetFullPath(), 5, 1);

		// AttackB Sprite
		GameEngineSprite::LoadSheet(Path.GetPlusFileName("Wolf_Normal_AttackB.png").GetFullPath(), 5, 1);

		// JumpAttack Sprite
		GameEngineSprite::LoadSheet(Path.GetPlusFileName("Wolf_Normal_JumpAttack.png").GetFullPath(), 7, 1);

		// SkillA Sprite
		GameEngineSprite::LoadSheet(Path.GetPlusFileName("Wolf_Normal_SkillA.png").GetFullPath(), 7, 1);

		// Skull Switch
		GameEngineSprite::LoadSheet(Path.GetPlusFileName("Wolf_Normal_Switch.png").GetFullPath(), 3, 1);
	}

	// 웨어울프 레어
	if (nullptr == GameEngineTexture::Find("Wolf_Rare_Idle.png"))
	{
		GameEngineDirectory Path;

		Path.MoveParentToDirectory("Resources");
		Path.Move("Resources");
		Path.Move("Texture");
		Path.Move("0_Common");
		Path.Move("Player");
		Path.Move("Skull");
		Path.Move("Wolf");
		Path.Move("Rare");

		// Idle Sprite
		GameEngineSprite::LoadSheet(Path.GetPlusFileName("Wolf_Rare_Idle.png").GetFullPath(), 6, 1);

		// Walk Sprite
		GameEngineSprite::LoadSheet(Path.GetPlusFileName("Wolf_Rare_Walk.png").GetFullPath(), 3, 2);

		// Dash Sprite
		GameEngineSprite::LoadSheet(Path.GetPlusFileName("Wolf_Rare_Dash.png").GetFullPath(), 3, 1);

		// FallEnter Sprite
		GameEngineSprite::LoadSheet(Path.GetPlusFileName("Wolf_Rare_Fall.png").GetFullPath(), 1, 1);

		// FallRepeat Sprite
		GameEngineSprite::LoadSheet(Path.GetPlusFileName("Wolf_Rare_FallRepeat.png").GetFullPath(), 3, 1);

		// Jump Sprite
		GameEngineSprite::LoadSheet(Path.GetPlusFileName("Wolf_Rare_Jump.png").GetFullPath(), 3, 1);

		// AttackA Sprite
		GameEngineSprite::LoadSheet(Path.GetPlusFileName("Wolf_Rare_AttackA.png").GetFullPath(), 5, 1);

		// AttackB Sprite 
		GameEngineSprite::LoadSheet(Path.GetPlusFileName("Wolf_Rare_AttackB.png").GetFullPath(), 5, 1);

		// JumpAttack Sprite
		GameEngineSprite::LoadSheet(Path.GetPlusFileName("Wolf_Rare_JumpAttack.png").GetFullPath(), 6, 1);

		// SkillA Sprite
		GameEngineSprite::LoadSheet(Path.GetPlusFileName("Wolf_Rare_SkillA.png").GetFullPath(), 7, 1);

		// Skull Switch
		GameEngineSprite::LoadSheet(Path.GetPlusFileName("Wolf_Rare_Switch.png").GetFullPath(), 6, 1);
	}

	// 웨어울프 유니크
	if (nullptr == GameEngineTexture::Find("Wolf_Unique_Idle.png"))
	{
		GameEngineDirectory Path;

		Path.MoveParentToDirectory("Resources");
		Path.Move("Resources");
		Path.Move("Texture");
		Path.Move("0_Common");
		Path.Move("Player");
		Path.Move("Skull");
		Path.Move("Wolf");
		Path.Move("Unique");

		// Idle Sprite
		GameEngineSprite::LoadSheet(Path.GetPlusFileName("Wolf_Unique_Idle.png").GetFullPath(), 7, 1);

		// Walk Sprite
		GameEngineSprite::LoadSheet(Path.GetPlusFileName("Wolf_Unique_Walk.png").GetFullPath(), 3, 2);

		// Dash Sprite
		GameEngineSprite::LoadSheet(Path.GetPlusFileName("Wolf_Unique_Dash.png").GetFullPath(), 3, 1);

		// FallEnter Sprite
		GameEngineSprite::LoadSheet(Path.GetPlusFileName("Wolf_Unique_Fall.png").GetFullPath(), 2, 1);

		// FallRepeat Sprite
		GameEngineSprite::LoadSheet(Path.GetPlusFileName("Wolf_Unique_FallRepeat.png").GetFullPath(), 3, 1);

		// Jump Sprite
		GameEngineSprite::LoadSheet(Path.GetPlusFileName("Wolf_Unique_Jump.png").GetFullPath(), 3, 1);

		// AttackA Sprite
		GameEngineSprite::LoadSheet(Path.GetPlusFileName("Wolf_Unique_AttackA.png").GetFullPath(), 5, 1);

		// AttackB Sprite 
		GameEngineSprite::LoadSheet(Path.GetPlusFileName("Wolf_Unique_AttackB.png").GetFullPath(), 5, 1);

		// JumpAttack Sprite
		GameEngineSprite::LoadSheet(Path.GetPlusFileName("Wolf_Unique_JumpAttack.png").GetFullPath(), 7, 1);

		// SkillA Sprite
		GameEngineSprite::LoadSheet(Path.GetPlusFileName("Wolf_Unique_SkillA.png").GetFullPath(), 7, 1);

		// SkillB Sprite
		GameEngineSprite::LoadSheet(Path.GetPlusFileName("Wolf_Unique_SkillB.png").GetFullPath(), 7, 1);

		// Skull Switch
		GameEngineSprite::LoadSheet(Path.GetPlusFileName("Wolf_Unique_Switch.png").GetFullPath(), 8, 1);
	}

	// 웨어울프 레전더리
	if (nullptr == GameEngineTexture::Find("Wolf_Legendary_Idle.png"))
	{
		GameEngineDirectory Path;

		Path.MoveParentToDirectory("Resources");
		Path.Move("Resources");
		Path.Move("Texture");
		Path.Move("0_Common");
		Path.Move("Player");
		Path.Move("Skull");
		Path.Move("Wolf");
		Path.Move("Legendary");

		// Idle Sprite
		GameEngineSprite::LoadSheet(Path.GetPlusFileName("Wolf_Legendary_Idle.png").GetFullPath(), 7, 1);

		// Walk Sprite
		GameEngineSprite::LoadSheet(Path.GetPlusFileName("Wolf_Legendary_Walk.png").GetFullPath(), 3, 2);

		// Dash Sprite
		GameEngineSprite::LoadSheet(Path.GetPlusFileName("Wolf_Legendary_Dash.png").GetFullPath(), 3, 1);

		// FallEnter Sprite
		GameEngineSprite::LoadSheet(Path.GetPlusFileName("Wolf_Legendary_Fall.png").GetFullPath(), 2, 1);

		// FallRepeat Sprite
		GameEngineSprite::LoadSheet(Path.GetPlusFileName("Wolf_Legendary_FallRepeat.png").GetFullPath(), 3, 1);

		// Jump Sprite
		GameEngineSprite::LoadSheet(Path.GetPlusFileName("Wolf_Legendary_Jump.png").GetFullPath(), 3, 1);

		// AttackA Sprite
		GameEngineSprite::LoadSheet(Path.GetPlusFileName("Wolf_Legendary_AttackA.png").GetFullPath(), 6, 1);

		// AttackB Sprite 
		GameEngineSprite::LoadSheet(Path.GetPlusFileName("Wolf_Legendary_AttackB.png").GetFullPath(), 6, 1);

		// JumpAttack Sprite
		GameEngineSprite::LoadSheet(Path.GetPlusFileName("Wolf_Legendary_JumpAttack.png").GetFullPath(), 7, 1);

		// SkillA Sprite
		GameEngineSprite::LoadSheet(Path.GetPlusFileName("Wolf_Legendary_SkillA.png").GetFullPath(), 7, 1);

		// SkillB Sprite
		GameEngineSprite::LoadSheet(Path.GetPlusFileName("Wolf_Legendary_SkillB.png").GetFullPath(), 7, 1);

		// Skull Switch
		GameEngineSprite::LoadSheet(Path.GetPlusFileName("Wolf_Legendary_Switch.png").GetFullPath(), 8, 1);
	}

	// 미노타우르스 레어
	if (nullptr == GameEngineTexture::Find("Minotaurus_Rare_Idle.png"))
	{
		GameEngineDirectory Path;

		Path.MoveParentToDirectory("Resources");
		Path.Move("Resources");
		Path.Move("Texture");
		Path.Move("0_Common");
		Path.Move("Player");
		Path.Move("Skull");
		Path.Move("Minotaurus");
		Path.Move("Rare");

		// Idle Sprite
		GameEngineSprite::LoadSheet(Path.GetPlusFileName("Minotaurus_Rare_Idle.png").GetFullPath(), 5, 1);

		// Walk Sprite
		GameEngineSprite::LoadSheet(Path.GetPlusFileName("Minotaurus_Rare_Walk.png").GetFullPath(), 8, 1);

		// Dash Sprite
		GameEngineSprite::LoadSheet(Path.GetPlusFileName("Minotaurus_Rare_Dash.png").GetFullPath(), 1, 1);

		// FallEnter Sprite
		GameEngineSprite::LoadSheet(Path.GetPlusFileName("Minotaurus_Rare_Fall.png").GetFullPath(), 2, 1);

		// FallRepeat Sprite
		GameEngineSprite::LoadSheet(Path.GetPlusFileName("Minotaurus_Rare_FallRepeat.png").GetFullPath(), 2, 1);

		// Jump Sprite
		GameEngineSprite::LoadSheet(Path.GetPlusFileName("Minotaurus_Rare_Jump.png").GetFullPath(), 2, 1);

		// AttackA Sprite
		GameEngineSprite::LoadSheet(Path.GetPlusFileName("Minotaurus_Rare_AttackA.png").GetFullPath(), 6, 1);

		// AttackB Sprite 
		GameEngineSprite::LoadSheet(Path.GetPlusFileName("Minotaurus_Rare_AttackB.png").GetFullPath(), 5, 1);

		// JumpAttack Sprite
		GameEngineSprite::LoadSheet(Path.GetPlusFileName("Minotaurus_Rare_JumpAttack.png").GetFullPath(), 3, 1);

		// JumpAttack Landing
		GameEngineSprite::LoadSheet(Path.GetPlusFileName("Minotaurus_Rare_JumpAttackLand.png").GetFullPath(), 1, 1);

		// SkillA Sprite
		GameEngineSprite::LoadSheet(Path.GetPlusFileName("Minotaurus_Rare_SkillA.png").GetFullPath(), 5, 1);

		// SkillB Sprite
		GameEngineSprite::LoadSheet(Path.GetPlusFileName("Minotaurus_Rare_SkillB.png").GetFullPath(), 6, 1);
	}

	// 미노타우르스 유니크
	if (nullptr == GameEngineTexture::Find("Minotaurus_Unique_Idle.png"))
	{
		GameEngineDirectory Path;

		Path.MoveParentToDirectory("Resources");
		Path.Move("Resources");
		Path.Move("Texture");
		Path.Move("0_Common");
		Path.Move("Player");
		Path.Move("Skull");
		Path.Move("Minotaurus");
		Path.Move("Unique");

		// Idle Sprite
		GameEngineSprite::LoadSheet(Path.GetPlusFileName("Minotaurus_Unique_Idle.png").GetFullPath(), 6, 1);

		// Walk Sprite
		GameEngineSprite::LoadSheet(Path.GetPlusFileName("Minotaurus_Unique_Walk.png").GetFullPath(), 8, 1);

		// Dash Sprite
		GameEngineSprite::LoadSheet(Path.GetPlusFileName("Minotaurus_Unique_Dash.png").GetFullPath(), 1, 1);

		// FallEnter Sprite
		GameEngineSprite::LoadSheet(Path.GetPlusFileName("Minotaurus_Unique_Fall.png").GetFullPath(), 2, 1);

		// FallRepeat Sprite
		GameEngineSprite::LoadSheet(Path.GetPlusFileName("Minotaurus_Unique_FallRepeat.png").GetFullPath(), 2, 1);

		// Jump Sprite
		GameEngineSprite::LoadSheet(Path.GetPlusFileName("Minotaurus_Unique_Jump.png").GetFullPath(), 2, 1);

		// AttackA Sprite
		GameEngineSprite::LoadSheet(Path.GetPlusFileName("Minotaurus_Unique_AttackA.png").GetFullPath(), 7, 1);

		// AttackB Sprite 
		GameEngineSprite::LoadSheet(Path.GetPlusFileName("Minotaurus_Unique_AttackB.png").GetFullPath(), 6, 1);

		// JumpAttack Sprite
		GameEngineSprite::LoadSheet(Path.GetPlusFileName("Minotaurus_Unique_JumpAttack.png").GetFullPath(), 3, 1);

		// JumpAttack Landing
		GameEngineSprite::LoadSheet(Path.GetPlusFileName("Minotaurus_Unique_JumpAttackLand.png").GetFullPath(), 1, 1);

		// SkillA Sprite
		GameEngineSprite::LoadSheet(Path.GetPlusFileName("Minotaurus_Unique_SkillA.png").GetFullPath(), 5, 1);

		// SkillB Sprite
		GameEngineSprite::LoadSheet(Path.GetPlusFileName("Minotaurus_Unique_SkillB.png").GetFullPath(), 7, 1);
	}
	
	// 미노타우르스 레전더리
	if (nullptr == GameEngineTexture::Find("Minotaurus_Legendary_Idle.png"))
	{
		GameEngineDirectory Path;

		Path.MoveParentToDirectory("Resources");
		Path.Move("Resources");
		Path.Move("Texture");
		Path.Move("0_Common");
		Path.Move("Player");
		Path.Move("Skull");
		Path.Move("Minotaurus");
		Path.Move("Legendary");

		// Idle Sprite
		GameEngineSprite::LoadSheet(Path.GetPlusFileName("Minotaurus_Legendary_Idle.png").GetFullPath(), 6, 1);

		// Walk Sprite
		GameEngineSprite::LoadSheet(Path.GetPlusFileName("Minotaurus_Legendary_Walk.png").GetFullPath(), 8, 1);

		// Dash Sprite
		GameEngineSprite::LoadSheet(Path.GetPlusFileName("Minotaurus_Legendary_Dash.png").GetFullPath(), 1, 1);

		// FallEnter Sprite
		GameEngineSprite::LoadSheet(Path.GetPlusFileName("Minotaurus_Legendary_Fall.png").GetFullPath(), 2, 1);

		// FallRepeat Sprite
		GameEngineSprite::LoadSheet(Path.GetPlusFileName("Minotaurus_Legendary_FallRepeat.png").GetFullPath(), 2, 1);

		// Jump Sprite
		GameEngineSprite::LoadSheet(Path.GetPlusFileName("Minotaurus_Legendary_Jump.png").GetFullPath(), 2, 1);

		// AttackA Sprite
		GameEngineSprite::LoadSheet(Path.GetPlusFileName("Minotaurus_Legendary_AttackA.png").GetFullPath(), 7, 1);

		// AttackB Sprite 
		GameEngineSprite::LoadSheet(Path.GetPlusFileName("Minotaurus_Legendary_AttackB.png").GetFullPath(), 6, 1);

		// JumpAttack Sprite
		GameEngineSprite::LoadSheet(Path.GetPlusFileName("Minotaurus_Legendary_JumpAttack.png").GetFullPath(), 3, 1);

		// JumpAttack Landing
		GameEngineSprite::LoadSheet(Path.GetPlusFileName("Minotaurus_Legendary_JumpAttackLand.png").GetFullPath(), 1, 1);

		// SkillA Sprite
		GameEngineSprite::LoadSheet(Path.GetPlusFileName("Minotaurus_Legendary_SkillA.png").GetFullPath(), 5, 1);

		// SkillB Sprite
		GameEngineSprite::LoadSheet(Path.GetPlusFileName("Minotaurus_Legendary_SkillB.png").GetFullPath(), 7, 1);
	}

	// 이펙트
	if (nullptr == GameEngineSprite::Find("Player_DashSmokeEffect.png"))
	{
		GameEngineDirectory Path;

		Path.MoveParentToDirectory("Resources");
		Path.Move("Resources");
		Path.Move("Texture");
		Path.Move("0_Common");
		Path.Move("Player");
		Path.Move("Effect");

		GameEngineSprite::LoadSheet(Path.GetPlusFileName("Player_DashSmokeEffect.png").GetFullPath(), 6, 2);
		GameEngineSprite::LoadSheet(Path.GetPlusFileName("Player_DoubleJumpEffect.png").GetFullPath(), 5, 2);
		GameEngineSprite::LoadSheet(Path.GetPlusFileName("HitSkul.png").GetFullPath(), 5, 2);
		GameEngineSprite::LoadSheet(Path.GetPlusFileName("HitNormal.png").GetFullPath(), 6, 2);
		GameEngineSprite::LoadSheet(Path.GetPlusFileName("HitSkeletonSword.png").GetFullPath(), 5, 3);
		GameEngineSprite::LoadSheet(Path.GetPlusFileName("StampEffect.png").GetFullPath(), 11, 2);

		GameEngineSprite::LoadSheet(Path.GetPlusFileName("SkullAppearance.png").GetFullPath(), 7, 1);
		GameEngineSprite::LoadSheet(Path.GetPlusFileName("LandSmoke.png").GetFullPath(), 7, 3);
		GameEngineSprite::LoadSheet(Path.GetPlusFileName("SwitchEffect.png").GetFullPath(), 5, 4);
		GameEngineSprite::LoadSheet(Path.GetPlusFileName("FireProjectile.png").GetFullPath(), 4, 6);
		GameEngineSprite::LoadSheet(Path.GetPlusFileName("FlashCut.png").GetFullPath(), 1, 8);
		GameEngineSprite::LoadSheet(Path.GetPlusFileName("FireSlash.png").GetFullPath(), 11, 2);
		GameEngineSprite::LoadSheet(Path.GetPlusFileName("WereWolfUnique_Dash_Effect.png").GetFullPath(), 2, 3);
		GameEngineSprite::LoadSheet(Path.GetPlusFileName("WereWolfUnique_Predation_Effect.png").GetFullPath(), 3, 5);
		GameEngineSprite::LoadSheet(Path.GetPlusFileName("WereWolfUnique_Switch_Effect1.png").GetFullPath(), 1, 13);
		GameEngineSprite::LoadSheet(Path.GetPlusFileName("WereWolfUnique_Switch_Effect2.png").GetFullPath(), 3, 3);

		GameEngineSprite::LoadSheet(Path.GetPlusFileName("WereWolfLegendary_Predation_Effect.png").GetFullPath(), 7, 2);
		GameEngineSprite::LoadSheet(Path.GetPlusFileName("WereWolfLegendary_Switch_Effect1.png").GetFullPath(), 1, 13);
		GameEngineSprite::LoadSheet(Path.GetPlusFileName("WereWolfLegendary_Switch_Effect2.png").GetFullPath(), 6, 2);

		GameEngineSprite::LoadSheet(Path.GetPlusFileName("HitMinotaurus.png").GetFullPath(), 3, 5);
		GameEngineSprite::LoadSheet(Path.GetPlusFileName("DashTackleEffect.png").GetFullPath(), 2, 5);
		GameEngineSprite::LoadSheet(Path.GetPlusFileName("Minotaurus_Rare_Passive.png").GetFullPath(), 5, 7);
		GameEngineSprite::LoadSheet(Path.GetPlusFileName("MinoSkillA_Smoke.png").GetFullPath(), 3, 7);
		GameEngineSprite::LoadSheet(Path.GetPlusFileName("Minotaurus_PlowUp_Smoke.png").GetFullPath(), 3, 4);
		GameEngineSprite::LoadSheet(Path.GetPlusFileName("Minotaurus_Projectile_Hit.png").GetFullPath(), 5, 4);
		GameEngineSprite::LoadSheet(Path.GetPlusFileName("Minotaurus_Rare_PlowUp.png").GetFullPath(), 3, 1);
		GameEngineSprite::LoadSheet(Path.GetPlusFileName("Minotaurus_Rare_PlowUp_Explosion.png").GetFullPath(), 5, 5);
		GameEngineSprite::LoadSheet(Path.GetPlusFileName("Minitaurus_Unique_Passive.png").GetFullPath(), 11, 2);

		GameEngineSprite::LoadSheet(Path.GetPlusFileName("Minotaurus_Rare_PlowUp_Projectile1.png").GetFullPath(), 1, 1);
		GameEngineSprite::LoadSheet(Path.GetPlusFileName("Minotaurus_Rare_PlowUp_Projectile2.png").GetFullPath(), 1, 1);
		GameEngineSprite::LoadSheet(Path.GetPlusFileName("Minotaurus_Rare_PlowUp_Projectile3.png").GetFullPath(), 1, 1);
		GameEngineSprite::LoadSheet(Path.GetPlusFileName("Minotaurus_Rare_PlowUp_Projectile4.png").GetFullPath(), 1, 1);

		EffectManager::CreateMetaData("PlayerDashEffect", {
			"Player_DashSmokeEffect.png" ,
			float4::Zero,
			0, 11,
			0.04f,
			2.0f });

		EffectManager::CreateMetaData("PlayerJumpEffect", {
			"Player_DoubleJumpEffect.png" ,
			float4::Zero,
			0, 9,
			0.05f,
			2.0f });

		EffectManager::CreateMetaData("SkullAppearance", {
			"SkullAppearance.png" ,
			float4::Zero,
			0, 6,
			0.05f,
			2.0f });

		EffectManager::CreateMetaData("HitSkul", {
			"HitSkul.png" ,
			float4::Zero,
			0, 9,
			0.05f,
			2.0f });

		EffectManager::CreateMetaData("HitNormal", {
			"HitNormal.png" ,
			float4::Zero,
			0, 11,
			0.05f,
			1.5f });

		EffectManager::CreateMetaData("HitSkeletonSword", {
			"HitSkeletonSword.png" ,
			float4::Zero,
			0, 14,
			0.03f,
			1.5f });

		EffectManager::CreateMetaData("LandSmoke", {
			"LandSmoke.png" ,
			float4::Zero,
			0, 20,
			0.03f,
			2.0f });

		EffectManager::CreateMetaData("SwitchEffect", {
			"SwitchEffect.png" ,
			float4::Zero,
			0, 19,
			0.03f,
			2.0f });

		EffectManager::CreateMetaData("FireProjectile", {
			"FireProjectile.png" ,
			float4::Zero,
			0, 23,
			0.03f,
			2.0f });

		EffectManager::CreateMetaData("FlashCut", {
			"FlashCut.png" ,
			float4::Zero,
			0, 7,
			0.025f,
			1.5f });

		EffectManager::CreateMetaData("FireSlash", {
			"FireSlash.png" ,
			float4::Zero,
			0, 21,
			0.03f,
			2.0f });

		EffectManager::CreateMetaData("WereWolf_Unique_DashSmoke", {
			"WereWolfUnique_Dash_Effect.png" ,
			float4::Zero,
			0, 5,
			0.06f,
			2.0f });

		EffectManager::CreateMetaData("WereWolf_Unique_Predation", {
			"WereWolfUnique_Predation_Effect.png" ,
			float4::Zero,
			0, 14,
			0.03f,
			2.0f });

		EffectManager::CreateMetaData("WereWolf_Unique_SwitchFlash", {
			"WereWolfUnique_Switch_Effect1.png" ,
			float4::Zero,
			0, 12,
			0.03f,
			2.0f });

		EffectManager::CreateMetaData("WereWolf_Unique_SwitchAttack", {
			"WereWolfUnique_Switch_Effect2.png" ,
			float4::Zero,
			0, 8,
			0.03f,
			2.0f });

		EffectManager::CreateMetaData("WereWolf_Legendary_Predation", {
			"WereWolfLegendary_Predation_Effect.png" ,
			float4::Zero,
			0, 13,
			0.03f,
			2.0f });

		EffectManager::CreateMetaData("WereWolf_Legendary_SwitchFlash", {
			"WereWolfLegendary_Switch_Effect1.png" ,
			float4::Zero,
			0, 12,
			0.03f,
			2.0f });

		EffectManager::CreateMetaData("WereWolf_Legendary_SwitchAttack", {
			"WereWolfLegendary_Switch_Effect2.png" ,
			float4::Zero,
			0, 11,
			0.02f,
			2.0f });

		EffectManager::CreateMetaData("HitMinotaurus", {
			"HitMinotaurus.png" ,
			float4::Zero,
			0, 14,
			0.03f,
			2.0f });		
		
		EffectManager::CreateMetaData("DashTackleEffect", {
			"DashTackleEffect.png" ,
			float4::Zero,
			0, 9,
			0.03f,
			2.0f });

		EffectManager::CreateMetaData("StampEffect", {
			.SpriteName = "StampEffect.png",
			.AnimStart = 0,
			.AnimEnd = 21,
			.AnimIter = 0.02f,
			.ScaleRatio = 2.0f,});

		EffectManager::CreateMetaData("Minotaurus_Rare_Passive", {
			.SpriteName = "Minotaurus_Rare_Passive.png",
			.AnimStart = 0,
			.AnimEnd = 34,
			.AnimIter = 0.035f,
			.ScaleRatio = 2.0f, });

		EffectManager::CreateMetaData("MinoSkillA_Smoke", {
			.SpriteName = "MinoSkillA_Smoke.png",
			.AnimStart = 0,
			.AnimEnd = 19,
			.AnimIter = 0.035f,
			.ScaleRatio = 2.0f, });

		EffectManager::CreateMetaData("Minotaurus_PlowUp_Smoke", {
			.SpriteName = "Minotaurus_PlowUp_Smoke.png",
			.AnimStart = 0,
			.AnimEnd = 11,
			.AnimIter = 0.05f,
			.ScaleRatio = 2.0f, });

		EffectManager::CreateMetaData("Minotaurus_Projectile_Hit", {
			.SpriteName = "Minotaurus_Projectile_Hit.png",
			.AnimStart = 0,
			.AnimEnd = 19,
			.AnimIter = 0.07f,
			.ScaleRatio = 1.5f, });

		EffectManager::CreateMetaData("Minotaurus_Rare_PlowUp", {
			.SpriteName = "Minotaurus_Rare_PlowUp.png",
			.AnimStart = 0,
			.AnimEnd = 2,
			.AnimIter = 0.035f,
			.ScaleRatio = 2.0f, });

		EffectManager::CreateMetaData("Minotaurus_Rare_PlowUp_Explosion", {
			.SpriteName = "Minotaurus_Rare_PlowUp_Explosion.png",
			.AnimStart = 0,
			.AnimEnd = 24,
			.AnimIter = 0.035f,
			.ScaleRatio = 2.0f, });

		EffectManager::CreateMetaData("Minotaurus_Rare_PlowUp_Projectile1", {
			.SpriteName = "Minotaurus_Rare_PlowUp_Projectile1.png",
			.AnimStart = 0,
			.AnimEnd = 0,
			.AnimIter = 0.1f,
			.ScaleRatio = 2.0f, });

		EffectManager::CreateMetaData("Minotaurus_Rare_PlowUp_Projectile2", {
			.SpriteName = "Minotaurus_Rare_PlowUp_Projectile2.png",
			.AnimStart = 0,
			.AnimEnd = 0,
			.AnimIter = 0.1f,
			.ScaleRatio = 2.0f, });

		EffectManager::CreateMetaData("Minotaurus_Rare_PlowUp_Projectile3", {
			.SpriteName = "Minotaurus_Rare_PlowUp_Projectile3.png",
			.AnimStart = 0,
			.AnimEnd = 0,
			.AnimIter = 0.1f,
			.ScaleRatio = 2.0f, });

		EffectManager::CreateMetaData("Minotaurus_Rare_PlowUp_Projectile4", {
			.SpriteName = "Minotaurus_Rare_PlowUp_Projectile4.png",
			.AnimStart = 0,
			.AnimEnd = 0,
			.AnimIter = 0.1f,
			.ScaleRatio = 2.0f, });

		EffectManager::CreateMetaData("Minitaurus_Unique_Passive", {
			.SpriteName = "Minitaurus_Unique_Passive.png",
			.AnimStart = 0,
			.AnimEnd = 21,
			.AnimIter = 0.02f,
			.ScaleRatio = 1.5f, });
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
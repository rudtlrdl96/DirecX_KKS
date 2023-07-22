#include "PrecompileHeader.h"
#include "ContentCore.h"
#include "SkullData.h"

static void LoadSkull(const SkullData& _Data)
{
	ContentDatabase<SkullData, SkullGrade>::InsertData(_Data);
}

void ContentCore::SkullDataLoad()
{

	/////////////////////////// �Ϲ� ���� /////////////////////////////////

	LoadSkull({ .Name = "��Ʋ��", .HeadTexName = "BoneSkul_Head.png",
		.StoryNote = "���ռ� ������ ���� ���̷���\n�ٸ� ���̷��濡 ���� ü���� �۾� ��Ʋ���̶� �Ҹ���.",
		.IconName_MainSkull = "Skul_UI_MainSkull.png", .IconName_SubSkull = "Skul_UI_SubSkull.png", .IconName_Inventory = "Skul_UI_Inventory.png",
		.IconName_SkillA = "SkullThrowing.png", .IconName_SkillB = "Rebone.png",
		.Name_SkillA = "�ΰ��� ��ô", .Name_SkillB = "�Ӹ��� ��ü", .Name_Switch = "������ġ",
		.Index = 0, .Grade = SkullGrade::Normal, .SkullType = SkullType::Balance,
		.MeleeAttack = 1.0f, .MagicAttack = 1.0f});

	LoadSkull({.Name = "�������", .HeadTexName = "Werewolf_Head1.png",
		.StoryNote = "���� �߰� ��ī�ο� ������ �����Դ� ���� ����",
		.SkullNote = "���� �� �������·� �����Ͽ� ������������ �����ϴ�.",
		.IconName_MainSkull = "Normal_WereWolf_UI_MainSkull.png", .IconName_SubSkull = "Normal_WereWolf_UI_SubSkull.png", .IconName_Inventory = "Normal_WereWolf_UI_Inventory.png",
		.IconName_SkillA = "WereWolf_Predation1.png", .IconName_SkillB = "Empty.png",
		.Name_SkillA = "����", .Name_SkillB = "", .Name_Switch = "�߻��� ����",
		.Index = 1, .UpgradeIndex = 100, .Grade = SkullGrade::Normal, .SkullType = SkullType::Speed,
		.MeleeAttack = 1.0f, .MagicAttack = 1.0f, .MoveSpeed = 440.0f, });

	/////////////////////////// ���� ���� /////////////////////////////////

	LoadSkull({.Name = "���� �� �������", .HeadTexName = "Werewolf_Head2.png",
		.StoryNote = "�����Ͽ� ������ �̷�� ���� ������ �Ͽ�",
		.SkullNote = "���� �� �������·� �����Ͽ� ������������ �����ϴ�.",
		.IconName_MainSkull = "Rare_WereWolf_UI_MainSkull.png", .IconName_SubSkull = "Rare_WereWolf_UI_SubSkull.png", .IconName_Inventory = "Rare_WereWolf_UI_Inventory.png",
		.IconName_SkillA = "WereWolf_Predation2.png", .IconName_SkillB = "Empty.png" ,
		.Name_SkillA = "����", .Name_SkillB = "", .Name_Switch = "�߻��� ����",
		.Index = 100, .UpgradeIndex = 200, .Grade = SkullGrade::Rare, .SkullType = SkullType::Speed,
		.MeleeAttack = 1.2f, .MagicAttack = 1.2f, .MoveSpeed = 440.0f });

	LoadSkull({ .Name = "�̳�Ÿ��ν� 1��", .HeadTexName = "Minotaurus_Head1.png",
		.StoryNote = "ũ��Ÿ �̱��� ��Ű�� ����",
		.SkullNote = "��ų ��� �� 3�ʰ� �ֺ��� ����� ������ ������������ �����ϴ�.",
		.IconName_MainSkull = "Rare_Minotaurus_UI_MainSkull.png", .IconName_SubSkull = "Rare_Minotaurus_UI_SubSkull.png", .IconName_Inventory = "Rare_Minotaurus_UI_Inventory.png",
		.IconName_SkillA = "Minotaurus_Stamp1.png", .IconName_SkillB = "Empty.png" ,
		.Name_SkillA = "�����", .Name_SkillB = "", .Name_Switch = "ī�� ������",
		.Index = 101, .UpgradeIndex = 201, .Grade = SkullGrade::Rare, .SkullType = SkullType::Power,
		.MeleeAttack = 1.2f, .MagicAttack = 1.2f , .MoveSpeed = 440.0f });


	/////////////////////////// ����ũ ���� /////////////////////////////////

	LoadSkull({.Name = "��θӸ� �������", .HeadTexName = "Werewolf_Head3.png",
		.StoryNote = "������ �̲��� �̸��� ��ġ��, �Ǹ� ���� ��θӸ�",
		.SkullNote = "���� �� �������·� �����Ͽ� ������������ �����ϴ�. ���� �ڸ��� �ټ��� Į�ٶ��� �Ͼ ������������ �����ϴ�.",
		.IconName_MainSkull = "Unique_WereWolf_UI_MainSkull.png", .IconName_SubSkull = "Unique_WereWolf_UI_SubSkull.png", .IconName_Inventory = "Unique_WereWolf_UI_Inventory.png",
		.IconName_SkillA = "WereWolf_Predation3.png", .IconName_SkillB = "WereWolf_Hunting3.png" ,
		.Name_SkillA = "����", .Name_SkillB = "����", .Name_Switch = "�߻��� ����",
		.Index = 200, .UpgradeIndex = 300, .Grade = SkullGrade::Unique, .SkullType = SkullType::Speed,
		.MeleeAttack = 1.4f, .MagicAttack = 1.4f });

	LoadSkull({ .Name = "�̳�Ÿ��ν� 2��", .HeadTexName = "Minotaurus_Head2.png",
		.StoryNote = "���谡�鿡�� ����� ��, ���� �������� ���ƿ� ����",
		.SkullNote = "��ų ��� �� ���︲�� 4ȸ ������ �ֺ� ������ ������������ ������ 10% Ȯ���� ������ �ο��մϴ�.",
		.IconName_MainSkull = "Unique_Minotaurus_UI_MainSkull.png", .IconName_SubSkull = "Unique_Minotaurus_UI_SubSkull.png", .IconName_Inventory = "Unique_Minotaurus_UI_Inventory.png",
		.IconName_SkillA = "Minotaurus_Stamp2.png", .IconName_SkillB = "Minotaurus_PlowUp2.png",
		.Name_SkillA = "�����", .Name_SkillB = "�ھ���", .Name_Switch = "ī�� ������",
		.Index = 201, .UpgradeIndex = 301, .Grade = SkullGrade::Unique, .SkullType = SkullType::Power,
		.MeleeAttack = 1.4f, .MagicAttack = 1.4f });

	LoadSkull({ .Name = "������", .HeadTexName = "ChiefGuard_Head.png",
		.StoryNote = "���ռ� ������ ����",
		.IconName_MainSkull = "ChiefGuard_UI_MainSkull.png", .IconName_SubSkull = "ChiefGuard_UI_SubSkull.png", .IconName_Inventory = "ChiefGuard_UI_Inventory.png",
		.IconName_SkillA = "ChiefGuard_Skill1.png", .IconName_SkillB = "ChiefGuard_Skill2.png" ,
		.Name_SkillA = "�ֵθ���", .Name_SkillB = "ȭ����", .Name_Switch = "�÷���",
		.Index = 203, .Grade = SkullGrade::Unique, .SkullType = SkullType::Balance,
		.MeleeAttack = 1.4f, .MagicAttack = 1.4f });
	
	/////////////////////////// �������� ���� /////////////////////////////////

	LoadSkull({.Name = "������ �������", .HeadTexName = "Werewolf_Head4.png",
		.StoryNote = "��ȭ�� ������ �Ĵ뿡 ��� �̸��� �����, ���� �ְ��� �������",
		.SkullNote = "���� �� �������·� �����Ͽ� ������������ �����ϴ�. ���� �ڸ��� �ټ��� Į�ٶ��� �Ͼ ������������ �����ϴ�.���� 5�ʰ� 1�ʸ��� ���� �ڸ��� Į�ٶ��� �Ͼ ������������ �����ϴ�.",
		.IconName_MainSkull = "Legandary_WereWolf_UI_MainSkull.png", .IconName_SubSkull = "Legandary_WereWolf_UI_SubSkull.png", .IconName_Inventory = "Legandary_WereWolf_UI_Inventory.png",
		.IconName_SkillA = "WereWolf_Predation4.png", .IconName_SkillB = "WereWolf_Hunting4.png" ,
		.Name_SkillA = "����", .Name_SkillB = "����", .Name_Switch = "�߻��� ����",
		.Index = 300, .Grade = SkullGrade::Legendary, .SkullType = SkullType::Speed,
		.MeleeAttack = 1.8f, .MagicAttack = 1.8f });

	LoadSkull({ .Name = "�̳�Ÿ��ν� 3��", .HeadTexName = "Minotaurus_Head3.png",
		.StoryNote = "�� ������ ħ�Ե� ������� �ʴ�, ũ��Ÿ �̱��� �������� ������",
		.SkullNote = "��ų ��� �� ���︲�� 4ȸ ������ �ֺ� ������ ������������ ������ 10% Ȯ���� ������ �ο��մϴ�.",
		.IconName_MainSkull = "Legendary_Minotaurus_UI_MainSkull.png", .IconName_SubSkull = "Legendary_Minotaurus_UI_SubSkull.png", .IconName_Inventory = "Legendary_Minotaurus_UI_Inventory.png",
		.IconName_SkillA = "Minotaurus_Stamp3.png", .IconName_SkillB = "Minotaurus_PlowUp3.png" ,
		.Name_SkillA = "�����", .Name_SkillB = "�ھ���", .Name_Switch = "ī�� ������",
		.Index = 301, .Grade = SkullGrade::Legendary, .SkullType = SkullType::Power,
		.MeleeAttack = 1.8f, .MagicAttack = 1.8f });

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

	// ��Ʋ�� �ؽ��� �ε�
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

	// ������ �ؽ��� �ε�
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

	// ������� �븻
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

	// ������� ����
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

	// ������� ����ũ
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

	// ������� ��������
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

	// �̳�Ÿ�츣�� ����
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

	// �̳�Ÿ�츣�� ����ũ
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
	
	// �̳�Ÿ�츣�� ��������
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

	// ����Ʈ
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
		GameEngineSprite::LoadSheet(Path.GetPlusFileName("HitNormalCritical.png").GetFullPath(), 4, 2);
		GameEngineSprite::LoadSheet(Path.GetPlusFileName("HitSpecialCritical.png").GetFullPath(), 4, 3);
		GameEngineSprite::LoadSheet(Path.GetPlusFileName("HitSlashCritical.png").GetFullPath(), 4, 2);

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
		GameEngineSprite::LoadSheet(Path.GetPlusFileName("Minotaurus_Projectile_Hit2.png").GetFullPath(), 5, 4);
		GameEngineSprite::LoadSheet(Path.GetPlusFileName("Minotaurus_Rare_PlowUp.png").GetFullPath(), 3, 1);
		GameEngineSprite::LoadSheet(Path.GetPlusFileName("Minotaurus_Rare_PlowUp_Explosion.png").GetFullPath(), 5, 5);
		GameEngineSprite::LoadSheet(Path.GetPlusFileName("Minitaurus_Unique_Passive.png").GetFullPath(), 11, 2);

		GameEngineSprite::LoadSheet(Path.GetPlusFileName("Minotaurus_Rare_PlowUp_Projectile1.png").GetFullPath(), 1, 1);
		GameEngineSprite::LoadSheet(Path.GetPlusFileName("Minotaurus_Rare_PlowUp_Projectile2.png").GetFullPath(), 1, 1);
		GameEngineSprite::LoadSheet(Path.GetPlusFileName("Minotaurus_Rare_PlowUp_Projectile3.png").GetFullPath(), 1, 1);
		GameEngineSprite::LoadSheet(Path.GetPlusFileName("Minotaurus_Rare_PlowUp_Projectile4.png").GetFullPath(), 1, 1);

		GameEngineSprite::LoadSheet(Path.GetPlusFileName("Minotaurus_Legendary_PlowUp.png").GetFullPath(), 3, 1);
		GameEngineSprite::LoadSheet(Path.GetPlusFileName("Minotaurus_Legendary_PlowUpExplosion.png").GetFullPath(), 5, 5);
		GameEngineSprite::LoadSheet(Path.GetPlusFileName("Minotaurus_Legendary_PlowUpSkome.png").GetFullPath(), 2, 6);
		GameEngineSprite::LoadSheet(Path.GetPlusFileName("Minotaurus_WaveSmoke_Effect.png").GetFullPath(), 4, 4);

		GameEngineSprite::LoadSheet(Path.GetPlusFileName("Minotaurus_Debris_Projectile1.png").GetFullPath(), 1, 1);
		GameEngineSprite::LoadSheet(Path.GetPlusFileName("Minotaurus_Debris_Projectile2.png").GetFullPath(), 1, 1);
		GameEngineSprite::LoadSheet(Path.GetPlusFileName("Minotaurus_Debris_Projectile3.png").GetFullPath(), 1, 1);

		GameEngineSprite::LoadSheet(Path.GetPlusFileName("Minotaurus_3_PlowUp_Rock1.png").GetFullPath(), 1, 1);
		GameEngineSprite::LoadSheet(Path.GetPlusFileName("Minotaurus_3_PlowUp_Rock2.png").GetFullPath(), 1, 1);
		GameEngineSprite::LoadSheet(Path.GetPlusFileName("Minotaurus_3_PlowUp_Rock3.png").GetFullPath(), 1, 1);
		GameEngineSprite::LoadSheet(Path.GetPlusFileName("Minotaurus_3_PlowUp_Remains_0.png").GetFullPath(), 1, 1);
		GameEngineSprite::LoadSheet(Path.GetPlusFileName("Minotaurus_3_Swap_Rock_0.png").GetFullPath(), 1, 1);

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

		EffectManager::CreateMetaData("HitNormalCritical", {
			"HitNormalCritical.png" ,
			float4::Zero,
			0, 6,
			0.04f,
			1.5f });

		EffectManager::CreateMetaData("HitSpecialCritical", {
			"HitSpecialCritical.png" ,
			float4::Zero,
			0, 10,
			0.03f,
			1.5f });

		EffectManager::CreateMetaData("HitSlashCritical", {
			"HitSlashCritical.png" ,
			float4::Zero,
			0, 6,
			0.04f,
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
			.AnimInter = 0.02f,
			.ScaleRatio = 2.0f,});

		EffectManager::CreateMetaData("Minotaurus_Rare_Passive", {
			.SpriteName = "Minotaurus_Rare_Passive.png",
			.AnimStart = 0,
			.AnimEnd = 34,
			.AnimInter = 0.035f,
			.ScaleRatio = 2.0f, });

		EffectManager::CreateMetaData("MinoSkillA_Smoke", {
			.SpriteName = "MinoSkillA_Smoke.png",
			.AnimStart = 0,
			.AnimEnd = 19,
			.AnimInter = 0.035f,
			.ScaleRatio = 2.0f, });

		EffectManager::CreateMetaData("Minotaurus_PlowUp_Smoke", {
			.SpriteName = "Minotaurus_PlowUp_Smoke.png",
			.AnimStart = 0,
			.AnimEnd = 11,
			.AnimInter = 0.05f,
			.ScaleRatio = 2.0f, });

		EffectManager::CreateMetaData("Minotaurus_Projectile_Hit", {
			.SpriteName = "Minotaurus_Projectile_Hit.png",
			.AnimStart = 0,
			.AnimEnd = 19,
			.AnimInter = 0.07f,
			.ScaleRatio = 1.5f, });

		EffectManager::CreateMetaData("Minotaurus_Projectile_Hit2", {
			.SpriteName = "Minotaurus_Projectile_Hit2.png",
			.AnimStart = 0,
			.AnimEnd = 19,
			.AnimInter = 0.07f,
			.ScaleRatio = 1.5f, });

		EffectManager::CreateMetaData("Minotaurus_Rare_PlowUp", {
			.SpriteName = "Minotaurus_Rare_PlowUp.png",
			.AnimStart = 0,
			.AnimEnd = 2,
			.AnimInter = 0.035f,
			.ScaleRatio = 2.0f, });

		EffectManager::CreateMetaData("Minotaurus_Rare_PlowUp_Explosion", {
			.SpriteName = "Minotaurus_Rare_PlowUp_Explosion.png",
			.AnimStart = 0,
			.AnimEnd = 24,
			.AnimInter = 0.035f,
			.ScaleRatio = 2.0f, });

		EffectManager::CreateMetaData("Minotaurus_Rare_PlowUp_Projectile1", {
			.SpriteName = "Minotaurus_Rare_PlowUp_Projectile1.png",
			.AnimStart = 0,
			.AnimEnd = 0,
			.AnimInter = 0.1f,
			.ScaleRatio = 2.0f, });

		EffectManager::CreateMetaData("Minotaurus_Rare_PlowUp_Projectile2", {
			.SpriteName = "Minotaurus_Rare_PlowUp_Projectile2.png",
			.AnimStart = 0,
			.AnimEnd = 0,
			.AnimInter = 0.1f,
			.ScaleRatio = 2.0f, });

		EffectManager::CreateMetaData("Minotaurus_Rare_PlowUp_Projectile3", {
			.SpriteName = "Minotaurus_Rare_PlowUp_Projectile3.png",
			.AnimStart = 0,
			.AnimEnd = 0,
			.AnimInter = 0.1f,
			.ScaleRatio = 2.0f, });

		EffectManager::CreateMetaData("Minotaurus_Rare_PlowUp_Projectile4", {
			.SpriteName = "Minotaurus_Rare_PlowUp_Projectile4.png",
			.AnimStart = 0,
			.AnimEnd = 0,
			.AnimInter = 0.1f,
			.ScaleRatio = 2.0f, });

		EffectManager::CreateMetaData("Minitaurus_Unique_Passive", {
			.SpriteName = "Minitaurus_Unique_Passive.png",
			.AnimStart = 0,
			.AnimEnd = 21,
			.AnimInter = 0.02f,
			.ScaleRatio = 1.5f, });

		EffectManager::CreateMetaData("Minotaurus_Legendary_PlowUp", {
			.SpriteName = "Minotaurus_Legendary_PlowUp.png",
			.AnimStart = 0,
			.AnimEnd = 2,
			.AnimInter = 0.035f,
			.ScaleRatio = 2.0f, });

		EffectManager::CreateMetaData("Minotaurus_Legendary_PlowUpExplosion", {
			.SpriteName = "Minotaurus_Legendary_PlowUpExplosion.png",
			.AnimStart = 0,
			.AnimEnd = 23,
			.AnimInter = 0.035f,
			.ScaleRatio = 2.0f, });

		EffectManager::CreateMetaData("Minotaurus_Legendary_PlowUpSkome", {
			.SpriteName = "Minotaurus_Legendary_PlowUpSkome.png",
			.AnimStart = 0,
			.AnimEnd = 11,
			.AnimInter = 0.035f,
			.ScaleRatio = 2.0f, });

		EffectManager::CreateMetaData("Minotaurus_Debris_Projectile1", {
			.SpriteName = "Minotaurus_Debris_Projectile1.png",
			.AnimStart = 0,
			.AnimEnd = 0,
			.AnimInter = 0.1f,
			.ScaleRatio = 2.0f, });

		EffectManager::CreateMetaData("Minotaurus_Debris_Projectile2", {
			.SpriteName = "Minotaurus_Debris_Projectile2.png",
			.AnimStart = 0,
			.AnimEnd = 0,
			.AnimInter = 0.1f,
			.ScaleRatio = 2.0f, });

		EffectManager::CreateMetaData("Minotaurus_Debris_Projectile3", {
			.SpriteName = "Minotaurus_Debris_Projectile3.png",
			.AnimStart = 0,
			.AnimEnd = 0,
			.AnimInter = 0.1f,
			.ScaleRatio = 2.0f, });

		EffectManager::CreateMetaData("Minotaurus_3_PlowUp_Rock1", {
			.SpriteName = "Minotaurus_3_PlowUp_Rock1.png",
			.AnimStart = 0,
			.AnimEnd = 0,
			.AnimInter = 0.1f,
			.ScaleRatio = 2.0f, });

		EffectManager::CreateMetaData("Minotaurus_3_PlowUp_Rock2", {
			.SpriteName = "Minotaurus_3_PlowUp_Rock2.png",
			.AnimStart = 0,
			.AnimEnd = 0,
			.AnimInter = 0.1f,
			.ScaleRatio = 2.0f, });

		EffectManager::CreateMetaData("Minotaurus_3_PlowUp_Rock3", {
			.SpriteName = "Minotaurus_3_PlowUp_Rock3.png",
			.AnimStart = 0,
			.AnimEnd = 0,
			.AnimInter = 0.1f,
			.ScaleRatio = 2.0f, });		

		EffectManager::CreateMetaData("Minotaurus_3_PlowUp_Remains_0", {
			.SpriteName = "Minotaurus_3_PlowUp_Remains_0.png",
			.AnimStart = 0,
			.AnimEnd = 0,
			.AnimInter = 0.1f,
			.ScaleRatio = 2.0f, });		
		
		EffectManager::CreateMetaData("Minotaurus_3_Swap_Rock_0", {
			.SpriteName = "Minotaurus_3_Swap_Rock_0.png",
			.AnimStart = 0,
			.AnimEnd = 0,
			.AnimInter = 0.1f,
			.ScaleRatio = 2.0f, });

		EffectManager::CreateMetaData("Minotaurus_WaveSmoke_Effect", {
			.SpriteName = "Minotaurus_WaveSmoke_Effect.png",
			.AnimStart = 0,
			.AnimEnd = 15,
			.AnimInter = 0.04f,
			.ScaleRatio = 2.0f });
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
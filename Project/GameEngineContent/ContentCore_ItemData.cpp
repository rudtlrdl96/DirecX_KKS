#include "PrecompileHeader.h"
#include "ContentCore.h"
#include "ItemData.h"


static void LoadItem(const ItemData& _Data)
{
	ContentDatabase<ItemData, ItemGrade>::InsertData(_Data);
}

void ContentCore::ItemDataLoad()
{
	{
		GameEngineDirectory Path;

		Path.MoveParentToDirectory("Resources");
		Path.Move("Resources");
		Path.Move("Texture");
		Path.Move("0_Common");
		Path.Move("Goods");

		{
			Path.Move("Bone");

			GameEngineSprite::LoadSheet(Path.GetPlusFileName("BoneChip_1.png").GetFullPath(), 1, 1);
			GameEngineSprite::LoadSheet(Path.GetPlusFileName("BoneChip_2.png").GetFullPath(), 1, 1);
			GameEngineSprite::LoadSheet(Path.GetPlusFileName("BoneChip_3.png").GetFullPath(), 1, 1);
			GameEngineSprite::LoadSheet(Path.GetPlusFileName("BoneChip_4.png").GetFullPath(), 1, 1);
			GameEngineSprite::LoadSheet(Path.GetPlusFileName("BoneGoodsEffect.png").GetFullPath(), 6, 5);

			EffectManager::CreateMetaData("BoneGoodsEffect",{
				.SpriteName = "BoneGoodsEffect.png",
				.AnimStart = 0, .AnimEnd = 28, .AnimInter = 0.025f,
				.ScaleRatio = 2.0f,});
	
			Path.MoveParent();			
		}


		{
			Path.Move("Gold");

			GameEngineSprite::LoadSheet(Path.GetPlusFileName("Goods_Gold.png").GetFullPath(), 3, 3);
			GameEngineSprite::LoadSheet(Path.GetPlusFileName("GoldGoodsEffect.png").GetFullPath(), 6, 5);

			EffectManager::CreateMetaData("GoldGoodsEffect", {
				.SpriteName = "GoldGoodsEffect.png",
				.AnimStart = 0, .AnimEnd = 28, .AnimInter = 0.025f,
				.ScaleRatio = 2.0f, });

			Path.MoveParent();
		}

		{
			Path.Move("ManaStone");

			GameEngineSprite::LoadSheet(Path.GetPlusFileName("DarkQuartz_1.png").GetFullPath(), 1, 1);
			GameEngineSprite::LoadSheet(Path.GetPlusFileName("DarkQuartz_2.png").GetFullPath(), 1, 1);
			GameEngineSprite::LoadSheet(Path.GetPlusFileName("DarkQuartz_3.png").GetFullPath(), 1, 1);
			GameEngineSprite::LoadSheet(Path.GetPlusFileName("DarkQuartz_4.png").GetFullPath(), 1, 1);
			GameEngineSprite::LoadSheet(Path.GetPlusFileName("ManaStoneGoodsEffect.png").GetFullPath(), 6, 5);

			EffectManager::CreateMetaData("ManaStoneGoodsEffect", {
				.SpriteName = "ManaStoneGoodsEffect.png",
				.AnimStart = 0, .AnimEnd = 28, .AnimInter = 0.025f,
				.ScaleRatio = 2.0f, });

			Path.MoveParent();
		}

	}

	LoadItem({.Name = "������ Į���� ��", .Note = "#R�������ݷ�#E�� 30% �����մϴ�.", .Index = 0,
		.Grade = ItemGrade::Normal, .Synergy1 = Synergy::Courage, .Synergy2 = Synergy::Antique,
		.MeleeAttack = 0.3f});
	LoadItem({.Name = "������ Į���� ������", .Note = "�޴� �������� 15% �����մϴ�.", .Index = 1,
		.Grade = ItemGrade::Normal, .Synergy1 = Synergy::Wisdom, .Synergy2 = Synergy::ManaCycle,
		.DamageReduction = 0.15f});
	LoadItem({.Name = "������ Į���� Ȱ", .Note = "ġ��Ÿ Ȯ���� 8% �����մϴ�.", .Index = 2,
		.Grade = ItemGrade::Normal, .Synergy1 = Synergy::Strike, .Synergy2 = Synergy::Chase,
		.CriticalPercent = 0.08f});
	LoadItem({.Name = "�� �ٷ� ���� ����", .Note = "�ִ� ü���� 25 �����մϴ�.", .Index = 3,
		.Grade = ItemGrade::Normal, .Synergy1 = Synergy::Antique, .Synergy2 = Synergy::Heritage,
		.HP = 25});
	LoadItem({.Name = "���� �⵵��", .Note = "��ų ��ٿ� �ӵ��� 40% �����մϴ�.",.Index = 4,
		.Grade = ItemGrade::Normal, .Synergy1 = Synergy::ManaCycle, .Synergy2 = Synergy::Soar,
		.SkillCoolDown = 0.4f});
	LoadItem({.Name = "�׵�", .Note = "���ݼӵ��� 20% �����մϴ�.", .Index = 5,
		.Grade = ItemGrade::Normal, .Synergy1 = Synergy::Rapidity, .Synergy2 = Synergy::Misfortune,
		.AttackSpeed = 0.2f});

	LoadItem({ .Name = "��� ���", .Note = "���� ��ٿ� �ӵ��� 65% �����մϴ�.\n�ִ�ü���� 35 �����մϴ�.", .Index = 100,
		.Grade = ItemGrade::Rare, .Synergy1 = Synergy::Antique, .Synergy2 = Synergy::Heritage,
		.HP = 35, .QuintessenceCoolDown = 0.65f});
	LoadItem({ .Name = "��Ʋ�� ���", .Note = "#R�������ݷ�#E�� 25% �����մϴ�.\nġ��Ÿ Ȯ���� 10 % �����մϴ�.", .Index = 101,
		.Grade = ItemGrade::Rare, .Synergy1 = Synergy::Misfortune, .Synergy2 = Synergy::Soar,
		.MeleeAttack = 0.25f, .CriticalPercent = 0.1f});
	LoadItem({ .Name = "�������� �߰�", .Note = "�������� �ӵ��� 40% �����ϰ� #R�������ݷ�#E�� 35% �����մϴ�", .Index = 102,
		.Grade = ItemGrade::Rare, .Synergy1 = Synergy::Courage, .Synergy2 = Synergy::Strike,
		.MeleeAttack = 0.35f, .CastingSpeed = 0.4f});
	LoadItem({ .Name = "�������� �����", .Note = "�������� �ӵ��� 40% �����ϰ� #B�������ݷ�#E�� 35% �����մϴ�.", .Index = 103,
		.Grade = ItemGrade::Rare, .Synergy1 = Synergy::Wisdom, .Synergy2 = Synergy::Chase,
		.MagicAttack = 0.4f ,.CastingSpeed = 0.4f});
	LoadItem({ .Name = "�¾��� ��", .Note = "#R�������ݷ�#E�� 40% �����մϴ�.", .Index = 104,
		.Grade = ItemGrade::Rare, .Synergy1 = Synergy::Courage, .Synergy2 = Synergy::Rapidity,
		.MeleeAttack = 0.4f});
	LoadItem({ .Name = "Ȳ�����", .Note = "ȹ���ϴ� ��差�� 25% �����մϴ�.\n�ִ�ü���� 35 �����մϴ�.", .Index = 105,
		.Grade = ItemGrade::Rare, .Synergy1 = Synergy::Antique, .Synergy2 = Synergy::Heritage,
		.HP = 35, .GoldPercent = 0.25f});

	LoadItem({ .Name = "��������", .Note = "���߿� ���� �� �޴� �������� 35% �����ϰ� ��ų ��ٿ� �ӵ��� 50% �����մϴ�.", .Index = 200,
		.Grade = ItemGrade::Unique, .Synergy1 = Synergy::Soar, .Synergy2 = Synergy::Rapidity,
		.DamageReduction = 0.35f, .SkillCoolDown = 0.5f});
	LoadItem({ .Name = "������ ��ö�ܰ�", .Note = "���� ������ ������ 2�ʰ� ġ��Ÿ Ȯ���� 2% �����մϴ�.\n�� ȿ���� 20ȸ���� ��ø�˴ϴ�.", .Index = 201,
		.Grade = ItemGrade::Unique, .Synergy1 = Synergy::Rapidity, .Synergy2 = Synergy::Chase,
		.CriticalPercent = 0.02f});
	LoadItem({ .Name = "��ɲ��� �������", .Note = "ġ��Ÿ �������� 35% �����մϴ�.", .Index = 202,
		.Grade = ItemGrade::Unique, .Synergy1 = Synergy::Strike, .Synergy2 = Synergy::Misfortune,
		.CriticalDamage = 0.35f});
	LoadItem({ .Name = "Ÿ�� ������ �κ�", .Note = "#B�������ݷ�#E�� 50% �����մϴ�.", .Index = 203,
		.Grade = ItemGrade::Unique, .Synergy1 = Synergy::Wisdom, .Synergy2 = Synergy::ManaCycle,
		.MagicAttack = 0.5f});

	LoadItem({ .Name = "������ ����", .Note = "ġ��Ÿ Ȯ���� 30% �����ϰ� ġ��Ÿ �������� 70% �����մϴ�.", .Index = 300,
		.Grade = ItemGrade::Legendary, .Synergy1 = Synergy::Strike, .Synergy2 = Synergy::Chase,
		.CriticalPercent = -0.3f, .CriticalDamage = 0.7f});
	LoadItem({ .Name = "������ ��", .Note = "��ų ��� �� 30% Ȯ���� �ش� ��ų�� ��Ÿ���� �ʱ�ȭ �˴ϴ�.", .Index = 301,
		.Grade = ItemGrade::Legendary, .Synergy1 = Synergy::ManaCycle, .Synergy2 = Synergy::Heritage,
		.SkillCoolDown = 0.3f});
	LoadItem({ .Name = "��� ���ܱ�", .Note = "#R�������ݷ�#N�� 100% �����մϴ�. ", .Index = 302,
		.Grade = ItemGrade::Legendary, .Synergy1 = Synergy::Courage, .Synergy2 = Synergy::Misfortune,
		.MeleeAttack = 1.0f});
	LoadItem({ .Name = "���ǵ��� ����", .Note = "#B�������ݷ�#E�� 100% �����մϴ�.", .Index = 303,
		.Grade = ItemGrade::Legendary, .Synergy1 = Synergy::Wisdom, .Synergy2 = Synergy::Soar,
		.MagicAttack = 1.0f});

	std::vector<ItemData> NormalDatas;
	ContentDatabase<ItemData, ItemGrade>::CopyGradeDatas(ItemGrade::Normal, NormalDatas);
	std::vector<ItemData> RareDatas;
	ContentDatabase<ItemData, ItemGrade>::CopyGradeDatas(ItemGrade::Rare, RareDatas);
	std::vector<ItemData> UniqueDatas;
	ContentDatabase<ItemData, ItemGrade>::CopyGradeDatas(ItemGrade::Unique, UniqueDatas);
	std::vector<ItemData> LegendaryDatas;
	ContentDatabase<ItemData, ItemGrade>::CopyGradeDatas(ItemGrade::Legendary, LegendaryDatas);

	int a = 0;
}
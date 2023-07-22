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

		Path.MoveParent();

		Path.Move("Item");

		{
			std::vector<GameEngineFile> Files = Path.GetAllFile({ ".png" });

			for (UINT i = 0; i < Files.size(); i++)
			{
				GameEngineTexture::Load(Files[i].GetFullPath());
			}
		}

	}

	/////////////////////////////////////////////////////////////////////// �Ϲ�
	
	// �Ϸ�
	LoadItem({.Name = "������ Į���� ��", .Note = "�������ݷ��� 10% �����մϴ�.", 
		.Story = "������ Į���� �� ���޿� ��. ������ �ǽ��� ������, ���� �� �˳��� ������� �ʴ�.", .Index = 0,
		.Grade = ItemGrade::Normal, .Synergy1 = Synergy::Courage, .Synergy2 = Synergy::Antique,
		.ItemTexName = "BasicCarleonSword.png",
		.InventoryTexName = "Inventory_BasicCarleonSword.png",
		.MeleeAttack = 0.1f});
	// �Ϸ�
	LoadItem({.Name = "������ Į���� ������", .Note = "�޴� �������� 15% �����մϴ�.",
		.Story = "Į������ ���� ��ī���� �������鿡�� ���޵� ����ǰ", .Index = 1,
		.Grade = ItemGrade::Normal, .Synergy1 = Synergy::Wisdom, .Synergy2 = Synergy::ManaCycle,
		.ItemTexName = "BasicCarleonStaff.png",
		.InventoryTexName = "Inventory_BasicCarleonStaff.png",
		.DamageReduction = 0.15f});
	// �Ϸ�
	LoadItem({.Name = "������ Į���� Ȱ", .Note = "ġ��Ÿ Ȯ���� 10% �����մϴ�.", 
		.Story = "������ ���޵� ���򿡴� �� ������ �ʴ´�.", .Index = 2,
		.Grade = ItemGrade::Normal, .Synergy1 = Synergy::Strike, .Synergy2 = Synergy::Chase,
		.ItemTexName = "BasicCarleonBow.png",
		.InventoryTexName = "Inventory_BasicCarleonBow.png",
		.CriticalPercent = 10.0f});
	// �Ϸ�
	LoadItem({.Name = "�� �ٷ� ���� ����", .Note = "�ִ� ü���� 25 �����մϴ�.", 
		.Story = "������ ��� �г밡 �������� ���� ������ ������ ���� ����̴�.", .Index = 3,
		.Grade = ItemGrade::Normal, .Synergy1 = Synergy::Antique, .Synergy2 = Synergy::Heritage,
		.ItemTexName = "DimLightDarkQuartz.png",
		.InventoryTexName = "Inventory_DimLightDarkQuartz.png",
		.HP = 25});
	// �Ϸ�
	LoadItem({.Name = "���� �⵵��", .Note = "��ų ��ٿ� �ӵ��� 30% �����մϴ�.",
		.Story = "�翬�� ����. ���� �ϴµ� �ݹ� �ؿ�. ���� �� �� �ƴմϴ�.", .Index = 4,
		.Grade = ItemGrade::Normal, .Synergy1 = Synergy::ManaCycle, .Synergy2 = Synergy::Soar,
		.ItemTexName = "PrayerBeforeMeal.png",
		.InventoryTexName = "Inventory_PrayerBeforeMeal.png",
		.SkillCoolDown = 0.3f});
	// �Ϸ�
	LoadItem({.Name = "�׵�", .Note = "���ݼӵ��� 10% �����մϴ�.", 
		.Story = "�Ӹ��� ������ ���� �� �ִ� ������ ������ ��", .Index = 5,
		.Grade = ItemGrade::Normal, .Synergy1 = Synergy::Rapidity, .Synergy2 = Synergy::Misfortune,
		.ItemTexName = "KendoStick.png",
		.InventoryTexName = "Inventory_KendoStick.png",
		.AttackSpeed = 0.1f});

	/////////////////////////////////////////////////////////////////////// ����
	
	// �Ϸ�
	LoadItem({ .Name = "��� ���", .Note = "���� ��ٿ� �ӵ��� 65% �����մϴ�.\n�ִ�ü���� 35 �����մϴ�.", 
		.Story = "������ ��� ������ ȥ�� ��ȭ�ϱ� ���� ���Ǵ� ���", .Index = 100,
		.Grade = ItemGrade::Rare, .Synergy1 = Synergy::Antique, .Synergy2 = Synergy::Heritage,
		.ItemTexName = "AncientCenser.png",
		.InventoryTexName = "Inventory_AncientCenser.png",
		.HP = 35, .QuintessenceCoolDown = 0.65f});
	// �Ϸ�
	LoadItem({ .Name = "��Ʋ�� ���", .Note = "�������ݷ��� 20% �����մϴ�.\nġ��Ÿ Ȯ���� 15% �����մϴ�.", 
		.Story = "�˵��� �� �� ���� ġ������ ���", .Index = 101,
		.Grade = ItemGrade::Rare, .Synergy1 = Synergy::Misfortune, .Synergy2 = Synergy::Soar,
		.ItemTexName = "FightersKnuckle.png",
		.InventoryTexName = "Inventory_FightersKnuckle.png",
		.MeleeAttack = 0.2f, .CriticalPercent = 15.0f});
	// �Ϸ�
	LoadItem({ .Name = "�������� �߰�", .Note = "�������� �ӵ��� 40% �����ϰ� �������ݷ��� 25% �����մϴ�", 
		.Story = "����� �������� ���ðԳ�.", .Index = 102,
		.Grade = ItemGrade::Rare, .Synergy1 = Synergy::Courage, .Synergy2 = Synergy::Strike,
		.ItemTexName = "AttendantsPauldron.png",
		.InventoryTexName = "Inventory_AttendantsPauldron.png",
		.MeleeAttack = 0.25f, .CastingSpeed = 0.4f});
	// �Ϸ�
	LoadItem({ .Name = "�������� �����", .Note = "�������� �ӵ��� 40% �����ϰ� �������ݷ��� 25% �����մϴ�.", 
		.Story = "����̶� �� ��â�� ���� �ƴҼ�. ���� ���� �����غ��Գ�.", .Index = 103,
		.Grade = ItemGrade::Rare, .Synergy1 = Synergy::Wisdom, .Synergy2 = Synergy::Chase,
		.ItemTexName = "AttendantsNecklace.png",
		.InventoryTexName = "Inventory_AttendantsNecklace.png",
		.MagicAttack = 0.25f ,.CastingSpeed = 0.4f});
	// �Ϸ�
	LoadItem({ .Name = "�¾��� ��", .Note = "�������ݷ��� 40% �����մϴ�.", 
		.Story = "���𰡸� �׸����ϴ� ����, �¾��� ������ ������ ��.", .Index = 104,
		.Grade = ItemGrade::Rare, .Synergy1 = Synergy::Courage, .Synergy2 = Synergy::Rapidity,
		.ItemTexName = "SwordOfSun.png",
		.InventoryTexName = "Inventory_SwordOfSun.png",
		.MeleeAttack = 0.4f});
	// �Ϸ�
	LoadItem({ .Name = "Ȳ�����", .Note = "ȹ���ϴ� ��差�� 25% �����մϴ�.\n�ִ�ü���� 35 �����մϴ�.", 
		.Story = "�̰� �Ĵ� ���ε��� Ȳ�ݾ��� ���� ������ �踦 ���� ���̴�!", .Index = 105,
		.Grade = ItemGrade::Rare, .Synergy1 = Synergy::Antique, .Synergy2 = Synergy::Heritage,
		.ItemTexName = "GoldenIncenseBurner.png",
		.InventoryTexName = "Inventory_GoldenIncenseBurner.png",
		.HP = 35, .GoldPercent = 0.25f});

	/////////////////////////////////////////////////////////////////////// ����ũ

	// �Ϸ�
	LoadItem({ .Name = "��������", .Note = "�޴� �������� 25% �����ϰ� ��ų ��ٿ� �ӵ��� 25% �����մϴ�.", 
		.Story = "�ϴ��� ������ ������ �¸��� �̲����ٴ� �������� ����. ���߿����� ���п��ٰ� �Ѵ�.", .Index = 200,
		.Grade = ItemGrade::Unique, .Synergy1 = Synergy::Soar, .Synergy2 = Synergy::Rapidity,
		.ItemTexName = "WingArmor.png",
		.InventoryTexName = "Inventory_WingArmor.png",
		.DamageReduction = 0.25f, .SkillCoolDown = 0.25f});
	// �Ϸ�
	LoadItem({ .Name = "������ ��ö�ܰ�", .Note = "ġ��Ÿ Ȯ���� 20% �����մϴ�.", 
		.Story = "���� ������� �پ ��ö�� ����� ��� �ӿ����� �� ������ �ʴ´�.", .Index = 201,
		.Grade = ItemGrade::Unique, .Synergy1 = Synergy::Rapidity, .Synergy2 = Synergy::Chase,
		.ItemTexName = "ThiefsBlackIronDaggers.png",
		.InventoryTexName = "Inventory_ThiefsBlackIronDaggers.png",
		.CriticalPercent = 20.0f});
	// �Ϸ�
	LoadItem({ .Name = "��ɲ��� �������", .Note = "ġ��Ÿ �������� 40% �����մϴ�.", 
		.Story = "���� ���õ��� �� �Ŵ��� ��������� �ı����� ����� �� ����.", .Index = 202,
		.Grade = ItemGrade::Unique, .Synergy1 = Synergy::Strike, .Synergy2 = Synergy::Misfortune,
		.ItemTexName = "HuntersWoodenLongbow.png",
		.InventoryTexName = "Inventory_HuntersWoodenLongbow.png",
		.CriticalDamage = 0.4f});
	// �Ϸ�
	LoadItem({ .Name = "Ÿ�� ������ �κ�", .Note = "�������ݷ��� 40% �����մϴ�.", 
		.Story = "���� ���� 30���� ������ ��� �κ�", .Index = 203,
		.Grade = ItemGrade::Unique, .Synergy1 = Synergy::Wisdom, .Synergy2 = Synergy::ManaCycle,
		.ItemTexName = "DarkPriestsRobes.png",
		.InventoryTexName = "Inventory_DarkPriestsRobes.png",
		.MagicAttack = 0.4f});

	/////////////////////////////////////////////////////////////////////// ��������

	// �Ϸ�
	LoadItem({ .Name = "������ ����", .Note = "ġ��Ÿ Ȯ���� 30% �����ϰ� ġ��Ÿ �������� 70% �����մϴ�.", 
		.Story = "�� ���� �񰡷� �Ŵ��� ���� �ο��ϴ� ������ ����", .Index = 300,
		.Grade = ItemGrade::Legendary, .Synergy1 = Synergy::Strike, .Synergy2 = Synergy::Chase,
		.ItemTexName = "VeiledMask.png",
		.InventoryTexName = "Inventory_VeiledMask.png",
		.CriticalPercent = -30.0f, .CriticalDamage = 0.7f});
	// �Ϸ�
	LoadItem({ .Name = "������ ��", .Note = "��ų ��ٿ� �ӵ��� 50% �����մϴ�.", 
		.Story = "������ ������� �η縶���� ���� �����ϰ� ��ȣ�� �� �ִ�.", .Index = 301,
		.Grade = ItemGrade::Legendary, .Synergy1 = Synergy::ManaCycle, .Synergy2 = Synergy::Heritage,
		.ItemTexName = "InfinityBone.png",
		.InventoryTexName = "Inventory_InfinityBone.png",
		.SkillCoolDown = 0.5f});
	// �Ϸ�
	LoadItem({ .Name = "��� ���ܱ�", .Note = "�������ݷ��� 100% �����մϴ�. ", 
		.Story = "��°�� �ٵ� �ڽŸ��� ��Ƴ��� ���̶� �����ϴ� �ɱ�...", .Index = 302,
		.Grade = ItemGrade::Legendary, .Synergy1 = Synergy::Courage, .Synergy2 = Synergy::Misfortune,
		.ItemTexName = "HopeCutter.png",
		.InventoryTexName = "Inventory_HopeCutter.png",
		.MeleeAttack = 1.0f});
	// �Ϸ�
	LoadItem({ .Name = "���ǵ��� ����", .Note = "�������ݷ��� 100% �����մϴ�.", 
		.Story = "������ �����ٰ� �˷��� ������ ������ ����", .Index = 303,
		.Grade = ItemGrade::Legendary, .Synergy1 = Synergy::Wisdom, .Synergy2 = Synergy::Soar,
		.ItemTexName = "SylphidsWing.png",
		.InventoryTexName = "Inventory_SylphidsWing.png",
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
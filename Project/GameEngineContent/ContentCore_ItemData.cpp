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

	LoadItem({.Name = "보급형 칼레온 검", .Note = "#R물리공격력#E이 30% 증가합니다.", .Index = 0,
		.Grade = ItemGrade::Normal, .Synergy1 = Synergy::Courage, .Synergy2 = Synergy::Antique,
		.MeleeAttack = 0.3f});
	LoadItem({.Name = "보급형 칼레온 스태프", .Note = "받는 데미지가 15% 감소합니다.", .Index = 1,
		.Grade = ItemGrade::Normal, .Synergy1 = Synergy::Wisdom, .Synergy2 = Synergy::ManaCycle,
		.DamageReduction = 0.15f});
	LoadItem({.Name = "보급형 칼레온 활", .Note = "치명타 확률이 8% 증가합니다.", .Index = 2,
		.Grade = ItemGrade::Normal, .Synergy1 = Synergy::Strike, .Synergy2 = Synergy::Chase,
		.CriticalPercent = 0.08f});
	LoadItem({.Name = "빛 바랜 마석 파편", .Note = "최대 체력이 25 증가합니다.", .Index = 3,
		.Grade = ItemGrade::Normal, .Synergy1 = Synergy::Antique, .Synergy2 = Synergy::Heritage,
		.HP = 25});
	LoadItem({.Name = "식전 기도문", .Note = "스킬 쿨다운 속도가 40% 증가합니다.",.Index = 4,
		.Grade = ItemGrade::Normal, .Synergy1 = Synergy::ManaCycle, .Synergy2 = Synergy::Soar,
		.SkillCoolDown = 0.4f});
	LoadItem({.Name = "죽도", .Note = "공격속도가 20% 증가합니다.", .Index = 5,
		.Grade = ItemGrade::Normal, .Synergy1 = Synergy::Rapidity, .Synergy2 = Synergy::Misfortune,
		.AttackSpeed = 0.2f});

	LoadItem({ .Name = "고대 향로", .Note = "정수 쿨다운 속도가 65% 증가합니다.\n최대체력이 35 증가합니다.", .Index = 100,
		.Grade = ItemGrade::Rare, .Synergy1 = Synergy::Antique, .Synergy2 = Synergy::Heritage,
		.HP = 35, .QuintessenceCoolDown = 0.65f});
	LoadItem({ .Name = "뒤틀린 곡검", .Note = "#R물리공격력#E이 25% 증가합니다.\n치명타 확률이 10 % 증가합니다.", .Index = 101,
		.Grade = ItemGrade::Rare, .Synergy1 = Synergy::Misfortune, .Synergy2 = Synergy::Soar,
		.MeleeAttack = 0.25f, .CriticalPercent = 0.1f});
	LoadItem({ .Name = "수행자의 견갑", .Note = "정신집중 속도가 40% 증가하고 #R물리공격력#E이 35% 증가합니다", .Index = 102,
		.Grade = ItemGrade::Rare, .Synergy1 = Synergy::Courage, .Synergy2 = Synergy::Strike,
		.MeleeAttack = 0.35f, .CastingSpeed = 0.4f});
	LoadItem({ .Name = "수행자의 목걸이", .Note = "정신집중 속도가 40% 증가하고 #B마법공격력#E이 35% 증가합니다.", .Index = 103,
		.Grade = ItemGrade::Rare, .Synergy1 = Synergy::Wisdom, .Synergy2 = Synergy::Chase,
		.MagicAttack = 0.4f ,.CastingSpeed = 0.4f});
	LoadItem({ .Name = "태양의 검", .Note = "#R물리공격력#E이 40% 증가합니다.", .Index = 104,
		.Grade = ItemGrade::Rare, .Synergy1 = Synergy::Courage, .Synergy2 = Synergy::Rapidity,
		.MeleeAttack = 0.4f});
	LoadItem({ .Name = "황금향로", .Note = "획득하는 골드량이 25% 증가합니다.\n최대체력이 35 증가합니다.", .Index = 105,
		.Grade = ItemGrade::Rare, .Synergy1 = Synergy::Antique, .Synergy2 = Synergy::Heritage,
		.HP = 35, .GoldPercent = 0.25f});

	LoadItem({ .Name = "날개갑주", .Note = "공중에 있을 시 받는 데미지가 35% 감소하고 스킬 쿨다운 속도가 50% 증가합니다.", .Index = 200,
		.Grade = ItemGrade::Unique, .Synergy1 = Synergy::Soar, .Synergy2 = Synergy::Rapidity,
		.DamageReduction = 0.35f, .SkillCoolDown = 0.5f});
	LoadItem({ .Name = "도적의 흑철단검", .Note = "적을 공격할 때마다 2초간 치명타 확률이 2% 증가합니다.\n이 효과는 20회까지 중첩됩니다.", .Index = 201,
		.Grade = ItemGrade::Unique, .Synergy1 = Synergy::Rapidity, .Synergy2 = Synergy::Chase,
		.CriticalPercent = 0.02f});
	LoadItem({ .Name = "사냥꾼의 나무장궁", .Note = "치명타 데미지가 35% 증가합니다.", .Index = 202,
		.Grade = ItemGrade::Unique, .Synergy1 = Synergy::Strike, .Synergy2 = Synergy::Misfortune,
		.CriticalDamage = 0.35f});
	LoadItem({ .Name = "타락 성자의 로브", .Note = "#B마법공격력#E이 50% 증가합니다.", .Index = 203,
		.Grade = ItemGrade::Unique, .Synergy1 = Synergy::Wisdom, .Synergy2 = Synergy::ManaCycle,
		.MagicAttack = 0.5f});

	LoadItem({ .Name = "가려진 가면", .Note = "치명타 확률이 30% 감소하고 치명타 데미지가 70% 증가합니다.", .Index = 300,
		.Grade = ItemGrade::Legendary, .Synergy1 = Synergy::Strike, .Synergy2 = Synergy::Chase,
		.CriticalPercent = -0.3f, .CriticalDamage = 0.7f});
	LoadItem({ .Name = "무한의 뼈", .Note = "스킬 사용 시 30% 확률로 해당 스킬의 쿨타임이 초기화 됩니다.", .Index = 301,
		.Grade = ItemGrade::Legendary, .Synergy1 = Synergy::ManaCycle, .Synergy2 = Synergy::Heritage,
		.SkillCoolDown = 0.3f});
	LoadItem({ .Name = "희망 절단기", .Note = "#R물리공격력#N이 100% 증가합니다. ", .Index = 302,
		.Grade = ItemGrade::Legendary, .Synergy1 = Synergy::Courage, .Synergy2 = Synergy::Misfortune,
		.MeleeAttack = 1.0f});
	LoadItem({ .Name = "실피드의 날개", .Note = "#B마법공격력#E이 100% 증가합니다.", .Index = 303,
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
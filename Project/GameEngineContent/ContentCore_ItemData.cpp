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

	/////////////////////////////////////////////////////////////////////// 일반
	
	// 완료
	LoadItem({.Name = "보급형 칼레온 검", .Note = "물리공격력이 10% 증가합니다.", 
		.Story = "묵직한 칼레온 군 보급용 검. 성능은 의심이 들지만, 관리 된 검날은 예사롭지 않다.", .Index = 0,
		.Grade = ItemGrade::Normal, .Synergy1 = Synergy::Courage, .Synergy2 = Synergy::Antique,
		.ItemTexName = "BasicCarleonSword.png",
		.InventoryTexName = "Inventory_BasicCarleonSword.png",
		.MeleeAttack = 0.1f});
	// 완료
	LoadItem({.Name = "보급형 칼레온 스태프", .Note = "받는 데미지가 15% 감소합니다.",
		.Story = "칼레온의 마법 아카데미 수강생들에게 지급된 보급품", .Index = 1,
		.Grade = ItemGrade::Normal, .Synergy1 = Synergy::Wisdom, .Synergy2 = Synergy::ManaCycle,
		.ItemTexName = "BasicCarleonStaff.png",
		.InventoryTexName = "Inventory_BasicCarleonStaff.png",
		.DamageReduction = 0.15f});
	// 완료
	LoadItem({.Name = "보급형 칼레온 활", .Note = "치명타 확률이 10% 증가합니다.", 
		.Story = "석궁이 보급된 요즘에는 잘 사용되지 않는다.", .Index = 2,
		.Grade = ItemGrade::Normal, .Synergy1 = Synergy::Strike, .Synergy2 = Synergy::Chase,
		.ItemTexName = "BasicCarleonBow.png",
		.InventoryTexName = "Inventory_BasicCarleonBow.png",
		.CriticalPercent = 10.0f});
	// 완료
	LoadItem({.Name = "빛 바랜 마석 파편", .Note = "최대 체력이 25 증가합니다.", 
		.Story = "복수로 모든 분노가 빠져나가 텅텅 비어버린 광인을 만난 기분이다.", .Index = 3,
		.Grade = ItemGrade::Normal, .Synergy1 = Synergy::Antique, .Synergy2 = Synergy::Heritage,
		.ItemTexName = "DimLightDarkQuartz.png",
		.InventoryTexName = "Inventory_DimLightDarkQuartz.png",
		.HP = 25});
	// 완료
	LoadItem({.Name = "식전 기도문", .Note = "스킬 쿨다운 속도가 30% 증가합니다.",
		.Story = "당연히 했죠. 매일 하는데 금방 해요. 대충 한 거 아닙니다.", .Index = 4,
		.Grade = ItemGrade::Normal, .Synergy1 = Synergy::ManaCycle, .Synergy2 = Synergy::Soar,
		.ItemTexName = "PrayerBeforeMeal.png",
		.InventoryTexName = "Inventory_PrayerBeforeMeal.png",
		.SkillCoolDown = 0.3f});
	// 완료
	LoadItem({.Name = "죽도", .Note = "공격속도가 10% 증가합니다.", 
		.Story = "머리를 빠르게 때릴 수 있는 동방의 연습용 검", .Index = 5,
		.Grade = ItemGrade::Normal, .Synergy1 = Synergy::Rapidity, .Synergy2 = Synergy::Misfortune,
		.ItemTexName = "KendoStick.png",
		.InventoryTexName = "Inventory_KendoStick.png",
		.AttackSpeed = 0.1f});

	/////////////////////////////////////////////////////////////////////// 레어
	
	// 완료
	LoadItem({ .Name = "고대 향로", .Note = "정수 쿨다운 속도가 65% 증가합니다.\n최대체력이 35 증가합니다.", 
		.Story = "정수에 깃든 선조의 혼과 대화하기 위해 사용되는 향로", .Index = 100,
		.Grade = ItemGrade::Rare, .Synergy1 = Synergy::Antique, .Synergy2 = Synergy::Heritage,
		.ItemTexName = "AncientCenser.png",
		.InventoryTexName = "Inventory_AncientCenser.png",
		.HP = 35, .QuintessenceCoolDown = 0.65f});
	// 완료
	LoadItem({ .Name = "뒤틀린 곡검", .Note = "물리공격력이 20% 증가합니다.\n치명타 확률이 15% 증가합니다.", 
		.Story = "궤도를 알 수 없는 치명적인 곡검", .Index = 101,
		.Grade = ItemGrade::Rare, .Synergy1 = Synergy::Misfortune, .Synergy2 = Synergy::Soar,
		.ItemTexName = "FightersKnuckle.png",
		.InventoryTexName = "Inventory_FightersKnuckle.png",
		.MeleeAttack = 0.2f, .CriticalPercent = 15.0f});
	// 완료
	LoadItem({ .Name = "수행자의 견갑", .Note = "정신집중 속도가 40% 증가하고 물리공격력이 25% 증가합니다", 
		.Story = "명상을 방해하지 마시게나.", .Index = 102,
		.Grade = ItemGrade::Rare, .Synergy1 = Synergy::Courage, .Synergy2 = Synergy::Strike,
		.ItemTexName = "AttendantsPauldron.png",
		.InventoryTexName = "Inventory_AttendantsPauldron.png",
		.MeleeAttack = 0.25f, .CastingSpeed = 0.4f});
	// 완료
	LoadItem({ .Name = "수행자의 목걸이", .Note = "정신집중 속도가 40% 증가하고 마법공격력이 25% 증가합니다.", 
		.Story = "명상이란 게 거창한 일이 아닐세. 눈을 감고 집중해보게나.", .Index = 103,
		.Grade = ItemGrade::Rare, .Synergy1 = Synergy::Wisdom, .Synergy2 = Synergy::Chase,
		.ItemTexName = "AttendantsNecklace.png",
		.InventoryTexName = "Inventory_AttendantsNecklace.png",
		.MagicAttack = 0.25f ,.CastingSpeed = 0.4f});
	// 완료
	LoadItem({ .Name = "태양의 검", .Note = "물리공격력이 40% 증가합니다.", 
		.Story = "무언가를 그리워하는 듯한, 태양의 문양이 새겨진 검.", .Index = 104,
		.Grade = ItemGrade::Rare, .Synergy1 = Synergy::Courage, .Synergy2 = Synergy::Rapidity,
		.ItemTexName = "SwordOfSun.png",
		.InventoryTexName = "Inventory_SwordOfSun.png",
		.MeleeAttack = 0.4f});
	// 완료
	LoadItem({ .Name = "황금향로", .Note = "획득하는 골드량이 25% 증가합니다.\n최대체력이 35 증가합니다.", 
		.Story = "이걸 파는 상인들은 황금알을 낳는 거위의 배를 가른 것이다!", .Index = 105,
		.Grade = ItemGrade::Rare, .Synergy1 = Synergy::Antique, .Synergy2 = Synergy::Heritage,
		.ItemTexName = "GoldenIncenseBurner.png",
		.InventoryTexName = "Inventory_GoldenIncenseBurner.png",
		.HP = 35, .GoldPercent = 0.25f});

	/////////////////////////////////////////////////////////////////////// 유니크

	// 완료
	LoadItem({ .Name = "날개갑주", .Note = "받는 데미지가 25% 감소하고 스킬 쿨다운 속도가 25% 증가합니다.", 
		.Story = "하늘을 가르며 전투를 승리로 이끌었다는 누군가의 갑주. 공중에서는 불패였다고 한다.", .Index = 200,
		.Grade = ItemGrade::Unique, .Synergy1 = Synergy::Soar, .Synergy2 = Synergy::Rapidity,
		.ItemTexName = "WingArmor.png",
		.InventoryTexName = "Inventory_WingArmor.png",
		.DamageReduction = 0.25f, .SkillCoolDown = 0.25f});
	// 완료
	LoadItem({ .Name = "도적의 흑철단검", .Note = "치명타 확률이 20% 증가합니다.", 
		.Story = "빛의 흡수력이 뛰어난 흑철로 만들어 어둠 속에서는 잘 보이지 않는다.", .Index = 201,
		.Grade = ItemGrade::Unique, .Synergy1 = Synergy::Rapidity, .Synergy2 = Synergy::Chase,
		.ItemTexName = "ThiefsBlackIronDaggers.png",
		.InventoryTexName = "Inventory_ThiefsBlackIronDaggers.png",
		.CriticalPercent = 20.0f});
	// 완료
	LoadItem({ .Name = "사냥꾼의 나무장궁", .Note = "치명타 데미지가 40% 증가합니다.", 
		.Story = "작은 석궁들은 이 거대한 나무장궁의 파괴력을 따라올 수 없다.", .Index = 202,
		.Grade = ItemGrade::Unique, .Synergy1 = Synergy::Strike, .Synergy2 = Synergy::Misfortune,
		.ItemTexName = "HuntersWoodenLongbow.png",
		.InventoryTexName = "Inventory_HuntersWoodenLongbow.png",
		.CriticalDamage = 0.4f});
	// 완료
	LoadItem({ .Name = "타락 성자의 로브", .Note = "마법공격력이 40% 증가합니다.", 
		.Story = "빛을 등진 30인의 마력이 담긴 로브", .Index = 203,
		.Grade = ItemGrade::Unique, .Synergy1 = Synergy::Wisdom, .Synergy2 = Synergy::ManaCycle,
		.ItemTexName = "DarkPriestsRobes.png",
		.InventoryTexName = "Inventory_DarkPriestsRobes.png",
		.MagicAttack = 0.4f});

	/////////////////////////////////////////////////////////////////////// 레전더리

	// 완료
	LoadItem({ .Name = "가려진 가면", .Note = "치명타 확률이 30% 감소하고 치명타 데미지가 70% 증가합니다.", 
		.Story = "두 눈을 댓가로 거대한 힘을 부여하는 미지의 가면", .Index = 300,
		.Grade = ItemGrade::Legendary, .Synergy1 = Synergy::Strike, .Synergy2 = Synergy::Chase,
		.ItemTexName = "VeiledMask.png",
		.InventoryTexName = "Inventory_VeiledMask.png",
		.CriticalPercent = -30.0f, .CriticalDamage = 0.7f});
	// 완료
	LoadItem({ .Name = "무한의 뼈", .Note = "스킬 쿨다운 속도가 50% 증가합니다.", 
		.Story = "여기라면 마녀님의 두루마리를 정말 안전하게 보호할 수 있다.", .Index = 301,
		.Grade = ItemGrade::Legendary, .Synergy1 = Synergy::ManaCycle, .Synergy2 = Synergy::Heritage,
		.ItemTexName = "InfinityBone.png",
		.InventoryTexName = "Inventory_InfinityBone.png",
		.SkillCoolDown = 0.5f});
	// 완료
	LoadItem({ .Name = "희망 절단기", .Note = "물리공격력이 100% 증가합니다. ", 
		.Story = "어째서 다들 자신만은 살아남을 것이라 생각하는 걸까...", .Index = 302,
		.Grade = ItemGrade::Legendary, .Synergy1 = Synergy::Courage, .Synergy2 = Synergy::Misfortune,
		.ItemTexName = "HopeCutter.png",
		.InventoryTexName = "Inventory_HopeCutter.png",
		.MeleeAttack = 1.0f});
	// 완료
	LoadItem({ .Name = "실피드의 날개", .Note = "마법공격력이 100% 증가합니다.", 
		.Story = "세상을 등졌다고 알려진 요정의 찢겨진 날개", .Index = 303,
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
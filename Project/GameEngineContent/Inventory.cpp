#include "PrecompileHeader.h"
#include "Inventory.h"

SkullData Inventory::MainSkullData;
SkullData Inventory::SubSkullData;

int Inventory::Goods_Gold = 0;
int Inventory::Goods_Bone = 0;
int Inventory::Goods_ManaStone = 0;

std::vector<ItemData> Inventory::PlayerItemDatas;

float Inventory::MeleeAttack = 0.0f;
float Inventory::MagicAttack = 0.0f;

float Inventory::HP = 0.0f;
float Inventory::DamageReduction = 0.0f;

float Inventory::AttackSpeed = 0.0f;
float Inventory::MoveSpeed = 0.0f;
float Inventory::CastingSpeed = 0.0f;

float Inventory::SkillCoolDown = 0.0f;
float Inventory::SwitchCoolDown = 0.0f;
float Inventory::QuintessenceCoolDown = 0.0f;

float Inventory::CriticalPercent = 0.0f;
float Inventory::CriticalDamage = 0.0f;

float Inventory::GoldPercent = 0.0f;


int Inventory::Synergy_Courage = 0;
int Inventory::Synergy_Antique = 0;
int Inventory::Synergy_Heritage = 0;
int Inventory::Synergy_Misfortune = 0;
int Inventory::Synergy_Rapidity = 0;
int Inventory::Synergy_Soar = 0;
int Inventory::Synergy_Strike = 0;
int Inventory::Synergy_Wisdom = 0;
int Inventory::Synergy_Chase = 0;
int Inventory::Synergy_ManaCycle = 0;

int Inventory::GetSynergyCount(Synergy _Synergy)
{
	switch (_Synergy)
	{
	case Synergy::Courage:
		return Synergy_Courage;
	case Synergy::Antique:
		return Synergy_Antique;
	case Synergy::Heritage:
		return Synergy_Heritage;
	case Synergy::Misfortune:
		return Synergy_Misfortune;
	case Synergy::Rapidity:
		return Synergy_Rapidity;
	case Synergy::Soar:
		return Synergy_Soar;
	case Synergy::Strike:
		return Synergy_Strike;
	case Synergy::Wisdom:
		return Synergy_Wisdom;
	case Synergy::Chase:
		return Synergy_Chase;
	case Synergy::ManaCycle:
		return Synergy_ManaCycle;
	}

	return 0;
}

Inventory::Inventory()
{
}

Inventory::~Inventory()
{
}

void Inventory::SwapSkull()
{
	SkullData TempSkullData = MainSkullData; 
	MainSkullData = SubSkullData;
	SubSkullData = TempSkullData;
}

void Inventory::AddGoods_Gold(int _Gold)
{
	if (0 < _Gold)
	{
		_Gold += static_cast<int>(_Gold * GoldPercent);
	}

	Goods_Gold += _Gold;
}

void Inventory::AddGoods_Bone(int _Bone)
{
	Goods_Bone += _Bone;
}

void Inventory::AddGoods_ManaStone(int _ManaStone)
{
	Goods_ManaStone += _ManaStone;
}

int Inventory::GetGoodsCount_Gold()
{
	return Goods_Gold;
}

int Inventory::GetGoodsCount_Bone()
{
	return Goods_Bone;
}

int Inventory::GetGoodsCount_ManaStone()
{
	return Goods_ManaStone;
}

void Inventory::GoodsReset()
{
	Goods_Gold = 0;
	Goods_Bone = 0;
}

void Inventory::SetMainSkull(SkullData _SkullData)
{
	MainSkullData = _SkullData;
}

void Inventory::SetSubSkull(SkullData _SkullData)
{
	SubSkullData = _SkullData;
}

void Inventory::ResetSkull()
{
	MainSkullData = ContentDatabase<SkullData, SkullGrade>::GetData(0);
	SubSkullData.Reset();
}

const SkullData& Inventory::GetMainSkull()
{
	return MainSkullData;
}

const SkullData& Inventory::GetSubSkull()
{
	return SubSkullData;
}


void Inventory::ItemReset()
{
	PlayerItemDatas.clear();
	PlayerItemDatas.reserve(9);
	CalItemState();
}

void Inventory::InsertItem(const ItemData& _Data)
{
	PlayerItemDatas.push_back(_Data);
	CalItemState();
}

ItemData Inventory::PopItem(size_t _Index)
{
	if (PlayerItemDatas.size() <= _Index)
	{
		MsgAssert_Rtti<Inventory>(" - 아이템 최대 개수를 초과해 아이템을 인벤토리에 넣으려 했습니다");
		return ItemData();
	}

	ItemData ReturnItem = PlayerItemDatas[_Index];
	PlayerItemDatas.erase(PlayerItemDatas.begin() + _Index);
	CalItemState();

	return ReturnItem;
}

size_t Inventory::GetItemCount()
{
	return PlayerItemDatas.size();
}

size_t Inventory::GetItemIndex(size_t _Index)
{
	return PlayerItemDatas[_Index].Index;
}

void Inventory::AddSynergy(Synergy _Synergy)
{
	switch (_Synergy)
	{
	case Synergy::Courage:
		++Synergy_Courage;
		break;
	case Synergy::Antique:
		++Synergy_Antique;
		break;
	case Synergy::Heritage:
		++Synergy_Heritage;
		break;
	case Synergy::Misfortune:
		++Synergy_Misfortune;
		break;
	case Synergy::Rapidity:
		++Synergy_Rapidity;
		break;
	case Synergy::Soar:
		++Synergy_Soar;
		break;
	case Synergy::Strike:
		++Synergy_Strike;
		break;
	case Synergy::Wisdom:
		++Synergy_Wisdom;
		break;
	case Synergy::Chase:
		++Synergy_Chase;
		break;
	case Synergy::ManaCycle:
		++Synergy_ManaCycle;
		break;
	}
}

void Inventory::CalItemState()
{
	MeleeAttack = 0.0f;
	MagicAttack = 0.0f;

	HP = 0.0f;
	DamageReduction = 0.0f;

	AttackSpeed = 0.0f;
	MoveSpeed = 0.0f;
	CastingSpeed = 0.0f;

	SkillCoolDown = 0.0f;
	SwitchCoolDown = 0.0f;
	QuintessenceCoolDown = 0.0f;

	CriticalPercent = 0.0f;
	CriticalDamage = 0.0f;

	GoldPercent = 0.0f;

	Synergy_Courage = 0;
	Synergy_Antique = 0;
	Synergy_Heritage = 0;
	Synergy_Misfortune = 0;
	Synergy_Rapidity = 0;
	Synergy_Soar = 0;
	Synergy_Strike = 0;
	Synergy_Wisdom = 0;
	Synergy_Chase = 0;
	Synergy_ManaCycle = 0;

	for (size_t i = 0; i < PlayerItemDatas.size(); i++)
	{
		MeleeAttack += PlayerItemDatas[i].MeleeAttack;
		MagicAttack += PlayerItemDatas[i].MagicAttack;

		HP += PlayerItemDatas[i].HP;
		DamageReduction += (1.0f - DamageReduction) * PlayerItemDatas[i].DamageReduction;

		AttackSpeed += PlayerItemDatas[i].AttackSpeed;
		MoveSpeed += PlayerItemDatas[i].MoveSpeed;
		CastingSpeed += PlayerItemDatas[i].CastingSpeed;

		SkillCoolDown += PlayerItemDatas[i].SkillCoolDown;
		SwitchCoolDown += PlayerItemDatas[i].SwitchCoolDown;
		QuintessenceCoolDown += PlayerItemDatas[i].QuintessenceCoolDown;

		CriticalPercent += PlayerItemDatas[i].CriticalPercent;
		CriticalDamage += PlayerItemDatas[i].CriticalDamage;

		AddSynergy(PlayerItemDatas[i].Synergy1);
		AddSynergy(PlayerItemDatas[i].Synergy2);
	}


	// 강타 시너지 효과
	if (2 <= Synergy_Strike)
	{
		CriticalDamage += 0.2f;
	}
	if (4 <= Synergy_Strike)
	{
		CriticalDamage += 0.3f;
	}

	// 골동품 시너지 효과
	if (2 <= Synergy_Antique)
	{
		HP += 35;
	}

	// 마나순환 시너지 효과
	if (2 <= Synergy_ManaCycle)
	{
		SkillCoolDown += 0.5f;
	}

	// 불운 시너지 효과
	if (2 <= Synergy_Misfortune)
	{
		CriticalPercent += 0.15f;
	}
	if (4 <= Synergy_Misfortune)
	{
		CriticalPercent += 0.15f;
	}

	// 용기 시너지 효과
	if (2 <= Synergy_Courage)
	{
		MeleeAttack += 0.2f;
	}
	if (4 <= Synergy_Courage)
	{
		MeleeAttack += 0.3f;
	}

	//지혜 시너지 효과
	if (2 <= Synergy_Wisdom)
	{
		MagicAttack += 0.2f;
	}
	if (4 <= Synergy_Wisdom)
	{
		MagicAttack += 0.3f;
	}

	// 신속 시너지 효과
	if (2 <= Synergy_Rapidity)
	{
		AttackSpeed += 0.15f;
	}
	if (4 <= Synergy_Rapidity)
	{
		AttackSpeed += 0.15f;
	}
}
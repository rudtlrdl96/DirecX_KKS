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

void Inventory::CalItemState()
{
	MeleeAttack = 0.0f;
	MagicAttack = 0.0f;

	HP = 0.0f;
	DamageReduction = 0.0f;

	AttackSpeed = 0.0f;
	MoveSpeed = 0.0f;
	CastingSpeed = 0.0f;

	SkillCoolDown = 1.0f;
	SwitchCoolDown = 0.0f;
	QuintessenceCoolDown = 0.0f;

	CriticalPercent = 0.0f;
	CriticalDamage = 0.0f;

	GoldPercent = 0.0f;

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
	}
}
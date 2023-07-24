#pragma once
#include "PlayerBaseSkull.h"
#include "ItemData.h"

class Inventory
{
public:
	static void SetMainSkull(SkullData _SkullData);
	static void SetSubSkull(SkullData _SkullData);

	static void ResetSkull();

	static const SkullData& GetMainSkull();
	static const SkullData& GetSubSkull();

	static void SwapSkull();

	static void AddGoods_Gold(int _Gold);
	static void AddGoods_Bone(int _Bone);
	static void AddGoods_ManaStone(int _ManaStone);

	static int GetGoodsCount_Gold();
	static int GetGoodsCount_Bone();
	static int GetGoodsCount_ManaStone();

	static void GoodsReset();

	// Item
	static void ItemReset();
	static void InsertItem(const ItemData& _Data);
	static ItemData PopItem(size_t _Index);

	static size_t GetItemCount();
	static size_t GetItemIndex(size_t _Index);


	static float GetMaxHP()
	{
		return HP;
	}

	static float GetMeleeAttack()
	{
		return 1.0f + MeleeAttack;
	}

	static float GetMagicAttack()
	{
		return 1.0f + MagicAttack;
	}

	static float GetAttackSpeed()
	{
		return 1.0f + AttackSpeed;
	}

	static float GetMoveSpeed()
	{
		return 1.0f + MoveSpeed;
	}	
	static float GetCastingSpeed()
	{
		return 1.0f + CastingSpeed;
	}

	static float GetSkillCoolDown()
	{
		return 1.0f + SkillCoolDown;
	}

	static float GetSwitchCoolDown()
	{
		return 1.0f + SwitchCoolDown;
	}

	static float GetQuintessenceCoolDown()
	{
		return 1.0f + QuintessenceCoolDown;
	}

	static float GetDamageReduction()
	{
		return 1.0f - DamageReduction;
	}

	static float GetCriPer()
	{
		return CriticalPercent;
	}
	
	static float GetCriDamage()
	{
		return CriticalDamage;
	}

	static int GetSynergyCount(Synergy _Synergy);

protected:
	
private:
	static SkullData MainSkullData;
	static SkullData SubSkullData;

	static int Goods_Gold;
	static int Goods_Bone;
	static int Goods_ManaStone;

	static std::vector<ItemData> PlayerItemDatas;

	// Item State

	static float MeleeAttack;
	static float MagicAttack;

	static float HP;
	static float DamageReduction;

	static float AttackSpeed;
	static float MoveSpeed;
	static float CastingSpeed;

	static float SkillCoolDown;
	static float SwitchCoolDown;
	static float QuintessenceCoolDown;

	static float CriticalPercent;
	static float CriticalDamage;

	static float GoldPercent;

	static int Synergy_Courage;
	static int Synergy_Antique;
	static int Synergy_Heritage;
	static int Synergy_Misfortune;
	static int Synergy_Rapidity;
	static int Synergy_Soar;
	static int Synergy_Strike;
	static int Synergy_Wisdom;
	static int Synergy_Chase;
	static int Synergy_ManaCycle;

	static void CalItemState();
	static void AddSynergy(Synergy _Synergy);

	Inventory();
	~Inventory();

	Inventory(const Inventory& _Other) = delete;
	Inventory(Inventory&& _Other) noexcept = delete;
	Inventory& operator=(const Inventory& _Other) = delete;
	Inventory& operator=(Inventory&& _Other) noexcept = delete;	
};


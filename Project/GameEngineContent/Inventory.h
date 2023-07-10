#pragma once
#include "PlayerBaseSkull.h"

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

	static int GetGoodsCount_Gold();
	static int GetGoodsCount_Bone();

protected:
	
private:
	static SkullData MainSkullData;
	static SkullData SubSkullData;

	static int Goods_Gold;
	static int Goods_Bone;

	Inventory();
	~Inventory();

	Inventory(const Inventory& _Other) = delete;
	Inventory(Inventory&& _Other) noexcept = delete;
	Inventory& operator=(const Inventory& _Other) = delete;
	Inventory& operator=(Inventory&& _Other) noexcept = delete;
};


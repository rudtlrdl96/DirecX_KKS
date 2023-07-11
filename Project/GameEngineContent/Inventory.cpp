#include "PrecompileHeader.h"
#include "Inventory.h"

SkullData Inventory::MainSkullData;
SkullData Inventory::SubSkullData;

int Inventory::Goods_Gold = 0;
int Inventory::Goods_Bone = 0;
int Inventory::Goods_ManaStone = 0;

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

	//SubSkullData = ContentDatabase<SkullData, SkullGrade>::GetData(1); //�������_�븻
	
	//SubSkullData = ContentDatabase<SkullData, SkullGrade>::GetData(100); //�������_����
	//SubSkullData = ContentDatabase<SkullData, SkullGrade>::GetData(200); //�������_����ũ
	//SubSkullData = ContentDatabase<SkullData, SkullGrade>::GetData(203); //��� ����
	 
	//SubSkullData = ContentDatabase<SkullData, SkullGrade>::GetData(300); //�������_��������

	//SubSkullData = ContentDatabase<SkullData, SkullGrade>::GetData(101); //�̳�Ÿ�츣��_����
	//SubSkullData = ContentDatabase<SkullData, SkullGrade>::GetData(201); //�̳�Ÿ�츣��_����ũ
	//SubSkullData = ContentDatabase<SkullData, SkullGrade>::GetData(301); //�̳�Ÿ�츣��_��������

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

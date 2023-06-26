#include "PrecompileHeader.h"
#include "Inventory.h"

SkullData Inventory::MainSkullData;
SkullData Inventory::SubSkullData;

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
	SubSkullData = ContentDatabase<SkullData, SkullGrade>::GetData(203); //경비 대장
	//SubSkullData = ContentDatabase<SkullData, SkullGrade>::GetData(1); //웨어울프_노말

	//SubSkullData.Reset();
}

const SkullData& Inventory::GetMainSkull()
{
	return MainSkullData;
}

const SkullData& Inventory::GetSubSkull()
{
	return SubSkullData;
}

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

const SkullData& Inventory::GetMainSkull()
{
	return MainSkullData;
}

const SkullData& Inventory::GetSubSkull()
{
	return SubSkullData;
}

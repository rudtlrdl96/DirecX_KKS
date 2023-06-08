#include "PrecompileHeader.h"
#include "BrokenObject.h"


void BrokenData::SaveBin(GameEngineSerializer& _SaveSerializer)
{
}

void BrokenData::LoadBin(GameEngineSerializer& _LoadSerializer)
{
}

void BrokenData::ShowGUI()
{

}

void BOjectMetaData::SaveBin(GameEngineSerializer& _SaveSerializer)
{
}

void BOjectMetaData::LoadBin(GameEngineSerializer& _LoadSerializer)
{
}

void BOjectMetaData::ShowGUI()
{

}

BrokenObject::BrokenObject()
{
}

BrokenObject::~BrokenObject()
{
}

void BrokenObject::SaveBin(GameEngineSerializer& _SaveSerializer)
{
	Data.SaveBin(_SaveSerializer);
}

BOjectMetaData BrokenObject::LoadBin(GameEngineSerializer& _LoadSerializer)
{
	BOjectMetaData LoadData;
	LoadData.LoadBin(_LoadSerializer);
	return LoadData;
}

void BrokenObject::ShowGUI()
{
	Data.ShowGUI();
}

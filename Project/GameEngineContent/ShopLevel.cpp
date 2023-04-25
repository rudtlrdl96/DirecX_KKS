#include "PrecompileHeader.h"
#include "ShopLevel.h"

ShopLevel::ShopLevel()
{
}

ShopLevel::~ShopLevel()
{
}

void ShopLevel::Start()
{
	BattleLevel::Start();
}

void ShopLevel::Update(float _DeltaTime)
{
	BattleLevel::Update(_DeltaTime);
}

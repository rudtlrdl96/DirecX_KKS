#include "PrecompileHeader.h"
#include "CastleLevel.h"

CastleLevel::CastleLevel()
{
}

CastleLevel::~CastleLevel()
{
}

void CastleLevel::Start()
{
	BattleLevel::Start();
}

void CastleLevel::Update(float _DeltaTime)
{
	BattleLevel::Update(_DeltaTime);
}

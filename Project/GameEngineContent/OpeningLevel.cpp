#include "PrecompileHeader.h"
#include "OpeningLevel.h"
#include "MultiBackground.h"

OpeningLevel::OpeningLevel()
{
}

OpeningLevel::~OpeningLevel()
{
}

void OpeningLevel::Start()
{
	BattleLevel::Start();
}

void OpeningLevel::Update(float _DeltaTime)
{
	BattleLevel::Update(_DeltaTime);
}

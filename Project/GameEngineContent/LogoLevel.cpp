#include "PrecompileHeader.h"
#include "LogoLevel.h"
#include <GameEngineBase/GameEngineMath.h>
#include <GameEngineCore/GameEngineCamera.h>

LogoLevel::LogoLevel()
{
}

LogoLevel::~LogoLevel()
{
}

void LogoLevel::Start()
{
	UILevel::Start();
}

void LogoLevel::Update(float _DeltaTime)
{
	UILevel::Update(_DeltaTime);
}

#include "PrecompileHeader.h"
#include "BaseDebugLevel.h"
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineCamera.h>

BaseDebugLevel::BaseDebugLevel()
{
}

BaseDebugLevel::~BaseDebugLevel()
{
}

void BaseDebugLevel::Update(float _DeltaTime)
{
	GameEngineLevel::Update(_DeltaTime);
}

#include "PrecompileHeader.h"
#include "LogoLevel.h"
#include <GameEngineBase/GameEngineMath.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/GameEngineCamera.h>
#include "StudyActor.h"

LogoLevel::LogoLevel()
{
}

LogoLevel::~LogoLevel()
{
}

void LogoLevel::Start()
{
	CreateActor<StudyActor>();
}

void LogoLevel::Update(float _DeltaTime)
{
	GameEngineLevel::Update(_DeltaTime);
}

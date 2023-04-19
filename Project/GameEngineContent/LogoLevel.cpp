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
	GetMainCamera()->GetTransform()->SetWorldPosition(float4(0, 0, -1000));
	GetMainCamera()->SetProjectionType(CameraType::Perspective);
	CreateActor<StudyActor>();
}

void LogoLevel::Update(float _DeltaTime)
{
	GameEngineLevel::Update(_DeltaTime);
}

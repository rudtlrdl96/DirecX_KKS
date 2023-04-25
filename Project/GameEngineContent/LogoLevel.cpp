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
	ContentLevel::Start();
	GetMainCamera()->GetTransform()->SetWorldPosition(float4(0, 0, -1000));
	GetMainCamera()->SetProjectionType(CameraType::Perspective);
}

void LogoLevel::Update(float _DeltaTime)
{
	ContentLevel::Update(_DeltaTime);
}

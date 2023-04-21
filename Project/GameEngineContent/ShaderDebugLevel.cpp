#include "PrecompileHeader.h"
#include "ShaderDebugLevel.h"

// Actors
#include "DebugBoxActor.h"

ShaderDebugLevel::ShaderDebugLevel()
{
}

ShaderDebugLevel::~ShaderDebugLevel()
{
}

void ShaderDebugLevel::Start()
{
	CreateActor<DebugBoxActor>();
	GetMainCamera()->SetProjectionType(CameraType::Perspective);
	GetMainCamera()->GetTransform()->SetWorldPosition(float4(0, 0, -1000, 1));
}

void ShaderDebugLevel::Update(float _DeltaTime)
{
	BaseDebugLevel::Update(_DeltaTime);
}

#include "PrecompileHeader.h"
#include "DebugBoxActor.h"
#include <GameEngineCore/GameEngineRenderingPipeLine.h>

DebugBoxActor::DebugBoxActor()
{
}

DebugBoxActor::~DebugBoxActor()
{
}

void DebugBoxActor::Start()
{
	BoxRender = CreateComponent<GameEngineRenderer>();
	BoxRender->SetPipeLine("BoxLight");
	BoxRender->GetShaderResHelper().SetTexture("DiffuseTex", "DebugBoxTexture.png");
	BoxRender->GetTransform()->SetLocalScale(float4(300, 300, 300, 1));
}

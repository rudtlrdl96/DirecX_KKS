#include "BaseContentActor.h"
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEnginePlatform/GameEngineInput.h>

BaseContentActor::BaseContentActor()
{
}

BaseContentActor::~BaseContentActor()
{
}

void BaseContentActor::Start()
{
	//RenderA = CreateComponent<GameEngineRenderer>();
	RenderB = CreateComponent<GameEngineRenderer>();
	//RenderC = CreateComponent<GameEngineRenderer>();

	//RenderA->GetTransform()->SetLocalPosition(float4(-200, 0, 0));
	RenderB->GetTransform()->SetLocalPosition(float4::Zero);
	//RenderC->GetTransform()->SetLocalPosition(float4(200, 0, 0));

	RenderB->GetTransform()->DebugOn();
}

void BaseContentActor::Update(float _DeltaTime)
{

	static const float RotSpeed = 180.0f;

	if(true == GameEngineInput::IsPress("ActorRotX+"))
	{
		GetTransform()->AddLocalRotation(float4(1.0f * _DeltaTime * RotSpeed, 0, 0));
	}
	if(true == GameEngineInput::IsPress("ActorRotY-"))
	{
		GetTransform()->AddLocalRotation(float4(0.0f, -1.0f * _DeltaTime * RotSpeed, 0));
	}
	if(true == GameEngineInput::IsPress("ActorRotX-"))
	{
		GetTransform()->AddLocalRotation(float4(-1.0f * _DeltaTime * RotSpeed, 0, 0));
	}
	if(true == GameEngineInput::IsPress("ActorRotY+"))
	{
		GetTransform()->AddLocalRotation(float4(0.0f, 1.0f * _DeltaTime * RotSpeed, 0));
	}
	if(true == GameEngineInput::IsPress("ActorRotZ-"))
	{
		GetTransform()->AddLocalRotation(float4(0.0f, 0.0f, -1.0f * _DeltaTime * RotSpeed));
	}
	if(true == GameEngineInput::IsPress("ActorRotZ+"))
	{
		GetTransform()->AddLocalRotation(float4(0.0f, 0.0f, 1.0f * _DeltaTime * RotSpeed));
	}

	RenderB->GetTransform()->SetWorldRotation(float4(60, 50, 40));
}

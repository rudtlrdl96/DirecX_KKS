#include "PrecompileHeader.h"
#include "DebugTrailActor.h"
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineLevel.h>
#include "CaptureTrail.h"

DebugTrailActor::DebugTrailActor()
{
}

DebugTrailActor::~DebugTrailActor()
{
}

void DebugTrailActor::Start()
{
	if(false == GameEngineInput::IsKey("TrailMoveY+"))
	{
		GameEngineInput::CreateKey("TrailMoveY+", VK_UP);
		GameEngineInput::CreateKey("TrailMoveY-", VK_DOWN);
		GameEngineInput::CreateKey("TrailMoveX-", VK_LEFT);
		GameEngineInput::CreateKey("TrailMoveX+", VK_RIGHT);
	}

	GetTransform()->SetLocalScale(float4::One);

	MainRender = CreateComponent<GameEngineSpriteRenderer>();
	std::shared_ptr<GameEngineTexture> FindTex = GameEngineTexture::Find("Opening_Object (57).png");
	float4 Size = float4(static_cast<float>(FindTex->GetWidth()), static_cast<float>(FindTex->GetHeight()), 1.0f);
	MainRender->SetTexture("Opening_Object (57).png");
	MainRender->GetTransform()->SetLocalScale(Size);

	Trail = GetLevel()->CreateActor<CaptureTrail>();
	Trail->GetTransform()->SetLocalScale(float4::One);
	Trail->GetTransform()->SetParent(GetTransform());
	Trail->GetTransform()->SetLocalPosition(float4(0, 0, 10));
	Trail->SetTime(0.75f);
}

void DebugTrailActor::Update(float _DeltaTime)
{	
	if (0.15f < GetLiveTime())
	{	
		Trail->PlayTrail("Opening_Object (57).png", float4(0.0f, 0.0f, 1.0f, 1.0f), false);
		ResetLiveTime();
	}

	float Speed = _DeltaTime * 400.0f;

	if (true == GameEngineInput::IsPress("TrailMoveY+"))
	{
		GetTransform()->AddLocalPosition(float4::Up * Speed);
	}
	else if(true == GameEngineInput::IsPress("TrailMoveY-"))
	{
		GetTransform()->AddLocalPosition(float4::Down * Speed);
	}
	
	if(true == GameEngineInput::IsPress("TrailMoveX+"))
	{
		GetTransform()->AddLocalPosition(float4::Right * Speed);
	}
	else if(true == GameEngineInput::IsPress("TrailMoveX-"))
	{
		GetTransform()->AddLocalPosition(float4::Left * Speed);
	}
}

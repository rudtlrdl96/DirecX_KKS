#include "PrecompileHeader.h"
#include "CollisionDebugRender.h"

CollisionDebugRender::CollisionDebugRender()
{
}

CollisionDebugRender::~CollisionDebugRender()
{
}

void CollisionDebugRender::SetTargetCollision(std::shared_ptr<GameEngineCollision> _TargetCollision)
{
	TargetCollision = _TargetCollision;
}

void CollisionDebugRender::Start()
{
	DebugRender = CreateComponent<GameEngineSpriteRenderer>();
	DebugRender->SetPipeLine("2DTexture_ColorLight");
	DebugRender->SetAtlasConstantBuffer();
	DebugRender->GetShaderResHelper().SetConstantBufferLink("ColorBuffer", DebugBuffer);
	DebugRender->SetTexture("BoxCol.png");
}

void CollisionDebugRender::Update(float _DeltaTime)
{
	std::shared_ptr<GameEngineCollision> LockPtr = TargetCollision.lock();

	if (nullptr == LockPtr)
	{
		Death();
		return;
	}

	if (true == LockPtr->GetActor()->IsDeath())
	{
		Death();
	}

	if (false == LockPtr->GetActor()->IsDebug())
	{
		Death();
		return;
	}

	if (nullptr == DebugRender)
	{
		MsgAssert_Rtti<CollisionDebugRender>(" - DebugRender가 생성되지 않았습니다.");
		return;
	}

	GameEngineTransform* CollisionTrans = LockPtr->GetTransform();

	if (nullptr != UpdateColorCallback)
	{
		Color = UpdateColorCallback();
	}

	switch (Color)
	{
	case CollisionDebugRender::DebugColor::Green:
		DebugBuffer.Color = float4(-1.0f, 1.0f, -1.0f, 1.0f);
		break;
	case CollisionDebugRender::DebugColor::Blue:
		DebugBuffer.Color = float4(-1.0f, -1.0f, 1.0f, 1.0f);
		break;
	case CollisionDebugRender::DebugColor::Red:
		DebugBuffer.Color = float4(1.0f, -1.0f, -1.0f, 1.0f);
		break;
	default:
		break;
	}

	DebugRender->GetTransform()->SetWorldScale(CollisionTrans->GetWorldScale());
}

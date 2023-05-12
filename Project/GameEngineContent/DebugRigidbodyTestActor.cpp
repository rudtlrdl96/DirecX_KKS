#include "PrecompileHeader.h"
#include "DebugRigidbodyTestActor.h"
#include <GameEnginePlatform/GameEngineInput.h>
#include "Rigidbody2D.h"

DebugRigidbodyTestActor::DebugRigidbodyTestActor()
{
}

DebugRigidbodyTestActor::~DebugRigidbodyTestActor()
{
}

void DebugRigidbodyTestActor::Start()
{
	if (false == GameEngineInput::IsKey("DebugForce_Up"))
	{
		GameEngineInput::CreateKey("DebugForce_Up", VK_UP);
		GameEngineInput::CreateKey("DebugForce_Down", VK_DOWN);
		GameEngineInput::CreateKey("DebugForce_Left", VK_LEFT);
		GameEngineInput::CreateKey("DebugForce_Right", VK_RIGHT);

		GameEngineInput::CreateKey("DebugForce_Jump", VK_SPACE);
	}

	RigdPtr.SetMass(1.0f);
	RigdPtr.SetMaxSpeed(400.0f);
	RigdPtr.SetFricCoeff(100.0f);
	RigdPtr.SetActiveGravity(true);
	RigdPtr.SetGravity(-800);


	TestRender = CreateComponent<GameEngineSpriteRenderer>();
	TestRender->GetTransform()->SetLocalScale(float4(50, 50, 1));
}

void DebugRigidbodyTestActor::Update(float _DeltaTime)
{
	if (false == IsMove)
	{
		return;
	}

	if (true == GameEngineInput::IsPress("DebugForce_Up"))
	{
		RigdPtr.AddForce(float4::Up * 400.0f);
	}
	if (true == GameEngineInput::IsPress("DebugForce_Down"))
	{
		RigdPtr.AddForce(float4::Down * 400.0f);
	}
	if (true == GameEngineInput::IsPress("DebugForce_Left"))
	{
		RigdPtr.AddForce(float4::Left * 400.0f);
	}
	if (true == GameEngineInput::IsPress("DebugForce_Right"))
	{
		RigdPtr.AddForce(float4::Right * 400.0f);
	}

	if (true == GameEngineInput::IsDown("DebugForce_Jump"))
	{
		RigdPtr.AddVelocity(float4(0, 800));
	}

	RigdPtr.UpdateForce(_DeltaTime);
	GetTransform()->AddLocalPosition(RigdPtr.GetVelocity() * _DeltaTime);
}

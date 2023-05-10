#include "PrecompileHeader.h"
#include "PlayerBaseSkull.h"

#include <GameEnginePlatform/GameEngineInput.h>

void PlayerBaseSkull::Idle_Enter()
{
	JumpCount = 1;
}

void PlayerBaseSkull::Idle_Update(float _DeltaTime)
{
	if (false == IsGround())
	{
		PlayerFSM.ChangeState("Fall");
		return;
	}

	if (true == GameEngineInput::IsDown("PlayerMove_Dash"))
	{
		PlayerFSM.ChangeState("Dash");
	}
	else if (true == GameEngineInput::IsDown("PlayerMove_Attack"))
	{
		PlayerFSM.ChangeState("Attack");
	}
	else if (true == GameEngineInput::IsDown("PlayerMove_Jump"))
	{
		JumpDir = float4::Up * JumpPower;
		PlayerFSM.ChangeState("Jump");
	}
	else if (true == GameEngineInput::IsDown("PlayerMove_Skill_A"))
	{
		// CoolTime Check
		PlayerFSM.ChangeState("Skill_A");
	}
	else if (true == GameEngineInput::IsDown("PlayerMove_Skill_B"))
	{
		// CoolTime Check
		PlayerFSM.ChangeState("Skill_B");
	}
	else if (true == GameEngineInput::IsDown("PlayerMove_Left"))
	{
		ViewDir = ActorWalkDir::Left;
		PlayerFSM.ChangeState("Walk");
	}
	else if (true == GameEngineInput::IsDown("PlayerMove_Right"))
	{
		ViewDir = ActorWalkDir::Right;
		PlayerFSM.ChangeState("Walk");
	}
}

void PlayerBaseSkull::Idle_End()
{
	JumpCount = 1;
}

void PlayerBaseSkull::Jump_Update(float _DeltaTime)
{
	// 충돌 체크 들어가야함
	GetTransform()->AddLocalPosition(JumpDir * _DeltaTime);

	JumpDir.y -= _DeltaTime * ContentConst::Gravity_f;

	if (true == GameEngineInput::IsDown("PlayerMove_Left"))
	{
		ViewDir = ActorWalkDir::Left;
		GetTransform()->AddLocalPosition(float4::Left  * WalkSpeed * _DeltaTime);
	}
	else if (true == GameEngineInput::IsDown("PlayerMove_Right"))
	{
		ViewDir = ActorWalkDir::Right;
		GetTransform()->AddLocalPosition(float4::Right * WalkSpeed * _DeltaTime);
	}

	if (JumpDir.y < 0)
	{
		PlayerFSM.ChangeState("Fall");
	}
}
#include "PrecompileHeader.h"
#include "PlayerBaseSkull.h"

#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineCollision.h>

void PlayerBaseSkull::Idle_Enter()
{
	SkullRenderer->ChangeAnimation("Idle");
	JumpDir = float4::Zero;
	CanJump = true;
	DoubleJump = true;
}

void PlayerBaseSkull::Idle_Update(float _DeltaTime)
{
	if (false == IsGround())
	{
		PlayerFSM.ChangeState("Fall");
		return;
	}

	if (true == CanDash && true == GameEngineInput::IsDown("PlayerMove_Dash"))
	{
		PlayerFSM.ChangeState("Dash");
	}
	else if (true == GameEngineInput::IsDown("PlayerMove_Attack"))
	{
		//PlayerFSM.ChangeState("Attack");
	}
	else if (true == GameEngineInput::IsDown("PlayerMove_Jump"))
	{
		PlayerFSM.ChangeState("Jump");
	}
	else if (true == GameEngineInput::IsDown("PlayerMove_Skill_A"))
	{
		// CoolTime Check
		//PlayerFSM.ChangeState("Skill_A");
	}
	else if (true == GameEngineInput::IsDown("PlayerMove_Skill_B"))
	{
		// CoolTime Check
		//PlayerFSM.ChangeState("Skill_B");
	}
	else if (true == GameEngineInput::IsDown("PlayerMove_Left"))
	{
		ViewDir = ActorViewDir::Left;
		PlayerFSM.ChangeState("Walk");
	}
	else if (true == GameEngineInput::IsDown("PlayerMove_Right"))
	{
		ViewDir = ActorViewDir::Right;
		PlayerFSM.ChangeState("Walk");
	}
}

void PlayerBaseSkull::Idle_End()
{
}

void PlayerBaseSkull::Jump_Enter()
{
	CanJump = false;
	JumpDir = float4::Up * JumpPower;
	SkullRenderer->ChangeAnimation("Jump");
}

void PlayerBaseSkull::Jump_Update(float _DeltaTime)
{
	// 충돌 체크 들어가야함
	JumpDir.y += ContentConst::Gravity_f * _DeltaTime;
	GetTransform()->AddLocalPosition(JumpDir * _DeltaTime);


	if (true == CanDash && true == GameEngineInput::IsDown("PlayerMove_Dash"))
	{
		PlayerFSM.ChangeState("Dash");
		return;
	}

	if (true == DoubleJump && true == GameEngineInput::IsDown("PlayerMove_Jump"))
	{
		JumpDir = float4::Up * JumpPower;
		DoubleJump = false;
	}

	if (true == GameEngineInput::IsPress("PlayerMove_Left"))
	{
		ViewDir = ActorViewDir::Left;

		float4 MoveDir = float4::Left * WalkSpeed * _DeltaTime;
		GetTransform()->AddLocalPosition(MoveDir);
	}
	else if (true == GameEngineInput::IsPress("PlayerMove_Right"))
	{
		ViewDir = ActorViewDir::Right;

		float4 MoveDir = float4::Right * WalkSpeed * _DeltaTime;
		GetTransform()->AddLocalPosition(MoveDir);
	}

	if (JumpDir.y < 0)
	{
		PlayerFSM.ChangeState("Fall");
	}
}

void PlayerBaseSkull::Walk_Enter() 
{
	SkullRenderer->ChangeAnimation("Walk");
	JumpDir = float4::Zero;
	CanJump = true;
	DoubleJump = true;
}

void PlayerBaseSkull::Walk_Update(float _DeltaTime) 
{
	if (false == IsGround())
	{
		PlayerFSM.ChangeState("Fall");
		return;
	}

	if (true == GameEngineInput::IsDown("PlayerMove_Jump"))
	{
		PlayerFSM.ChangeState("Jump");
		return;
	}

	if (true == CanDash && true == GameEngineInput::IsDown("PlayerMove_Dash"))
	{
		PlayerFSM.ChangeState("Dash");
		return;
	}

	if (true == GameEngineInput::IsPress("PlayerMove_Left"))
	{
		ViewDir = ActorViewDir::Left;

		float4 MoveDir = float4::Left * WalkSpeed * _DeltaTime;
		GetTransform()->AddLocalPosition(MoveDir);
	}
	else if (true == GameEngineInput::IsPress("PlayerMove_Right"))
	{
		ViewDir = ActorViewDir::Right;

		float4 MoveDir = float4::Right * WalkSpeed * _DeltaTime;
		GetTransform()->AddLocalPosition(MoveDir);
	}
	else
	{
		PlayerFSM.ChangeState("Idle");
		return;
	}
}

void PlayerBaseSkull::Walk_End() 
{

}

void PlayerBaseSkull::Dash_Enter()
{
	SkullRenderer->ChangeAnimation("Dash");

	switch (ViewDir)
	{
	case ActorViewDir::Left:
		PlayerRigidbody.SetVelocity(float4::Left * DashVelocity);
		break;
	case ActorViewDir::Right:
		PlayerRigidbody.SetVelocity(float4::Right * DashVelocity);
		break;
	default:
		break;
	}

	CanDash = false;
	DashCombo = false;

	JumpDir = float4::Zero;
}

void PlayerBaseSkull::Dash_Update(float _DeltaTime)
{
	if (true == CanJump && GameEngineInput::IsDown("PlayerMove_Jump"))
	{
		PlayerFSM.ChangeState("Jump");
		return;
	}

	if (false == DashCombo && GameEngineInput::IsDown("PlayerMove_Dash"))
	{
		DashCombo = true;

		if (true == GameEngineInput::IsPress("PlayerMove_Left"))
		{
			ViewDir = ActorViewDir::Left;
		}
		else if (true == GameEngineInput::IsPress("PlayerMove_Left"))
		{
			ViewDir = ActorViewDir::Right;
		}

		switch (ViewDir)
		{
		case ActorViewDir::Left:
			PlayerRigidbody.SetVelocity(float4::Left * DashVelocity);
			break;
		case ActorViewDir::Right:
			PlayerRigidbody.SetVelocity(float4::Right * DashVelocity);
			break;
		default:
			break;
		}
	}

	if (5.0f > PlayerRigidbody.GetVelocity().Size())
	{
		if (false == IsGround())
		{
			PlayerFSM.ChangeState("Fall");
			return;
		}

		if (true == GameEngineInput::IsPress("PlayerMove_Left"))
		{
			ViewDir = ActorViewDir::Left;
			PlayerFSM.ChangeState("Walk");
		}
		else if (true == GameEngineInput::IsPress("PlayerMove_Right"))
		{
			ViewDir = ActorViewDir::Right;
			PlayerFSM.ChangeState("Walk");
		}
		else 
		{
			PlayerFSM.ChangeState("Idle");
		}
	}
}

void PlayerBaseSkull::Dash_End()
{
}

void PlayerBaseSkull::Fall_Enter() 
{
	SkullRenderer->ChangeAnimation("Fall");
}

void PlayerBaseSkull::Fall_Update(float _DeltaTime) 
{
	if (true == SkullRenderer->FindAnimation("Fall")->IsEnd())
	{
		SkullRenderer->ChangeAnimation("FallRepeat");
	}

	if (true == CanDash && true == GameEngineInput::IsDown("PlayerMove_Dash"))
	{
		PlayerFSM.ChangeState("Dash");
		return;
	}

	if (true == DoubleJump && true == GameEngineInput::IsDown("PlayerMove_Jump"))
	{
		PlayerFSM.ChangeState("Jump");
		DoubleJump = false;
		return;
	}

	JumpDir.y += _DeltaTime * ContentConst::Gravity_f;
	GetTransform()->AddLocalPosition(JumpDir * _DeltaTime);

	if (true == GameEngineInput::IsPress("PlayerMove_Left"))
	{
		ViewDir = ActorViewDir::Left;
		float4 MoveDir = float4::Left * WalkSpeed * _DeltaTime;
		GetTransform()->AddLocalPosition(MoveDir);

	}
	else if (true == GameEngineInput::IsPress("PlayerMove_Right"))
	{
		ViewDir = ActorViewDir::Right;
		float4 MoveDir = float4::Right * WalkSpeed * _DeltaTime;
		GetTransform()->AddLocalPosition(MoveDir);
	}

	if (true == IsGround())
	{
		if (true == GameEngineInput::IsPress("PlayerMove_Left"))
		{
			ViewDir = ActorViewDir::Left;
			PlayerFSM.ChangeState("Walk");
		}
		else if (true == GameEngineInput::IsPress("PlayerMove_Right"))
		{
			ViewDir = ActorViewDir::Right;
			PlayerFSM.ChangeState("Walk");
		}
		else
		{
			PlayerFSM.ChangeState("Idle");
		}
	}	
}

void PlayerBaseSkull::Fall_End() 
{

}
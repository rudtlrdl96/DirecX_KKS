#include "PrecompileHeader.h"
#include "PlayerBaseSkull.h"

#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineCollision.h>

#include "CaptureTrail.h"

void PlayerBaseSkull::Idle_Enter()
{
	SkullRenderer->ChangeAnimation("Idle");
	JumpDir = float4::Zero;
	CanJump = true;
	DoubleJump = true;
}

void PlayerBaseSkull::Idle_Update(float _DeltaTime)
{
	if (nullptr == PlatformColCheck(GroundCol, true))
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
		PlayerFSM.ChangeState("Attack");
	}
	else if (true == GameEngineInput::IsDown("PlayerMove_Jump"))
	{
		if (true == GameEngineInput::IsPress("PlayerMove_Down"))
		{
			if (nullptr == PlatformColCheck(GroundCol))
			{
				FallCooldown = 0.2f;
				PlayerFSM.ChangeState("Fall");
				return;
			}
		}

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
	if (nullptr == PlatformColCheck(WalkCol))
	{
		float4 Velocity = DashRigidbody.GetVelocity() * _DeltaTime;
		GetTransform()->AddLocalPosition(Velocity);
	}

	if (nullptr == PlatformColCheck(JumpCol))
	{
		JumpDir.y += ContentConst::Gravity_f * _DeltaTime;
		GetTransform()->AddLocalPosition(JumpDir * _DeltaTime);
	}
	else 
	{
		JumpDir.y = -1.0f;
	}

	if (true == CanDash && true == GameEngineInput::IsDown("PlayerMove_Dash"))
	{
		PlayerFSM.ChangeState("Dash");
		return;
	}

	if (true == DoubleJump && true == GameEngineInput::IsDown("PlayerMove_Jump"))
	{
		EffectManager::PlayEffect({.EffectName = "PlayerJumpEffect", .Postion = GetTransform()->GetWorldPosition()});

		JumpDir = float4::Up * JumpPower;
		DoubleJump = false;
	}

	if (true == GameEngineInput::IsPress("PlayerMove_Left"))
	{
		SetViewDir(ActorViewDir::Left);

		if (nullptr == PlatformColCheck(WalkCol))
		{
			float4 MoveDir = float4::Left * WalkSpeed * _DeltaTime;
			GetTransform()->AddLocalPosition(MoveDir);
		}
	}
	else if (true == GameEngineInput::IsPress("PlayerMove_Right"))
	{
		SetViewDir(ActorViewDir::Right);

		if (nullptr == PlatformColCheck(WalkCol))
		{
			float4 MoveDir = float4::Right * WalkSpeed * _DeltaTime;
			GetTransform()->AddLocalPosition(MoveDir);
		}
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
	if (nullptr == PlatformColCheck(WalkCol))
	{
		float4 Velocity = DashRigidbody.GetVelocity() * _DeltaTime;
		GetTransform()->AddLocalPosition(Velocity);
	}

	if (nullptr == PlatformColCheck(GroundCol, true))
	{
		PlayerFSM.ChangeState("Fall");
		return;
	}

	if (true == GameEngineInput::IsDown("PlayerMove_Jump"))
	{
		if (true == GameEngineInput::IsPress("PlayerMove_Down"))
		{
			if (nullptr == PlatformColCheck(GroundCol))
			{
				FallCooldown = 0.2f;
				PlayerFSM.ChangeState("Fall");
				return;
			}
		}

		PlayerFSM.ChangeState("Jump");
	}

	if (true == GameEngineInput::IsDown("PlayerMove_Attack"))
	{
		PlayerFSM.ChangeState("Attack");
		return;
	}

	if (true == CanDash && true == GameEngineInput::IsDown("PlayerMove_Dash"))
	{
		PlayerFSM.ChangeState("Dash");
		return;
	}

	if (true == GameEngineInput::IsPress("PlayerMove_Left"))
	{
		SetViewDir(ActorViewDir::Left);

		if (nullptr == PlatformColCheck(WalkCol))
		{
			float4 MoveDir = float4::Left * WalkSpeed * _DeltaTime;
			GetTransform()->AddLocalPosition(MoveDir);
		}
	}
	else if (true == GameEngineInput::IsPress("PlayerMove_Right"))
	{
		SetViewDir(ActorViewDir::Right);

		if (nullptr == PlatformColCheck(WalkCol))
		{
			float4 MoveDir = float4::Right * WalkSpeed * _DeltaTime;
			GetTransform()->AddLocalPosition(MoveDir);
		}
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
	DashTrail->PlayTrail(SkullRenderer->GetTexName(),
		SkullRenderer->GetAtlasData(),
		(ActorViewDir::Left == ViewDir),
		SkullRenderer->GetScaleRatio());

	SkullRenderer->ChangeAnimation("Dash");

	EffectManager::PlayEffect({ 
		.EffectName = "PlayerDashEffect",
		.Postion = GetTransform()->GetWorldPosition(), 
		.FlipX = ViewDir == ActorViewDir::Left});

	switch (ViewDir)
	{
	case ActorViewDir::Left:
		DashRigidbody.SetVelocity(float4::Left * DashVelocity);
		break;
	case ActorViewDir::Right:
		DashRigidbody.SetVelocity(float4::Right * DashVelocity);
		break;
	default:
		break;
	}

	CanDash = false;
	DashCombo = false;

	JumpDir = float4::Zero;

	DashTrailCoolTime = 0.05f;
}

void PlayerBaseSkull::Dash_Update(float _DeltaTime)
{
	if (nullptr == PlatformColCheck(WalkCol))
	{
		float4 Velocity = DashRigidbody.GetVelocity() * _DeltaTime;
		GetTransform()->AddLocalPosition(Velocity);
	}

	if (true == CanJump && GameEngineInput::IsDown("PlayerMove_Jump"))
	{
		PlayerFSM.ChangeState("Jump");
		return;
	}

	if (true == GameEngineInput::IsDown("PlayerMove_Attack"))
	{
		if (nullptr == PlatformColCheck(GroundCol))
		{
			//JumpAttack
		}
		else
		{
			PlayerFSM.ChangeState("Attack");
		}
		return;
	}

	DashTrailCoolTime -= _DeltaTime;

	if (0.0f >= DashTrailCoolTime)
	{
		DashTrailCoolTime += 0.05f;
		DashTrail->PlayTrail(SkullRenderer->GetTexName(),
			SkullRenderer->GetAtlasData(),
			(ActorViewDir::Left == ViewDir),
			SkullRenderer->GetScaleRatio());
	}

	if (false == DashCombo && GameEngineInput::IsDown("PlayerMove_Dash"))
	{
		if (true == GameEngineInput::IsPress("PlayerMove_Left"))
		{
			SetViewDir(ActorViewDir::Left);
		}
		else if (true == GameEngineInput::IsPress("PlayerMove_Right"))
		{
			SetViewDir(ActorViewDir::Right);
		}

		EffectManager::PlayEffect({
			.EffectName = "PlayerDashEffect",
			.Postion = GetTransform()->GetWorldPosition(),
			.FlipX = ViewDir == ActorViewDir::Left });

		DashCombo = true;

		switch (ViewDir)
		{
		case ActorViewDir::Left:
			DashRigidbody.SetVelocity(float4::Left * DashVelocity);
			break;
		case ActorViewDir::Right:
			DashRigidbody.SetVelocity(float4::Right * DashVelocity);
			break;
		default:
			break;
		}
	}

	if (5.0f > DashRigidbody.GetVelocity().Size())
	{
		if (nullptr == PlatformColCheck(GroundCol))
		{
			PlayerFSM.ChangeState("Fall");
			return;
		}

		if (true == GameEngineInput::IsPress("PlayerMove_Left"))
		{
			PlayerFSM.ChangeState("Walk");
		}
		else if (true == GameEngineInput::IsPress("PlayerMove_Right"))
		{
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

	if (nullptr == PlatformColCheck(WalkCol))
	{
		float4 Velocity = DashRigidbody.GetVelocity() * _DeltaTime;
		GetTransform()->AddLocalPosition(Velocity);
	}

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
		EffectManager::PlayEffect({ .EffectName = "PlayerJumpEffect", .Postion = GetTransform()->GetWorldPosition() });

		PlayerFSM.ChangeState("Jump");
		DoubleJump = false;
		return;
	}

	JumpDir.y += _DeltaTime * ContentConst::Gravity_f;
	GetTransform()->AddLocalPosition(JumpDir * _DeltaTime);

	if (true == GameEngineInput::IsPress("PlayerMove_Left"))
	{
		SetViewDir(ActorViewDir::Left);

		if (nullptr == PlatformColCheck(WalkCol))
		{
			float4 MoveDir = float4::Left * WalkSpeed * _DeltaTime;
			GetTransform()->AddLocalPosition(MoveDir);
		}
	}
	else if (true == GameEngineInput::IsPress("PlayerMove_Right"))
	{
		SetViewDir(ActorViewDir::Right);

		if (nullptr == PlatformColCheck(WalkCol))
		{
			float4 MoveDir = float4::Right * WalkSpeed * _DeltaTime;
			GetTransform()->AddLocalPosition(MoveDir);
		}
	}

	bool IsHalfCheck = 0.0f >= FallCooldown;
	
	std::shared_ptr<GameEngineCollision> GroundColPtr = PlatformColCheck(GroundCol, IsHalfCheck);

	if (nullptr != GroundColPtr)
	{	
		GameEngineTransform* PlayerTrans = GetTransform();
		float4 CurPos = PlayerTrans->GetWorldPosition();

		GameEngineTransform* ColTrans = GroundColPtr->GetTransform();
		CurPos.y = ColTrans->GetWorldPosition().y + ColTrans->GetWorldScale().hy();

		PlayerTrans->SetWorldPosition(CurPos);
		PlayerTrans->SetLocalPosition(PlayerTrans->GetLocalPosition());

		if (true == GameEngineInput::IsPress("PlayerMove_Left"))
		{
			PlayerFSM.ChangeState("Walk");

		}
		else if (true == GameEngineInput::IsPress("PlayerMove_Right"))
		{
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

void PlayerBaseSkull::Attack_Enter() 
{
	if (0 == AnimColMeta_Attack.size())
	{
		MsgAssert_Rtti<PlayerBaseSkull>(" - 스컬의 공격 정보가 없습니다");
	}

	IsAttackCombo = false;
	AttackComboCount = 0;
	SkullRenderer->ChangeAnimation(AnimColMeta_Attack[AttackComboCount].GetAnimationName());
}

void PlayerBaseSkull::Attack_Update(float _DeltaTime) 
{
	if (nullptr == PlatformColCheck(WalkCol))
	{
		float4 Velocity = DashRigidbody.GetVelocity() * _DeltaTime;
		GetTransform()->AddLocalPosition(Velocity);
	}

	if (true == CanDash && true == GameEngineInput::IsDown("PlayerMove_Dash"))
	{
		PlayerFSM.ChangeState("Dash");
		return;
	}

	if (true == GameEngineInput::IsDown("PlayerMove_Attack"))
	{
		IsAttackCombo = true;
	}

	if (true == SkullRenderer->IsAnimationEnd())
	{
		if (true == IsAttackCombo)
		{
			++AttackComboCount;

			if (AttackComboCount >= AnimColMeta_Attack.size())
			{
				AttackComboCount = 0;
			}

			IsAttackCombo = false;
			SkullRenderer->ChangeAnimation(AnimColMeta_Attack[AttackComboCount].GetAnimationName());
		}
		else if (true == GameEngineInput::IsPress("PlayerMove_Left"))
		{
			PlayerFSM.ChangeState("Walk");

		}
		else if (true == GameEngineInput::IsPress("PlayerMove_Right"))
		{
			PlayerFSM.ChangeState("Walk");
		}
		else
		{
			PlayerFSM.ChangeState("Idle");
		}
	}

}

void PlayerBaseSkull::Attack_End() {}
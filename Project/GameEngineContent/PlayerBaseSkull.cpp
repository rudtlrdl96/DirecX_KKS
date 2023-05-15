#include "PrecompileHeader.h"
#include "PlayerBaseSkull.h"

#include <GameEnginePlatform/GameEngineInput.h>

PlayerBaseSkull::PlayerBaseSkull()
{
}

PlayerBaseSkull::~PlayerBaseSkull()
{
}

void PlayerBaseSkull::Start()
{
	SkullRenderer = CreateComponent<GameEngineSpriteRenderer>();
	SkullRenderer->GetTransform()->SetLocalPosition(float4::Zero);
	SkullRenderer->SetScaleRatio(2.0f);

	TextureLoad();
	CreateAnimation();

	if (nullptr == GameEngineSprite::Find("DashSmokeEffect.png"))
	{
		GameEngineDirectory Path;

		Path.MoveParentToDirectory("Resources");
		Path.Move("Resources");
		Path.Move("Texture");
		Path.Move("0_Common");
		Path.Move("Player");
		Path.Move("Effect");

		GameEngineSprite::LoadSheet(Path.GetPlusFileName("DashSmokeEffect.png").GetFullPath(), 6, 2);
		GameEngineSprite::LoadSheet(Path.GetPlusFileName("DoubleJumpEffect.png").GetFullPath(), 5, 2);
	}

	if (false == GameEngineInput::IsKey("PlayerMove_Left"))
	{
		GameEngineInput::CreateKey("PlayerMove_Up", VK_UP);
		GameEngineInput::CreateKey("PlayerMove_Down", VK_DOWN);
		GameEngineInput::CreateKey("PlayerMove_Left", VK_LEFT);
		GameEngineInput::CreateKey("PlayerMove_Right", VK_RIGHT);
		GameEngineInput::CreateKey("PlayerMove_Dash", 'Z');
		GameEngineInput::CreateKey("PlayerMove_Attack", 'X');
		GameEngineInput::CreateKey("PlayerMove_Jump", 'C');
		GameEngineInput::CreateKey("PlayerMove_Skill_A", 'A');
		GameEngineInput::CreateKey("PlayerMove_Skill_B", 'S');
	}

	PlayerFSM.Init(this);

	PlayerFSM.AddFSM("Idle", &PlayerBaseSkull::Idle_Enter, &PlayerBaseSkull::Idle_Update, &PlayerBaseSkull::Idle_End);
	PlayerFSM.AddFSM("Walk", &PlayerBaseSkull::Walk_Enter, &PlayerBaseSkull::Walk_Update, &PlayerBaseSkull::Walk_End);
	PlayerFSM.AddFSM("Attack", &PlayerBaseSkull::Attack_Enter, &PlayerBaseSkull::Attack_Update, &PlayerBaseSkull::Attack_End);
	PlayerFSM.AddFSM("Jump", &PlayerBaseSkull::Jump_Enter, &PlayerBaseSkull::Jump_Update, &PlayerBaseSkull::Jump_End);
	PlayerFSM.AddFSM("JumpAttack", &PlayerBaseSkull::JumpAttack_Enter, &PlayerBaseSkull::JumpAttack_Update, &PlayerBaseSkull::JumpAttack_End);
	PlayerFSM.AddFSM("Fall", &PlayerBaseSkull::Fall_Enter, &PlayerBaseSkull::Fall_Update, &PlayerBaseSkull::Fall_End);
	PlayerFSM.AddFSM("Dash", &PlayerBaseSkull::Dash_Enter, &PlayerBaseSkull::Dash_Update, &PlayerBaseSkull::Dash_End);
	PlayerFSM.AddFSM("Switch", &PlayerBaseSkull::Switch_Enter, &PlayerBaseSkull::Switch_Update, &PlayerBaseSkull::Switch_End);
	PlayerFSM.AddFSM("Skill_A", &PlayerBaseSkull::Skill_SlotA_Enter, &PlayerBaseSkull::Skill_SlotA_Update, &PlayerBaseSkull::Skill_SlotA_End);
	PlayerFSM.AddFSM("Skill_B", &PlayerBaseSkull::Skill_SlotB_Enter, &PlayerBaseSkull::Skill_SlotB_Update, &PlayerBaseSkull::Skill_SlotB_End);

	PlayerFSM.ChangeState("Idle");

	PlayerRigidbody.SetActiveGravity(false);
	PlayerRigidbody.SetMaxSpeed(1050);
	PlayerRigidbody.SetFricCoeff(3500);
}

void PlayerBaseSkull::Update(float _DeltaTime)
{
	PlayerFSM.Update(_DeltaTime);

	switch (ViewDir)
	{
	case ActorViewDir::Left:
		GetTransform()->SetLocalNegativeScaleX();
		break;
	case ActorViewDir::Right:
		GetTransform()->SetLocalPositiveScaleX();
		break;
	default:
		break;
	}

	PlayerRigidbody.UpdateForce(_DeltaTime);
	float4 Velocity = PlayerRigidbody.GetVelocity();

	// Todo Map Ãæµ¹
	GetTransform()->AddLocalPosition(Velocity * _DeltaTime);

	if (false == CanDash)
	{
		DashCoolTime += _DeltaTime;
	}

	if (DashCoolTime >= 0.7f)
	{
		CanDash = true;
		DashCoolTime = 0.0f;
	}
}

bool PlayerBaseSkull::IsGround() const
{
	static bool GroundCheck = true;

	if (false == GameEngineInput::IsKey("Debug Ground Check"))
	{
		GameEngineInput::CreateKey("Debug Ground Check", 'G');
	}

	if (true == GameEngineInput::IsDown("Debug Ground Check"))
	{
		GroundCheck = !GroundCheck;	
	}

	return GroundCheck;
}
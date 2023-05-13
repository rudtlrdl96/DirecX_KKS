#pragma once
#include "BaseContentActor.h"
#include "ClassFSM.h"
#include "Rigidbody2D.h"
#include "AttackMetaData.h"

class PlayerBaseSkull : public BaseContentActor
{
public:
	PlayerBaseSkull();
	~PlayerBaseSkull();

	PlayerBaseSkull(const PlayerBaseSkull& _Other) = delete;
	PlayerBaseSkull(PlayerBaseSkull&& _Other) noexcept = delete;
	PlayerBaseSkull& operator=(const PlayerBaseSkull& _Other) = delete;
	PlayerBaseSkull& operator=(PlayerBaseSkull&& _Other) noexcept = delete;

	inline Rigidbody2D* GetRigidbody()
	{
		return &PlayerRigidbody;
	}

protected:	
	std::shared_ptr<GameEngineSpriteRenderer> SkullRenderer = nullptr;

	//std::vector<AttackMetaData> 

	void Start() override;
	void Update(float _DeltaTime) override;
	
	bool IsGround() const;

	// FSM Functions
	virtual void Idle_Enter();
	virtual void Idle_Update(float _DeltaTime);
	virtual void Idle_End();

	virtual void Walk_Enter();
	virtual void Walk_Update(float _DeltaTime);
	virtual void Walk_End();

	virtual void Attack_Enter() {}
	virtual void Attack_Update(float _DeltaTime) {}
	virtual void Attack_End() {}

	virtual void JumpAttack_Enter() {}
	virtual void JumpAttack_Update(float _DeltaTime) {}
	virtual void JumpAttack_End() {}

	virtual void Jump_Enter();
	virtual void Jump_Update(float _DeltaTime);
	virtual void Jump_End() {}

	virtual void Fall_Enter();
	virtual void Fall_Update(float _DeltaTime);
	virtual void Fall_End();

	virtual void Dash_Enter();
	virtual void Dash_Update(float _DeltaTime);
	virtual void Dash_End();

	virtual void Switch_Enter() {}
	virtual void Switch_Update(float _DeltaTime) {}
	virtual void Switch_End() {}

	virtual void Skill_SlotA_Enter() {}
	virtual void Skill_SlotA_Update(float _DeltaTime) {}
	virtual void Skill_SlotA_End() {}

	virtual void Skill_SlotB_Enter() {}
	virtual void Skill_SlotB_Update(float _DeltaTime) {}
	virtual void Skill_SlotB_End() {}

	virtual void TextureLoad() = 0;
	virtual void CreateAnimation() = 0;

private:		
	Rigidbody2D PlayerRigidbody;
	ClassFSM<PlayerBaseSkull> PlayerFSM;
	
	ActorViewDir ViewDir = ActorViewDir::Right;

	float4 JumpDir = float4::Zero;
	float JumpPower = 700.0f;
	bool CanJump = false;
	bool DoubleJump = false;

	bool CanDash = false;
	float DashCoolTime = 0.0f;

	float DashVelocity = 3000.0f;
	bool DashCombo = false;

	float WalkSpeed = 350.0f;
	float MaxFallSpeed = 1400.0f;

};


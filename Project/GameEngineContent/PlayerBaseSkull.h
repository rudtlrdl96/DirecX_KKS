#pragma once
#include "BaseContentActor.h"
#include "ClassFSM.h"

class PlayerBaseSkull : public BaseContentActor
{
public:
	PlayerBaseSkull();
	~PlayerBaseSkull();

	PlayerBaseSkull(const PlayerBaseSkull& _Other) = delete;
	PlayerBaseSkull(PlayerBaseSkull&& _Other) noexcept = delete;
	PlayerBaseSkull& operator=(const PlayerBaseSkull& _Other) = delete;
	PlayerBaseSkull& operator=(PlayerBaseSkull&& _Other) noexcept = delete;

protected:	
	void Start() override;

	ActorWalkDir ViewDir = ActorWalkDir::Right;
	ClassFSM<PlayerBaseSkull> PlayerFSM;

	std::shared_ptr<GameEngineSpriteRenderer> SkullRenderer = nullptr;
	
	float4 JumpDir = float4::Zero;
	float JumpPower = 100.0f;
	int JumpCount = 2;

	float WalkSpeed = 250.0f;

	float MaxFallSpeed = 400.0f;

	bool IsGround() const;

	// FSM Functions
	virtual void Idle_Enter();
	virtual void Idle_Update(float _DeltaTime);
	virtual void Idle_End();

	virtual void Walk_Enter() {}
	virtual void Walk_Update(float _DeltaTime) {}
	virtual void Walk_End() {}

	virtual void Attack_Enter() {}
	virtual void Attack_Update(float _DeltaTime) {}
	virtual void Attack_End() {}

	virtual void JumpAttack_Enter() {}
	virtual void JumpAttack_Update(float _DeltaTime) {}
	virtual void JumpAttack_End() {}

	virtual void Jump_Enter() {}
	virtual void Jump_Update(float _DeltaTime);
	virtual void Jump_End() {}

	virtual void Fall_Enter() {}
	virtual void Fall_Update(float _DeltaTime) {}
	virtual void Fall_End() {}

	virtual void Dash_Enter() {}
	virtual void Dash_Update(float _DeltaTime) {}
	virtual void Dash_End() {}

	virtual void Switch_Enter() {}
	virtual void Switch_Update(float _DeltaTime) {}
	virtual void Switch_End() {}

	virtual void Skill_SlotA_Enter() {}
	virtual void Skill_SlotA_Update(float _DeltaTime) {}
	virtual void Skill_SlotA_End() {}

	virtual void Skill_SlotB_Enter() {}
	virtual void Skill_SlotB_Update(float _DeltaTime) {}
	virtual void Skill_SlotB_End() {}
private:

};


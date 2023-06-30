#pragma once
#include "PlayerBaseSkull.h"

class MinotaurusSkull_Rare : public PlayerBaseSkull
{
public:
	MinotaurusSkull_Rare();
	~MinotaurusSkull_Rare();

	MinotaurusSkull_Rare(const MinotaurusSkull_Rare& _Other) = delete;
	MinotaurusSkull_Rare(MinotaurusSkull_Rare&& _Other) noexcept = delete;
	MinotaurusSkull_Rare& operator=(const MinotaurusSkull_Rare& _Other) = delete;
	MinotaurusSkull_Rare& operator=(MinotaurusSkull_Rare&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	
	void Attack_Enter() override;
	void Attack_End() override;

	void JumpAttack_Enter() override;
	void JumpAttack_Update(float _DeltaTime) override;
	void JumpAttack_End() override;

	void Switch_Enter() override;
	void Switch_Update(float _DeltaTime) override;

	void Dash_Enter() override;
	void Dash_Update(float _DeltaTime) override;
	void Dash_End() override;

	void Skill_SlotA_Enter() override;
	void Skill_SlotA_Update(float _DeltaTime) override;
	void Skill_SlotA_End() override;

private:
	std::shared_ptr<GameEngineCollision> JumpAttackCol = nullptr;
	std::shared_ptr<GameEngineCollision> DashAttackCol = nullptr;
	std::shared_ptr<GameEngineCollision> SkillACol = nullptr;
	std::shared_ptr<GameEngineCollision> PassiveCol = nullptr;

	std::map<UINT, std::shared_ptr <class BaseMonster>> AttackDoubleCheck;
	std::map<UINT, float> PassiveDoubleCheck;
	std::shared_ptr<EffectActor> PassiveEffect = nullptr;

	Rigidbody2D SkillARigidbody;

	float JumpAttackTime = 0.0f;
	float JumpAttackLandTime = 0.0f;
	float SkillALandTime = 0.0f;
	float PassiveTime = 0.0f;

	bool IsJumpAttackLand = false;
	bool IsSkillALand = false;
	bool IsSwitchMove = false;
	bool IsPassive = false;

	void DataLoad() override;
	void TextureLoad() override;
	void CreateAnimation() override;
	void AnimationColLoad() override;

	void PassiveCheck();
};


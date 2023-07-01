#pragma once
#include "PlayerBaseSkull.h"


class MinotaurusSkull_Unique : public PlayerBaseSkull
{
public:
	MinotaurusSkull_Unique();
	~MinotaurusSkull_Unique();

	MinotaurusSkull_Unique(const MinotaurusSkull_Unique& _Other) = delete;
	MinotaurusSkull_Unique(MinotaurusSkull_Unique&& _Other) noexcept = delete;
	MinotaurusSkull_Unique& operator=(const MinotaurusSkull_Unique& _Other) = delete;
	MinotaurusSkull_Unique& operator=(MinotaurusSkull_Unique&& _Other) noexcept = delete;

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

	void Skill_SlotB_Enter() override;
	void Skill_SlotB_Update(float _DeltaTime) override;
	void Skill_SlotB_End() override;

private:
	std::shared_ptr<GameEngineCollision> JumpAttackCol = nullptr;
	std::shared_ptr<GameEngineCollision> DashAttackCol = nullptr;
	std::shared_ptr<GameEngineCollision> SkillACol = nullptr;
	std::shared_ptr<GameEngineCollision> SkillBCol = nullptr;

	std::shared_ptr<GameEngineCollision> PassiveCol = nullptr;

	std::map<UINT, std::shared_ptr <class BaseMonster>> AttackDoubleCheck;
	std::map<UINT, float> PassiveDoubleCheck;
	std::shared_ptr<EffectActor> PassiveEffect = nullptr;
	std::shared_ptr<EffectActor> SkillBPlowUpEffect = nullptr;

	std::vector<std::string> ProjectileEffectNames;

	Rigidbody2D SkillARigidbody;

	float JumpAttackTime = 0.0f;
	float JumpAttackLandTime = 0.0f;
	float SkillALandTime = 0.0f;
	float SkillBWaitTime = 0.0f;
	float SkillBProjectileTime = 0.0f;
	float SwitchProjectileTime = 0.0f;
	float PassiveTime = 0.0f;

	bool IsJumpAttackLand = false;
	bool IsSkillALand = false;
	bool IsSkillADoubleAttack = false;

	bool IsSkillBWait = false;
	bool IsSkillBEffect = false;
	bool IsSKillBProjectileShot = false;

	bool IsSwitchProjectileShot = false;

	bool IsSwitchMove = false;
	bool IsPassive = false;

	int SkillBShotCount = 0;
	int SwitchShotCount = 0;

	void DataLoad() override;
	void TextureLoad() override;
	void CreateAnimation() override;
	void AnimationColLoad() override;

	void PassiveCheck();
	void ShotProjectile(size_t _TextureIndex);
};


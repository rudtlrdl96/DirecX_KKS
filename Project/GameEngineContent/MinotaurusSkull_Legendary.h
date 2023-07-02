#pragma once
#include "PlayerBaseSkull.h"

class MinotaurusSkull_Legendary : public PlayerBaseSkull
{
public:
	MinotaurusSkull_Legendary();
	~MinotaurusSkull_Legendary();

	MinotaurusSkull_Legendary(const MinotaurusSkull_Legendary& _Other) = delete;
	MinotaurusSkull_Legendary(MinotaurusSkull_Legendary&& _Other) noexcept = delete;
	MinotaurusSkull_Legendary& operator=(const MinotaurusSkull_Legendary& _Other) = delete;
	MinotaurusSkull_Legendary& operator=(MinotaurusSkull_Legendary&& _Other) noexcept = delete;

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
	std::shared_ptr<GameEngineCollision> SkillBDoubleAttackCol = nullptr;
	std::shared_ptr<GameEngineCollision> EarthquakeFindCol = nullptr;
	std::shared_ptr<GameEngineCollision> EarthquakeAttackCol = nullptr;

	std::shared_ptr<GameEngineCollision> PassiveCol = nullptr;

	std::map<UINT, std::shared_ptr <class BaseMonster>> AttackDoubleCheck;
	std::shared_ptr<EffectActor> SkillBPlowUpEffect = nullptr;

	std::vector<std::string> ProjectileEffectNames;
	std::vector<std::string> LargeProjectileEffectNames;

	Rigidbody2D SkillARigidbody;

	float JumpAttackTime = 0.0f;
	float JumpAttackLandTime = 0.0f;
	float SkillALandTime = 0.0f;
	float SkillBWaitTime = 0.0f;
	float SkillBProjectileTime = 0.0f;
	float SwitchProjectileTime = 0.0f;
	float SwitchEarthquakeTime = 0.0f;
	float PassiveTime = 0.0f;

	bool IsJumpAttackLand = false;
	bool IsSkillALand = false;
	bool IsSkillADoubleAttack = false;

	bool IsSkillBWait = false;
	bool IsSkillBEffect = false;
	bool IsSKillBProjectileShot = false;
	bool IsSKillBDoubleAttack = false;

	bool IsSwitchProjectileShot = false;
	bool IsSwitchEarthquake = false;

	bool IsSwitchMove = false;
	bool IsPassive = false;

	float4 SwitchEarthquakePos = float4::Zero;
	float4 SwitchEarthquakeInter = float4::Zero;

	int SkillBShotCount = 0;
	int SwitchShotCount = 0;
	int PassiveCount = 0;
	int SwitchEarthquakeCount = 0;

	void DataLoad() override;
	void TextureLoad() override;
	void CreateAnimation() override;
	void AnimationColLoad() override;

	void PassiveCheck();
	void ShotProjectile(size_t _TextureIndex);
	void ShotLargeProjectile(size_t _TextureIndex);
};


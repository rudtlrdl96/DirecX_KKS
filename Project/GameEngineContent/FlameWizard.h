#pragma once
#include "BaseMonster.h"

class FlameWizard : public BaseMonster
{
	friend void TeleportOut_Enter(BaseMonster* _this);

public:
	FlameWizard();
	~FlameWizard();

	FlameWizard(const FlameWizard& _Other) = delete;
	FlameWizard(FlameWizard&& _Other) noexcept = delete;
	FlameWizard& operator=(const FlameWizard& _Other) = delete;
	FlameWizard& operator=(FlameWizard&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

	void DataLoad() override;
	void TextureLoad() override;
	void LoadAnimation() override;
	void AnimationAttackMetaDataLoad() override;
	void SetColData() override;
	void DeathPartLoad() override;

	void Idle_Update(float _DeltaTime) override;

	void Chasing_Enter() override;
	void Chasing_Update(float _DeltaTime) override;
	void Chasing_End() override;

	void Hit_Enter() override;
	void Hit_End() override;

	void Attack_Enter() override;
	void Attack_Update(float _DeltaTime) override;

private:
	bool IsAttackLoop = false;
	float4 AttackPos = float4::Zero;

	int AttackCount = 0;
	float AttackCoolTime = 0.0f;

	float TeleportCoolTime = 0.0f;

	std::shared_ptr<GameEngineCollision> FloorCheckCol;
	std::vector<std::shared_ptr<GameEngineCollision>> PlatformCols;

	std::shared_ptr<class Projectile> ShotProjectile = nullptr;

	void CreateProjectile(float _WaitTime);

	static void ProjectileEndEffect(const float4& _EndPos);
	static void PlayerHit(std::shared_ptr<class BaseContentActor> _HitActor, const class ProjectileHitParameter& _Parameter);
};


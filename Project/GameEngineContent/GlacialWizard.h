#pragma once
#include "NormalMonster.h"

class GlacialWizard : public NormalMonster
{
public:
	GlacialWizard();
	~GlacialWizard();

	GlacialWizard(const GlacialWizard& _Other) = delete;
	GlacialWizard(GlacialWizard&& _Other) noexcept = delete;
	GlacialWizard& operator=(const GlacialWizard& _Other) = delete;
	GlacialWizard& operator=(GlacialWizard&& _Other) noexcept = delete;

protected:
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

	void Hit_End() override;

	void Attack_Enter() override;
	void Attack_Update(float _DeltaTime) override;

private:
	bool IsProjectileShot = false;

	static void ProjectileEndEffect(const float4& _EndPos);
	static void PlayerHit(std::shared_ptr<class BaseContentActor> _HitActor, const class ProjectileHitParameter& _Parameter);

};


#pragma once
#include "BaseMonster.h"

class GiantEnt : public BaseMonster
{
public:
	GiantEnt();
	~GiantEnt();

	GiantEnt(const GiantEnt& _Other) = delete;
	GiantEnt(GiantEnt&& _Other) noexcept = delete;
	GiantEnt& operator=(const GiantEnt& _Other) = delete;
	GiantEnt& operator=(GiantEnt&& _Other) noexcept = delete;

protected:
	void DataLoad() override;
	void TextureLoad() override;
	void LoadAnimation() override;
	void AnimationAttackMetaDataLoad() override;
	void SetColData() override;


	void Idle_Update(float _DelatTime) override;

	void Walk_Enter() override; // 해당 스테이트에 들어올경우 터트리기

	void Chasing_Enter() override;
	void Chasing_Update(float _DeltaTime) override;

	void Attack_Enter() override;
	void Attack_Update(float _DeltaTime) override;

private:
	bool IsAttackStempEffect = false;

	bool IsRangeAttack = false;
	bool IsRnageProjectile = false;
	
	std::map<UINT, float> RangeAttackPauseTimes;

	void ShotProjectile(float _Deg);

	static void ProjectileEndEffect(const float4& _EndPos);
	static void PlayerHit(std::shared_ptr<class BaseContentActor> _HitActor, const class ProjectileHitParameter& _Parameter);
};


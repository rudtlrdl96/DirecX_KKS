#pragma once
#include "NormalMonster.h"

class RootEnt : public NormalMonster
{
public:
	RootEnt();
	~RootEnt();

	RootEnt(const RootEnt& _Other) = delete;
	RootEnt(RootEnt&& _Other) noexcept = delete;
	RootEnt& operator=(const RootEnt& _Other) = delete;
	RootEnt& operator=(RootEnt&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

	void DataLoad() override;
	void TextureLoad() override;
	void LoadAnimation() override;
	void AnimationAttackMetaDataLoad() override;
	void SetColData() override;
	void DeathPartLoad() override;

	void Hit_Enter() override;
	void Hit_End() override;

	void Attack_Enter() override;
	void Attack_Update(float _DeltaTime) override;

private:
	bool IsAttackSign = false;
	bool IsAttackEffect = false;
	bool IsAttackEffectPause = false;

	float4 AttackPos = float4::Zero;

	float EffectStopTime = 0.0f;

	std::vector<std::shared_ptr<GameEngineCollision>> PlatformCols;

	std::shared_ptr<class GameEngineCollision> FloorCheckCol = nullptr;
	std::shared_ptr<EffectActor> SignEffectActor = nullptr;
	std::shared_ptr<EffectActor> AttackEffectActor = nullptr;
};


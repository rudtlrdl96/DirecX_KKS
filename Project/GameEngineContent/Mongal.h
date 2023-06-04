#pragma once
#include "NormalMonster.h"

class Mongal : public NormalMonster
{
private:
	enum class DeathState
	{
		BattleDeath,
		WakeUp,
		NormalIdle,
		Laugh,
		DoorWalk,
		NormalDeath
	};
public:
	Mongal();
	~Mongal();

	Mongal(const Mongal& _Other) = delete;
	Mongal(Mongal&& _Other) noexcept = delete;
	Mongal& operator=(const Mongal& _Other) = delete;
	Mongal& operator=(Mongal&& _Other) noexcept = delete;

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
	void Hit_Update(float _DeltaTime) override;

	void Attack_Enter() override;
	void Attack_Update(float _DeltaTime) override;
	void Attack_End() override;

private:
	int AttackLoopCount = 0;

	bool IsMongalDeath = false;
	bool IsAttackMove = false;
	bool DeathCameraShake = false;

	float ForceEscapeTime = 0.0f;
	float DeathTimeCheck = 0.0f;

	bool IsFade = false;
	float FadeTimeCheck = 0.0f;

	float LaughTime = 0.0f;

	float4 WalkStart = float4::Zero;
	float4 WalkEnd = float4::Zero;
	float WalkProgress = 0.0f;
	float WalkSpeed = 0.3f;

	std::map<int, float> WakeupWaitTime;

	DeathState State = DeathState::BattleDeath;

	void MonsterDeath() override;
	void StoryUpdate(float _DeltaTime);
};


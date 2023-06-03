#pragma once
#include "NormalMonster.h"

class Mongal : public NormalMonster
{
private:
	enum class DeathState
	{
		BattleDeath,
		WakeUp,
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
	void MonsterDeath() override;

	int AttackLoopCount = 0;

	bool IsMongalDeath = false;
	bool IsAttackMove = false;
	bool DeathCameraShake = false;

	float ForceEscapeTime = 0.0f;

	float DeathTimeCheck = 0.0f;

	DeathState State = DeathState::BattleDeath;
};


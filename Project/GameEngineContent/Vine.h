#pragma once
#include "BehaviorObject.h"

class Vine : public BehaviorObject
{
private:
	enum class VineState
	{
		Idle,
		AttackReady,
		BattleIdle,
		Attack
	};
public:
	Vine();
	~Vine();

	Vine(const Vine& _Other) = delete;
	Vine(Vine&& _Other) noexcept = delete;
	Vine& operator=(const Vine& _Other) = delete;
	Vine& operator=(Vine&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	
	void ResetBehavior() override;
	void PlayBehavior() override;

private:
	VineState State = VineState::Idle;

	std::shared_ptr<class GameEngineCollision> FindCol = nullptr;
	std::shared_ptr<class GameEngineCollision> AttackCol = nullptr;

	bool IsPlayerHit = false;

	float AttackCoolTime = 0.0f;
};


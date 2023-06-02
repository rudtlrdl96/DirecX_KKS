#pragma once
#include "BehaviorObject.h"

class ThornBush : public BehaviorObject
{
public:
	ThornBush();
	~ThornBush();

	ThornBush(const ThornBush& _Other) = delete;
	ThornBush(ThornBush&& _Other) noexcept = delete;
	ThornBush& operator=(const ThornBush& _Other) = delete;
	ThornBush& operator=(ThornBush&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

	void ResetBehavior() override;
	void PlayBehavior() override;

private:
	std::shared_ptr<GameEngineCollision> AttackCol = nullptr;

};


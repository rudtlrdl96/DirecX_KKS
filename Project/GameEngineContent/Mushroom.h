#pragma once
#include "BehaviorObject.h"

class Mushroom : public BehaviorObject
{
private:
	enum class MushroomState
	{
		Idle,
		Active,
		Return
	};

public:
	Mushroom();
	~Mushroom();

	Mushroom(const Mushroom& _Other) = delete;
	Mushroom(Mushroom&& _Other) noexcept = delete;
	Mushroom& operator=(const Mushroom& _Other) = delete;
	Mushroom& operator=(Mushroom&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

	void ResetBehavior() override;
	void PlayBehavior() override;

private:

	std::shared_ptr<class GameEngineCollision> Col = nullptr;

	MushroomState State = MushroomState::Idle;
};


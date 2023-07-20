#pragma once
#include "BehaviorObject.h"

class Pigeon : public BehaviorObject
{
	enum class PigeonState
	{
		Idle,
		Ready,
		Fly,
	};
public:
	Pigeon();
	~Pigeon();

	Pigeon(const Pigeon& _Other) = delete;
	Pigeon(Pigeon&& _Other) noexcept = delete;
	Pigeon& operator=(const Pigeon& _Other) = delete;
	Pigeon& operator=(Pigeon&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	
	void Init() override;
	void ResetBehavior() override;
	void PlayBehavior() override;
private:

	std::shared_ptr<GameEngineCollision> EventCol = nullptr;

	float4 StartPos = float4::Zero;
	float4 EndPos = float4::Zero;

	PigeonState State = PigeonState::Idle;

	float MoveProgress = 0.0f;
};
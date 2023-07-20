#pragma once
#include "BehaviorObject.h"


class Bat : public BehaviorObject
{
private:
	class BatlInfo
	{
	public:
		std::shared_ptr<GameEngineSpriteRenderer> BatRender = nullptr;

		float4 StartPos = float4::Zero;
		float4 EndPos = float4::Zero;
	};
public:
	Bat();
	~Bat();

	Bat(const Bat& _Other) = delete;
	Bat(Bat&& _Other) noexcept = delete;
	Bat& operator=(const Bat& _Other) = delete;
	Bat& operator=(Bat&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

	void ResetBehavior() override;
	void PlayBehavior() override;

private:
	std::vector<BatlInfo> BatRenders;
	std::vector<std::function<void()>> FlyEventFuncs;
	std::shared_ptr<GameEngineCollision> EventCol = nullptr;

	size_t EventIndex = 0;
	size_t RandBatCount = 0;

	bool IsFly = false;

	float MoveProgress = 0.0f;
	float BatFlyCoolTime = 0.0f;
	float MoveSpeed = 1.0f;

	void CreateBat();

};


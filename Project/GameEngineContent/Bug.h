#pragma once
#include "BehaviorObject.h"

class Bug : public BehaviorObject
{
public:
	Bug();
	~Bug();

	Bug(const Bug& _Other) = delete;
	Bug(Bug&& _Other) noexcept = delete;
	Bug& operator=(const Bug& _Other) = delete;
	Bug& operator=(Bug&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

	void Init() override;
	void ResetBehavior() override;
	void PlayBehavior() override;

private:
	ActorViewDir Dir = ActorViewDir::Right;

	float WalkTime = 0.0f;
	float4 CenterPos = float4::Zero;

	void SetViewDir(ActorViewDir _Dir);

};


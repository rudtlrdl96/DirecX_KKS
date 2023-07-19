#pragma once
#include "BehaviorObject.h"

class Mouse : public BehaviorObject
{
private:
	enum class MouseState
	{
		Idle,
		Walk
	};
public:
	Mouse();
	~Mouse();

	Mouse(const Mouse& _Other) = delete;
	Mouse(Mouse&& _Other) noexcept = delete;
	Mouse& operator=(const Mouse& _Other) = delete;
	Mouse& operator=(Mouse&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

	void Init() override;
	void ResetBehavior() override;
	void PlayBehavior() override;

private:
	MouseState State = MouseState::Idle;
	ActorViewDir Dir = ActorViewDir::Right;

	float IdleTime = 0.0f;
	float WalkTime = 0.0f;

	float4 CenterPos = float4::Zero;

	void SetViewDir(ActorViewDir _Dir);

};


#pragma once
#include "BaseContentActor.h"
#include <vector>

class ArmRopeShooter : public BaseContentActor
{
private:
	enum class ArmState
	{
		Wait,
		Shot,
		Hook,
		Reset
	};
public:
	ArmRopeShooter();
	~ArmRopeShooter();

	ArmRopeShooter(const ArmRopeShooter& _Other) = delete;
	ArmRopeShooter(ArmRopeShooter&& _Other) noexcept = delete;
	ArmRopeShooter& operator=(const ArmRopeShooter& _Other) = delete;
	ArmRopeShooter& operator=(ArmRopeShooter&& _Other) noexcept = delete;

	bool CanShot(const float4& _Pos) const;
	void RopeShot(const float4& _Pos);
	void RopeEnd();

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	ArmState State = ArmState::Wait;
	
	int ChainCount = 0;

	float Interval = 0.0f;
	float ShotMaxDistance = 0.0f;

	float ProgressTime = 0.0f;
	float ShotSpeed = 0.0f;
	float HookDistance = 0.0f;

	float4 HookPos = float4::Zero;

	std::shared_ptr<class ArmRopeHook> EndHook;
	std::vector<std::shared_ptr<class ArmRopeChain>> ChainList;
};
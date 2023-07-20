#pragma once
#include "BehaviorObject.h"

class FlagA : public BehaviorObject
{
public:
	FlagA();
	~FlagA();

	FlagA(const FlagA& _Other) = delete;
	FlagA(FlagA&& _Other) noexcept = delete;
	FlagA& operator=(const FlagA& _Other) = delete;
	FlagA& operator=(FlagA&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

	void ResetBehavior() override;
	void PlayBehavior() override;
private:


};


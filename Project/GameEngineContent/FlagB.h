#pragma once
#include "BehaviorObject.h"

class FlagB : public BehaviorObject
{
public:
	FlagB();
	~FlagB();

	FlagB(const FlagB& _Other) = delete;
	FlagB(FlagB&& _Other) noexcept = delete;
	FlagB& operator=(const FlagB& _Other) = delete;
	FlagB& operator=(FlagB&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

	void ResetBehavior() override;
	void PlayBehavior() override;
private:


};


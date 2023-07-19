#pragma once
#include "BehaviorObject.h"

class Spider : public BehaviorObject
{
public:
	Spider();
	~Spider();

	Spider(const Spider& _Other) = delete;
	Spider(Spider&& _Other) noexcept = delete;
	Spider& operator=(const Spider& _Other) = delete;
	Spider& operator=(Spider&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

	void ResetBehavior() override;
	void PlayBehavior() override;

private:


};


#pragma once
#include "BehaviorObject.h"

class Observatory : public BehaviorObject
{
public:
	Observatory();
	~Observatory();

	Observatory(const Observatory& _Other) = delete;
	Observatory(Observatory&& _Other) noexcept = delete;
	Observatory& operator=(const Observatory& _Other) = delete;
	Observatory& operator=(Observatory&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

	void ResetBehavior() override;
	void PlayBehavior() override;
private:


};


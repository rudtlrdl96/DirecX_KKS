#pragma once
#include "BehaviorObject.h"


class Bat : public BehaviorObject
{
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


};


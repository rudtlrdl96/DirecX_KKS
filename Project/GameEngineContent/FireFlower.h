#pragma once
#include "BehaviorObject.h"

class FireFlower : public BehaviorObject
{
public:
	FireFlower();
	~FireFlower();

	FireFlower(const FireFlower& _Other) = delete;
	FireFlower(FireFlower&& _Other) noexcept = delete;
	FireFlower& operator=(const FireFlower& _Other) = delete;
	FireFlower& operator=(FireFlower&& _Other) noexcept = delete;

protected:
	void Start() override;

	void ResetBehavior() override;
	void PlayBehavior() override;

private:


};


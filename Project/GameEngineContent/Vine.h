#pragma once
#include "BehaviorObject.h"

class Vine : public BehaviorObject
{
public:
	Vine();
	~Vine();

	Vine(const Vine& _Other) = delete;
	Vine(Vine&& _Other) noexcept = delete;
	Vine& operator=(const Vine& _Other) = delete;
	Vine& operator=(Vine&& _Other) noexcept = delete;

protected:
	void Start() override;
	
	void ResetBehavior() override;
	void PlayBehavior() override;

private:


};


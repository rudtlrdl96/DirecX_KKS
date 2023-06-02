#pragma once
#include "BehaviorObject.h"

class Mushroom : public BehaviorObject
{
public:
	Mushroom();
	~Mushroom();

	Mushroom(const Mushroom& _Other) = delete;
	Mushroom(Mushroom&& _Other) noexcept = delete;
	Mushroom& operator=(const Mushroom& _Other) = delete;
	Mushroom& operator=(Mushroom&& _Other) noexcept = delete;

protected:
	void Start() override;

	void ResetBehavior() override;
	void PlayBehavior() override;

private:


};


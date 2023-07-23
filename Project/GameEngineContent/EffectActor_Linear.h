#pragma once
#include "EffectActor.h"

class EffectActor_Linear : public EffectActor
{
public:
	EffectActor_Linear();
	~EffectActor_Linear();

	EffectActor_Linear(const EffectActor_Linear& _Other) = delete;
	EffectActor_Linear(EffectActor_Linear&& _Other) noexcept = delete;
	EffectActor_Linear& operator=(const EffectActor_Linear& _Other) = delete;
	EffectActor_Linear& operator=(EffectActor_Linear&& _Other) noexcept = delete;

protected:
	void Start() override;

private:


};


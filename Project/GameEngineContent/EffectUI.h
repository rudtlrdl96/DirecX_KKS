#pragma once
#include "EffectActor.h"

class EffectUI : public EffectActor
{
public:
	EffectUI();
	~EffectUI();

	EffectUI(const EffectUI& _Other) = delete;
	EffectUI(EffectUI&& _Other) noexcept = delete;
	EffectUI& operator=(const EffectUI& _Other) = delete;
	EffectUI& operator=(EffectUI&& _Other) noexcept = delete;

protected:
	void Start() override;
	
private:


};


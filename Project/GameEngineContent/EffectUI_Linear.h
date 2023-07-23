#pragma once
#include "EffectUI.h"

class EffectUI_Linear : public EffectUI
{
public:
	EffectUI_Linear();
	~EffectUI_Linear();

	EffectUI_Linear(const EffectUI_Linear& _Other) = delete;
	EffectUI_Linear(EffectUI_Linear&& _Other) noexcept = delete;
	EffectUI_Linear& operator=(const EffectUI_Linear& _Other) = delete;
	EffectUI_Linear& operator=(EffectUI_Linear&& _Other) noexcept = delete;

protected:
	void Start() override;
	
private:


};


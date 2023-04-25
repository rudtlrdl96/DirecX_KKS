#pragma once
#include "BattleLevel.h"

class HolyCourtyardLevel : public BattleLevel
{
public:
	HolyCourtyardLevel();
	~HolyCourtyardLevel();

	HolyCourtyardLevel(const HolyCourtyardLevel& _Other) = delete;
	HolyCourtyardLevel(HolyCourtyardLevel&& _Other) noexcept = delete;
	HolyCourtyardLevel& operator=(const HolyCourtyardLevel& _Other) = delete;
	HolyCourtyardLevel& operator=(HolyCourtyardLevel&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:


};


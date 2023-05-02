#pragma once
#include "BattleLevel.h"

class HolyCourtyardLevel_Boss : public BattleLevel
{
public:
	HolyCourtyardLevel_Boss();
	~HolyCourtyardLevel_Boss();

	HolyCourtyardLevel_Boss(const HolyCourtyardLevel_Boss& _Other) = delete;
	HolyCourtyardLevel_Boss(HolyCourtyardLevel_Boss&& _Other) noexcept = delete;
	HolyCourtyardLevel_Boss& operator=(const HolyCourtyardLevel_Boss& _Other) = delete;
	HolyCourtyardLevel_Boss& operator=(HolyCourtyardLevel_Boss&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
private:


};


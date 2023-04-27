#pragma once
#include "BattleLevel.h"

class ForestOfHarmonyLevel_Boss : public BattleLevel
{
public:
	ForestOfHarmonyLevel_Boss();
	~ForestOfHarmonyLevel_Boss();

	ForestOfHarmonyLevel_Boss(const ForestOfHarmonyLevel_Boss& _Other) = delete;
	ForestOfHarmonyLevel_Boss(ForestOfHarmonyLevel_Boss&& _Other) noexcept = delete;
	ForestOfHarmonyLevel_Boss& operator=(const ForestOfHarmonyLevel_Boss& _Other) = delete;
	ForestOfHarmonyLevel_Boss& operator=(ForestOfHarmonyLevel_Boss&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:


};


#pragma once
#include "BattleLevel.h"

class ForestOfHarmonyLevel : public BattleLevel
{
public:
	ForestOfHarmonyLevel();
	~ForestOfHarmonyLevel();

	ForestOfHarmonyLevel(const ForestOfHarmonyLevel& _Other) = delete;
	ForestOfHarmonyLevel(ForestOfHarmonyLevel&& _Other) noexcept = delete;
	ForestOfHarmonyLevel& operator=(const ForestOfHarmonyLevel& _Other) = delete;
	ForestOfHarmonyLevel& operator=(ForestOfHarmonyLevel&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	void TextureLoad();

};


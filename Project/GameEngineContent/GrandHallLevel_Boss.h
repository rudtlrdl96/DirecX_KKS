#pragma once
#include "BattleLevel.h"

class GrandHallLevel_Boss : public BattleLevel
{
public:
	GrandHallLevel_Boss();
	~GrandHallLevel_Boss();

	GrandHallLevel_Boss(const GrandHallLevel_Boss& _Other) = delete;
	GrandHallLevel_Boss(GrandHallLevel_Boss&& _Other) noexcept = delete;
	GrandHallLevel_Boss& operator=(const GrandHallLevel_Boss& _Other) = delete;
	GrandHallLevel_Boss& operator=(GrandHallLevel_Boss&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:

};


#pragma once
#include "BattleLevel.h"

class GrandHallLevel : public BattleLevel
{
public:
	GrandHallLevel();
	~GrandHallLevel();

	GrandHallLevel(const GrandHallLevel& _Other) = delete;
	GrandHallLevel(GrandHallLevel&& _Other) noexcept = delete;
	GrandHallLevel& operator=(const GrandHallLevel& _Other) = delete;
	GrandHallLevel& operator=(GrandHallLevel&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

	void AreaClear() override;
private:


};


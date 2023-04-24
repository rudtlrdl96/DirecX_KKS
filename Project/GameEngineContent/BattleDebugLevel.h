#pragma once
#include "BaseDebugLevel.h"

class BattleDebugLevel : public BaseDebugLevel
{
public:
	BattleDebugLevel();
	~BattleDebugLevel();

	BattleDebugLevel(const BattleDebugLevel& _Other) = delete;
	BattleDebugLevel(BattleDebugLevel&& _Other) noexcept = delete;
	BattleDebugLevel& operator=(const BattleDebugLevel& _Other) = delete;
	BattleDebugLevel& operator=(BattleDebugLevel&& _Other) noexcept = delete;

protected:

private:

};


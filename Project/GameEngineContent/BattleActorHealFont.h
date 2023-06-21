#pragma once
#include "BattleActorDamageFont.h"

class BattleActorHealFont : public BattleActorDamageFont
{
public:
	BattleActorHealFont();
	~BattleActorHealFont();

	BattleActorHealFont(const BattleActorHealFont& _Other) = delete;
	BattleActorHealFont(BattleActorHealFont&& _Other) noexcept = delete;
	BattleActorHealFont& operator=(const BattleActorHealFont& _Other) = delete;
	BattleActorHealFont& operator=(BattleActorHealFont&& _Other) noexcept = delete;

protected:
	void Start() override;
	
private:


};


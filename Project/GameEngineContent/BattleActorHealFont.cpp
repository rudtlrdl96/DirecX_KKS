#include "PrecompileHeader.h"
#include "BattleActorHealFont.h"

BattleActorHealFont::BattleActorHealFont()
{
}

BattleActorHealFont::~BattleActorHealFont()
{
}

void BattleActorHealFont::Start()
{
	BattleActorDamageFont::Start();

	FontRigid.SetFricCoeff(0);
	FontRigid.SetGravity(0);
	FontRigid.SetActiveGravity(false);
}

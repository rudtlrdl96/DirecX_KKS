#include "PrecompileHeader.h"
#include "RookieHero.h"

void RookieHero::TempPattern_Enter()
{
	PlayAnimation("RookieHero_Yeah");
}

void RookieHero::TempPattern_Update(float _DeltaTime)
{
	if (true == Render->IsAnimationEnd())
	{
		BossFsm.ChangeState("Idle");
	}
}

void RookieHero::TempPattern_End()
{

}
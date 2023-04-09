#include "ArmRopeChain.h"

ArmRopeChain::ArmRopeChain()
{
}

ArmRopeChain::~ArmRopeChain()
{
}

void ArmRopeChain::LinkChain(GameEngineTransform* _Prev, GameEngineTransform* _Next)
{
	PrevChain = _Prev;
	NextChain = _Next;
}

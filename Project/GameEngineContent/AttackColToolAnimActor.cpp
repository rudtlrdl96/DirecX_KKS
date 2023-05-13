#include "PrecompileHeader.h"
#include "AttackColToolAnimActor.h"

AttackColToolAnimActor::AttackColToolAnimActor()
{
}

AttackColToolAnimActor::~AttackColToolAnimActor()
{
}

void AttackColToolAnimActor::Start()
{
	Render = CreateComponent<GameEngineSpriteRenderer>();
}

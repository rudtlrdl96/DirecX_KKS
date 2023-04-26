#include "PrecompileHeader.h"
#include "PlayerBaseSkull.h"

PlayerBaseSkull::PlayerBaseSkull()
{
}

PlayerBaseSkull::~PlayerBaseSkull()
{
}

void PlayerBaseSkull::Start()
{
	SkullRenderer = CreateComponent<GameEngineSpriteRenderer>();
	
}
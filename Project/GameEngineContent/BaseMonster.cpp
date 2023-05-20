#include "PrecompileHeader.h"
#include "BaseMonster.h"
#include <GameEngineCore/GameEngineCollision.h>

BaseMonster::BaseMonster()
{
}

BaseMonster::~BaseMonster()
{
}

void BaseMonster::Start()
{
	MonsterFsm.Init(this);
	MonsterFsm.AddFSM("Idle", &BaseMonster::Idle_Enter, &BaseMonster::Idle_Update, &BaseMonster::Idle_End);
	MonsterFsm.AddFSM("Walk", &BaseMonster::Walk_Enter, &BaseMonster::Walk_Update, &BaseMonster::Walk_End);
	MonsterFsm.AddFSM("Chasing", &BaseMonster::Chasing_Enter, &BaseMonster::Chasing_Update, &BaseMonster::Chasing_End);
	MonsterFsm.AddFSM("Attack", &BaseMonster::Attack_Enter, &BaseMonster::Attack_Update, &BaseMonster::Attack_End);
	MonsterFsm.AddFSM("Hit", &BaseMonster::Hit_Enter, &BaseMonster::Hit_Update, &BaseMonster::Hit_End);
	MonsterFsm.AddFSM("Death", &BaseMonster::Death_Enter, &BaseMonster::Death_Update, &BaseMonster::Death_End);
}

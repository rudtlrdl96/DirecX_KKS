#include "PrecompileHeader.h"
#include "BattleStage.h"

#include <GameEngineCore/GameEngineLevel.h>

#include "MultiBackground.h"
#include "ObjectManager.h"
#include "Tilemap.h"


BattleStage::BattleStage()
{
}

BattleStage::~BattleStage()
{
}

void BattleStage::Start()
{
	std::shared_ptr<GameEngineLevel> LevelPtr = GetLevel()->Shared_This_dynamic_pointer<GameEngineLevel>();

	TilemapPtr = LevelPtr->CreateActor<Tilemap>();
	ObjectManagerPtr = LevelPtr->CreateActor<ObjectManager>();
}
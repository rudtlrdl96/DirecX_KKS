#include "PrecompileHeader.h"
#include "BattleStage.h"

#include <GameEngineCore/GameEngineLevel.h>

#include "MultiBackground.h"
#include "ObjectManager.h"
#include "Tilemap.h"
#include "GameEventManager.h"


BattleStage::BattleStage()
{
}

BattleStage::~BattleStage()
{
}

void BattleStage::Init(GameEngineSerializer& _LoadSerializer)
{
	TilemapPtr->LoadBin(_LoadSerializer);
	ObjectManagerPtr->LoadBin(_LoadSerializer);
	EventManagerPtr->LoadBin(_LoadSerializer);
}

Tilemap_Meta BattleStage::GetTilemapDesc() const
{
	return TilemapPtr->GetTilemap_DESC();
}

float4 BattleStage::GetSpawnPoint() const
{
	return EventManagerPtr->GetSpawnPoint();
}

void BattleStage::Start()
{
	std::shared_ptr<GameEngineLevel> LevelPtr = GetLevel()->Shared_This_dynamic_pointer<GameEngineLevel>();

	TilemapPtr = LevelPtr->CreateActor<Tilemap>();
	TilemapPtr->GetTransform()->SetParent(GetTransform());

	ObjectManagerPtr = LevelPtr->CreateActor<ObjectManager>();
	ObjectManagerPtr->GetTransform()->SetParent(GetTransform());

	EventManagerPtr = LevelPtr->CreateActor<GameEventManager>();
	EventManagerPtr->GetTransform()->SetParent(GetTransform());
}
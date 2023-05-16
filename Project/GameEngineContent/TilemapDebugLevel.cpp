#include "PrecompileHeader.h"
#include "TilemapDebugLevel.h"

#include "TilemapDebugActor.h"

TilemapDebugLevel::TilemapDebugLevel()
{
}

TilemapDebugLevel::~TilemapDebugLevel()
{
}

void TilemapDebugLevel::Start()
{
	ContentLevel::Start();
	DebugTilemapActorPtr = CreateActor<TilemapDebugActor>();
}

void TilemapDebugLevel::Update(float _DeltaTime)
{
	ContentLevel::Update(_DeltaTime);
}

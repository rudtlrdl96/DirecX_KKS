#pragma once
#include "BaseContentActor.h"
#include <GameEngineCore/GameEngineTileMapRenderer.h>

class TilemapDebugActor : public BaseContentActor
{
public:
	TilemapDebugActor();
	~TilemapDebugActor();

	TilemapDebugActor(const TilemapDebugActor& _Other) = delete;
	TilemapDebugActor(TilemapDebugActor&& _Other) noexcept = delete;
	TilemapDebugActor& operator=(const TilemapDebugActor& _Other) = delete;
	TilemapDebugActor& operator=(TilemapDebugActor&& _Other) noexcept = delete;

protected:
	void Start() override;

private:
	std::shared_ptr<GameEngineTileMapRenderer> TilemapRender = nullptr;

};


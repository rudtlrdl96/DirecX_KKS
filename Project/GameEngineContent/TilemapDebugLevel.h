#pragma once
#include "ContentLevel.h"

class TilemapDebugLevel : public ContentLevel
{
public:
	TilemapDebugLevel();
	~TilemapDebugLevel();

	TilemapDebugLevel(const TilemapDebugLevel& _Other) = delete;
	TilemapDebugLevel(TilemapDebugLevel&& _Other) noexcept = delete;
	TilemapDebugLevel& operator=(const TilemapDebugLevel& _Other) = delete;
	TilemapDebugLevel& operator=(TilemapDebugLevel&& _Other) noexcept = delete;

protected:
	
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	std::shared_ptr<class TilemapDebugActor> DebugTilemapActorPtr = nullptr;


};


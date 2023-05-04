#pragma once
#include "BaseContentActor.h"

class TilemapHoverRenderActor : public BaseContentActor
{
public:
	TilemapHoverRenderActor();
	~TilemapHoverRenderActor();

	TilemapHoverRenderActor(const TilemapHoverRenderActor& _Other) = delete;
	TilemapHoverRenderActor(TilemapHoverRenderActor&& _Other) noexcept = delete;
	TilemapHoverRenderActor& operator=(const TilemapHoverRenderActor& _Other) = delete;
	TilemapHoverRenderActor& operator=(TilemapHoverRenderActor&& _Other) noexcept = delete;

	void HoverOn();
	void HoverOff();

protected:
	void Start() override;

private:
	std::shared_ptr<GameEngineSpriteRenderer> TilemapHoverRender = nullptr;


};


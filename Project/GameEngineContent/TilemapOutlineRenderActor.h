#pragma once
#include "BaseContentActor.h"

class TilemapOutlineRenderActor : public BaseContentActor
{
public:
	TilemapOutlineRenderActor();
	~TilemapOutlineRenderActor();

	TilemapOutlineRenderActor(const TilemapOutlineRenderActor& _Other) = delete;
	TilemapOutlineRenderActor(TilemapOutlineRenderActor&& _Other) noexcept = delete;
	TilemapOutlineRenderActor& operator=(const TilemapOutlineRenderActor& _Other) = delete;
	TilemapOutlineRenderActor& operator=(TilemapOutlineRenderActor&& _Other) noexcept = delete;

	void SetSize(const float4& _Size);

protected:
	void Start() override;

private:
	std::shared_ptr<GameEngineSpriteRenderer> Render = nullptr;

};


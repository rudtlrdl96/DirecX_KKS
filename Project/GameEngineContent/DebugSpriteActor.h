#pragma once
#include "BaseContentActor.h"

class DebugSpriteActor : public BaseContentActor
{
public:
	DebugSpriteActor();
	~DebugSpriteActor();

	DebugSpriteActor(const DebugSpriteActor& _Other) = delete;
	DebugSpriteActor(DebugSpriteActor&& _Other) noexcept = delete;
	DebugSpriteActor& operator=(const DebugSpriteActor& _Other) = delete;
	DebugSpriteActor& operator=(DebugSpriteActor&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	std::shared_ptr<GameEngineSpriteRenderer> SpriteRender0 = nullptr;
	std::shared_ptr<GameEngineSpriteRenderer> SpriteRender1 = nullptr;
	std::shared_ptr<GameEngineSpriteRenderer> SpriteRender2 = nullptr;
	float MoveSpeed = 200.0f;
	float RotSpeed = 360.0f;
};
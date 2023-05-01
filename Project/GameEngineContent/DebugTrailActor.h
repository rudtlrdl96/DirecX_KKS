#pragma once
#include "BaseContentActor.h"

class DebugTrailActor : public BaseContentActor
{
public:
	DebugTrailActor();
	~DebugTrailActor();

	DebugTrailActor(const DebugTrailActor& _Other) = delete;
	DebugTrailActor(DebugTrailActor&& _Other) noexcept = delete;
	DebugTrailActor& operator=(const DebugTrailActor& _Other) = delete;
	DebugTrailActor& operator=(DebugTrailActor&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	std::shared_ptr<class CaptureTrail> Trail = nullptr;
	std::shared_ptr<GameEngineSpriteRenderer> MainRender = nullptr;
};


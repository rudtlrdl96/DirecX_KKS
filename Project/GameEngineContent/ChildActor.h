#pragma once
#include <GameEngineCore/GameEngineActor.h>

class ChildActor : public GameEngineActor
{
public:
	ChildActor();
	~ChildActor();

	ChildActor(const ChildActor& _Other) = delete;
	ChildActor(ChildActor&& _Other) noexcept = delete;
	ChildActor& operator=(const ChildActor& _Other) = delete;
	ChildActor& operator=(ChildActor&& _Other) noexcept = delete;

protected:

	void Start() override;
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override;

private:
	float Angle = 0.0f;
	float Scale = 1.0f;

};
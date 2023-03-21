#pragma once
#include <GameEngineCore/GameEngineActor.h>

class ChildActor;
class VertexActor : public GameEngineActor
{
	friend class ChildActor;
public:
	VertexActor();
	~VertexActor();

	VertexActor(const VertexActor& _Other) = delete;
	VertexActor(VertexActor&& _Other) noexcept = delete;
	VertexActor& operator=(const VertexActor& _Other) = delete;
	VertexActor& operator=(VertexActor&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override;

private:
	float Angle = 0.0f;
	float Scale = 1.0f;

	std::shared_ptr<ChildActor> ChildPtr = nullptr;
};
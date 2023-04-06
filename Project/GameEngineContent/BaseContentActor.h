#pragma once
#include <memory>
#include <GameEngineCore/GameEngineActor.h>


class GameEngineRenderer;
class BaseContentActor : public GameEngineActor
{
public:
	BaseContentActor();
	~BaseContentActor();

	BaseContentActor(const BaseContentActor& _Other) = delete;
	BaseContentActor(BaseContentActor&& _Other) noexcept = delete;
	BaseContentActor& operator=(const BaseContentActor& _Other) = delete;
	BaseContentActor& operator=(BaseContentActor&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	std::shared_ptr<GameEngineRenderer> RenderA = nullptr;
	std::shared_ptr<GameEngineRenderer> RenderB = nullptr;
	std::shared_ptr<GameEngineRenderer> RenderC = nullptr;
};
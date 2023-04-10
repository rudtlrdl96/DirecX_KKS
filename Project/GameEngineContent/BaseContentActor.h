#pragma once
#include <GameEngineCore/GameEngineActor.h>

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

private:
};
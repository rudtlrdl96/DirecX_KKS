#pragma once
#include <GameEngineCore/GameEngineActor.h>
#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include "ClassFSM.h"

class BaseContentActor : public GameEngineActor
{

public:
	BaseContentActor();
	~BaseContentActor();

	BaseContentActor(const BaseContentActor& _Other) = delete;
	BaseContentActor(BaseContentActor&& _Other) noexcept = delete;
	BaseContentActor& operator=(const BaseContentActor& _Other) = delete;
	BaseContentActor& operator=(BaseContentActor&& _Other) noexcept = delete;

	inline UINT GetActorCode() const
	{
		return Code;
	}

	virtual void ShowGUI() {}

protected:

private:
	const UINT Code;
};
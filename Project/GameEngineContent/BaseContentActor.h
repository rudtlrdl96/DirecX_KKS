#pragma once
#include <GameEngineCore/GameEngineActor.h>
#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include "ContentSpriteRenderer.h"
#include "ClassFSM.h"
#include "AnimationAttackMetaData.h"

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

	class ContentLevel* GetContentLevel() const;

	virtual void CallUseEvent() {}

	bool IsFocus()
	{
		return  DynamicThis<BaseContentActor>() == IsFocusPtr;
	}

	inline void FocusOn()
	{
		IsFocusPtr = DynamicThis<BaseContentActor>();
	}

	static void FocusOff()
	{
		IsFocusPtr = nullptr;
	}

protected:

private:
	const UINT Code;

	static std::shared_ptr<BaseContentActor> IsFocusPtr;
};
#pragma once
#include "BaseContentActor.h"

class DebugBoxActor : public BaseContentActor
{
public:
	DebugBoxActor();
	~DebugBoxActor();

	DebugBoxActor(const DebugBoxActor& _Other) = delete;
	DebugBoxActor(DebugBoxActor&& _Other) noexcept = delete;
	DebugBoxActor& operator=(const DebugBoxActor& _Other) = delete;
	DebugBoxActor& operator=(DebugBoxActor&& _Other) noexcept = delete;

protected:
	void Start() override;
	
private:	
	class std::shared_ptr<GameEngineRenderer> BoxRender = nullptr;
};


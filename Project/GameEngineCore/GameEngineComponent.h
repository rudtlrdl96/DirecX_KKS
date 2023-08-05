#pragma once
#include "GameEngineActor.h"

class GameEngineComponent : public GameEngineObject
{
	friend class GameEngineActor;

public:
	GameEngineComponent();
	~GameEngineComponent();

	GameEngineComponent(const GameEngineComponent& _Other) = delete;
	GameEngineComponent(GameEngineComponent&& _Other) noexcept = delete;
	GameEngineComponent& operator=(const GameEngineComponent& _Other) = delete;
	GameEngineComponent& operator=(GameEngineComponent&& _Other) noexcept = delete;

	class GameEngineActor* GetActor() 
	{
		return Actor;
	}

protected:

private:
	class GameEngineActor* Actor;

	void SetActor(class GameEngineActor* _Actor);

};


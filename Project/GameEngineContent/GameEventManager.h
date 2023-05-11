#pragma once
#include "BaseContentActor.h"

class GameEventManager : public BaseContentActor
{
public:
	GameEventManager();
	~GameEventManager();

	GameEventManager(const GameEventManager& _Other) = delete;
	GameEventManager(GameEventManager&& _Other) noexcept = delete;
	GameEventManager& operator=(const GameEventManager& _Other) = delete;
	GameEventManager& operator=(GameEventManager&& _Other) noexcept = delete;

	void SaveBin(GameEngineSerializer& _SaveSerializer);
	void LoadBin(GameEngineSerializer& _LoadSerializer);

	void ShowGUI() override;

protected:
	
private:
	float4 SpawnPoint = float4::Zero;


};


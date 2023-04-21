#pragma once
#include <GameEngineCore/GameEngineLevel.h>

class BaseDebugLevel : public GameEngineLevel
{
public:
	BaseDebugLevel();
	~BaseDebugLevel();

	BaseDebugLevel(const BaseDebugLevel& _Other) = delete;
	BaseDebugLevel(BaseDebugLevel&& _Other) noexcept = delete;
	BaseDebugLevel& operator=(const BaseDebugLevel& _Other) = delete;
	BaseDebugLevel& operator=(BaseDebugLevel&& _Other) noexcept = delete;

protected:
	
private:


};


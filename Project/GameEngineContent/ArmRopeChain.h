#pragma once
#include "BaseContentActor.h"

class ArmRopeChain : public BaseContentActor
{
public:
	ArmRopeChain();
	~ArmRopeChain();

	ArmRopeChain(const ArmRopeChain& _Other) = delete;
	ArmRopeChain(ArmRopeChain&& _Other) noexcept = delete;
	ArmRopeChain& operator=(const ArmRopeChain& _Other) = delete;
	ArmRopeChain& operator=(ArmRopeChain&& _Other) noexcept = delete;

	void LinkChain(GameEngineTransform* _Prev, GameEngineTransform* _Next);

	//void SetRenderPos();
	//void ChainRenderOn();
	//void ChainRenderOff();
	//void PhysicsUpdate();
protected:

private:
	GameEngineTransform* PrevChain = nullptr;
	GameEngineTransform* NextChain = nullptr;
};
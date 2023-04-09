#pragma once
#include "BaseContentActor.h"

class ArmRopeShooter : public BaseContentActor
{
public:
	ArmRopeShooter();
	~ArmRopeShooter();

	ArmRopeShooter(const ArmRopeShooter& _Other) = delete;
	ArmRopeShooter(ArmRopeShooter&& _Other) noexcept = delete;
	ArmRopeShooter& operator=(const ArmRopeShooter& _Other) = delete;
	ArmRopeShooter& operator=(ArmRopeShooter&& _Other) noexcept = delete;

protected:

private:

};
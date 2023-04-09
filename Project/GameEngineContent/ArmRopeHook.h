#pragma once
#include "BaseContentActor.h"

class ArmRopeHook : public BaseContentActor
{
public:
	ArmRopeHook();
	~ArmRopeHook();

	ArmRopeHook(const ArmRopeHook& _Other) = delete;
	ArmRopeHook(ArmRopeHook&& _Other) noexcept = delete;
	ArmRopeHook& operator=(const ArmRopeHook& _Other) = delete;
	ArmRopeHook& operator=(ArmRopeHook&& _Other) noexcept = delete;

protected:

private:

};
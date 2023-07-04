#pragma once
#include "BaseGear.h"

class SkullGear : public BaseGear
{
public:
	SkullGear();
	~SkullGear();

	SkullGear(const SkullGear& _Other) = delete;
	SkullGear(SkullGear&& _Other) noexcept = delete;
	SkullGear& operator=(const SkullGear& _Other) = delete;
	SkullGear& operator=(SkullGear&& _Other) noexcept = delete;

protected:
	void Start() override;

private:


};


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

	void Init(size_t _SkullIndex);

protected:
	void Start() override;
	void UseGear() override;

private:
	size_t SkullIndex = 0;


};
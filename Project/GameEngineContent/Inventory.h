#pragma once
#include "PlayerBaseSkull.h"

class Inventory
{
public:
	static void SetMainSkull(SkullData _SkullData);
	static void SetSubSkull(SkullData _SkullData);

	static void ResetSkull();

	static const SkullData& GetMainSkull();
	static const SkullData& GetSubSkull();

	static void SwapSkull();

protected:
	
private:
	static SkullData MainSkullData;
	static SkullData SubSkullData;

	Inventory();
	~Inventory();

	Inventory(const Inventory& _Other) = delete;
	Inventory(Inventory&& _Other) noexcept = delete;
	Inventory& operator=(const Inventory& _Other) = delete;
	Inventory& operator=(Inventory&& _Other) noexcept = delete;
};


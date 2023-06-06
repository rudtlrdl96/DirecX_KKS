#pragma once
#include "BaseNPC.h"

class SueKeleton : public BaseNPC
{
public:
	SueKeleton();
	~SueKeleton();

	SueKeleton(const SueKeleton& _Other) = delete;
	SueKeleton(SueKeleton&& _Other) noexcept = delete;
	SueKeleton& operator=(const SueKeleton& _Other) = delete;
	SueKeleton& operator=(SueKeleton&& _Other) noexcept = delete;

protected:
	void Start() override;

private:
	void SpriteLoad() override;


};


#pragma once
#include "BaseNPC.h"

class CastleFoxHunterNPC : public BaseNPC
{
public:
	CastleFoxHunterNPC();
	~CastleFoxHunterNPC();

	CastleFoxHunterNPC(const CastleFoxHunterNPC& _Other) = delete;
	CastleFoxHunterNPC(CastleFoxHunterNPC&& _Other) noexcept = delete;
	CastleFoxHunterNPC& operator=(const CastleFoxHunterNPC& _Other) = delete;
	CastleFoxHunterNPC& operator=(CastleFoxHunterNPC&& _Other) noexcept = delete;

protected:
	void Start() override;

	void SpriteLoad() override;

private:


};


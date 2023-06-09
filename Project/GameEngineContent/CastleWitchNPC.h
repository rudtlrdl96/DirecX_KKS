#pragma once
#include "BaseNPC.h"

class CastleWitchNPC : public BaseNPC
{
public:
	CastleWitchNPC();
	~CastleWitchNPC();

	CastleWitchNPC(const CastleWitchNPC& _Other) = delete;
	CastleWitchNPC(CastleWitchNPC&& _Other) noexcept = delete;
	CastleWitchNPC& operator=(const CastleWitchNPC& _Other) = delete;
	CastleWitchNPC& operator=(CastleWitchNPC&& _Other) noexcept = delete;

protected:
	void Start() override;
	void SpriteLoad() override;
	
private:

};


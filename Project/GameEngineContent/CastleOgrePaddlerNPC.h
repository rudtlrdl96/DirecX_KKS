#pragma once
#include "BaseNPC.h"

class CastleOgrePaddlerNPC : public BaseNPC
{
public:
	CastleOgrePaddlerNPC();
	~CastleOgrePaddlerNPC();

	CastleOgrePaddlerNPC(const CastleOgrePaddlerNPC& _Other) = delete;
	CastleOgrePaddlerNPC(CastleOgrePaddlerNPC&& _Other) noexcept = delete;
	CastleOgrePaddlerNPC& operator=(const CastleOgrePaddlerNPC& _Other) = delete;
	CastleOgrePaddlerNPC& operator=(CastleOgrePaddlerNPC&& _Other) noexcept = delete;

protected:
	void Start() override;

	void SpriteLoad() override;

private:


};


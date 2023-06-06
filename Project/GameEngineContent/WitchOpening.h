#pragma once
#include "BaseNPC.h"

class WitchOpening : public BaseNPC
{
public:
	WitchOpening();
	~WitchOpening();

	WitchOpening(const WitchOpening& _Other) = delete;
	WitchOpening(WitchOpening&& _Other) noexcept = delete;
	WitchOpening& operator=(const WitchOpening& _Other) = delete;
	WitchOpening& operator=(WitchOpening&& _Other) noexcept = delete;

protected:
	void Start() override;
	
private:
	void SpriteLoad() override;


};


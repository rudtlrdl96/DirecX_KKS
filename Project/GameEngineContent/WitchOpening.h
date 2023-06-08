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
	void Update(float _DeltaTime) override;

	void ResetBehavior() override;
	void PlayBehavior() override;
		
private:
	void SpriteLoad() override;


};


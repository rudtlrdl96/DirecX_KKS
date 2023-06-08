#pragma once
#include "BaseNPC.h"
#include "WitchCage.h"

class WitchOpening : public BaseNPC
{
public:
	WitchOpening();
	~WitchOpening();

	WitchOpening(const WitchOpening& _Other) = delete;
	WitchOpening(WitchOpening&& _Other) noexcept = delete;
	WitchOpening& operator=(const WitchOpening& _Other) = delete;
	WitchOpening& operator=(WitchOpening&& _Other) noexcept = delete;

	void On() override;
	void Off() override;
	void Death() override;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

	void ResetBehavior() override;
	void PlayBehavior() override;
		
private:
	std::shared_ptr<WitchCage> CagePtr = nullptr;
	std::shared_ptr<GameEngineCollision> PlayerFindCol = nullptr;
	std::shared_ptr<GameEngineCollision> GroundCol = nullptr;

	std::shared_ptr<class Player> PlayerPtr = nullptr;

	bool IsPolymorpEnd = false;
	float WalkSpeed = 200.0f;
	float Fall = 0.0f;

	void SpriteLoad() override;

};


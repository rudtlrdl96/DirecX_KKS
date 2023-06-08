#pragma once
#include "BaseNPC.h"


class Witch_CatFollow : public BaseNPC
{
public:
	Witch_CatFollow();
	~Witch_CatFollow();

	Witch_CatFollow(const Witch_CatFollow& _Other) = delete;
	Witch_CatFollow(Witch_CatFollow&& _Other) noexcept = delete;
	Witch_CatFollow& operator=(const Witch_CatFollow& _Other) = delete;
	Witch_CatFollow& operator=(Witch_CatFollow&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

	void ResetBehavior() override;
	void PlayBehavior() override;
	
private:
	std::shared_ptr<GameEngineCollision> PlayerFindCol = nullptr;
	std::shared_ptr<GameEngineCollision> GroundCol = nullptr;

	std::shared_ptr<class Player> PlayerPtr = nullptr;

	float WalkSpeed = 200.0f;
	float Fall = 0.0f;
	
	void SpriteLoad() override;

};


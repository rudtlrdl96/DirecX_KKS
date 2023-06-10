#pragma once
#include "BossMonster.h"

class RookieHero : public BossMonster
{
public:
	RookieHero();
	~RookieHero();

	RookieHero(const RookieHero& _Other) = delete;
	RookieHero(RookieHero&& _Other) noexcept = delete;
	RookieHero& operator=(const RookieHero& _Other) = delete;
	RookieHero& operator=(RookieHero&& _Other) noexcept = delete;

	void Death() override;

protected:
	std::shared_ptr<GameEngineCollision> EventCol = nullptr;
	std::shared_ptr<GameEngineCollision> Battle_Platform_Left = nullptr;
	std::shared_ptr<GameEngineCollision> Battle_Platform_Right = nullptr;

	bool IsPlayerEnter = false;

	void Start() override;
	void Update(float _DeltaTime) override;
	 
	void DataLoad() override;
	void SpriteLoad() override;

	void SelectPattern() override;

	void TempPattern_Enter();
	void TempPattern_Update(float _DeltaTime);
	void TempPattern_End();


};


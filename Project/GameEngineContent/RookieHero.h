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

protected:
	
private:


};


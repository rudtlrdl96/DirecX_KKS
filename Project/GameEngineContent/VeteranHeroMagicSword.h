#pragma once
#include "Projectile.h"

class VeteranHeroMagicSword : public Projectile
{
public:
	VeteranHeroMagicSword();
	~VeteranHeroMagicSword();

	VeteranHeroMagicSword(const VeteranHeroMagicSword& _Other) = delete;
	VeteranHeroMagicSword(VeteranHeroMagicSword&& _Other) noexcept = delete;
	VeteranHeroMagicSword& operator=(const VeteranHeroMagicSword& _Other) = delete;
	VeteranHeroMagicSword& operator=(VeteranHeroMagicSword&& _Other) noexcept = delete;

	void FadeDeath();

protected:
	void Update(float _DeltaTime) override;

private:


};


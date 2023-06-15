#pragma once
#include "Projectile.h"

class VeteranHeroEnergyBall : public Projectile
{
public:
	VeteranHeroEnergyBall();
	~VeteranHeroEnergyBall();

	VeteranHeroEnergyBall(const VeteranHeroEnergyBall& _Other) = delete;
	VeteranHeroEnergyBall(VeteranHeroEnergyBall&& _Other) noexcept = delete;
	VeteranHeroEnergyBall& operator=(const VeteranHeroEnergyBall& _Other) = delete;
	VeteranHeroEnergyBall& operator=(VeteranHeroEnergyBall&& _Other) noexcept = delete;

	void ShotProjectile(const ProjectileParameter& _Parameter) override;

protected:
	void Update(float _DeltaTime) override;
	
private:
	bool TrackingStart = false;
	float TrackingWaitTime = 0.0f;

};


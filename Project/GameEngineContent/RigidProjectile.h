#pragma once
#include "Projectile.h"
#include "Rigidbody2D.h"

class RigidProjectile : public Projectile
{
public:
	RigidProjectile();
	~RigidProjectile();

	RigidProjectile(const RigidProjectile& _Other) = delete;
	RigidProjectile(RigidProjectile&& _Other) noexcept = delete;
	RigidProjectile& operator=(const RigidProjectile& _Other) = delete;
	RigidProjectile& operator=(RigidProjectile&& _Other) noexcept = delete;

	void InitRigd(float _MaxSpeed, float _FricCoeff, float _Mass = 1.0f);

protected:
	void Update(float _DeltaTime) override;

	
private:
	Rigidbody2D ProjectileRigidbody;

};


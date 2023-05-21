#pragma once
#include "BaseContentActor.h"

class ProjectileParameter
{
public:
	const std::string_view& EffectName = "";
	
	float4 Pos = float4::Zero;
	float4 Dir = float4::Up;
	float Speed = 100.0f;
	float LiveTime = 1.0f;

	std::function<void()> ColEvent = nullptr;
};

class Projectile : public BaseContentActor
{
public:
	Projectile();
	~Projectile();

	Projectile(const Projectile& _Other) = delete;
	Projectile(Projectile&& _Other) noexcept = delete;
	Projectile& operator=(const Projectile& _Other) = delete;
	Projectile& operator=(Projectile&& _Other) noexcept = delete;

	void ShotProjectile(const ProjectileParameter& _Parameter);

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	float4 Dir = float4::Zero;

	float LiveTime = 1.0f;
	float Speed = 100.0f;
};


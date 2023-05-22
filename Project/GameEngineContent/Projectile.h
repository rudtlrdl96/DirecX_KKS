#pragma once
#include "BaseContentActor.h"
#include "ColEnterCheck.h"

class ProjectileParameter
{
public:
	const std::string_view& EffectName = "";
	
	float4 Pos = float4::Zero;
	float4 Dir = float4::Up;
	float4 ColScale = float4::Zero;

	int ColOrder = -1;

	float Speed = 100.0f;
	float LiveTime = 1.0f;

	std::function<void(std::shared_ptr<class BaseContentActor>)> EnterEvent = nullptr;
	std::function<void(std::shared_ptr<class BaseContentActor>)> UpdateEvent = nullptr;
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
	std::shared_ptr<class GameEngineCollision> ProjectileCol = nullptr;

	float4 Dir = float4::Zero;

	int ColOrder = -1;

	float LiveTime = 1.0f;
	float Speed = 100.0f;

	std::function<void(std::shared_ptr<class BaseContentActor>)> EnterEvent = nullptr;
	std::function<void(std::shared_ptr<class BaseContentActor>)> UpdateEvent = nullptr;

	std::vector<std::shared_ptr<GameEngineCollision>> ColDatas;
	std::map<UINT, std::shared_ptr<BaseContentActor>> ColBuffers;
};
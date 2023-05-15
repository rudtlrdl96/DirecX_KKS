#pragma once
#include "BaseContentActor.h"

enum class AreaParticle
{
	Opening,
	Castle,
	ForestOfHarmony,
	GrandHall,
};

class ParticleAreaParameter
{
public:
	AreaParticle Type = AreaParticle::Castle;

	float4 Center = float4::Zero;
	float4 Size = float4::Zero;

	float4 RandRot = float4::Zero;
	float4 WindDir = float4::Down;

	float MinWindDiff = 1.0f;
	float MaxWindDiff = 1.0f;


	float CreateMinTime = 0.0f;
	float CreateMaxTime = 1.0f;
};

class ParticleArea : public BaseContentActor
{
public:

public:
	ParticleArea();
	~ParticleArea();

	ParticleArea(const ParticleArea& _Other) = delete;
	ParticleArea(ParticleArea&& _Other) noexcept = delete;
	ParticleArea& operator=(const ParticleArea& _Other) = delete;
	ParticleArea& operator=(ParticleArea&& _Other) noexcept = delete;

	inline void Init(const ParticleAreaParameter& _Parameter)
	{
		Parameter = _Parameter;

		GetTransform()->SetLocalPosition(Parameter.Center);
	}

protected:
	void Update(float _DeltaTime) override;

private:
	std::list<std::shared_ptr<class MapParticleBase>> ParticleActors;

	ParticleAreaParameter Parameter = ParticleAreaParameter();

	float CreateCoolTime = 0.0f;
	float NextCreateTime = 0.0f;

	std::shared_ptr<MapParticleBase> CreateParticle();
};


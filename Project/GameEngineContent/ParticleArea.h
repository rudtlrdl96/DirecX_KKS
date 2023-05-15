#pragma once
#include "BaseContentActor.h"

enum class ParticleAreaType
{
	Opening,
	Castle,
	ForestOfHarmony,
	GrandHall,
};

class ParticleAreaMetaData
{
public:
	ParticleAreaType Type = ParticleAreaType::Castle;

	float4 Center = float4::Zero;
	float4 Size = float4::Zero;

	bool IsTopSpawn = true;

	float4 MinWindDir = float4::Down;
	float4 MaxWindDir = float4::Down;
	
	float4 MinRandRot = float4::Zero;
	float4 MaxRandRot = float4::Zero;

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

	inline void Init(const ParticleAreaMetaData& _Parameter)
	{
		Parameter = _Parameter;

		GetTransform()->SetLocalPosition(Parameter.Center);
	}

	void SaveBin(GameEngineSerializer& _SaveSerializer);
	static ParticleAreaMetaData LoadBin(GameEngineSerializer& _LoadSerializer);

protected:
	void Update(float _DeltaTime) override;

private:
	std::list<std::shared_ptr<class MapParticleBase>> ParticleActors;

	ParticleAreaMetaData Parameter = ParticleAreaMetaData();

	float CreateCoolTime = 0.0f;
	float NextCreateTime = 0.0f;

	std::shared_ptr<MapParticleBase> CreateParticle();
};


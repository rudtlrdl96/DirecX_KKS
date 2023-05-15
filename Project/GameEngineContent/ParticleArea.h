#pragma once
#include "BaseContentActor.h"

enum class ParticleAreaType
{
	Opening,
	Castle,
	ForestOfHarmony,
	ForestOfHarmony_Blue,
	GrandHall,
};

class ParticleAreaMetaData
{
public:
	ParticleAreaType Type = ParticleAreaType::Castle;

	float4 Center = float4::Zero;
	float4 Size = float4(100.0f, 100.0f, 1.0f);

	bool IsTopSpawn = true;

	float4 MinWindDir = float4(0.0f, -30.0f, 0.0f);
	float4 MaxWindDir = float4(0.0f, -30.0f, 0.0f);
	
	float4 MinRandRot = float4::Zero;
	float4 MaxRandRot = float4::Zero;

	float CreateMinTime = 0.1f;
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

	inline void Init(const ParticleAreaMetaData& _MetaData)
	{
		MetaData = _MetaData;

		GetTransform()->SetLocalPosition(MetaData.Center);
	}

	inline ParticleAreaMetaData& GetMetaData()
	{
		return MetaData;
	}

	void SaveBin(GameEngineSerializer& _SaveSerializer);
	static ParticleAreaMetaData LoadBin(GameEngineSerializer& _LoadSerializer);

protected:
	void Update(float _DeltaTime) override;

private:
	std::list<std::shared_ptr<class MapParticleBase>> ParticleActors;

	ParticleAreaMetaData MetaData = ParticleAreaMetaData();

	float CreateCoolTime = 0.0f;
	float NextCreateTime = 0.0f;

	std::shared_ptr<MapParticleBase> CreateParticle();
};


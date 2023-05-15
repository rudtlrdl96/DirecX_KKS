#include "PrecompileHeader.h"
#include "ParticleArea.h"

#include <GameEngineCore/GameEngineLevel.h>

#include "MapParticleBase.h"
#include "ForestOfHarmony_MapParticle.h"
#include "Opening_MapParticle.h"

ParticleArea::ParticleArea()
{
}

ParticleArea::~ParticleArea()
{
}

void ParticleArea::SaveBin(GameEngineSerializer& _SaveSerializer)
{
	_SaveSerializer.Write(&Parameter.Type, sizeof(AreaParticle));
	_SaveSerializer.Write(&Parameter.Center, sizeof(float4));
	_SaveSerializer.Write(&Parameter.Size, sizeof(float4));
	_SaveSerializer.Write(&Parameter.IsTopSpawn, sizeof(bool));
	_SaveSerializer.Write(&Parameter.MinWindDir, sizeof(float4));
	_SaveSerializer.Write(&Parameter.MaxWindDir, sizeof(float4));
	_SaveSerializer.Write(&Parameter.MinRandRot, sizeof(float4));
	_SaveSerializer.Write(&Parameter.MaxRandRot, sizeof(float4));
	_SaveSerializer.Write(&Parameter.CreateMinTime, sizeof(float));
	_SaveSerializer.Write(&Parameter.CreateMaxTime, sizeof(float));
}

ParticleAreaParameter ParticleArea::LoadBin(GameEngineSerializer& _LoadSerializer)
{
	ParticleAreaParameter LoadParameter = ParticleAreaParameter();

	_LoadSerializer.Read(&LoadParameter.Type, sizeof(AreaParticle));
	_LoadSerializer.Read(&LoadParameter.Center, sizeof(float4));
	_LoadSerializer.Read(&LoadParameter.Size, sizeof(float4));
	_LoadSerializer.Read(&LoadParameter.IsTopSpawn, sizeof(bool));
	_LoadSerializer.Read(&LoadParameter.MinWindDir, sizeof(float4));
	_LoadSerializer.Read(&LoadParameter.MaxWindDir, sizeof(float4));
	_LoadSerializer.Read(&LoadParameter.MinRandRot, sizeof(float4));
	_LoadSerializer.Read(&LoadParameter.MaxRandRot, sizeof(float4));
	_LoadSerializer.Read(&LoadParameter.CreateMinTime, sizeof(float));
	_LoadSerializer.Read(&LoadParameter.CreateMaxTime, sizeof(float));

	return LoadParameter;
}

void ParticleArea::Update(float _DeltaTime)
{
	CreateCoolTime += _DeltaTime;

	GameEngineRandom& Rand = GameEngineRandom::MainRandom;

	if (CreateCoolTime >= NextCreateTime)
	{
		std::shared_ptr <MapParticleBase> NewParticle = CreateParticle();

		if (nullptr == NewParticle)
		{
			MsgAssert_Rtti<ParticleArea>(" - 파티클 생성에 실패했습니다");
			return;
		}

		NewParticle->GetTransform()->SetParent(GetTransform());

		float4 SpawnPostion = float4::Zero;

		SpawnPostion.x = Rand.RandomFloat(-Parameter.Size.hx(), Parameter.Size.hx());

		if (true == Parameter.IsTopSpawn)
		{
			SpawnPostion.y = Parameter.Size.hy() * 1.05f;
		}
		else
		{
			SpawnPostion.y = -Parameter.Size.hy() * 1.05f;
		}

		NewParticle->GetTransform()->SetLocalPosition(SpawnPostion);

		float4 RandomWind = float4::Zero;

		RandomWind.x = Rand.RandomFloat(
			(Parameter.MinWindDir.x < Parameter.MaxWindDir.x) ? Parameter.MinWindDir.x : Parameter.MaxWindDir.x,
			(Parameter.MinWindDir.x >= Parameter.MaxWindDir.x) ? Parameter.MinWindDir.x : Parameter.MaxWindDir.x);
		RandomWind.y = Rand.RandomFloat(
			(Parameter.MinWindDir.y < Parameter.MaxWindDir.y) ? Parameter.MinWindDir.y : Parameter.MaxWindDir.y,
			(Parameter.MinWindDir.y >= Parameter.MaxWindDir.y) ? Parameter.MinWindDir.y : Parameter.MaxWindDir.y);
		RandomWind.z = Rand.RandomFloat(
			(Parameter.MinWindDir.z < Parameter.MaxWindDir.z) ? Parameter.MinWindDir.z : Parameter.MaxWindDir.z,
			(Parameter.MinWindDir.z >= Parameter.MaxWindDir.z) ? Parameter.MinWindDir.z : Parameter.MaxWindDir.z);

		float4 RandomRot = float4::Zero;

		RandomRot.x = Rand.RandomFloat(
			(Parameter.MinRandRot.x < Parameter.MaxRandRot.x) ? Parameter.MinRandRot.x : Parameter.MaxRandRot.x,
			(Parameter.MinRandRot.x >= Parameter.MaxRandRot.x) ? Parameter.MinRandRot.x : Parameter.MaxRandRot.x);
		RandomRot.y = Rand.RandomFloat(
			(Parameter.MinRandRot.y < Parameter.MaxRandRot.y) ? Parameter.MinRandRot.y : Parameter.MaxRandRot.y,
			(Parameter.MinRandRot.y >= Parameter.MaxRandRot.y) ? Parameter.MinRandRot.y : Parameter.MaxRandRot.y);
		RandomRot.z = Rand.RandomFloat(
			(Parameter.MinRandRot.z < Parameter.MaxRandRot.z) ? Parameter.MinRandRot.z : Parameter.MaxRandRot.z,
			(Parameter.MinRandRot.z >= Parameter.MaxRandRot.z) ? Parameter.MinRandRot.z : Parameter.MaxRandRot.z);

		NewParticle->Init(RandomWind, RandomRot);
		ParticleActors.push_back(NewParticle);
		CreateCoolTime -= NextCreateTime;
		NextCreateTime = Rand.RandomFloat(Parameter.CreateMinTime, Parameter.CreateMaxTime);
	}

	std::list<std::shared_ptr<MapParticleBase>>::iterator LoopIter = ParticleActors.begin();
	std::list<std::shared_ptr<MapParticleBase>>::iterator EndIter = ParticleActors.end();

	float DeadLineDistance = std::fabsf(Parameter.Size.hy() * 1.1f);

	while (LoopIter != EndIter)
	{
		std::shared_ptr<MapParticleBase> LoopParticle = *LoopIter;

		GameEngineTransform* Trans = LoopParticle->GetTransform();

		float Distance = std::fabsf(Trans->GetLocalPosition().y);

		if (Distance >= DeadLineDistance)
		{
			(*LoopIter)->Death();
			(*LoopIter) = nullptr;
			LoopIter = ParticleActors.erase(LoopIter);
		}
		else
		{
			++LoopIter;
		}
	}
}

std::shared_ptr<MapParticleBase> ParticleArea::CreateParticle()
{
	std::shared_ptr <MapParticleBase> NewParticle = nullptr;
	//  Opening,
	//	Castle,
	//	ForestOfHarmony,
	//	GrandHall,
	switch (Parameter.Type)
	{
	case AreaParticle::Opening:
		NewParticle = GetLevel()->CreateActor<Opening_MapParticle>();
		break;

	case AreaParticle::Castle:
	case AreaParticle::GrandHall:

		break;

	case AreaParticle::ForestOfHarmony:
		NewParticle = GetLevel()->CreateActor<ForestOfHarmony_MapParticle>();
		break;
	default:
		break;
	}

	return NewParticle;
}

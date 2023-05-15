#include "PrecompileHeader.h"
#include "ParticleArea.h"

#include <GameEngineCore/GameEngineLevel.h>

#include "MapParticleBase.h"
#include "ForestOfHarmony_MapParticle.h"
#include "ForestOfHarmony_MapBlueParticle.h"
#include "Opening_MapParticle.h"
#include "Castle_MapParticle.h"

ParticleArea::ParticleArea()
{
}

ParticleArea::~ParticleArea()
{
}

void ParticleArea::SaveBin(GameEngineSerializer& _SaveSerializer)
{
	_SaveSerializer.Write(&MetaData.Type, sizeof(ParticleAreaType));
	_SaveSerializer.Write(&MetaData.Center, sizeof(float4));
	_SaveSerializer.Write(&MetaData.Size, sizeof(float4));
	_SaveSerializer.Write(&MetaData.IsTopSpawn, sizeof(bool));
	_SaveSerializer.Write(&MetaData.MinWindDir, sizeof(float4));
	_SaveSerializer.Write(&MetaData.MaxWindDir, sizeof(float4));
	_SaveSerializer.Write(&MetaData.MinRandRot, sizeof(float4));
	_SaveSerializer.Write(&MetaData.MaxRandRot, sizeof(float4));
	_SaveSerializer.Write(&MetaData.CreateMinTime, sizeof(float));
	_SaveSerializer.Write(&MetaData.CreateMaxTime, sizeof(float));
}

ParticleAreaMetaData ParticleArea::LoadBin(GameEngineSerializer& _LoadSerializer)
{
	ParticleAreaMetaData LoadMetaData = ParticleAreaMetaData();

	_LoadSerializer.Read(&LoadMetaData.Type, sizeof(ParticleAreaType));
	_LoadSerializer.Read(&LoadMetaData.Center, sizeof(float4));
	_LoadSerializer.Read(&LoadMetaData.Size, sizeof(float4));
	_LoadSerializer.Read(&LoadMetaData.IsTopSpawn, sizeof(bool));
	_LoadSerializer.Read(&LoadMetaData.MinWindDir, sizeof(float4));
	_LoadSerializer.Read(&LoadMetaData.MaxWindDir, sizeof(float4));
	_LoadSerializer.Read(&LoadMetaData.MinRandRot, sizeof(float4));
	_LoadSerializer.Read(&LoadMetaData.MaxRandRot, sizeof(float4));
	_LoadSerializer.Read(&LoadMetaData.CreateMinTime, sizeof(float));
	_LoadSerializer.Read(&LoadMetaData.CreateMaxTime, sizeof(float));

	return LoadMetaData;
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

		SpawnPostion.x = Rand.RandomFloat(-MetaData.Size.hx(), MetaData.Size.hx());

		if (true == MetaData.IsTopSpawn)
		{
			SpawnPostion.y = MetaData.Size.hy() * 1.05f;
		}
		else
		{
			SpawnPostion.y = -MetaData.Size.hy() * 1.05f;
		}

		NewParticle->GetTransform()->SetLocalPosition(SpawnPostion);

		float4 RandomWind = float4::Zero;

		RandomWind.x = Rand.RandomFloat(
			(MetaData.MinWindDir.x < MetaData.MaxWindDir.x) ? MetaData.MinWindDir.x : MetaData.MaxWindDir.x,
			(MetaData.MinWindDir.x >= MetaData.MaxWindDir.x) ? MetaData.MinWindDir.x : MetaData.MaxWindDir.x);
		RandomWind.y = Rand.RandomFloat(
			(MetaData.MinWindDir.y < MetaData.MaxWindDir.y) ? MetaData.MinWindDir.y : MetaData.MaxWindDir.y,
			(MetaData.MinWindDir.y >= MetaData.MaxWindDir.y) ? MetaData.MinWindDir.y : MetaData.MaxWindDir.y);
		RandomWind.z = Rand.RandomFloat(
			(MetaData.MinWindDir.z < MetaData.MaxWindDir.z) ? MetaData.MinWindDir.z : MetaData.MaxWindDir.z,
			(MetaData.MinWindDir.z >= MetaData.MaxWindDir.z) ? MetaData.MinWindDir.z : MetaData.MaxWindDir.z);

		float4 RandomRot = float4::Zero;

		RandomRot.x = Rand.RandomFloat(
			(MetaData.MinRandRot.x < MetaData.MaxRandRot.x) ? MetaData.MinRandRot.x : MetaData.MaxRandRot.x,
			(MetaData.MinRandRot.x >= MetaData.MaxRandRot.x) ? MetaData.MinRandRot.x : MetaData.MaxRandRot.x);
		RandomRot.y = Rand.RandomFloat(
			(MetaData.MinRandRot.y < MetaData.MaxRandRot.y) ? MetaData.MinRandRot.y : MetaData.MaxRandRot.y,
			(MetaData.MinRandRot.y >= MetaData.MaxRandRot.y) ? MetaData.MinRandRot.y : MetaData.MaxRandRot.y);
		RandomRot.z = Rand.RandomFloat(
			(MetaData.MinRandRot.z < MetaData.MaxRandRot.z) ? MetaData.MinRandRot.z : MetaData.MaxRandRot.z,
			(MetaData.MinRandRot.z >= MetaData.MaxRandRot.z) ? MetaData.MinRandRot.z : MetaData.MaxRandRot.z);

		NewParticle->Init(RandomWind, RandomRot);
		ParticleActors.push_back(NewParticle);
		CreateCoolTime -= NextCreateTime;
		NextCreateTime = Rand.RandomFloat(
			(MetaData.CreateMinTime < MetaData.CreateMaxTime) ? MetaData.CreateMinTime : MetaData.CreateMaxTime,
			(MetaData.CreateMinTime >= MetaData.CreateMaxTime) ? MetaData.CreateMinTime : MetaData.CreateMaxTime);
	}

	std::list<std::shared_ptr<MapParticleBase>>::iterator LoopIter = ParticleActors.begin();
	std::list<std::shared_ptr<MapParticleBase>>::iterator EndIter = ParticleActors.end();

	float DeadLineDistance = std::fabsf(MetaData.Size.hy() * 1.1f);

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
	switch (MetaData.Type)
	{
	case ParticleAreaType::Opening:
		NewParticle = GetLevel()->CreateActor<Opening_MapParticle>();
		break;

	case ParticleAreaType::Castle:
	case ParticleAreaType::GrandHall:
		NewParticle = GetLevel()->CreateActor<Castle_MapParticle>();
		break;

	case ParticleAreaType::ForestOfHarmony:
		NewParticle = GetLevel()->CreateActor<ForestOfHarmony_MapParticle>();
		break;
	case ParticleAreaType::ForestOfHarmony_Blue:
		NewParticle = GetLevel()->CreateActor<ForestOfHarmony_MapBlueParticle>();
		break;
	default:
		break;
	}

	return NewParticle;
}

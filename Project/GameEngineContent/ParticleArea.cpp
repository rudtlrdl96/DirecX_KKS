#include "PrecompileHeader.h"
#include "ParticleArea.h"

#include <GameEngineCore/GameEngineLevel.h>

#include "MapParticleBase.h"
#include "ForestOfHarmony_MapParticle.h"

ParticleArea::ParticleArea()
{
}

ParticleArea::~ParticleArea()
{
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
		SpawnPostion.y = Parameter.Size.hy();

		NewParticle->GetTransform()->SetLocalPosition(SpawnPostion);

		float4 RandomRot = float4::Zero;

		RandomRot.x = Rand.RandomFloat(0.0f, Parameter.RandRot.x);
		RandomRot.y = Rand.RandomFloat(0.0f, Parameter.RandRot.y);
		RandomRot.z = Rand.RandomFloat(0.0f, Parameter.RandRot.z);

		NewParticle->Init(RandomRot);
		ParticleActors.push_back(NewParticle);
		CreateCoolTime -= NextCreateTime;
		NextCreateTime = Rand.RandomFloat(Parameter.CreateMinTime, Parameter.CreateMaxTime);
	}

	float RandDiff = Rand.RandomFloat(Parameter.MinWindDiff, Parameter.MaxWindDiff);
	float4 RandWind = Parameter.WindDir.NormalizeReturn() * RandDiff;

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

		LoopParticle->AddForce(RandWind);
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

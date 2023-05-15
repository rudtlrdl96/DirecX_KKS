#include "PrecompileHeader.h"
#include "ParticleManager.h"

#include <GameEngineCore/GameEngineLevel.h>

ParticleManager::ParticleManager()
{
}

ParticleManager::~ParticleManager()
{
}

void ParticleManager::CreateMapParticleArea(const ParticleAreaParameter& _Parameter)
{
	std::shared_ptr<ParticleArea> NewArea = GetLevel()->CreateActor<ParticleArea>();

	NewArea->GetTransform()->SetParent(GetTransform());
	NewArea->Init(_Parameter);

	ParticleAreaDatas.push_back(NewArea);
}

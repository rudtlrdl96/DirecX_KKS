#include "PrecompileHeader.h"
#include "ParticleManager.h"

#include <GameEngineCore/GameEngineLevel.h>

ParticleManager::ParticleManager()
{
}

ParticleManager::~ParticleManager()
{
}

void ParticleManager::CreateMapParticleArea(const ParticleAreaMetaData& _Parameter)
{
	std::shared_ptr<ParticleArea> NewArea = GetLevel()->CreateActor<ParticleArea>();

	NewArea->GetTransform()->SetParent(GetTransform());
	NewArea->Init(_Parameter);

	ParticleAreaDatas.push_back(NewArea);
}

void ParticleManager::SaveBin(GameEngineSerializer& _SaveSerializer)
{
	_SaveSerializer.Write(static_cast<int>(ParticleAreaDatas.size()));

	for (size_t i = 0; i < ParticleAreaDatas.size(); i++)
	{
		ParticleAreaDatas[i]->SaveBin(_SaveSerializer);
	}
}

void ParticleManager::LoadBin(GameEngineSerializer& _LoadSerializer)
{
	for (size_t i = 0; i < ParticleAreaDatas.size(); i++)
	{
		ParticleAreaDatas[i]->Death();
		ParticleAreaDatas[i] = nullptr;
	}

	ParticleAreaDatas.clear();

	int LoadSize = 0;
	_LoadSerializer.Read(LoadSize);

	for (int i = 0; i < LoadSize; i++)
	{
		CreateMapParticleArea(ParticleArea::LoadBin(_LoadSerializer));
	}
}

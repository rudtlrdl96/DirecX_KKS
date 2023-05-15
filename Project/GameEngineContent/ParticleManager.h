#pragma once
#include "BaseContentActor.h"
#include "ParticleArea.h"

class ParticleManager : public BaseContentActor
{
public:
	ParticleManager();
	~ParticleManager();

	ParticleManager(const ParticleManager& _Other) = delete;
	ParticleManager(ParticleManager&& _Other) noexcept = delete;
	ParticleManager& operator=(const ParticleManager& _Other) = delete;
	ParticleManager& operator=(ParticleManager&& _Other) noexcept = delete;

	void CreateMapParticleArea(const ParticleAreaParameter& _Parameter);

protected:

private:
	std::vector<std::shared_ptr<ParticleArea>> ParticleAreaDatas;


};


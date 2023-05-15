#pragma once
#include "MapParticleBase.h"


class Castle_MapParticle : public MapParticleBase
{
public:
	Castle_MapParticle();
	~Castle_MapParticle();

	Castle_MapParticle(const Castle_MapParticle& _Other) = delete;
	Castle_MapParticle(Castle_MapParticle&& _Other) noexcept = delete;
	Castle_MapParticle& operator=(const Castle_MapParticle& _Other) = delete;
	Castle_MapParticle& operator=(Castle_MapParticle&& _Other) noexcept = delete;

protected:
	void Start() override;
	
private:
	void SetTexture() override;


};


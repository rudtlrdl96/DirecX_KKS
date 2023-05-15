#pragma once
#include "MapParticleBase.h"

class ForestOfHarmony_MapParticle : public MapParticleBase
{
public:
	ForestOfHarmony_MapParticle();
	~ForestOfHarmony_MapParticle();

	ForestOfHarmony_MapParticle(const ForestOfHarmony_MapParticle& _Other) = delete;
	ForestOfHarmony_MapParticle(ForestOfHarmony_MapParticle&& _Other) noexcept = delete;
	ForestOfHarmony_MapParticle& operator=(const ForestOfHarmony_MapParticle& _Other) = delete;
	ForestOfHarmony_MapParticle& operator=(ForestOfHarmony_MapParticle&& _Other) noexcept = delete;

protected:
	void Start() override;
	
private:
	void SetTexture() override;

};


#pragma once
#include "MapParticleBase.h"


class ForestOfHarmony_MapBlueParticle : public MapParticleBase
{
public:
	ForestOfHarmony_MapBlueParticle();
	~ForestOfHarmony_MapBlueParticle();

	ForestOfHarmony_MapBlueParticle(const ForestOfHarmony_MapBlueParticle& _Other) = delete;
	ForestOfHarmony_MapBlueParticle(ForestOfHarmony_MapBlueParticle&& _Other) noexcept = delete;
	ForestOfHarmony_MapBlueParticle& operator=(const ForestOfHarmony_MapBlueParticle& _Other) = delete;
	ForestOfHarmony_MapBlueParticle& operator=(ForestOfHarmony_MapBlueParticle&& _Other) noexcept = delete;

protected:
	void Start() override;

private:
	void SetTexture() override;


};


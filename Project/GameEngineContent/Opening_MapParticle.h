#pragma once
#include "MapParticleBase.h"
 
class Opening_MapParticle : public MapParticleBase
{
public:
	Opening_MapParticle();
	~Opening_MapParticle();

	Opening_MapParticle(const Opening_MapParticle& _Other) = delete;
	Opening_MapParticle(Opening_MapParticle&& _Other) noexcept = delete;
	Opening_MapParticle& operator=(const Opening_MapParticle& _Other) = delete;
	Opening_MapParticle& operator=(Opening_MapParticle&& _Other) noexcept = delete;

protected:
	void Start() override;

private:
	void SetTexture() override;

};


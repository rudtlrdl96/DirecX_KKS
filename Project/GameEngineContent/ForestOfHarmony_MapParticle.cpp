#include "PrecompileHeader.h"
#include "ForestOfHarmony_MapParticle.h"

ForestOfHarmony_MapParticle::ForestOfHarmony_MapParticle()
{
}

ForestOfHarmony_MapParticle::~ForestOfHarmony_MapParticle()
{
}

void ForestOfHarmony_MapParticle::Start()
{

	if (nullptr == GameEngineTexture::Find("MapParticle00.png"))
	{
		GameEngineDirectory Path;

		Path.MoveParentToDirectory("Resources");
		Path.Move("Resources");
		Path.Move("Texture");
		Path.Move("3_ForestOfHarmony");
		Path.Move("Particle");

		GameEngineTexture::Load(Path.GetPlusFileName("MapParticle00.png").GetFullPath());
	}

	MapParticleBase::Start();
}

void ForestOfHarmony_MapParticle::SetTexture()
{
	ParticleRender->SetScaleToTexture("MapParticle00.png");

	GameEngineTransform* RenderTrans = ParticleRender->GetTransform();

	float4 TextureScale = RenderTrans->GetLocalScale();
	TextureScale *= 2.0f;
	RenderTrans->SetLocalScale(TextureScale);
}

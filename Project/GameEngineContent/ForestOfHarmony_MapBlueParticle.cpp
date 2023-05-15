#include "PrecompileHeader.h"
#include "ForestOfHarmony_MapBlueParticle.h"

ForestOfHarmony_MapBlueParticle::ForestOfHarmony_MapBlueParticle()
{
}

ForestOfHarmony_MapBlueParticle::~ForestOfHarmony_MapBlueParticle()
{
}

void ForestOfHarmony_MapBlueParticle::Start()
{

	if (nullptr == GameEngineTexture::Find("MapParticle_Blue.png"))
	{
		GameEngineDirectory Path;

		Path.MoveParentToDirectory("Resources");
		Path.Move("Resources");
		Path.Move("Texture");
		Path.Move("3_ForestOfHarmony");
		Path.Move("Particle");

		GameEngineTexture::Load(Path.GetPlusFileName("MapParticle_Blue.png").GetFullPath());
	}

	MapParticleBase::Start();
}

void ForestOfHarmony_MapBlueParticle::SetTexture()
{
	ParticleRender->SetScaleToTexture("MapParticle_Blue.png");

	GameEngineTransform* RenderTrans = ParticleRender->GetTransform();

	float4 TextureScale = RenderTrans->GetLocalScale();
	TextureScale *= 2.0f;
	RenderTrans->SetLocalScale(TextureScale);
}

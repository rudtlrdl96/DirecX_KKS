#include "PrecompileHeader.h"
#include "Castle_MapParticle.h"

Castle_MapParticle::Castle_MapParticle()
{
}

Castle_MapParticle::~Castle_MapParticle()
{
}

void Castle_MapParticle::Start()
{

	if (nullptr == GameEngineTexture::Find("Castle_Particle.png"))
	{
		GameEngineDirectory Path;

		Path.MoveParentToDirectory("Resources");
		Path.Move("Resources");
		Path.Move("Texture");
		Path.Move("2_Castle");
		Path.Move("Particle");

		GameEngineTexture::Load(Path.GetPlusFileName("Castle_Particle.png").GetFullPath());
	}

	MapParticleBase::Start();
}

void Castle_MapParticle::SetTexture()
{
	ParticleRender->SetScaleToTexture("Castle_Particle.png");

	GameEngineTransform* RenderTrans = ParticleRender->GetTransform();

	float4 TextureScale = RenderTrans->GetLocalScale();
	TextureScale *= 0.5f;
	RenderTrans->SetLocalScale(TextureScale);
}

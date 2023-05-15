#include "PrecompileHeader.h"
#include "Opening_MapParticle.h"

Opening_MapParticle::Opening_MapParticle()
{
}

Opening_MapParticle::~Opening_MapParticle()
{
}

void Opening_MapParticle::Start()
{

	if (nullptr == GameEngineTexture::Find("Opening_Particle.png"))
	{
		GameEngineDirectory Path;

		Path.MoveParentToDirectory("Resources");
		Path.Move("Resources");
		Path.Move("Texture");
		Path.Move("1_Opening");
		Path.Move("Particle");

		GameEngineTexture::Load(Path.GetPlusFileName("Opening_Particle.png").GetFullPath());
	}

	MapParticleBase::Start();
}

void Opening_MapParticle::SetTexture()
{
	ParticleRender->SetScaleToTexture("Opening_Particle.png");

	GameEngineTransform* RenderTrans = ParticleRender->GetTransform();

	float4 TextureScale = RenderTrans->GetLocalScale();
	//TextureScale *= 2.0f;
	RenderTrans->SetLocalScale(TextureScale);
}

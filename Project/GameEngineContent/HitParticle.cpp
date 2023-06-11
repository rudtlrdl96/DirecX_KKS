#include "PrecompileHeader.h"
#include "HitParticle.h"

HitParticle::HitParticle()
{
}

HitParticle::~HitParticle()
{
}

void HitParticle::Init(const float4& _Dir, float _Power, float _LiveTime)
{
	ParticleRigid.SetVelocity(_Dir.NormalizeReturn() * _Power);

	LiveTime = _LiveTime;
}

void HitParticle::Start()
{
	ParticleRigid.SetMaxSpeed(1000.0f);
	ParticleRigid.SetActiveGravity(true);
	ParticleRigid.SetGravity(ContentConst::Gravity_f);

	Render = CreateComponent<ContentSpriteRenderer>();
	Render->PipeSetting("2DTexture_Color");
	Render->GetShaderResHelper().SetConstantBufferLink("ColorBuffer", Buffer);
	Render->SetScaleToTexture("BaseHitParticle.png");

	float4 TexScale = Render->GetTransform()->GetLocalScale();
	Render->GetTransform()->SetLocalScale(TexScale * 2.0f);

	Buffer.Color = float4(1, 1, 1, 1);
}

void HitParticle::Update(float _DeltaTime)
{
	float Progress = GetLiveTime() / LiveTime;

	if (GetLiveTime() >= LiveTime)
	{
		Death();
		return;
	}

	Buffer.Color.a = 1.0f - Progress;
	ParticleRigid.UpdateForce(_DeltaTime);

	float4 Velocity = ParticleRigid.GetVelocity() * _DeltaTime;
	GetTransform()->AddLocalPosition(Velocity);
}

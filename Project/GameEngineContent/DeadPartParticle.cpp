#include "PrecompileHeader.h"
#include "DeadPartParticle.h"

DeadPartParticle::DeadPartParticle()
{
}

DeadPartParticle::~DeadPartParticle()
{
}

void DeadPartParticle::Init(const std::string_view& _TexName, const float4& _Dir, float _Power, float _LiveTime)
{
	Render->SetScaleToTexture(_TexName);
	ParticleRigid.SetVelocity(_Dir.NormalizeReturn() * _Power);
	LiveTime = _LiveTime;
	On();
}

void DeadPartParticle::Start()
{
	ParticleRigid.SetMaxSpeed(1000.0f);
	ParticleRigid.SetActiveGravity(true);
	ParticleRigid.SetGravity(ContentConst::Gravity_f);

	Render = CreateComponent<ContentSpriteRenderer>();
	Render->PipeSetting("2DTexture_ColorLight");
	Render->GetShaderResHelper().SetConstantBufferLink("ColorBuffer", Buffer);
	//Render->SetScaleToTexture("BaseHitParticle.png");

	float4 TexScale = Render->GetTransform()->GetLocalScale();
	Render->GetTransform()->SetLocalScale(TexScale * 2.0f);

	RandRot = float4(0, 0, GameEngineRandom::MainRandom.RandomFloat(-80, 80));

	Buffer.Color = float4::Zero;

	Off();
}

void DeadPartParticle::Update(float _DeltaTime)
{
	float Progress = GetLiveTime() / LiveTime;

	if (GetLiveTime() >= LiveTime)
	{
		Death();
		return;
	}

	if (Progress >= 0.75f)
	{
		Buffer.Color.a = 1.0f - ((Progress - 0.75f) * 4.0f);
	}

	ParticleRigid.UpdateForce(_DeltaTime);

	float4 Velocity = ParticleRigid.GetVelocity() * _DeltaTime;
	GetTransform()->AddLocalPosition(Velocity);
	GetTransform()->AddWorldRotation(RandRot * _DeltaTime);
}

void DeadPartParticle::LevelChangeEnd()
{
	Death();
}

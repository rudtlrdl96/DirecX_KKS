#include "PrecompileHeader.h"
#include "AnimationPartParticle.h"

AnimationPartParticle::AnimationPartParticle()
{
}

AnimationPartParticle::~AnimationPartParticle()
{
}


void AnimationPartParticle::Init(const ContentAnimationParameter& _Parameter, float _ScaleRatio, const float4& _Dir, float _Power, float _LiveTime)
{
	Render->CreateAnimation(_Parameter);
	Render->SetScaleRatio(_ScaleRatio);
	Render->ChangeAnimation(_Parameter.AnimationName);

	ParticleRigid.SetVelocity(_Dir.NormalizeReturn() * _Power);
	LiveTime = _LiveTime;
	On();
}

void AnimationPartParticle::Start()
{
	ParticleRigid.SetMaxSpeed(1000.0f);
	ParticleRigid.SetActiveGravity(true);
	ParticleRigid.SetGravity(ContentConst::Gravity_f);

	Render = CreateComponent<ContentSpriteRenderer>();
	Render->PipeSetting("2DTexture_Color");
	Render->GetShaderResHelper().SetConstantBufferLink("ColorBuffer", Buffer);
	RandRot = float4(0, 0, GameEngineRandom::MainRandom.RandomFloat(-80, 80));

	Buffer.Color = float4::Zero;

	Off();
}

void AnimationPartParticle::Update(float _DeltaTime)
{
	float Progress = GetLiveTime() / LiveTime;

	if (GetLiveTime() >= LiveTime)
	{
		if (nullptr != EndCallback)
		{
			EndCallback();
		}

		Death();
		return;
	}

	ParticleRigid.UpdateForce(_DeltaTime);

	float4 Velocity = ParticleRigid.GetVelocity() * _DeltaTime;
	GetTransform()->AddLocalPosition(Velocity);

	if (true == IsRot)
	{
		GetTransform()->AddWorldRotation(RandRot * _DeltaTime);
	}
}

void AnimationPartParticle::LevelChangeEnd()
{
	Death();
}
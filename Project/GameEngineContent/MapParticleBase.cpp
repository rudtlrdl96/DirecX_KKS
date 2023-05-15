#include "PrecompileHeader.h"
#include "MapParticleBase.h"

MapParticleBase::MapParticleBase()
{
}

MapParticleBase::~MapParticleBase()
{
}

void MapParticleBase::Init(const float4& _RandWind, const float4& _RandRot)
{
	RandWind = _RandWind;
	RandRot = _RandRot;
}

void MapParticleBase::Start()
{
	//ParticleRigid.SetActiveGravity(true);
	//ParticleRigid.SetGravity(-60.0f);
	ParticleRigid.SetMass(1.0f);
	ParticleRigid.SetMaxSpeed(150.0f);
	ParticleRigid.SetFricCoeff(5.0f);

	ParticleRender = CreateComponent<GameEngineSpriteRenderer>();
	ParticleRender->SetTexture("Empty.png");

	SetTexture();
}

void MapParticleBase::Update(float _DeltaTime)
{
	ParticleRigid.AddForce(RandWind);
	ParticleRigid.UpdateForce(_DeltaTime);

	GameEngineTransform* ActorTrans = GetTransform();
	GameEngineTransform* RenderTrans = ParticleRender->GetTransform();

	ActorTrans->AddLocalPosition(ParticleRigid.GetVelocity() * _DeltaTime);
	RenderTrans->AddLocalRotation(RandRot * _DeltaTime);
}

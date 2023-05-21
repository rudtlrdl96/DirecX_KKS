#include "PrecompileHeader.h"
#include "Projectile.h"
#include "EffectManager.h"

Projectile::Projectile()
{
}

Projectile::~Projectile()
{
}

void Projectile::ShotProjectile(const ProjectileParameter& _Parameter)
{
	GameEngineTransform* Trans = GetTransform();

	Trans->SetLocalPosition(_Parameter.Pos);

	if ("" != _Parameter.EffectName)
	{
		std::shared_ptr<EffectActor> NewEffect = EffectManager::PlayEffect({
			.EffectName = _Parameter.EffectName,
			.Postion = _Parameter.Pos,
			.Triger = EffectDeathTrigger::Time,
			.Time = _Parameter.LiveTime,
			.FlipX = false,
			});

		NewEffect->GetTransform()->SetParent(GetTransform());
		NewEffect->GetTransform()->SetLocalPosition(float4::Zero);
	}

	Dir = _Parameter.Dir.NormalizeReturn();
	LiveTime = _Parameter.LiveTime;
	Speed = _Parameter.Speed;

	On();
}

void Projectile::Start()
{
	Off();
}

void Projectile::Update(float _DeltaTime)
{
	if (GetLiveTime() >= LiveTime)
	{
		Death();
		return;
	}

	float RotZ = 0.0f;

	if (float4::Right != Dir)
	{
		RotZ = float4::GetAngleVectorToVectorDeg(Dir, float4::Right);
	}

	GameEngineTransform* Trans = GetTransform();
	Trans->AddLocalPosition(Dir * _DeltaTime * Speed);
	Trans->SetLocalRotation(float4(0, 0, RotZ));
}

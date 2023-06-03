#include "PrecompileHeader.h"
#include "NormalMonster.h"
#include <GameEngineCore/GameEngineLevel.h>

#include "HealthBar.h"

NormalMonster::NormalMonster()
{
}

NormalMonster::~NormalMonster()
{
}

void NormalMonster::HitMonster(float _Damage, ActorViewDir _HitDir, bool _IsStiffen, bool _IsPush)
{
	BaseMonster::HitMonster(_Damage, _HitDir, _IsStiffen, _IsPush);
	HealthBarActiveTime = 3.0f;
}

void NormalMonster::Start()
{
	BaseMonster::Start();

	HealthBarPtr = GetLevel()->CreateActor<HealthBar>();
	HealthBarPtr->GetTransform()->SetParent(GetTransform());
	HealthBarPtr->GetTransform()->SetLocalPosition(float4(0, -15, -10));
	HealthBarPtr->SetTexture("EnemyHpFrame.png", "EnemyHpBar.png", "EnemySubBar.png", HealthBarScale);
	HealthBarPtr->Off();

	IsAppear = true;

	Render->Off();
	BodyCol->Off();
}

void NormalMonster::Update(float _DeltaTime)
{
	if (true == IsAppear)
	{
		if (nullptr == AppearEffect)
		{
			AppearEffect = EffectManager::PlayEffect({
				.EffectName = "MonsterAppear",
				.Position = GetTransform()->GetWorldPosition() + float4(0, 50, 0) });
		}

		if (5 == AppearEffect->GetCurrentFrame())
		{
			AppearEffect = nullptr;
			IsAppear = false;
			Render->On();
			BodyCol->On();
		}

		return;
	}

	BaseMonster::Update(_DeltaTime);

	HealthBarActiveTime -= _DeltaTime;

	if (0.0f < HealthBarActiveTime)
	{
		HealthBarPtr->On();
	}
	else
	{
		HealthBarPtr->Off();
	}
	HealthBarPtr->UpdateBar(HP / Data.HP, _DeltaTime);
}

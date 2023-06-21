#include "PrecompileHeader.h"
#include "BattleActorDamageFont.h"

BattleActorDamageFont::BattleActorDamageFont()
{
}

BattleActorDamageFont::~BattleActorDamageFont()
{
}

void BattleActorDamageFont::InitFont(const BattleActorDamageFontParameter& _Parameter)
{
	GameEngineTransform* Trans = GetTransform();

	GameEngineRandom& MainRand = GameEngineRandom::MainRandom;
	float RandX = MainRand.RandomFloat(-_Parameter.RandX, _Parameter.RandX);
	float RandY = MainRand.RandomFloat(-_Parameter.RandY, _Parameter.RandY);
		
	float4 RandPos = float4(RandX, RandY, 0 );

	Trans->SetWorldPosition(_Parameter.Pos + RandPos);

	FontRigid.SetVelocity(_Parameter.Dir.NormalizeReturn() * _Parameter.MoveSpeed);

	DamageFont->SetText(std::to_string(static_cast<int>(_Parameter.Damage)));
	DamageFont->SetScale(_Parameter.FontSize);
	DamageFont->SetColor(_Parameter.FontColor);

	DamageFont->On();

	LiveTime = -_Parameter.LiveTime;
}

void BattleActorDamageFont::Start()
{
	DamageFont = CreateComponent<GameEngineFontRenderer>();

	DamageFont->SetFont("Perfect DOS VGA 437");
	DamageFont->Off();

	FontRigid.SetMaxSpeed(1000);
	FontRigid.SetFricCoeff(300);
	FontRigid.SetGravity(-1700);
	FontRigid.SetActiveGravity(true);
}

void BattleActorDamageFont::Update(float _DeltaTime)
{
	if (true == DamageFont->IsUpdate())
	{
		FontRigid.UpdateForce(_DeltaTime);
		float4 Vel = FontRigid.GetVelocity();

		LiveTime += _DeltaTime;
		GetTransform()->AddWorldPosition(Vel * _DeltaTime);

		if (0.0f <= LiveTime)
		{
			Death();
		}
	}
}

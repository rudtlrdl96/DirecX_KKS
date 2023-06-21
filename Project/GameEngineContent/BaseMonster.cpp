#include "PrecompileHeader.h"
#include "BaseMonster.h"
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineCollision.h>
#include <GameEngineCore/GameEngineLevel.h>

#include "CollisionDebugRender.h"
#include "HitParticle.h"
#include "DeadPartParticle.h"
#include "Player.h"

#include "MonsterDamageFont.h"

bool BaseMonster::MonsterUnMove = false;

void BaseMonster::SetMonstersMove(bool _IsMove)
{
	MonsterUnMove = _IsMove;
}

BaseMonster::BaseMonster()
{
}

BaseMonster::~BaseMonster()
{
}

void BaseMonster::HitMonster(float _Damage, ActorViewDir _HitDir, bool _IsStiffen, bool _IsPush, bool _IsMagicAttack)
{
	HP -= _Damage;
	HitDamageCheck += _Damage;

	HitDir = _HitDir;
	IsHit = true;
	IsHitEffectOn = true;
	IsStiffen = _IsStiffen;
	IsPush = _IsPush;
	HitEffectProgress = 0.0f;

	std::shared_ptr<MonsterDamageFont> NewDamageFont = GetLevel()->CreateActor<MonsterDamageFont>();

	float4 FontDir;

	switch (_HitDir)
	{
	case ActorViewDir::Left:
		FontDir = float4(-0.5f, 10, 0);
		break;
	case ActorViewDir::Right:
		FontDir = float4(0.5f, 10, 0);
		break;
	default:
		break;
	}

	float4 FontColor;

	if (true == _IsMagicAttack)
	{
		FontColor = float4(0.54117f, 0.8392f, 0.90196f, 1);
	}
	else
	{
		FontColor = float4(0.85f, 0.705f, 0.17254f, 1);
	}

	NewDamageFont->InitFont({
		.Damage = _Damage,
		.FontSize = 30,
		.FontColor = FontColor,
		.Pos = GetTransform()->GetWorldPosition() + float4(0, 50, -100) + DamageFontPivot,
		.Dir = FontDir,
		.MoveSpeed = 700,
		.RandX = 20.0f,
		.LiveTime = 1.0f,
		});

	HitEffect();
}

void BaseMonster::Start()
{
	BattleActor::Start();

	if (false == GameEngineInput::IsKey("Debug_MonsterAllDeath"))
	{
		GameEngineInput::CreateKey("Debug_MonsterAllDeath", '9');
	}

	if (nullptr == GameEngineTexture::Find("EnemyHpBar.png"))
	{
		GameEngineDirectory Path;

		Path.MoveParentToDirectory("Resources");
		Path.Move("Resources");
		Path.Move("Texture");
		Path.Move("0_Common");
		Path.Move("UI");

		GameEngineTexture::Load(Path.GetPlusFileName("EnemyHpBar.png").GetFullPath());
		GameEngineTexture::Load(Path.GetPlusFileName("EnemySubBar.png").GetFullPath());
		GameEngineTexture::Load(Path.GetPlusFileName("EnemyHpFrame.png").GetFullPath());
	}

	DataLoad();
	HP = Data.HP;
}

void BaseMonster::Update(float _DeltaTime)
{
	BattleActor::Update(_DeltaTime);

	if (true == GameEngineInput::IsDown("Debug_MonsterAllDeath"))
	{
		HP = 0;
	}
}

void BaseMonster::SetViewDir(ActorViewDir _Dir, bool _Force)
{
	Dir = _Dir;

	switch (_Dir)
	{
	case ActorViewDir::Left:
	{
		GetTransform()->SetLocalNegativeScaleX();
	}
	break;
	case ActorViewDir::Right:
	{
		GetTransform()->SetLocalPositiveScaleX();
	}
	break;
	default:
		break;
	}
}

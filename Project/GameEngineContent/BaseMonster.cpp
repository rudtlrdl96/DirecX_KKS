#include "PrecompileHeader.h"
#include "BaseMonster.h"
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineCollision.h>
#include <GameEngineCore/GameEngineLevel.h>

#include "CollisionDebugRender.h"
#include "HitParticle.h"
#include "DeadPartParticle.h"
#include "Player.h"

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

void BaseMonster::HitMonster(float _Damage, ActorViewDir _HitDir, bool _IsStiffen, bool _IsPush)
{
	HP -= _Damage;

	HitDir = _HitDir;
	IsHit = true;
	IsHitEffectOn = true;
	IsStiffen = _IsStiffen;
	IsPush = _IsPush;
	HitEffectProgress = 0.0f;
}

void BaseMonster::Start()
{
	BattleActor::Start();
	DataLoad();
	HP = Data.HP;
}

void BaseMonster::Update(float _DeltaTime)
{
	BattleActor::Update(_DeltaTime);
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

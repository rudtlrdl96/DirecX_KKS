#include "PrecompileHeader.h"
#include "BossMonster.h"

BossMonster::BossMonster() :
	CurAnimPause(PauseTimes["Idle"])
{
}

BossMonster::~BossMonster()
{
}

void BossMonster::Start()
{
	BaseMonster::Start();

	SpriteLoad();

	BossFsm.Init(this);

	BossFsm.AddFSM("Idle", &BossMonster::Idle_Enter, &BossMonster::Idle_Update, &BossMonster::Idle_End);
	BossFsm.AddFSM("Dash", &BossMonster::Dash_Enter, &BossMonster::Dash_Update, &BossMonster::Dash_End);
	BossFsm.AddFSM("Pattern", &BossMonster::Pattern_Enter, &BossMonster::Pattern_Update, &BossMonster::Pattern_End);
	BossFsm.AddFSM("Hit", &BossMonster::Hit_Enter, &BossMonster::Hit_Update, &BossMonster::Hit_End);
	BossFsm.AddFSM("Behavior", &BossMonster::Behavior_Enter, &BossMonster::Behavior_Update, &BossMonster::Behavior_End);

	PlayerFindCol = CreateComponent<GameEngineCollision>((int)CollisionOrder::Unknown);
	PlayerFindCol->GetTransform()->SetLocalPosition(float4(100000, 100000, 1));

	BossFsm.ChangeState("Idle");
}

void BossMonster::Update(float _DeltaTime)
{
	CurWaitTime += _DeltaTime;
	CurFramePauseTime += _DeltaTime;

	if (CurFrameIndex != Render->GetCurrentFrame())
	{
		CurFrameIndex = static_cast<UINT>(Render->GetCurrentFrame());
		CurFramePauseTime = 0.0f;
	}

	if (CurFramePauseTime < CurAnimPause[CurFrameIndex])
	{
		Render->SetAnimPauseOn();
	}
	else
	{
		Render->SetAnimPauseOff();
	}

	BossFsm.Update(_DeltaTime);
	BaseMonster::Update(_DeltaTime);
}

bool BossMonster::HitCheck()
{
	if (true == IsHit && false == IsSuperArmor)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void BossMonster::PlayAnimation(const std::string_view& _AnimationName)
{
	CurFrameIndex = static_cast<UINT>(-1);
	CurFramePauseTime = 0.0f;

	CurAnimPause = PauseTimes[_AnimationName.data()];
	Render->ChangeAnimation(_AnimationName);
}

bool BossMonster::MoveableCheck(const float4& _Dir, bool _IsHalf)
{
	return true;
}

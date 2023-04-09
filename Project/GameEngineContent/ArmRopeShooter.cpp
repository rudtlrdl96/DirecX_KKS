#include "ArmRopeShooter.h"
#include <GameEngineCore/GameEngineLevel.h>
#include "ContentConst.h"
#include "ArmRopeChain.h"
#include "ArmRopeHook.h"

ArmRopeShooter::ArmRopeShooter()
{
}

ArmRopeShooter::~ArmRopeShooter()
{
}

bool ArmRopeShooter::CanShot(const float4& _Pos) const
{
    GameEngineTransform* Trans = GetTransform();
    float Distance = (Trans->GetWorldPosition() - _Pos).Size();

    if (Distance >= ShotMaxDistance)
    {
        return false;
    }

    return true;
}

void ArmRopeShooter::RopeShot(const float4& _Pos)
{
    if (ArmState::Wait != State)
    {
        return;
    }

    GameEngineTransform* Trans = GetTransform();

    HookPos = _Pos;
    HookDistance = (Trans->GetWorldPosition() - _Pos).Size();

    //ChainList[0]->LinkChain(this->GetTransform(), ChainList[1]->GetTransform());
    //
    //for (int i = 1; i < ChainCount - 1; i++)
    //{
    //    ChainList[i]->LinkChain(ChainList[i - 1]->GetTransform(), ChainList[i + 1]->GetTransform());
    //}
    //
    //ChainList[ChainCount - 1]->LinkChain(ChainList[ChainCount - 2]->GetTransform(), EndHook->GetTransform());

    ProgressTime = 0.0f;
    State = ArmState::Shot;
}

void ArmRopeShooter::RopeEnd()
{
    if (ArmState::Hook != State)
    {
        return;
    }

    State = ArmState::Reset;
}

void ArmRopeShooter::Start()
{
    ChainCount = ContentConst::ArmChainCount;
    Interval = ContentConst::ArmChainInterval;
    ShotSpeed = ContentConst::ArmShotSpeed;

    ShotMaxDistance = ChainCount * Interval;

    GameEngineLevel* Level = GetLevel();

    EndHook = Level->CreateActor<ArmRopeHook>();
    EndHook->Off();

    for (int i = 0; i < ChainCount; ++i)
    {
        ChainList[i] = Level->CreateActor<ArmRopeChain>();
        ChainList[i]->Off();
    }
}

void ArmRopeShooter::Update(float _DeltaTime)
{
    switch (State)
    {
    case ArmRopeShooter::ArmState::Shot:
    {
        ProgressTime += _DeltaTime;
    


        if (1.0f <= ProgressTime)
        {
            State = ArmState::Hook;
        }
    }
        break;
    case ArmRopeShooter::ArmState::Reset:
    {
        ProgressTime += _DeltaTime;
    


        if (1.0f <= ProgressTime)
        {
            State = ArmState::Wait;
        }
    }
        break;
    }
}
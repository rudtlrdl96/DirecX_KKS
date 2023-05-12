#include "PrecompileHeader.h"
#include "BattleLevel.h"

// Debug
#include "BoneSkull.h"

// Game
#include "BattleArea.h"

BattleLevel::BattleLevel()
{
}

BattleLevel::~BattleLevel()
{
}

void BattleLevel::Start()
{
	ContentLevel::Start();

	float4 HalfWindowSize = GameEngineWindow::GetScreenSize().half();

	DebugActor = CreateActor<BoneSkull>();
	MainCamCtrl.SetLookatTarget(DebugActor);

	BattleAreaPtr = CreateActor<BattleArea>();
}

void BattleLevel::Update(float _DeltaTime)
{
	ContentLevel::Update(_DeltaTime);
	BattleAreaPtr->UpdateBackground(_DeltaTime, MainCamCtrl.GetCameraPos());
}

void BattleLevel::SetPosDebugActor(const float4& _Pos)
{
	DebugActor->GetTransform()->SetLocalPosition(_Pos);
}

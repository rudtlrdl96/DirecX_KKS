#include "PrecompileHeader.h"
#include "BattleLevel.h"

#include "EffectManager.h"

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

	BattleAreaPtr = CreateActor<BattleArea>();
	DebugActor = CreateActor<BoneSkull>();
	MainCamCtrl.SetLookatTarget(DebugActor);
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

void BattleLevel::LevelChangeStart()
{
	EffectManager::SetLevel(DynamicThis<GameEngineLevel>());
}

void BattleLevel::LevelChangeEnd()
{
	EffectManager::SetLevel(nullptr);
}

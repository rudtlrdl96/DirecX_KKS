#include "PrecompileHeader.h"
#include "BattleLevel.h"

// Debug
#include "DebugSpriteActor.h"

// Game
#include "MultiBackground.h"
#include "Tilemap.h"
#include "ObjectManager.h"

BattleLevel::BattleLevel()
{
}

BattleLevel::~BattleLevel()
{
}

void BattleLevel::Start()
{
	ContentLevel::Start();

	MBackgroundPtr = CreateActor<MultiBackground>();
	TilemapPtr = CreateActor<Tilemap>();
	ObjectManagerPtr = CreateActor<ObjectManager>();


	float4 HalfWindowSize = GameEngineWindow::GetScreenSize().half();

	MBackgroundPtr->GetTransform()->SetWorldPosition(float4::Zero);
	TilemapPtr->GetTransform()->SetWorldPosition(float4::Zero);
	ObjectManagerPtr->GetTransform()->SetWorldPosition(float4::Zero);

	//MainCamCtrl.SetMinHeight(-HalfWindowSize.y);
	//MainCamCtrl.SetMaxHeight(HalfWindowSize.y);
	//MainCamCtrl.SetMinWidth(-HalfWindowSize.x);
	//MainCamCtrl.SetMinWidth(HalfWindowSize.x);

	DebugActor = CreateActor<DebugSpriteActor>();
	MainCamCtrl.SetLookatTarget(DebugActor);
}

void BattleLevel::Update(float _DeltaTime)
{
	ContentLevel::Update(_DeltaTime);

	MBackgroundPtr->UpdateTargetPos(_DeltaTime, MainCamCtrl.GetCameraPos());
}

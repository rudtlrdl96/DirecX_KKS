#include "PrecompileHeader.h"
#include "ForestOfHarmonyLevel_Boss.h"
#include "MultiBackground.h"

ForestOfHarmonyLevel_Boss::ForestOfHarmonyLevel_Boss()
{
}

ForestOfHarmonyLevel_Boss::~ForestOfHarmonyLevel_Boss()
{
}

void ForestOfHarmonyLevel_Boss::Start()
{
	BattleLevel::Start();

	//{
	//	Background::BG_DESC BgDesc;
	//
	//	BgDesc.TextureName = "ForestOfHarmonyBoss_BackImage_0.png";
	//	BgDesc.Center = { 0.0f, 0.0f, 0, 0 };
	//	BgDesc.Ratio = 0.1f;
	//	BgDesc.Size = float4(900.0f, 560.0f, 0, 0);
	//	BgDesc.Size *= 2.0f;
	//
	//	MBackgroundPtr->CreateBackground(BgDesc, 11);
	//}
	//
	//{
	//	Background::BG_DESC BgDesc;
	//
	//	BgDesc.TextureName = "ForestOfHarmonyBoss_BackImage_1.png";
	//	BgDesc.Center = { 0.0f, 0.0f, 0, 0 };
	//	BgDesc.Ratio = 0.2f;
	//	BgDesc.Size = float4(900.0f, 560.0f, 0, 0);
	//	BgDesc.Size *= 2.0f;
	//
	//	MBackgroundPtr->CreateBackground(BgDesc, 10);
	//}
}

void ForestOfHarmonyLevel_Boss::Update(float _DeltaTime)
{
	BattleLevel::Update(_DeltaTime);
}


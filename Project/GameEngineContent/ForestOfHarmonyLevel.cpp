#include "PrecompileHeader.h"
#include "ForestOfHarmonyLevel.h"
#include "MultiBackground.h"

ForestOfHarmonyLevel::ForestOfHarmonyLevel()
{
}

ForestOfHarmonyLevel::~ForestOfHarmonyLevel()
{
}

void ForestOfHarmonyLevel::Start()
{
	BattleLevel::Start();

	//{
	//	Background::BG_DESC BgDesc;
	//
	//	BgDesc.TextureName = "ForestOfHarmony_BackImage_0.png";
	//	BgDesc.Center = { 0.0f, 400.0f, 0, 0 };
	//	BgDesc.Ratio = 0.0f;
	//	BgDesc.Size = float4(960.0f, 800.0f, 0, 0);
	//	BgDesc.Size *= 2.0f;
	//
	//	MBackgroundPtr->CreateBackground(BgDesc, 11);
	//}
	//
	//{
	//	Background::BG_DESC BgDesc;
	//
	//	BgDesc.TextureName = "ForestOfHarmony_BackImage_1.png";
	//	BgDesc.Center = { 0.0f, 450.0f, 0, 0 };
	//	BgDesc.Ratio = 0.1f;
	//	BgDesc.Size = float4(960.0f, 800.0f, 0, 0);
	//	BgDesc.Size *= 2.0f;
	//
	//	MBackgroundPtr->CreateBackground(BgDesc, 10);
	//}
	//
	//{
	//	Background::BG_DESC BgDesc;
	//
	//	BgDesc.TextureName = "ForestOfHarmony_BackImage_2.png";
	//	BgDesc.Center = { 0.0f, 400.0f, 0, 0 };
	//	BgDesc.Ratio = 0.2f;
	//	BgDesc.Size = float4(960.0f, 800.0f, 0, 0);
	//	BgDesc.Size *= 2.0f;
	//
	//	MBackgroundPtr->CreateBackground(BgDesc, 9);
	//}
	//
	////{
	//	Background::BG_DESC BgDesc;
	//
	//	BgDesc.TextureName = "ForestOfHarmony_BackImage_3.png";
	//	BgDesc.Center = { 0.0f, 300.0f, 0, 0 };
	//	BgDesc.Ratio = 0.4f;
	//	BgDesc.Size = float4(960.0f, 800.0f, 0, 0);
	//	BgDesc.Size *= 2.0f;
	//
	//	MBackgroundPtr->CreateBackground(BgDesc, 8);
	//}
}

void ForestOfHarmonyLevel::Update(float _DeltaTime)
{
	BattleLevel::Update(_DeltaTime);
}
#include "PrecompileHeader.h"
#include "ContentLevelLightGUI.h"
#include "WorldLightEffect.h"

ContentLevelLightGUI::ContentLevelLightGUI()
{
}

ContentLevelLightGUI::~ContentLevelLightGUI()
{
}

void ContentLevelLightGUI::Start()
{

}

void ContentLevelLightGUI::OnGUI(std::shared_ptr<class GameEngineLevel>, float _DeltaTime)
{
	std::shared_ptr<ContentLevel> CastingPtr = LevelPtr.lock();

	if (nullptr == CastingPtr)
	{
		return;
	}

	ImGui::Text("World Light");

	std::shared_ptr<WorldLightEffect> WorldLight = CastingPtr->GetWorldLight();
	float4 PrevWorldColor = WorldLight->WorldLight;

	float LightValue[4] = { PrevWorldColor.x, PrevWorldColor.y, PrevWorldColor.z, PrevWorldColor.w };
	ImGui::DragFloat4("World", LightValue, 0.01f);
	WorldLight->WorldLight = ContentFunc::ConvertFloat4(LightValue);
}
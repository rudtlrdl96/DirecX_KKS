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

	ImGui::Spacing();
	ImGui::Text("Point Light");

	if (ImGui::BeginListBox("PointLight ListBox"))
	{
		static int SelectLight = 0;

		if (SelectLight < 0)
		{
			SelectLight = 0;
		}

		if (SelectLight >= CastingPtr->PointLightEffects.size())
		{
			SelectLight = static_cast<int>(CastingPtr->PointLightEffects.size() - 1);
		}

		for (int n = 0; n < CastingPtr->PointLightEffects.size(); n++)
		{
			const bool is_selected = (SelectLight == n);

			if (ImGui::Selectable(std::string("Light, " + std::to_string(n)).c_str(), is_selected))
			{
				SelectLight = n;
			}

			// Set the initial focus when opening the combo (scrolling + keyboard navigation focus)
			if (is_selected)
				ImGui::SetItemDefaultFocus();
		}

		ImGui::EndListBox();

		if (0 <= SelectLight && SelectLight < CastingPtr->PointLightEffects.size())
		{
			CastingPtr->PointLightEffects[SelectLight]->ShowGUI();
		}
	}

}
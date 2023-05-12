#include "PrecompileHeader.h"
#include "AttackCollisionToolGUI.h"

AttackCollisionToolGUI::AttackCollisionToolGUI()
{
}

AttackCollisionToolGUI::~AttackCollisionToolGUI()
{
}

void AttackCollisionToolGUI::Start()
{
}

void AttackCollisionToolGUI::OnGUI(std::shared_ptr<class GameEngineLevel> _Level, float _DeltaTime)
{
	//ImGui::Text();

	int InputStart = StartIndex;

	ImGui::InputInt("Start", &InputStart);

	if (InputStart != StartIndex)
	{
		if (InputStart < 0)
		{
			InputStart = 0;
		}

		StartIndex = static_cast<UINT>(InputStart);
	}

	int InputEnd = EndIndex;

	ImGui::InputInt("End", &InputEnd);

	if (InputEnd != EndIndex)
	{
		if (InputEnd < 0)
		{
			InputEnd = 0;
		}

		EndIndex = static_cast<UINT>(InputEnd);
	}

	if (true == ImGui::Button("Prev", ImVec2(60, 30)))
	{
	}

	ImGui::SameLine();

	if (true == ImGui::Button("Next", ImVec2(60, 30)))
	{
	}


}
#include "PrecompileHeader.h"
#include "TalkboxDebugGUI.h"

TalkboxDebugGUI::TalkboxDebugGUI()
{
}

TalkboxDebugGUI::~TalkboxDebugGUI()
{
}

void TalkboxDebugGUI::SetNameText(const std::string_view& _NameText)
{
	NameText = _NameText;
}

void TalkboxDebugGUI::SetMainText(const std::string_view& _MainText)
{
	MainText = _MainText;
}

void TalkboxDebugGUI::OnGUI(std::shared_ptr<class GameEngineLevel>, float _DeltaTime)
{
	ImGui::Text(GameEngineString::AnsiToUTF8(std::string("Name : ") + NameText).data());
	ImGui::Spacing();
	ImGui::Spacing();

	if (0 == MainText.size())
	{
		return;
	}

	ImGui::Text(GameEngineString::AnsiToUTF8(MainText).data());
}

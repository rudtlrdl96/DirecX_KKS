#include "PrecompileHeader.h"
#include "ItemGearMorePopupFont.h"

ItemGearMorePopupFont::ItemGearMorePopupFont()
{
}

ItemGearMorePopupFont::~ItemGearMorePopupFont()
{
}

void ItemGearMorePopupFont::SetSynergyText(Synergy _Synergy, int _Grade)
{
	std::wstring Text = GameEngineString::AnsiToUniCode(ItemData::GetSynergyNote(_Synergy, _Grade));

	float TextureBoardX = 250.0f;
	float TextureBoardY = 0.0f;

	float CurX = 0.0f;
	SizeY = 50.0f;

	for (size_t i = 0; i < Text.size(); i++)
	{
		if (L'\n' == Text[i])
		{
			CurX = 0;
			SizeY += 15.0f;
			continue;
		}

		CurX += 15.0f * 0.7f;

		if (TextureBoardX < CurX + 15.0f)
		{
			CurX = 0;
			Text.insert(Text.begin() + i, L'\n');
			SizeY += 15.0f;
		}
	}

	NoteText->SetText(GameEngineString::UniCodeToAnsi(Text));
	GradeText->SetText(std::to_string(_Grade));

}

void ItemGearMorePopupFont::Start()
{
	LineImage = CreateComponent<GameEngineUIRenderer>();
	LineImage->SetScaleToTexture("ItemPopup_TextFrame2.png", 2.0f);	
	
	ArrowImage = CreateComponent<GameEngineUIRenderer>();
	ArrowImage->GetTransform()->SetLocalPosition(float4(-105, -23));
	ArrowImage->SetScaleToTexture("Inscription_Arrow.png", 1.0f);
	ArrowImage->GetTransform()->SetLocalScale(float4(4, 8));

	NoteText = CreateComponent<ContentUIFontRenderer>();
	NoteText->GetTransform()->SetLocalPosition(float4(-96, -13));
	NoteText->SetFont("³Ø½¼Lv2°íµñ");
	NoteText->SetScale(15);
	NoteText->SetColor(float4(0.45882f, 0.33725f, 0.33333f, 1));
	NoteText->SetFontFlag(static_cast<FW1_TEXT_FLAG>(FW1_TEXT_FLAG::FW1_TOP | FW1_TEXT_FLAG::FW1_LEFT));

	GradeText = CreateComponent<ContentUIFontRenderer>();
	GradeText->GetTransform()->SetLocalPosition(float4(-121, -23));
	GradeText->SetFont("³Ø½¼Lv2°íµñ");
	GradeText->SetScale(20);
	GradeText->SetColor(float4(0.45882f, 0.33725f, 0.33333f, 1));
	GradeText->SetFontFlag(static_cast<FW1_TEXT_FLAG>(FW1_TEXT_FLAG::FW1_VCENTER | FW1_TEXT_FLAG::FW1_CENTER));

}
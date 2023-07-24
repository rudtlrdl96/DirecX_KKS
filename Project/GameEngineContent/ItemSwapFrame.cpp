#include "PrecompileHeader.h"
#include "ItemSwapFrame.h"
#include "UINoteActor.h"

ItemSwapFrame::ItemSwapFrame()
{
}

ItemSwapFrame::~ItemSwapFrame()
{
}

void ItemSwapFrame::PopupOn(ItemData& _Data)
{
	Data = _Data;

	if (false == ContentDatabase<ItemData, ItemGrade>::IsVaild(Data.Index))
	{
		MsgAssert_Rtti<ItemSwapFrame>(" - Á¸ÀçÇÏÁö ¾Ê´Â ½ºÄÃÀÇ µ¥ÀÌÅÍ¸¦ ÂüÁ¶ÇÏ·Á Çß½À´Ï´Ù.");
		return;
	}

	float4 NoteScale = float4::Zero;

	NoteScale.x = 333.0f;
	NoteScale.y = 285.0f;
	NoteScale.z = 1.0f;

	ItemNameFont->SetText(Data.Name);

	switch (Data.Grade)
	{
	case ItemGrade::Normal:
		ItemGradeFont->SetText("ÀÏ¹Ý");
		break;

	case ItemGrade::Rare:
		ItemGradeFont->SetText("·¹¾î");;
		break;

	case ItemGrade::Unique:
		ItemGradeFont->SetText("À¯´ÏÅ©");
		break;

	case ItemGrade::Legendary:
		ItemGradeFont->SetText("·¹Àü´õ¸®");
		break;
	default:
		break;
	}

	SynergyIconA->SetTexture(Data.GetSynergyIconTextureName(Data.Synergy1));
	SynergyAFont->SetText(Data.GetSynergyName(Data.Synergy1));

	SynergyIconB->SetTexture(Data.GetSynergyIconTextureName(Data.Synergy2));
	SynergyBFont->SetText(Data.GetSynergyName(Data.Synergy2));

	if ("" == Data.Note)
	{
		ItemNoteFont->Off();
		ItemFrameRender->GetTransform()->SetLocalScale(NoteScale);
	}
	else
	{
		ItemNoteFont->On();

		std::wstring NoteText = GameEngineString::AnsiToUniCode(Data.Note);

		float TextureBoardX = 280.0f;
		float TextureBoardY = 0.0f;

		float CurX = 0.0f;
		float CurY = 0.0f;

		for (size_t i = 0; i < NoteText.size(); i++)
		{
			CurX += 16.0f * 0.7f;

			if ('\n' == NoteText[i])
			{
				CurX = 0;
				CurY += 16.0f;
			}
			else if (TextureBoardX < CurX + 16.0f)
			{
				CurX = 0;
				NoteText.insert(NoteText.begin() + i, L'\n');
				CurY += 16.0f;
			}
		}

		NoteScale.y += CurY;

		ItemFrameRender->GetTransform()->SetLocalScale(NoteScale);
		ItemFrameRender->GetTransform()->SetLocalPosition(float4(0, -NoteScale.hy() + 190.0f, 0));

		float4 MainFramePos = ItemFrameRender->GetTransform()->GetLocalPosition();
		float4 MainFrameScale = ItemFrameRender->GetTransform()->GetLocalScale();

		float4 TopLocalPos = MainFramePos + float4(0, MainFrameScale.hy(), 0);
		float4 BotLocalPos = MainFramePos - float4(0, MainFrameScale.hy(), 0);

		ItemNoteFont->SetText(GameEngineString::UniCodeToAnsi(NoteText));
		ItemNoteFont->GetTransform()->SetLocalPosition(TopLocalPos + float4(-135, -112, -5));

		SynergyIconA->GetTransform()->SetLocalPosition(BotLocalPos + float4(-76, 84, -1.0f));
		SynergyAFont->GetTransform()->SetLocalPosition(BotLocalPos + float4(-76, 29, -1.0f));
		SynergyIconB->GetTransform()->SetLocalPosition(BotLocalPos + float4(77, 84, -1.0f));
		SynergyBFont->GetTransform()->SetLocalPosition(BotLocalPos + float4(77, 29, -1.0f));
	}

	On();
}

void ItemSwapFrame::PopupOff()
{
	Off();
}

void ItemSwapFrame::Start()
{
	ItemFrameRender = CreateComponent<ContentSlice9UIRenderer>();
	ItemFrameRender->SetTextureAndSlice("ItemPopupKeywords.png", 0.0f, 0.0f, 0.38f, 0.527f);
	ItemFrameRender->SetTexturePer(float4(3.0f, 3.0f));

	ItemNoteFont = CreateComponent<ContentUIFontRenderer>();
	ItemNoteFont->SetFont("³Ø½¼Lv2°íµñ");
	ItemNoteFont->SetScale(16);
	ItemNoteFont->SetColor(float4(0.45882f, 0.33725f, 0.33333f, 1));
	ItemNoteFont->SetFontFlag(static_cast<FW1_TEXT_FLAG>(FW1_TEXT_FLAG::FW1_TOP | FW1_TEXT_FLAG::FW1_LEFT));

	SynergyIconA = CreateComponent<GameEngineUIRenderer>();
	SynergyIconA->GetTransform()->SetParent(GetTransform());
	SynergyIconA->GetTransform()->SetLocalPosition(float4(0, 0, -0.3f));
	SynergyIconA->GetTransform()->SetLocalScale(float4(78, 78, 1));

	SynergyAFont = CreateComponent<ContentUIFontRenderer>();
	SynergyAFont->GetTransform()->SetParent(GetTransform());
	SynergyAFont->SetFont("³Ø½¼Lv2°íµñ");
	SynergyAFont->SetScale(16);
	SynergyAFont->SetColor(float4(0.29411f, 0.20784f, 0.19607f, 1));
	SynergyAFont->SetFontFlag(static_cast<FW1_TEXT_FLAG>(FW1_TEXT_FLAG::FW1_VCENTER | FW1_TEXT_FLAG::FW1_CENTER));
	SynergyAFont->GetTransform()->SetLocalPosition(float4(0, -42, -1));

	SynergyIconB = CreateComponent<GameEngineUIRenderer>();
	SynergyIconB->GetTransform()->SetParent(GetTransform());
	SynergyIconB->GetTransform()->SetLocalPosition(float4(0, 0, -0.4f));
	SynergyIconB->GetTransform()->SetLocalScale(float4(78, 78, 1));

	SynergyBFont = CreateComponent<ContentUIFontRenderer>();
	SynergyBFont->GetTransform()->SetParent(GetTransform());
	SynergyBFont->SetFont("³Ø½¼Lv2°íµñ");
	SynergyBFont->SetScale(16);
	SynergyBFont->SetColor(float4(0.29411f, 0.20784f, 0.19607f, 1));
	SynergyBFont->SetFontFlag(static_cast<FW1_TEXT_FLAG>(FW1_TEXT_FLAG::FW1_VCENTER | FW1_TEXT_FLAG::FW1_CENTER));
	SynergyBFont->GetTransform()->SetLocalPosition(float4(0, -42, -1));

	ItemNameFont = CreateComponent<ContentUIFontRenderer>();
	ItemNameFont->SetFont("³Ø½¼Lv2°íµñ");
	ItemNameFont->SetScale(20);
	ItemNameFont->SetColor(float4(0.29411f, 0.20784f, 0.19607f, 1));
	ItemNameFont->SetFontFlag(static_cast<FW1_TEXT_FLAG>(FW1_TEXT_FLAG::FW1_VCENTER | FW1_TEXT_FLAG::FW1_CENTER));
	ItemNameFont->GetTransform()->SetLocalPosition(float4(0, 146, -1));

	ItemGradeFont = CreateComponent<ContentUIFontRenderer>();
	ItemGradeFont->SetFont("³Ø½¼Lv2°íµñ");
	ItemGradeFont->SetScale(16);
	ItemGradeFont->SetColor(float4(0.29411f, 0.20784f, 0.19607f, 1));
	ItemGradeFont->SetFontFlag(static_cast<FW1_TEXT_FLAG>(FW1_TEXT_FLAG::FW1_VCENTER | FW1_TEXT_FLAG::FW1_LEFT));
	ItemGradeFont->GetTransform()->SetLocalPosition(float4(-139, 104, -1));

	Off();
}
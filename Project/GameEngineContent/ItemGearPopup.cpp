#include "PrecompileHeader.h"
#include "ItemGearPopup.h"
#include "UINoteActor.h"

ItemData ItemGearPopup::GlobalData;

ItemGearPopup::ItemGearPopup()
{
}

ItemGearPopup::~ItemGearPopup()
{
}

void ItemGearPopup::PopupOn()
{
	PopupOn(GlobalData);
}

void ItemGearPopup::PopupOn(ItemData& _Data)
{
	LocalData = _Data;

	if (false == ContentDatabase<ItemData, ItemGrade>::IsVaild(LocalData.Index))
	{
		MsgAssert_Rtti<ItemGearPopup>(" - Á¸ÀçÇÏÁö ¾Ê´Â ½ºÄÃÀÇ µ¥ÀÌÅÍ¸¦ ÂüÁ¶ÇÏ·Á Çß½À´Ï´Ù.");
		return;
	}

	float4 BackgroundScale = float4(434, 220, 1);
	float4 NoteScale = float4::Zero;

	ItemNameFont->SetText(LocalData.Name);

	switch (LocalData.Grade)
	{
	case ItemGrade::Normal:
		ItemGradeFont->SetText("ÀÏ¹Ý");
		BrokenFontActor->SetText("¡¡ÆÄ±«ÇÏ±â (¡¡ " + std::to_string(ContentConst::Goods_Item_Normal) + ")");
		BrokenKeyRender->GetTransform()->SetLocalPosition(float4(-72, 0, -1));
		BrokenGoldRender->GetTransform()->SetLocalPosition(float4(23, 0, -1));
		break;

	case ItemGrade::Rare:
		ItemGradeFont->SetText("·¹¾î");
		BrokenFontActor->SetText("¡¡ÆÄ±«ÇÏ±â (¡¡ " + std::to_string(ContentConst::Goods_Item_Rare) + ")");
		BrokenKeyRender->GetTransform()->SetLocalPosition(float4(-72, 0, -1));
		BrokenGoldRender->GetTransform()->SetLocalPosition(float4(23, 0, -1));
		break;

	case ItemGrade::Unique:
		ItemGradeFont->SetText("À¯´ÏÅ©");
		BrokenFontActor->SetText("¡¡ÆÄ±«ÇÏ±â (¡¡ " + std::to_string(ContentConst::Goods_Item_Unique) + ")");
		BrokenKeyRender->GetTransform()->SetLocalPosition(float4(-72, 0, -1));
		BrokenGoldRender->GetTransform()->SetLocalPosition(float4(23, 0, -1));
		break;

	case ItemGrade::Legendary:
		ItemGradeFont->SetText("·¹Àü´õ¸®");
		BrokenFontActor->SetText("¡¡ÆÄ±«ÇÏ±â (¡¡ " + std::to_string(ContentConst::Goods_Item_Legendary) + ")");
		BrokenKeyRender->GetTransform()->SetLocalPosition(float4(-72, 0, -1));
		BrokenGoldRender->GetTransform()->SetLocalPosition(float4(23, 0, -1));
		break;
	default:
		break;
	}

	SynergyIconA->SetTexture(LocalData.GetSynergyIconTextureName(LocalData.Synergy1));
	SynergyAFont->SetText(LocalData.GetSynergyName(LocalData.Synergy1));

	if (Synergy::Count == LocalData.Synergy2)
	{
		SynergyFrame->SetScaleToTexture("Frame_1SKill.png");
		SynergyIconA->GetTransform()->SetLocalPosition(float4(-1, 18, -1.0f));
		SynergyIconA->On();
		SynergyIconB->Off();
	}
	else
	{
		SynergyFrame->SetScaleToTexture("Frame_2SKill.png");
		SynergyIconB->SetTexture(LocalData.GetSynergyIconTextureName(LocalData.Synergy2));
		SynergyBFont->SetText(LocalData.GetSynergyName(LocalData.Synergy2));

		SynergyIconA->GetTransform()->SetLocalPosition(float4(-101, 18, -1.0f));
		SynergyIconB->GetTransform()->SetLocalPosition(float4(101, 18, -1.0f));

		SynergyIconA->On();
		SynergyIconB->On();
	}

	if ("" == LocalData.Note)
	{
		NoteRender->Off();
		ItemNoteFont->Off();
	}
	else
	{
		NoteRender->On();
		ItemNoteFont->On();

		std::wstring NoteText = GameEngineString::AnsiToUniCode(LocalData.Note);

		float TextureBoardX = 380.0f;
		float TextureBoardY = 0.0f;

		float CurX = 0.0f;
		float CurY = 16.0f;

		for (size_t i = 0; i < NoteText.size(); i++)
		{
			if (L'\n' == NoteText[i])
			{
				CurX = 0;
				CurY += 16.0f;
				continue;
			}

			CurX += 16.0f * 0.7f;

			if (TextureBoardX < CurX + 16.0f)
			{
				CurX = 0;
				NoteText.insert(NoteText.begin() + i, L'\n');
				CurY += 16.0f;
			}
		}

		NoteScale.x = 414.0f;
		NoteScale.y = CurY + 20;

		ItemNoteFont->SetText(GameEngineString::UniCodeToAnsi(NoteText));

		NoteRender->GetTransform()->SetLocalScale(NoteScale);
		NoteRender->GetTransform()->SetLocalPosition(float4(0, -NoteScale.hy() + 20, -0.1f));

		ItemNoteFont->GetTransform()->SetLocalPosition(NoteRender->GetTransform()->GetLocalPosition() + float4(-190, 0, -1));
	}


	SynergyFrame->GetTransform()->SetLocalPosition(float4(0, -44 - NoteScale.y, -0.2f));
	GetItemFontActor->GetTransform()->SetLocalPosition(float4(10, -125 - NoteScale.y, -5.0f));
	BrokenFontActor->GetTransform()->SetLocalPosition(float4(10, -155 - NoteScale.y, -5.0f));

	ItemFrameRender->GetTransform()->SetLocalPosition(float4(0, -NoteScale.hy(), 0));
	ItemFrameRender->GetTransform()->SetLocalScale(BackgroundScale + float4(0, NoteScale.y, 0));

	On();
}

void ItemGearPopup::PopupOff()
{
	Off();
}

void ItemGearPopup::Start()
{
	if (nullptr == GameEngineTexture::Find("ItemPopup_Back.png"))
	{
		GameEngineDirectory Path;

		Path.MoveParentToDirectory("Resources");
		Path.Move("Resources");
		Path.Move("Texture");
		Path.Move("0_Common");
		Path.Move("UI");

		GameEngineTexture::Load(Path.GetPlusFileName("ItemPopup_Back.png").GetFullPath());
		GameEngineTexture::Load(Path.GetPlusFileName("ItemPopup_Front.png").GetFullPath());
		GameEngineTexture::Load(Path.GetPlusFileName("Frame_1SKill.png").GetFullPath());
		GameEngineTexture::Load(Path.GetPlusFileName("Frame_2SKill.png").GetFullPath());
	}


	ItemFrameRender = CreateComponent<ContentSlice9UIRenderer>();
	ItemFrameRender->SetTextureAndSlice("ItemPopup_Back.png", 0, 0, 0.59f, 0.12f);

	NoteRender = CreateComponent<ContentSlice9UIRenderer>();
	NoteRender->SetTextureAndSlice("ItemPopup_Front.png", 0.1f, 0.1f, 0.3f, 0.3f);
	NoteRender->GetTransform()->SetLocalPosition(float4(0, -6, -0.1f));

	ItemNoteFont = CreateComponent<ContentUIFontRenderer>();
	ItemNoteFont->SetFont("³Ø½¼Lv2°íµñ");
	ItemNoteFont->SetScale(16);
	ItemNoteFont->SetColor(float4(0.45882f, 0.33725f, 0.33333f, 1));
	ItemNoteFont->SetFontFlag(static_cast<FW1_TEXT_FLAG>(FW1_TEXT_FLAG::FW1_VCENTER | FW1_TEXT_FLAG::FW1_LEFT));

	SynergyFrame = CreateComponent<GameEngineUIRenderer>();
	SynergyFrame->GetTransform()->SetLocalPosition(float4(0, 0, -0.2f));

	std::shared_ptr<GameEngineComponent> SynergyIconPivot = CreateComponent<GameEngineComponent>();
	SynergyIconPivot->GetTransform()->SetParent(SynergyFrame->GetTransform());
	SynergyIconPivot->GetTransform()->SetWorldScale(float4(1, 1, 1));

	SynergyIconA = CreateComponent<GameEngineUIRenderer>();
	SynergyIconA->GetTransform()->SetParent(SynergyIconPivot->GetTransform());
	SynergyIconA->GetTransform()->SetLocalPosition(float4(0, 0, -0.3f));
	SynergyIconA->GetTransform()->SetLocalScale(float4(48, 48, 1));

	std::shared_ptr<GameEngineComponent> SynergyAPivot = CreateComponent<GameEngineComponent>();
	SynergyAPivot->GetTransform()->SetParent(SynergyIconA->GetTransform());
	SynergyAPivot->GetTransform()->SetWorldScale(float4(1, 1, 1));

	SynergyAFont = CreateComponent<ContentUIFontRenderer>();
	SynergyAFont->GetTransform()->SetParent(SynergyAPivot->GetTransform());
	SynergyAFont->SetFont("³Ø½¼Lv2°íµñ");
	SynergyAFont->SetScale(16);
	SynergyAFont->SetColor(float4(0.29411f, 0.20784f, 0.19607f, 1));
	SynergyAFont->SetFontFlag(static_cast<FW1_TEXT_FLAG>(FW1_TEXT_FLAG::FW1_VCENTER | FW1_TEXT_FLAG::FW1_CENTER));
	SynergyAFont->GetTransform()->SetLocalPosition(float4(0, -42, -1));

	SynergyIconB = CreateComponent<GameEngineUIRenderer>();
	SynergyIconB->GetTransform()->SetParent(SynergyIconPivot->GetTransform());
	SynergyIconB->GetTransform()->SetLocalPosition(float4(0, 0, -0.4f));
	SynergyIconB->GetTransform()->SetLocalScale(float4(48, 48, 1));

	std::shared_ptr<GameEngineComponent> SynergyBPivot = CreateComponent<GameEngineComponent>();
	SynergyBPivot->GetTransform()->SetParent(SynergyIconB->GetTransform());
	SynergyBPivot->GetTransform()->SetWorldScale(float4(1, 1, 1));

	SynergyBFont = CreateComponent<ContentUIFontRenderer>();
	SynergyBFont->GetTransform()->SetParent(SynergyBPivot->GetTransform());
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
	ItemNameFont->GetTransform()->SetLocalPosition(float4(0, 71, -1));

	ItemGradeFont = CreateComponent<ContentUIFontRenderer>();
	ItemGradeFont->SetFont("³Ø½¼Lv2°íµñ");
	ItemGradeFont->SetScale(16);
	ItemGradeFont->SetColor(float4(0.29411f, 0.20784f, 0.19607f, 1));
	ItemGradeFont->SetFontFlag(static_cast<FW1_TEXT_FLAG>(FW1_TEXT_FLAG::FW1_VCENTER | FW1_TEXT_FLAG::FW1_LEFT));
	ItemGradeFont->GetTransform()->SetLocalPosition(float4(-195, 33, -1));

	GetItemFontActor = GetLevel()->CreateActor<UINoteActor>();
	GetItemFontActor->GetTransform()->SetParent(GetTransform());
	GetItemFontActor->GetTransform()->SetLocalPosition(float4(10, -125, -5.0f));
	GetItemFontActor->SetText("¤± ±³Ã¼ÇÏ±â");
	GetItemFontActor->AddKeyImage("KeyUI_F.png", float4(-35, 0, -1));

	BrokenFontActor = GetLevel()->CreateActor<UINoteActor>();
	BrokenFontActor->GetTransform()->SetParent(GetTransform());
	BrokenFontActor->GetTransform()->SetLocalPosition(float4(10, -155, -5.0f));
	BrokenKeyRender = BrokenFontActor->AddKeyImage("KeyUI_F_Press.png", float4(0, 0, -1)).get();
	BrokenGoldRender = BrokenFontActor->AddKeyImage("Gold_Icon.png", float4(0, 0, -1)).get();

	Off();
}

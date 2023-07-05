#include "PrecompileHeader.h"
#include "SkullGearPopup.h"

SkullData SkullGearPopup::Data = SkullData();

SkullGearPopup::SkullGearPopup()
{
}

SkullGearPopup::~SkullGearPopup()
{
}

#include "GameEngineActorGUI.h"

void SkullGearPopup::PopupOn()
{
	if (false == ContentDatabase<SkullData, SkullGrade>::IsVaild(Data.Index))
	{
		MsgAssert_Rtti<SkullGearPopup>(" - Á¸ÀçÇÏÁö ¾Ê´Â ½ºÄÃÀÇ µ¥ÀÌÅÍ¸¦ ÂüÁ¶ÇÏ·Á Çß½À´Ï´Ù.");
		return;
	}

	float4 BackgroundScale = float4(434, 220, 1);
	float4 NoteScale = float4::Zero;


	SkullNameFont->SetText(Data.Name);

	switch (Data.Grade)
	{
	case SkullGrade::Normal:
		SkullGradeFont->SetText("ÀÏ¹Ý");
		break;

	case SkullGrade::Rare:
		SkullGradeFont->SetText("·¹¾î");
		break;

	case SkullGrade::Unique:
		SkullGradeFont->SetText("À¯´ÏÅ©");
		break;

	case SkullGrade::Legendary:
		SkullGradeFont->SetText("·¹Àü´õ¸®");
		break;
	default:
		break;
	}
	
	switch (Data.SkullType)
	{
	case SkullType::Balance:
		SkullTypeFont->SetText("¹ë·±½º");
		break;
	case SkullType::Power:
		SkullTypeFont->SetText("ÆÄ¿ö");
		break;
	case SkullType::Speed:
		SkullTypeFont->SetText("½ºÇÇµå");
		break;
	default:
		break;
	}
		

	std::shared_ptr<GameEngineActorGUI> Ptr = GameEngineGUI::FindGUIWindowConvert<GameEngineActorGUI>("GameEngineActorGUI");
	Ptr->SetTarget(SkullTypeFont->GetTransform());
	Ptr->On();

	SkillIconA->SetTexture(Data.IconName_SkillA);

	if ("Empty.png" == Data.IconName_SkillB)
	{
		SkillFrame->SetScaleToTexture("Frame_1SKill.png");

		SkillIconA->GetTransform()->SetLocalPosition(float4(-1, 18, -1.0f));
		SkillIconA->On();
		SkillIconB->Off();
	}
	else
	{
		SkillFrame->SetScaleToTexture("Frame_2SKill.png");
		SkillIconB->SetTexture(Data.IconName_SkillB);


		SkillIconA->GetTransform()->SetLocalPosition(float4(-101, 18, -1.0f));
		SkillIconB->GetTransform()->SetLocalPosition(float4(101, 18, -1.0f));

		SkillIconA->On();
		SkillIconB->On();
	}



	if ("" == Data.SkullNote)
	{
		NoteRender->Off();
	}
	else
	{
		NoteRender->On();
	}


	SkillFrame->GetTransform()->SetLocalPosition(float4(0, -44, -0.2f));
	ItemFrameRender->GetTransform()->SetLocalScale(BackgroundScale + float4(0, NoteScale.y, 0));

	On();
}

void SkullGearPopup::PopupOff()
{
	Off();
}

void SkullGearPopup::Start()
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
	NoteRender->GetTransform()->SetLocalPosition(float4(0, 0, -0.1f));

	SkillFrame = CreateComponent<GameEngineUIRenderer>();
	SkillFrame->GetTransform()->SetLocalPosition(float4(0, 0, -0.2f));

	std::shared_ptr<GameEngineComponent> SkillIconPivot = CreateComponent<GameEngineComponent>();
	SkillIconPivot->GetTransform()->SetParent(SkillFrame->GetTransform());
	SkillIconPivot->GetTransform()->SetWorldScale(float4(1, 1, 1));

	SkillIconA = CreateComponent<GameEngineUIRenderer>();
	SkillIconA->GetTransform()->SetParent(SkillIconPivot->GetTransform());
	SkillIconA->GetTransform()->SetLocalPosition(float4(0, 0, -0.3f));
	SkillIconA->GetTransform()->SetLocalScale(float4(48, 48, 1));

	SkillIconB = CreateComponent<GameEngineUIRenderer>();
	SkillIconB->GetTransform()->SetParent(SkillIconPivot->GetTransform());
	SkillIconB->GetTransform()->SetLocalPosition(float4(0, 0, -0.4f));
	SkillIconB->GetTransform()->SetLocalScale(float4(48, 48, 1));

	SkullNameFont = CreateComponent<ContentUIFontRenderer>();
	SkullNameFont->SetFont("³Ø½¼Lv2°íµñ");
	SkullNameFont->SetScale(20);
	SkullNameFont->SetColor(float4(0.29411f, 0.20784f, 0.19607f, 1));
	SkullNameFont->SetFontFlag(static_cast<FW1_TEXT_FLAG>(FW1_TEXT_FLAG::FW1_VCENTER | FW1_TEXT_FLAG::FW1_CENTER));
	SkullNameFont->GetTransform()->SetLocalPosition(float4(0, 71, -1));

	SkullGradeFont = CreateComponent<ContentUIFontRenderer>();
	SkullGradeFont->SetFont("³Ø½¼Lv2°íµñ");
	SkullGradeFont->SetScale(16);
	SkullGradeFont->SetColor(float4(0.29411f, 0.20784f, 0.19607f, 1));
	SkullGradeFont->SetFontFlag(static_cast<FW1_TEXT_FLAG>(FW1_TEXT_FLAG::FW1_VCENTER | FW1_TEXT_FLAG::FW1_LEFT));
	SkullGradeFont->GetTransform()->SetLocalPosition(float4(-195, 33, -1));

	SkullTypeFont = CreateComponent<ContentUIFontRenderer>();
	SkullTypeFont->SetFont("³Ø½¼Lv2°íµñ");
	SkullTypeFont->SetScale(16);
	SkullTypeFont->SetColor(float4(0.29411f, 0.20784f, 0.19607f, 1));
	SkullTypeFont->SetFontFlag(static_cast<FW1_TEXT_FLAG>(FW1_TEXT_FLAG::FW1_VCENTER | FW1_TEXT_FLAG::FW1_RIGHT));
	SkullTypeFont->GetTransform()->SetLocalPosition(float4(195, 33, -1));

	Off();
}

#include "PrecompileHeader.h"
#include "InventorySkullPopup.h"
#include "ContentUIRender.h"
#include "SkullData.h"

InventorySkullPopup::InventorySkullPopup()
{
}

InventorySkullPopup::~InventorySkullPopup()
{
}

void InventorySkullPopup::UpdateSkullData(size_t _DataIndex)
{
	const SkullData& FindData = ContentDatabase<SkullData, SkullGrade>::GetData(_DataIndex);

	if ("" != FindData.Name_SkillB)
	{
		PopupFrameRender->SetTexture("Inventory_Skul_Double_Frame.png");

		SkullAFont->GetTransform()->SetLocalPosition(float4(-157, -188, -2));
		SkullBFont->GetTransform()->SetLocalPosition(float4(160, -188, -2));

		SkillIconA->GetTransform()->SetLocalPosition(float4(-157, -146, -2));
		SkillIconB->GetTransform()->SetLocalPosition(float4(158, -146, -2));

		SkillIconA->SetTexture(FindData.IconName_SkillA);
		SkillIconB->SetTexture(FindData.IconName_SkillB);

		SkullAFont->On();
		SkullBFont->On();

		SkillIconA->On();
		SkillIconB->On();
	}
	else
	{
		PopupFrameRender->SetTexture("Inventory_Skul_Single_Frame.png");

		SkullAFont->GetTransform()->SetLocalPosition(float4(0, -188, -2));
		SkillIconA->GetTransform()->SetLocalPosition(float4(0, -146, -2));

		SkillIconA->SetTexture(FindData.IconName_SkillA);

		SkullAFont->On();
		SkullBFont->Off();

		SkillIconA->On();
		SkillIconB->Off();
	}

	SkullIcon->SetScaleToTexture(FindData.IconName_Inventory);

	float4 TextureScale = SkullIcon->GetTransform()->GetLocalScale() * 2.0f;

	SkullIcon->GetTransform()->SetLocalScale(TextureScale);
	SkullIcon->GetTransform()->SetLocalPosition(float4(0, 250 + TextureScale.hy(), -1));

	SkullNameFont->SetText(FindData.Name);

	switch (FindData.Grade)
	{
	case SkullGrade::Normal:
		SkullGradeFont->SetText("일반");
		break;
	case SkullGrade::Rare:
		SkullGradeFont->SetText("레어");
		break;
	case SkullGrade::Unique:
		SkullGradeFont->SetText("유니크");
		break;
	case SkullGrade::Legendary:
		SkullGradeFont->SetText("레전더리");
		break;
	default:
		break;
	}

	switch (FindData.SkullType)
	{
	case SkullType::Power:
		SkullTypeFont->SetText("파워");
		break;
	case SkullType::Balance:
		SkullTypeFont->SetText("밸런스");
		break;
	case SkullType::Speed:
		SkullTypeFont->SetText("스피드");
		break;
	default:
		break;
	}

	SkullStoryFont->SetText(FindData.StoryNote);


	if (0 != FindData.SkullNote.size())
	{
		std::wstring NoteText = GameEngineString::AnsiToUniCode(FindData.SkullNote);

		float TextureBoardX = 500.0f;
		float TextureBoardY = 0.0f;

		float CurX = 0.0f;
		float CurY = 18.0f;

		for (size_t i = 0; i < NoteText.size(); i++)
		{
			CurX += 18.0f * 0.7f;

			if (TextureBoardX < CurX + 18.0f)
			{
				CurX = 0;
				NoteText.insert(NoteText.begin() + i, L'\n');
				CurY += 18.0f;
			}
		}

		SkullNoteFont->SetText(GameEngineString::UniCodeToAnsi(NoteText));
	}
	else
	{
		SkullNoteFont->SetText("");
	}



	SwitchFont->SetText(FindData.Name_Switch);
	SkullAFont->SetText(FindData.Name_SkillA);
	SkullBFont->SetText(FindData.Name_SkillB);

}

void InventorySkullPopup::Start()
{
	std::shared_ptr<GameEngineTexture> FindTex = GameEngineTexture::Find("Inventory_Skul_Single_Frame.png");

	if (nullptr == FindTex)
	{
		MsgAssert_Rtti<InventorySkullPopup>(" - 설정하려는 텍스쳐를 찾지 못했습니다.");
		return;
	}

	float4 TexSize = { static_cast<float>(FindTex->GetWidth()), static_cast<float>(FindTex->GetHeight()) };
	TexSize.x *= 2.0f;
	TexSize.y *= 2.0f;

	PopupFrameRender = CreateComponent<GameEngineUIRenderer>();
	PopupFrameRender->SetTexture("Inventory_Skul_Single_Frame.png");
	PopupFrameRender->GetTransform()->SetLocalScale(TexSize);
	//PopupFrameRender->ColorOptionValue.MulColor = float4(1.21f, 1.21f, 1.21f, 1.0f);

	SkullIcon = CreateComponent<GameEngineUIRenderer>();
	SkullIcon->GetTransform()->SetLocalPosition(float4(0, 0, -1));
	SkullIcon->GetTransform()->SetLocalScale(float4(1, 1, 1));

	FW1_TEXT_FLAG LeftSort = static_cast<FW1_TEXT_FLAG>(FW1_TEXT_FLAG::FW1_VCENTER | FW1_TEXT_FLAG::FW1_LEFT);
	FW1_TEXT_FLAG CenterSort = static_cast<FW1_TEXT_FLAG>(FW1_TEXT_FLAG::FW1_VCENTER | FW1_TEXT_FLAG::FW1_CENTER);
	FW1_TEXT_FLAG RightSort = static_cast<FW1_TEXT_FLAG>(FW1_TEXT_FLAG::FW1_VCENTER | FW1_TEXT_FLAG::FW1_RIGHT);

	SkullNameFont = CreateNewFont(float4(0, 249, -2), 21, float4(0.302f, 0.2274f, 0.2078f, 1.0f), CenterSort);
	SkullGradeFont = CreateNewFont(float4(-238, 242, -2), 18, float4(0.5137f, 0.38f, 0.349f, 1.0f), CenterSort);
	SkullTypeFont = CreateNewFont(float4(242, 242, -2), 18, float4(0.5137f, 0.38f, 0.349f, 1.0f), CenterSort);
	SkullStoryFont = CreateNewFont(float4(0, 203, -2), 16, float4(0.5137f, 0.38f, 0.349f, 1.0f), CenterSort);
	SkullNoteFont = CreateNewFont(float4(0, 75, -2), 18, float4(0.447f, 0.34117f, 0.302f, 1.0f), CenterSort);
	SwitchFont = CreateNewFont(float4(0, -87, -2), 18, float4(0.302f, 0.2274f, 0.2078f, 1.0f), CenterSort);
	SkullAFont = CreateNewFont(float4(-50, -110, -2), 18, float4(0.302f, 0.2274f, 0.2078f, 1.0f), CenterSort);
	SkullBFont = CreateNewFont(float4(50, -110, -2), 18, float4(0.302f, 0.2274f, 0.2078f, 1.0f), CenterSort);

	SkillIconA = CreateComponent<GameEngineUIRenderer>();
	SkillIconA->GetTransform()->SetLocalScale(float4(50, 50, 1));

	SkillIconB = CreateComponent<GameEngineUIRenderer>();
	SkillIconB->GetTransform()->SetLocalScale(float4(50, 50, 1));
}

std::shared_ptr<ContentUIFontRenderer> InventorySkullPopup::CreateNewFont(const float4& _Pos, float FontSize, const float4& _Color, FW1_TEXT_FLAG _Sort)
{
	std::shared_ptr<ContentUIFontRenderer> NewFont = CreateComponent<ContentUIFontRenderer>();
	NewFont->GetTransform()->SetLocalPosition(_Pos);

	NewFont->SetFont("넥슨Lv2고딕");
	NewFont->SetScale(FontSize);
	NewFont->SetColor(_Color);
	NewFont->SetFontFlag(_Sort);

	return NewFont;
}

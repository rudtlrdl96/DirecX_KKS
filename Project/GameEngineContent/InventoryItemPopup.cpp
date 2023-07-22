#include "PrecompileHeader.h"
#include "InventoryItemPopup.h"
#include "ContentUIRender.h"
#include "ItemData.h"
#include "InventorySynergyGrade.h"
#include "Inventory.h"

InventoryItemPopup::InventoryItemPopup()
{
}

InventoryItemPopup::~InventoryItemPopup()
{
}

void InventoryItemPopup::UpdateItemData(size_t _DataIndex)
{
	const ItemData& FindData = ContentDatabase<ItemData, ItemGrade>::GetData(_DataIndex);

	SynergyAFont->GetTransform()->SetLocalPosition(float4(-157, -186, -2));
	SynergyBFont->GetTransform()->SetLocalPosition(float4(160, -186, -2));

	SynergyIconA->GetTransform()->SetLocalPosition(float4(-157, -146, -2));
	SynergyIconB->GetTransform()->SetLocalPosition(float4(158, -146, -2));

	SynergyIconA->SetTexture(FindData.GetSynergyIconTextureName(FindData.Synergy1));
	SynergyIconB->SetTexture(FindData.GetSynergyIconTextureName(FindData.Synergy2));

	ItemIcon->SetScaleToTexture(FindData.InventoryTexName);

	float4 TextureScale = ItemIcon->GetTransform()->GetLocalScale() * 2.0f;

	ItemIcon->GetTransform()->SetLocalScale(TextureScale);
	ItemIcon->GetTransform()->SetLocalPosition(float4(0, 260 + TextureScale.hy(), -1));

	ItemNameFont->SetText(FindData.Name);

	switch (FindData.Grade)
	{
	case ItemGrade::Normal:
		ItemGradeFont->SetText("일반");
		break;
	case ItemGrade::Rare:
		ItemGradeFont->SetText("레어");
		break;
	case ItemGrade::Unique:
		ItemGradeFont->SetText("유니크");
		break;
	case ItemGrade::Legendary:
		ItemGradeFont->SetText("레전더리");
		break;
	default:
		break;
	}

	ItemStoryFont->SetText(FindData.Story);

	if (0 != FindData.Note.size())
	{
		std::wstring NoteText = GameEngineString::AnsiToUniCode(FindData.Note);

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

		ItemNoteFont->SetText(GameEngineString::UniCodeToAnsi(NoteText));
	}
	else
	{
		ItemNoteFont->SetText("");
	}

	SynergyAFont->SetText(FindData.GetSynergyName(FindData.Synergy1));
	SynergyBFont->SetText(FindData.GetSynergyName(FindData.Synergy2));

	SynergyAGrade->UpdateSynergyData(FindData.Synergy1, Inventory::GetSynergyCount(FindData.Synergy1));
	SynergyBGrade->UpdateSynergyData(FindData.Synergy2, Inventory::GetSynergyCount(FindData.Synergy2));
}

void InventoryItemPopup::Start()
{
	std::shared_ptr<GameEngineTexture> FindTex = GameEngineTexture::Find("Inventory_Item_Frame.png");

	if (nullptr == FindTex)
	{
		MsgAssert_Rtti<InventoryItemPopup>(" - 설정하려는 텍스쳐를 찾지 못했습니다.");
		return;
	}

	float4 TexSize = { static_cast<float>(FindTex->GetWidth()), static_cast<float>(FindTex->GetHeight()) };
	TexSize.x *= 2.0f;
	TexSize.y *= 1.97f;

	PopupFrameRender = CreateComponent<GameEngineUIRenderer>();
	PopupFrameRender->SetTexture("Inventory_Item_Frame.png");
	PopupFrameRender->GetTransform()->SetLocalScale(TexSize);

	ItemIcon = CreateComponent<GameEngineUIRenderer>();
	ItemIcon->GetTransform()->SetLocalPosition(float4(0, 0, -1));
	ItemIcon->GetTransform()->SetLocalScale(float4(1, 1, 1));

	FW1_TEXT_FLAG LeftSort = static_cast<FW1_TEXT_FLAG>(FW1_TEXT_FLAG::FW1_VCENTER | FW1_TEXT_FLAG::FW1_LEFT);
	FW1_TEXT_FLAG CenterSort = static_cast<FW1_TEXT_FLAG>(FW1_TEXT_FLAG::FW1_VCENTER | FW1_TEXT_FLAG::FW1_CENTER);
	FW1_TEXT_FLAG RightSort = static_cast<FW1_TEXT_FLAG>(FW1_TEXT_FLAG::FW1_VCENTER | FW1_TEXT_FLAG::FW1_RIGHT);

	ItemNameFont = CreateNewFont(float4(0, 249, -2), 21, float4(0.302f, 0.2274f, 0.2078f, 1.0f), CenterSort);
	ItemGradeFont = CreateNewFont(float4(-238, 242, -2), 18, float4(0.5137f, 0.38f, 0.349f, 1.0f), CenterSort);
	ItemStoryFont = CreateNewFont(float4(0, 200, -2), 16, float4(0.5137f, 0.38f, 0.349f, 1.0f), CenterSort);
	ItemNoteFont = CreateNewFont(float4(0, 75, -2), 18, float4(0.447f, 0.34117f, 0.302f, 1.0f), CenterSort);
	SynergyAFont = CreateNewFont(float4(-50, -107, -2), 18, float4(0.302f, 0.2274f, 0.2078f, 1.0f), CenterSort);
	SynergyBFont = CreateNewFont(float4(50, -107, -2), 18, float4(0.302f, 0.2274f, 0.2078f, 1.0f), CenterSort);

	SynergyIconA = CreateComponent<GameEngineUIRenderer>();
	SynergyIconA->GetTransform()->SetLocalScale(float4(50, 50, 1));

	SynergyIconB = CreateComponent<GameEngineUIRenderer>();
	SynergyIconB->GetTransform()->SetLocalScale(float4(50, 50, 1));

	SynergyAGrade = GetLevel()->CreateActor<InventorySynergyGrade>();
	SynergyAGrade->GetTransform()->SetParent(GetTransform());
	SynergyAGrade->GetTransform()->SetLocalPosition(float4(-158, -211, -2));

	SynergyBGrade = GetLevel()->CreateActor<InventorySynergyGrade>();
	SynergyBGrade->GetTransform()->SetParent(GetTransform());
	SynergyBGrade->GetTransform()->SetLocalPosition(float4(160, -211, -2));
}

std::shared_ptr<ContentUIFontRenderer> InventoryItemPopup::CreateNewFont(const float4& _Pos, float FontSize, const float4& _Color, FW1_TEXT_FLAG _Sort)
{
	std::shared_ptr<ContentUIFontRenderer> NewFont = CreateComponent<ContentUIFontRenderer>();
	NewFont->GetTransform()->SetLocalPosition(_Pos);

	NewFont->SetFont("넥슨Lv2고딕");
	NewFont->SetScale(FontSize);
	NewFont->SetColor(_Color);
	NewFont->SetFontFlag(_Sort);

	return NewFont;
}

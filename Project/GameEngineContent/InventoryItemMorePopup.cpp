#include "PrecompileHeader.h"
#include "InventoryItemMorePopup.h"
#include "Inventory.h"
#include "InventoryItemMorePopupFont.h"

InventoryItemMorePopup::InventoryItemMorePopup()
{
}

InventoryItemMorePopup::~InventoryItemMorePopup()
{
}

void InventoryItemMorePopup::SynergyUpdate(Synergy _SynergyA, Synergy _SynergyB)
{
	SynergyFontSort(SynergyAFonts, float4(-158, 115, -2), _SynergyA);
	SynergyFontSort(SynergyBFonts, float4(158, 115, -2), _SynergyB);

	SynergyAImage->SetTexture(ItemData::GetSynergyIconTextureName(_SynergyA));
	SynergyBImage->SetTexture(ItemData::GetSynergyIconTextureName(_SynergyB));

	SynergyANameFont->SetText(ItemData::GetSynergyName(_SynergyA));
	SynergyBNameFont->SetText(ItemData::GetSynergyName(_SynergyB));

	SynergyAGradeFont->SetText(std::to_string(Inventory::GetSynergyCount(_SynergyA)));
	SynergyBGradeFont->SetText(std::to_string(Inventory::GetSynergyCount(_SynergyB)));
}

void InventoryItemMorePopup::Start()
{
	FrameRender = CreateComponent<GameEngineUIRenderer>();
	FrameRender->SetScaleToTexture("Item_Frame_MoreFrame.png", 2.0f);
		
	SynergyAImage = CreateComponent<GameEngineUIRenderer>();
	SynergyAImage->GetTransform()->SetLocalPosition(float4(-158, 200, -1));
	SynergyAImage->GetTransform()->SetLocalScale(float4(50, 50, 1));
	SynergyBImage = CreateComponent<GameEngineUIRenderer>();
	SynergyBImage->GetTransform()->SetLocalPosition(float4(158, 200, -1));
	SynergyBImage->GetTransform()->SetLocalScale(float4(50, 50, 1));

	SynergyANameFont = CreateComponent<ContentUIFontRenderer>();
	SynergyANameFont->GetTransform()->SetLocalPosition(float4(-158, 158, -1));
	SynergyANameFont->SetFont("³Ø½¼Lv2°íµñ");
	SynergyANameFont->SetScale(18);
	SynergyANameFont->SetColor(float4(0.302f, 0.2274f, 0.2078f, 1.0f));
	SynergyANameFont->SetFontFlag(static_cast<FW1_TEXT_FLAG>(FW1_TEXT_FLAG::FW1_VCENTER | FW1_TEXT_FLAG::FW1_CENTER));

	SynergyBNameFont = CreateComponent<ContentUIFontRenderer>();
	SynergyBNameFont->GetTransform()->SetLocalPosition(float4(158, 158, -1));
	SynergyBNameFont->SetFont("³Ø½¼Lv2°íµñ");
	SynergyBNameFont->SetScale(18);
	SynergyBNameFont->SetColor(float4(0.302f, 0.2274f, 0.2078f, 1.0f));
	SynergyBNameFont->SetFontFlag(static_cast<FW1_TEXT_FLAG>(FW1_TEXT_FLAG::FW1_VCENTER | FW1_TEXT_FLAG::FW1_CENTER));

	SynergyAGradeFont = CreateComponent<ContentUIFontRenderer>();
	SynergyAGradeFont->GetTransform()->SetLocalPosition(float4(-158, 132, -1));
	SynergyAGradeFont->SetFont("³Ø½¼Lv2°íµñ");
	SynergyAGradeFont->SetScale(15);
	SynergyAGradeFont->SetColor(float4(0.902f, 0.82745f, 0.7569f, 1));
	SynergyAGradeFont->SetFontFlag(static_cast<FW1_TEXT_FLAG>(FW1_TEXT_FLAG::FW1_VCENTER | FW1_TEXT_FLAG::FW1_CENTER));

	SynergyBGradeFont = CreateComponent<ContentUIFontRenderer>();
	SynergyBGradeFont->GetTransform()->SetLocalPosition(float4(158, 132, -1));
	SynergyBGradeFont->SetFont("³Ø½¼Lv2°íµñ");
	SynergyBGradeFont->SetScale(15);
	SynergyBGradeFont->SetColor(float4(0.902f, 0.82745f, 0.7569f, 1));
	SynergyBGradeFont->SetFontFlag(static_cast<FW1_TEXT_FLAG>(FW1_TEXT_FLAG::FW1_VCENTER | FW1_TEXT_FLAG::FW1_CENTER));
}

void InventoryItemMorePopup::SynergyFontSort(std::vector<std::shared_ptr<InventoryItemMorePopupFont>>& _Font, const float4& _Pos, Synergy _Synergy)
{
	for (size_t i = 0; i < _Font.size(); i++)
	{
		_Font[i]->Off();
	}

	std::vector<int> SynergyGrades = ItemData::GetSynergyGrade(_Synergy);

	for (size_t i = _Font.size(); i < SynergyGrades.size(); i++)
	{
		std::shared_ptr<InventoryItemMorePopupFont> NewFont = GetLevel()->CreateActor<InventoryItemMorePopupFont>();
		NewFont->GetTransform()->SetParent(GetTransform());
		NewFont->Off();
		_Font.push_back(NewFont);
	}

	float TotalDistance = 320.0f;
	float Inter = TotalDistance / SynergyGrades.size();

	for (size_t i = 0; i < SynergyGrades.size(); i++)
	{
		_Font[i]->GetTransform()->SetLocalPosition(_Pos - float4(0, i * Inter, 0));
		_Font[i]->SetSynergyText(_Synergy, SynergyGrades[i]);
		_Font[i]->On();
	}
}

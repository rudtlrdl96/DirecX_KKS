#include "PrecompileHeader.h"
#include "InventorySynergyFrame.h"
#include "InventorySynergyGrade.h"
#include "Inventory.h"

InventorySynergyFrame::InventorySynergyFrame()
{
}

InventorySynergyFrame::~InventorySynergyFrame()
{
}

void InventorySynergyFrame::UpdateSynergy(Synergy _Synergy)
{
	CurSynergy = _Synergy;

	int SynergyCount = Inventory::GetSynergyCount(CurSynergy);

	if (0 == SynergyCount)
	{
		Off();
		return;
	}

	On();

	SynergyImage->SetScaleToTexture(ItemData::GetSynergyIconTextureName(CurSynergy, (size_t)SynergyCount), 1.9f);

	SynergyGrade->UpdateSynergyData(CurSynergy, SynergyCount);
	SynergyNameFont->SetText(ItemData::GetSynergyName(CurSynergy));
	GradeFont->SetText(std::to_string(SynergyCount));

	std::vector<int> AllGrade = ItemData::GetSynergyGrade(CurSynergy);

	GradeFont->SetColor(DisableFontColor);

	for (int i = (int)AllGrade.size() - 1; i >= 0; --i)
	{
		if (AllGrade[i] <= SynergyCount)
		{
			if (i == (int)AllGrade.size() - 1)
			{
				GradeFont->SetColor(FullGradeFontColor);
			}
			else
			{
				GradeFont->SetColor(ActiveFontColor);
			}

			break;
		}
	}
}

void InventorySynergyFrame::Start()
{
	Frame = CreateComponent<GameEngineUIRenderer>();
	Frame->SetScaleToTexture("SynergyFrame.png", 1.9f);

	SynergyImage = CreateComponent<GameEngineUIRenderer>();
	SynergyImage->GetTransform()->SetLocalPosition(float4(-80, 4, -5));

	FW1_TEXT_FLAG CenterSort = static_cast<FW1_TEXT_FLAG>(FW1_TEXT_FLAG::FW1_VCENTER | FW1_TEXT_FLAG::FW1_CENTER);

	GradeFont = CreateNewFont(float4(-35, 3, -5), 20, DisableFontColor, CenterSort);
	SynergyNameFont = CreateNewFont(float4(45, 3, -5), 19, float4(0.294f, 0.208f, 0.196f), CenterSort);

	SynergyGrade = GetLevel()->CreateActor<InventorySynergyGrade>();
	SynergyGrade->GetTransform()->SetParent(GetTransform());
	SynergyGrade->GetTransform()->SetLocalPosition(float4(44, -20, -5));
	SynergyGrade->FullGradeColorOn();
}

std::shared_ptr<ContentUIFontRenderer> InventorySynergyFrame::CreateNewFont(const float4& _Pos, float FontSize, const float4& _Color, FW1_TEXT_FLAG _Sort)
{
	std::shared_ptr<ContentUIFontRenderer> NewFont = CreateComponent<ContentUIFontRenderer>();
	NewFont->GetTransform()->SetLocalPosition(_Pos);

	NewFont->SetFont("³Ø½¼Lv2°íµñ");
	NewFont->SetScale(FontSize);
	NewFont->SetColor(_Color);
	NewFont->SetFontFlag(_Sort);

	return NewFont;
}
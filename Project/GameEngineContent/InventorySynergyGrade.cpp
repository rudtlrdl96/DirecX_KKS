#include "PrecompileHeader.h"
#include "InventorySynergyGrade.h"

InventorySynergyGrade::InventorySynergyGrade()
{
}

InventorySynergyGrade::~InventorySynergyGrade()
{
}

void InventorySynergyGrade::UpdateSynergyData(Synergy _Synergy, int _Grade)
{
	std::vector<int> SynergyGrade = ItemData::GetSynergyGrade(_Synergy);

	if (SynergyGrade.size() > GradeFonts.size())
	{
		for (size_t i = GradeFonts.size(); i < SynergyGrade.size(); i++)
		{
			CreateGradeFont();
		}
	}

	if (SynergyGrade.size() - 1 > GradeArrows.size())
	{
		for (size_t i = GradeArrows.size(); i < SynergyGrade.size() - 1; i++)
		{
			CreateGradeArrow();
		}
	}

	for (size_t i = 0; i < GradeFonts.size(); i++)
	{
		GradeFonts[i]->SetColor(DisableFontColor);
		GradeFonts[i]->Off();
	}

	for (size_t i = 0; i < GradeArrows.size(); i++)
	{
		GradeArrows[i]->Off();
	}

	for (int i = (int)SynergyGrade.size() - 1; i >= 0 ; --i)
	{
		if (SynergyGrade[i] <= _Grade)
		{
			if (true == IsFullGradeColorOn && i == (int)SynergyGrade.size() - 1)
			{
				GradeFonts[i]->SetColor(FullGradeFontColor);
			}
			else
			{
				GradeFonts[i]->SetColor(ActiveFontColor);
			}

			break;
		}
	}

	SortActor(SynergyGrade);
}

void InventorySynergyGrade::CreateGradeArrow()
{
	std::shared_ptr<GameEngineUIRenderer> NewArrow = CreateComponent<GameEngineUIRenderer>();
	NewArrow->SetScaleToTexture("Inscription_Arrow.png");
	//float4 LocalScale = NewArrow->GetTransform()->GetLocalScale();
	NewArrow->GetTransform()->AddLocalScale(float4(0, 1, 0));

	GradeArrows.push_back(NewArrow);
}

void InventorySynergyGrade::CreateGradeFont()
{
	std::shared_ptr<ContentUIFontRenderer> NewFont = CreateComponent<ContentUIFontRenderer>();

	NewFont->SetFont("³Ø½¼Lv2°íµñ");
	NewFont->SetScale(15);
	NewFont->SetColor(DisableFontColor);

	FW1_TEXT_FLAG CenterSort = static_cast<FW1_TEXT_FLAG>(FW1_TEXT_FLAG::FW1_VCENTER | FW1_TEXT_FLAG::FW1_CENTER);
	NewFont->SetFontFlag(CenterSort);

	GradeFonts.push_back(NewFont);
}

void InventorySynergyGrade::SortActor(std::vector<int>& _Grades)
{
	size_t TotalCount = _Grades.size() + (_Grades.size() - 1);
	size_t CenterIndex = (TotalCount - 1) / 2;

	for (size_t i = 0; i < _Grades.size(); i++)
	{
		int IndexDir = static_cast<int>((i * 2) - CenterIndex);

		GradeFonts[i]->GetTransform()->SetLocalPosition(float4(20.0f * IndexDir, 0.0f, 0.0f));
		GradeFonts[i]->SetText(std::to_string(_Grades[i]));
		GradeFonts[i]->On();
	}

	for (size_t i = 0; i < _Grades.size() - 1; i++)
	{
		int IndexDir = static_cast<int>(((i * 2) + 1) - CenterIndex);

		GradeArrows[i]->GetTransform()->SetLocalPosition(float4(20.0f * IndexDir, 0.0f, 0.0f));
		GradeArrows[i]->On();
	}
}
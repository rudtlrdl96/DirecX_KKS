#include "PrecompileHeader.h"
#include "SwapSynergySlot.h"
#include "Inventory.h"

SwapSynergySlot::SwapSynergySlot()
{
}

SwapSynergySlot::~SwapSynergySlot()
{
}

void SwapSynergySlot::SetSynergy(Synergy _Synergy, int _NewSynergyGradeCount)
{
	NewSynergyCount = _NewSynergyGradeCount;
	SynergyTexRender->SetScaleToTexture(ItemData::GetSynergyIconTextureName(_Synergy), 3.0f);
	GradeFontRender->SetText(std::to_string(NewSynergyCount));

	int PrevSynergyCount = Inventory::GetSynergyCount(_Synergy);

	if (PrevSynergyCount == NewSynergyCount)
	{
		GradeFontRender->SetColor(NormalColor);
	}
	else if(PrevSynergyCount < NewSynergyCount)
	{
		GradeFontRender->SetColor(AddColor);
	}
	else
	{
		GradeFontRender->SetColor(MinusColor);
	}
}

void SwapSynergySlot::Start()
{
	FrameRender = CreateComponent<GameEngineUIRenderer>();
	FrameRender->SetScaleToTexture("ItemSelectPopup_Inscription_Frame.png", 3.0f);

	SynergyTexRender = CreateComponent<GameEngineUIRenderer>();
	SynergyTexRender->GetTransform()->SetLocalPosition(float4(0, 20, -1));
	SynergyTexRender->SetScaleToTexture("Brave.png", 3.0f);

	GradeFontRender = CreateComponent<ContentUIFontRenderer>();
	GradeFontRender->SetFont("³Ø½¼Lv2°íµñ");
	GradeFontRender->SetScale(20);
	GradeFontRender->SetColor(NormalColor);
	GradeFontRender->SetFontFlag(static_cast<FW1_TEXT_FLAG>(FW1_TEXT_FLAG::FW1_VCENTER | FW1_TEXT_FLAG::FW1_RIGHT));
	GradeFontRender->GetTransform()->SetLocalPosition(float4(6, -38, -1));
	GradeFontRender->SetText("0");
}


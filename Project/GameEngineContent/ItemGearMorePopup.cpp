#include "PrecompileHeader.h"
#include "ItemGearMorePopup.h"
#include "ItemGearMorePopupFont.h"
#include "Inventory.h"

ItemGearMorePopup::ItemGearMorePopup()
{
}

ItemGearMorePopup::~ItemGearMorePopup()
{
}

void ItemGearMorePopup::SynergyUpdate(Synergy _Synergy)
{
	for (size_t i = 0; i < NoteActors.size(); i++)
	{
		NoteActors[i]->Off();
	}

	std::vector<int> Grades = ItemData::GetSynergyGrade(_Synergy);

	for (size_t i = NoteActors.size(); i < Grades.size(); i++)
	{
		NoteActors.push_back(CreatePopupFont());
	}

	float4 StartPos = float4(0, 40, -1);
	float SizeY = 0;

	for (size_t i = 0; i < NoteActors.size(); i++)
	{
		NoteActors[i]->SetSynergyText(_Synergy, Grades[i]);
		NoteActors[i]->GetTransform()->SetLocalPosition(StartPos + float4(0, -SizeY, 0));
		NoteActors[i]->On();

		SizeY += NoteActors[i]->GetSizeY();
	}

	int CurGrade = Inventory::GetSynergyCount(_Synergy);
	int MaxGrade = Grades[Grades.size() - 1];

	SynergyImage->SetTexture(ItemData::GetSynergyIconTextureName(_Synergy));
	SynergyNameText->SetText(ItemData::GetSynergyName(_Synergy));
	GradeText->SetText(std::to_string(CurGrade) + "/" + std::to_string(MaxGrade));
}

void ItemGearMorePopup::Start()
{
	FrameRender = CreateComponent<ContentSlice9UIRenderer>();
	FrameRender->SetTextureAndSlice("ItemPopup_MoreFrame2.png", 0.04f, 0.04f, 0.247f, 0.0785f);

	SynergyImage = CreateComponent<GameEngineUIRenderer>();
	SynergyImage->GetTransform()->SetLocalPosition(float4(0, 132, -1));
	SynergyImage->GetTransform()->SetLocalScale(float4(50, 50, 1));

	SynergyNameText = CreateComponent<ContentUIFontRenderer>();
	SynergyNameText->GetTransform()->SetLocalPosition(float4(0, 89, -1));
	SynergyNameText->SetFont("³Ø½¼Lv2°íµñ");
	SynergyNameText->SetScale(17);
	SynergyNameText->SetColor(float4(0.298f, 0.204f, 0.1843f, 1));
	SynergyNameText->SetFontFlag(static_cast<FW1_TEXT_FLAG>(FW1_TEXT_FLAG::FW1_VCENTER | FW1_TEXT_FLAG::FW1_CENTER));

	GradeText = CreateComponent<ContentUIFontRenderer>();
	GradeText->GetTransform()->SetLocalPosition(float4(0, 61, -1));
	GradeText->SetFont("³Ø½¼Lv2°íµñ");
	GradeText->SetScale(15);
	GradeText->SetColor(float4(0.847f, 0.7725f, 0.7137f, 1));
	GradeText->SetFontFlag(static_cast<FW1_TEXT_FLAG>(FW1_TEXT_FLAG::FW1_VCENTER | FW1_TEXT_FLAG::FW1_CENTER));

	float4 TextureScale = FrameRender->GetTransform()->GetLocalScale();
	FrameRender->GetTransform()->SetLocalScale(TextureScale * 2.0f);
	FrameRender->SetTexturePer(float4(2.0f, 2.0f));
}

std::shared_ptr<class ItemGearMorePopupFont> ItemGearMorePopup::CreatePopupFont()
{
	std::shared_ptr<ItemGearMorePopupFont> NewFont = GetLevel()->CreateActor<ItemGearMorePopupFont>();
	NewFont->GetTransform()->SetParent(GetTransform());
	NewFont->GetTransform()->SetLocalPosition(float4::Zero);
	NewFont->Off();

	return NewFont;
}

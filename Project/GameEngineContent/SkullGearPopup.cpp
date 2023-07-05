#include "PrecompileHeader.h"
#include "SkullGearPopup.h"

SkullData SkullGearPopup::Data = SkullData();

SkullGearPopup::SkullGearPopup()
{
}

SkullGearPopup::~SkullGearPopup()
{
}

void SkullGearPopup::PopupOn()
{
	if (false == ContentDatabase<SkullData, SkullGrade>::IsVaild(Data.Index))
	{
		MsgAssert_Rtti<SkullGearPopup>(" - 존재하지 않는 스컬의 데이터를 참조하려 했습니다.");
		return;
	}

	float4 BackgroundScale = float4(434, 170, 1);
	float4 NoteScale = float4::Zero;

	if ("Empty.png" == Data.IconName_SkillB)
	{
		SkillFrame->SetScaleToTexture("Frame_1SKill.png");
	}
	else
	{
		SkillFrame->SetScaleToTexture("Frame_2SKill.png");
	}

	SkillIconA->SetScaleToTexture(Data.IconName_SkillA);
	SkillIconB->SetScaleToTexture(Data.IconName_SkillB);

	if ("" == Data.SkullNote)
	{
		NoteRender->Off();
	}
	else
	{
		NoteRender->On();
	}

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

	SkillIconB = CreateComponent<GameEngineUIRenderer>();
	SkillIconB->GetTransform()->SetParent(SkillIconPivot->GetTransform());
	SkillIconB->GetTransform()->SetLocalPosition(float4(0, 0, -0.4f));

	Off();
}

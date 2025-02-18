#include "PrecompileHeader.h"
#include "InventoryUI.h"

#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineLevel.h>

#include "ContentUIRender.h"

#include "Inventory.h"

#include "InventorySlot.h"
#include "InventoryItemPopup.h"
#include "InventoryQuintessencePopup.h"
#include "InventorySkullPopup.h"
#include "InventoryStatPopup.h"
#include "InventorySynergyFrame.h"

InventoryUI::InventoryUI()
{
}

InventoryUI::~InventoryUI()
{
}

void InventoryUI::InventoryOn()
{
	GameEngineTime::GlobalTime.SetAllUpdateOrderTimeScale(0.0f);
	GameEngineTime::GlobalTime.SetAllRenderOrderTimeScale(0.0f);

	GetContentLevel()->CallEvent("PlayerInputLock");
	GetContentLevel()->CallEvent("UseKeyOff");

	for (size_t i = 0; i < InventorySlotDatas.size(); i++)
	{
		InventorySlotDatas[i]->SetDataIndex(-1);
		InventorySlotDatas[i]->SelectOff();
	}

	InventorySlotDatas[0]->SetDataIndex(Inventory::GetMainSkull().Index);
	InventorySlotDatas[1]->SetDataIndex(Inventory::GetSubSkull().Index);

	for (size_t i = 0; i < Inventory::GetItemCount(); i++)
	{
		InventorySlotDatas[3 + i]->SetDataIndex(Inventory::GetItemIndex(i));
	}

	SlotIndex = 0;
	InventorySlotDatas[SlotIndex]->SelectOn();
	GameEngineSound::Play("UI_Inventory_Open.wav");
	On();
}

void InventoryUI::InventoryOff()
{
	GameEngineTime::GlobalTime.SetAllUpdateOrderTimeScale(1.0f);
	GameEngineTime::GlobalTime.SetAllRenderOrderTimeScale(1.0f);

	GetContentLevel()->CallEvent("PlayerInputUnLock");
	GetContentLevel()->CallEvent("UseKeyOn");
	GameEngineSound::Play("UI_Inventory_Close.wav");
	Off();
}

void InventoryUI::Start()
{
	if (false == GameEngineInput::IsKey("ShowInventoryStat"))
	{
		GameEngineInput::CreateKey("ShowInventoryStat", 'A');
		GameEngineInput::CreateKey("InventoryOff_TAB", VK_TAB);
		GameEngineInput::CreateKey("InventoryOff_ESC", VK_ESCAPE);

		GameEngineInput::CreateKey("Inventory_SlotMove_Up", VK_UP);
		GameEngineInput::CreateKey("Inventory_SlotMove_Down", VK_DOWN);
		GameEngineInput::CreateKey("Inventory_SlotMove_Left", VK_LEFT);
		GameEngineInput::CreateKey("Inventory_SlotMove_Right", VK_RIGHT);
	}

	InventoryBackRender = CreateComponent<GameEngineUIRenderer>();
	InventoryBackRender->SetTexture("Inventory_Background.png");
	InventoryBackRender->GetTransform()->SetLocalScale(GameEngineWindow::GetScreenSize());
	InventoryBackRender->GetTransform()->SetLocalPosition(float4(0, 0, 1));
	InventoryBackRender->ColorOptionValue.MulColor = float4(0.0f, 0.0f, 0.0f, 0.7f);

	MainFrameRender = CreateComponent<GameEngineUIRenderer>();
	MainFrameRender->SetTexture("Inventory_Main_Frame.png");
	MainFrameRender->GetTransform()->SetLocalScale(GameEngineWindow::GetScreenSize());
	MainFrameRender->GetTransform()->SetLocalPosition({0, 0, 0.0f});
	//MainFrameRender->ColorOptionValue.MulColor = float4(1.21f, 1.21f, 1.21f, 1.0f);

	GameEngineTransform* Trans = GetTransform();
	Trans->SetLocalPosition(float4(0, 0, -4900.0f));

	InventorySlotDatas.resize(12);

	{	
		InventorySlotDatas[0] = GetLevel()->CreateActor<InventorySlot>();
		InventorySlotDatas[0]->GetTransform()->SetParent(Trans);
		InventorySlotDatas[0]->GetTransform()->SetLocalPosition(float4{-276, 218, -5});
		InventorySlotDatas[0]->SetInventorySlotType(InventorySlotType::Skull);
		InventorySlotDatas[0]->SetMoveIndex(-1, 2, -1, 1);

		InventorySlotDatas[1] = GetLevel()->CreateActor<InventorySlot>();
		InventorySlotDatas[1]->GetTransform()->SetParent(Trans);
		InventorySlotDatas[1]->GetTransform()->SetLocalPosition(float4{-192, 218, -5});
		InventorySlotDatas[1]->SetInventorySlotType(InventorySlotType::Skull);
		InventorySlotDatas[1]->SetMoveIndex(-1, 2, 0, -1);

		InventorySlotDatas[2] = GetLevel()->CreateActor<InventorySlot>();
		InventorySlotDatas[2]->GetTransform()->SetParent(Trans);
		InventorySlotDatas[2]->GetTransform()->SetLocalPosition(float4{-234, 114, -5});
		InventorySlotDatas[2]->SetMoveIndex(0, 4, -1, -1);

		InventorySlotDatas[3] = GetLevel()->CreateActor<InventorySlot>();
		InventorySlotDatas[3]->GetTransform()->SetParent(Trans);
		InventorySlotDatas[3]->GetTransform()->SetLocalPosition(float4{ -318, 10, -5 });
		InventorySlotDatas[3]->SetInventorySlotType(InventorySlotType::Item);
		InventorySlotDatas[3]->SetMoveIndex(2, 6, -1, 4);

		InventorySlotDatas[4] = GetLevel()->CreateActor<InventorySlot>();
		InventorySlotDatas[4]->GetTransform()->SetParent(Trans);
		InventorySlotDatas[4]->GetTransform()->SetLocalPosition(float4{ -234, 10, -5 });
		InventorySlotDatas[4]->SetInventorySlotType(InventorySlotType::Item);
		InventorySlotDatas[4]->SetMoveIndex(2, 7, 3, 5);

		InventorySlotDatas[5] = GetLevel()->CreateActor<InventorySlot>();
		InventorySlotDatas[5]->GetTransform()->SetParent(Trans);
		InventorySlotDatas[5]->GetTransform()->SetLocalPosition(float4{ -150, 10, -5 });
		InventorySlotDatas[5]->SetInventorySlotType(InventorySlotType::Item);
		InventorySlotDatas[5]->SetMoveIndex(2, 8, 4, -1);

		InventorySlotDatas[6] = GetLevel()->CreateActor<InventorySlot>();
		InventorySlotDatas[6]->GetTransform()->SetParent(Trans);
		InventorySlotDatas[6]->GetTransform()->SetLocalPosition(float4{ -318, -54, -5 });
		InventorySlotDatas[6]->SetInventorySlotType(InventorySlotType::Item);
		InventorySlotDatas[6]->SetMoveIndex(3, 9, -1, 7);

		InventorySlotDatas[7] = GetLevel()->CreateActor<InventorySlot>();
		InventorySlotDatas[7]->GetTransform()->SetParent(Trans);
		InventorySlotDatas[7]->GetTransform()->SetLocalPosition(float4{ -234, -54, -5 });
		InventorySlotDatas[7]->SetInventorySlotType(InventorySlotType::Item);
		InventorySlotDatas[7]->SetMoveIndex(4, 10, 6, 8);

		InventorySlotDatas[8] = GetLevel()->CreateActor<InventorySlot>();
		InventorySlotDatas[8]->GetTransform()->SetParent(Trans);
		InventorySlotDatas[8]->GetTransform()->SetLocalPosition(float4{ -150, -54, -5 });
		InventorySlotDatas[8]->SetInventorySlotType(InventorySlotType::Item);
		InventorySlotDatas[8]->SetMoveIndex(5, 11, 7, -1);

		InventorySlotDatas[9] = GetLevel()->CreateActor<InventorySlot>();
		InventorySlotDatas[9]->GetTransform()->SetParent(Trans);
		InventorySlotDatas[9]->GetTransform()->SetLocalPosition(float4{ -318, -118, -5 });
		InventorySlotDatas[9]->SetInventorySlotType(InventorySlotType::Item);
		InventorySlotDatas[9]->SetMoveIndex(6, -1, -1, 10);

		InventorySlotDatas[10] = GetLevel()->CreateActor<InventorySlot>();
		InventorySlotDatas[10]->GetTransform()->SetParent(Trans);
		InventorySlotDatas[10]->GetTransform()->SetLocalPosition(float4{ -234, -118, -5 });
		InventorySlotDatas[10]->SetInventorySlotType(InventorySlotType::Item);
		InventorySlotDatas[10]->SetMoveIndex(7, -1, 9, 11);

		InventorySlotDatas[11] = GetLevel()->CreateActor<InventorySlot>();
		InventorySlotDatas[11]->GetTransform()->SetParent(Trans);
		InventorySlotDatas[11]->GetTransform()->SetLocalPosition(float4{ -150, -118, -5 });
		InventorySlotDatas[11]->SetInventorySlotType(InventorySlotType::Item);
		InventorySlotDatas[11]->SetMoveIndex(8, -1, 10, -1);
	}


	ItemPopup = GetLevel()->CreateActor<InventoryItemPopup>();
	ItemPopup->GetTransform()->SetParent(Trans);
	ItemPopup->GetTransform()->SetLocalPosition(float4{ 224, -80, -10 });
	ItemPopup->Off();

	QuintessencePopup = GetLevel()->CreateActor<InventoryQuintessencePopup>();
	QuintessencePopup->GetTransform()->SetParent(Trans);
	QuintessencePopup->GetTransform()->SetLocalPosition(float4{ 224, -67, -11});
	QuintessencePopup->Off();

	SkullPopup = GetLevel()->CreateActor<InventorySkullPopup>();
	SkullPopup->GetTransform()->SetParent(Trans);
	SkullPopup->GetTransform()->SetLocalPosition(float4{ 224, -75, -12 });
	SkullPopup->Off();

	StatPopup = GetLevel()->CreateActor<InventoryStatPopup>();
	StatPopup->GetTransform()->SetParent(Trans);
	StatPopup->GetTransform()->SetLocalPosition(float4{ 224, -3, -20 });
	StatPopup->Off();

	FW1_TEXT_FLAG CenterSort = static_cast<FW1_TEXT_FLAG>(FW1_TEXT_FLAG::FW1_VCENTER | FW1_TEXT_FLAG::FW1_CENTER);

	SkullTitleFont = CreateNewFont(float4(-235, 264, -20), 22, float4(0.34117f, 0.2588f, 0.153f, 1.0f), CenterSort);
	SkullTitleFont->SetText("����");
	QuintessenceTitleFont = CreateNewFont(float4(-235, 161, -20), 22, float4(0.34117f, 0.2588f, 0.153f, 1.0f), CenterSort);
	QuintessenceTitleFont->SetText("����");
	ItemTitleFont = CreateNewFont(float4(-235, 57, -20), 22, float4(0.34117f, 0.2588f, 0.153f, 1.0f), CenterSort);
	ItemTitleFont->SetText("������");

	SynergyFrames.reserve((int)Synergy::Count);

	for (size_t i = 0; i < (int)Synergy::Count; i++)
	{
		SynergyFrames.push_back(CreateSynergyFrame());
	}

	StatKeyImage = CreateComponent<GameEngineUIRenderer>();
	StatKeyImage->GetTransform()->SetLocalPosition(float4(-540, -271, -1));
	StatKeyImage->SetScaleToTexture("KeyUI_A.png", 2.0f);

	StatNameFont = CreateNewFont(float4(-474, -272, -5), 18, float4(0.8667f, 0.792f, 0.7255f, 1.0f), CenterSort);
	StatNameFont->SetText("ĳ���� ����");

}

void InventoryUI::Update(float _DeltaTime)
{
	SortSynergyFrame();

	if (true == GameEngineInput::IsPress("ShowInventoryStat"))
	{
		StatPopup->On();
		ItemPopup->Off();
		QuintessencePopup->Off();
		SkullPopup->Off();

		SkullTitleFont->Off();
		ItemTitleFont->Off();
		QuintessenceTitleFont->Off();

		return;
	}
	else
	{
		StatPopup->Off();
		SkullTitleFont->On();
		ItemTitleFont->On();
		QuintessenceTitleFont->On();
	}

	if (true == GameEngineInput::IsDown("InventoryOff_TAB") || true == GameEngineInput::IsDown("InventoryOff_ESC"))
	{
		GetContentLevel()->CallEvent("InventoryOff");
		return;
	}

	if (true == GameEngineInput::IsDown("Inventory_SlotMove_Up"))
	{
		MoveSlot_Up();
	}
	else if (true == GameEngineInput::IsDown("Inventory_SlotMove_Down"))
	{
		MoveSlot_Down();
	}
	else if (true == GameEngineInput::IsDown("Inventory_SlotMove_Left"))
	{
		MoveSlot_Left();
	}
	else if (true == GameEngineInput::IsDown("Inventory_SlotMove_Right"))
	{
		MoveSlot_Right();
	}

	UpdateInventoryFrame();
}

std::shared_ptr<ContentUIFontRenderer> InventoryUI::CreateNewFont(const float4& _Pos, float FontSize, const float4& _Color, FW1_TEXT_FLAG _Sort)
{
	std::shared_ptr<ContentUIFontRenderer> NewFont = CreateComponent<ContentUIFontRenderer>();
	NewFont->GetTransform()->SetLocalPosition(_Pos);

	NewFont->SetFont("�ؽ�Lv2����");
	NewFont->SetScale(FontSize);
	NewFont->SetColor(_Color);
	NewFont->SetFontFlag(_Sort);

	return NewFont;
}

std::shared_ptr<InventorySynergyFrame> InventoryUI::CreateSynergyFrame()
{
	std::shared_ptr<InventorySynergyFrame> NewFrame = GetLevel()->CreateActor<InventorySynergyFrame>();
	NewFrame->GetTransform()->SetParent(GetTransform());
	NewFrame->GetTransform()->SetLocalPosition(float4(0, 0, -21));

	return NewFrame;
}

void InventoryUI::UpdateInventoryFrame()
{
	StatPopup->Off();
	ItemPopup->Off();
	QuintessencePopup->Off();
	SkullPopup->Off();

	if (-1 == InventorySlotDatas[SlotIndex]->GetDataIndex())
	{
		return;
	}

	switch (InventorySlotDatas[SlotIndex]->GetInventorySlotType())
	{
	case InventorySlotType::None:
		break;

	case InventorySlotType::Skull:
		SkullPopup->UpdateSkullData(InventorySlotDatas[SlotIndex]->GetDataIndex());
		SkullPopup->On();
		break;

	case InventorySlotType::Item:
		ItemPopup->UpdateItemData(InventorySlotDatas[SlotIndex]->GetDataIndex());
		ItemPopup->On();
		break;
	default:
		break;
	}

}

bool SynergyCountCompare(std::shared_ptr<InventorySynergyFrame> _Left, std::shared_ptr<InventorySynergyFrame> _Right)
{
	int LeftCount = Inventory::GetSynergyCount(_Left->GetSynergy());
	int RightCount = Inventory::GetSynergyCount(_Right->GetSynergy());

	return LeftCount > RightCount;
}

void InventoryUI::SortSynergyFrame()
{
	for (size_t i = 0; i < (int)Synergy::Count; i++)
	{
		SynergyFrames[i]->UpdateSynergy((Synergy)i);
	}

	std::sort(SynergyFrames.begin(), SynergyFrames.end(), SynergyCountCompare);

	for (size_t i = 0; i < SynergyFrames.size(); i++)
	{
		size_t OffsetX = i / 9;
		size_t OffsetY = i % 9;

		SynergyFrames[i]->GetTransform()->SetLocalPosition(float4(-492 + (OffsetX * 247.0f), 254.0f + (-58.0f * OffsetY), -22));

		if (false == StatPopup->IsUpdate() && 0 != OffsetX)
		{
			SynergyFrames[i]->Off();
		}
	}
}

void InventoryUI::MoveSlot_Up()
{
	if (-1 != InventorySlotDatas[SlotIndex]->GetUpIndex())
	{
		InventorySlotDatas[SlotIndex]->SelectOff();
		SlotIndex = InventorySlotDatas[SlotIndex]->GetUpIndex();
		InventorySlotDatas[SlotIndex]->SelectOn();
		GameEngineSound::Play("UI_Move.wav");
	}
}

void InventoryUI::MoveSlot_Down()
{
	if (-1 != InventorySlotDatas[SlotIndex]->GetDownIndex())
	{
		InventorySlotDatas[SlotIndex]->SelectOff();
		SlotIndex = InventorySlotDatas[SlotIndex]->GetDownIndex();
		InventorySlotDatas[SlotIndex]->SelectOn();
		GameEngineSound::Play("UI_Move.wav");
	}
}

void InventoryUI::MoveSlot_Left()
{
	if (-1 != InventorySlotDatas[SlotIndex]->GetLeftIndex())
	{
		InventorySlotDatas[SlotIndex]->SelectOff();
		SlotIndex = InventorySlotDatas[SlotIndex]->GetLeftIndex();
		InventorySlotDatas[SlotIndex]->SelectOn();
		GameEngineSound::Play("UI_Move.wav");
	}
}

void InventoryUI::MoveSlot_Right()
{
	if (-1 != InventorySlotDatas[SlotIndex]->GetRightIndex())
	{
		InventorySlotDatas[SlotIndex]->SelectOff();
		SlotIndex = InventorySlotDatas[SlotIndex]->GetRightIndex();
		InventorySlotDatas[SlotIndex]->SelectOn();
		GameEngineSound::Play("UI_Move.wav");
	}
}

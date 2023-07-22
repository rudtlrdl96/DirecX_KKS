#include "PrecompileHeader.h"
#include "ItemSwapPopup.h"
#include "InventorySlot.h"
#include "Inventory.h"
#include "ItemGear.h"

ItemData ItemSwapPopup::Data;
std::function<void()> ItemSwapPopup::SwapCallback = nullptr;
std::function<void()> ItemSwapPopup::CancelCallback = nullptr;
float4 ItemSwapPopup::SpawnPos = float4::Zero;

ItemSwapPopup::ItemSwapPopup()
{
}

ItemSwapPopup::~ItemSwapPopup()
{
}

void ItemSwapPopup::PopupOn()
{
	GetContentLevel()->CallEvent("PlayerInputLock");
	GetContentLevel()->CallEvent("UseKeyOff");
	GameEngineSound::Play("UI_Inventory_Open.wav");

	for (size_t i = 0; i < ItemSlots.size(); i++)
	{
		ItemSlots[i]->SetDataIndex(-1);
		ItemSlots[i]->SelectOff();
	}

	for (size_t i = 0; i < Inventory::GetItemCount(); i++)
	{
		ItemSlots[i]->SetDataIndex(Inventory::GetItemIndex(i));
	}

	SlotIndex = 0;
	ItemSlots[SlotIndex]->SelectOn();

	On();
}

void ItemSwapPopup::PopupOff()
{
	GetContentLevel()->CallEvent("PlayerInputUnLock");
	GetContentLevel()->CallEvent("UseKeyOn");
	GameEngineSound::Play("UI_Inventory_Close.wav");
	Off();
}

void ItemSwapPopup::Start()
{
	if (false == GameEngineInput::IsKey("SwapOff"))
	{
		GameEngineInput::CreateKey("Swap", 'F');
		GameEngineInput::CreateKey("SwapOff", VK_ESCAPE);
		GameEngineInput::CreateKey("Swap_SlotMove_Up", VK_UP);
		GameEngineInput::CreateKey("Swap_SlotMove_Down", VK_DOWN);
		GameEngineInput::CreateKey("Swap_SlotMove_Left", VK_LEFT);
		GameEngineInput::CreateKey("Swap_SlotMove_Right", VK_RIGHT);
	}

	SwapBackRender = CreateComponent<GameEngineUIRenderer>();
	SwapBackRender->SetTexture("Inventory_Background.png");
	SwapBackRender->GetTransform()->SetLocalScale(GameEngineWindow::GetScreenSize());
	SwapBackRender->GetTransform()->SetLocalPosition(float4(0, 0, 1));
	SwapBackRender->ColorOptionValue.MulColor = float4(0.0f, 0.0f, 0.0f, 0.5f);

	MainFrameRender = CreateComponent<GameEngineUIRenderer>();
	MainFrameRender->SetScaleToTexture("ItemSelectPopup.png", 3.0f);
	MainFrameRender->GetTransform()->SetLocalPosition({ 0, 0, 0.0f });

	GameEngineTransform* Trans = GetTransform();

	ItemSlots.resize(9);
	{
		ItemSlots[0] = GetLevel()->CreateActor<InventorySlot>();
		ItemSlots[0]->GetTransform()->SetParent(Trans);
		ItemSlots[0]->GetTransform()->SetLocalScale(float4(1.5f, 1.5f, 1.0f));
		ItemSlots[0]->GetTransform()->SetLocalPosition(float4{ 248, 55, -5 });
		ItemSlots[0]->SetInventorySlotType(InventorySlotType::Item);
		ItemSlots[0]->SetMoveIndex(-1, 3, -1, 1);

		ItemSlots[1] = GetLevel()->CreateActor<InventorySlot>();
		ItemSlots[1]->GetTransform()->SetParent(Trans);
		ItemSlots[1]->GetTransform()->SetLocalScale(float4(1.5f, 1.5f, 1.0f));
		ItemSlots[1]->GetTransform()->SetLocalPosition(float4{ 374, 55, -5 });
		ItemSlots[1]->SetInventorySlotType(InventorySlotType::Item);
		ItemSlots[1]->SetMoveIndex(-1, 4, 0, 2);

		ItemSlots[2] = GetLevel()->CreateActor<InventorySlot>();
		ItemSlots[2]->GetTransform()->SetParent(Trans);
		ItemSlots[2]->GetTransform()->SetLocalScale(float4(1.5f, 1.5f, 1.0f));
		ItemSlots[2]->GetTransform()->SetLocalPosition(float4{ 500, 55, -5 });
		ItemSlots[2]->SetInventorySlotType(InventorySlotType::Item);
		ItemSlots[2]->SetMoveIndex(-1, 5, 1, -1);

		ItemSlots[3] = GetLevel()->CreateActor<InventorySlot>();
		ItemSlots[3]->GetTransform()->SetParent(Trans);
		ItemSlots[3]->GetTransform()->SetLocalScale(float4(1.5f, 1.5f, 1.0f));
		ItemSlots[3]->GetTransform()->SetLocalPosition(float4{ 248, -41, -5 });
		ItemSlots[3]->SetInventorySlotType(InventorySlotType::Item);
		ItemSlots[3]->SetMoveIndex(0, 6, -1, 4);

		ItemSlots[4] = GetLevel()->CreateActor<InventorySlot>();
		ItemSlots[4]->GetTransform()->SetParent(Trans);
		ItemSlots[4]->GetTransform()->SetLocalScale(float4(1.5f, 1.5f, 1.0f));
		ItemSlots[4]->GetTransform()->SetLocalPosition(float4{ 374, -41, -5 });
		ItemSlots[4]->SetInventorySlotType(InventorySlotType::Item);
		ItemSlots[4]->SetMoveIndex(1, 7, 3, 5);

		ItemSlots[5] = GetLevel()->CreateActor<InventorySlot>();
		ItemSlots[5]->GetTransform()->SetParent(Trans);
		ItemSlots[5]->GetTransform()->SetLocalScale(float4(1.5f, 1.5f, 1.0f));
		ItemSlots[5]->GetTransform()->SetLocalPosition(float4{ 500, -41, -5 });
		ItemSlots[5]->SetInventorySlotType(InventorySlotType::Item);
		ItemSlots[5]->SetMoveIndex(2, 8, 4, -1);

		ItemSlots[6] = GetLevel()->CreateActor<InventorySlot>();
		ItemSlots[6]->GetTransform()->SetParent(Trans);
		ItemSlots[6]->GetTransform()->SetLocalScale(float4(1.5f, 1.5f, 1.0f));
		ItemSlots[6]->GetTransform()->SetLocalPosition(float4{ 248, -137, -5 });
		ItemSlots[6]->SetInventorySlotType(InventorySlotType::Item);
		ItemSlots[6]->SetMoveIndex(3, -1, -1, 7);

		ItemSlots[7] = GetLevel()->CreateActor<InventorySlot>();
		ItemSlots[7]->GetTransform()->SetParent(Trans);
		ItemSlots[7]->GetTransform()->SetLocalScale(float4(1.5f, 1.5f, 1.0f));
		ItemSlots[7]->GetTransform()->SetLocalPosition(float4{ 374, -137, -5 });
		ItemSlots[7]->SetInventorySlotType(InventorySlotType::Item);
		ItemSlots[7]->SetMoveIndex(4, -1, 6, 8);

		ItemSlots[8] = GetLevel()->CreateActor<InventorySlot>();
		ItemSlots[8]->GetTransform()->SetParent(Trans);
		ItemSlots[8]->GetTransform()->SetLocalScale(float4(1.5f, 1.5f, 1.0f));
		ItemSlots[8]->GetTransform()->SetLocalPosition(float4{ 500, -137, -5 });
		ItemSlots[8]->SetInventorySlotType(InventorySlotType::Item);
		ItemSlots[8]->SetMoveIndex(5, -1, 7, -1);
	}

}

#include "GameEngineActorGUI.h"


void ItemSwapPopup::Update(float _DeltaTime)
{
	std::shared_ptr<GameEngineActorGUI> Ptr = GameEngineGUI::FindGUIWindowConvert<GameEngineActorGUI>("GameEngineActorGUI");
	Ptr->SetTarget(ItemSlots[0]->GetTransform());
	Ptr->On();

	if (true == GameEngineInput::IsUp("Swap"))
	{
		ItemData PopData = Inventory::PopItem(SlotIndex);

		{
			std::shared_ptr<ItemGear> Gear = GetLevel()->CreateActor<ItemGear>();
			Gear->Init(PopData);
			Gear->DropGear(SpawnPos);

			Gear->SetEndCallback([Gear]()
				{
					Gear->ColWaveOn();
				});
		}

		if (nullptr != SwapCallback)
		{
			SwapCallback();
			SwapCallback = nullptr;
		}

		GetContentLevel()->CallEvent("ItemSwapPopupOff");
		return;
	}

	if (true == GameEngineInput::IsDown("SwapOff"))
	{
		if (nullptr != CancelCallback)
		{
			CancelCallback();
		}

		GetContentLevel()->CallEvent("ItemSwapPopupOff");
		return;
	}

	if (true == GameEngineInput::IsDown("Swap_SlotMove_Up"))
	{
		MoveSlot_Up();
	}
	else if (true == GameEngineInput::IsDown("Swap_SlotMove_Down"))
	{
		MoveSlot_Down();
	}
	else if (true == GameEngineInput::IsDown("Swap_SlotMove_Left"))
	{
		MoveSlot_Left();
	}
	else if (true == GameEngineInput::IsDown("Swap_SlotMove_Right"))
	{
		MoveSlot_Right();
	}
}


void ItemSwapPopup::MoveSlot_Up()
{
	if (-1 != ItemSlots[SlotIndex]->GetUpIndex())
	{
		ItemSlots[SlotIndex]->SelectOff();
		SlotIndex = ItemSlots[SlotIndex]->GetUpIndex();
		ItemSlots[SlotIndex]->SelectOn();
		GameEngineSound::Play("UI_Move.wav");
	}
}

void ItemSwapPopup::MoveSlot_Down()
{
	if (-1 != ItemSlots[SlotIndex]->GetDownIndex())
	{
		ItemSlots[SlotIndex]->SelectOff();
		SlotIndex = ItemSlots[SlotIndex]->GetDownIndex();
		ItemSlots[SlotIndex]->SelectOn();
		GameEngineSound::Play("UI_Move.wav");
	}
}

void ItemSwapPopup::MoveSlot_Left()
{
	if (-1 != ItemSlots[SlotIndex]->GetLeftIndex())
	{
		ItemSlots[SlotIndex]->SelectOff();
		SlotIndex = ItemSlots[SlotIndex]->GetLeftIndex();
		ItemSlots[SlotIndex]->SelectOn();
		GameEngineSound::Play("UI_Move.wav");
	}
}

void ItemSwapPopup::MoveSlot_Right()
{
	if (-1 != ItemSlots[SlotIndex]->GetRightIndex())
	{
		ItemSlots[SlotIndex]->SelectOff();
		SlotIndex = ItemSlots[SlotIndex]->GetRightIndex();
		ItemSlots[SlotIndex]->SelectOn();
		GameEngineSound::Play("UI_Move.wav");
	}
}
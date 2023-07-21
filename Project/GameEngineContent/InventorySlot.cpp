#include "PrecompileHeader.h"
#include "InventorySlot.h"
#include "ContentUIRender.h"

InventorySlot::InventorySlot()
{
}

InventorySlot::~InventorySlot()
{
}

void InventorySlot::SetMoveIndex(size_t _Up, size_t _Down, size_t _Left, size_t _Right)
{
	UpIIndex = _Up;
	DownIIndex = _Down;
	LeftIIndex = _Left;
	RightIIndex = _Right;
}

void InventorySlot::Start()
{
	float4 FrameSize = { 53, 53 };
		
	SlotFrameRender = CreateComponent<GameEngineUIRenderer>();
	SlotFrameRender->SetTexture("Inventory_Deactivate.png");
	SlotFrameRender->GetTransform()->SetLocalScale(FrameSize);
	SlotFrameRender->GetTransform()->SetLocalPosition(float4::Zero);
	SlotFrameRender->ColorOptionValue.MulColor = float4(1.34f, 1.34f, 1.34f, 1.0f);

	SlotImageRender = CreateComponent<GameEngineUIRenderer>();
	SlotImageRender->SetTexture("Empty.png");
	SlotImageRender->GetTransform()->SetLocalScale(FrameSize);
	SlotImageRender->GetTransform()->SetLocalPosition({ 0, 0, -1.0f });

	SlotSelectRender = CreateComponent<GameEngineUIRenderer>();
	SlotSelectRender->SetTexture("Inventory_Select.png");
	SlotSelectRender->GetTransform()->SetLocalScale(FrameSize + float4(3, 3));
	SlotSelectRender->Off();
}
#include "PrecompileHeader.h"
#include "InventorySlot.h"
#include "ContentUIRender.h"
#include "SkullData.h"
#include "ItemData.h"

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

void InventorySlot::SetDataIndex(size_t _Index)
{
	DataIndex = _Index;

	if (-1 == DataIndex)
	{
		SlotFrameRender->SetTexture("Inventory_Deactivate.png");
		return;
	}

	SlotFrameRender->SetTexture("Inventory_Activate.png");
	switch (Type)
	{
	case InventorySlotType::None:
		break;
	case InventorySlotType::Skull:
	{
		const SkullData& FindData = ContentDatabase<SkullData, SkullGrade>::GetData(DataIndex);
		SlotImageRender->SetScaleToTexture(FindData.HeadTexName);
		float4 Scale = SlotImageRender->GetTransform()->GetLocalScale();
		SlotImageRender->GetTransform()->SetLocalScale(Scale * 2.0f);
	}
		break;
	case InventorySlotType::Item:
	{
		const ItemData& FindData = ContentDatabase<ItemData, ItemGrade>::GetData(DataIndex);
		SlotImageRender->SetScaleToTexture(FindData.ItemTexName);
		float4 Scale = SlotImageRender->GetTransform()->GetLocalScale();
		SlotImageRender->GetTransform()->SetLocalScale(Scale * 2.0f);
	}
		break;
	default:
		break;
	}
}

void InventorySlot::Start()
{
	float4 FrameSize = { 53, 53 };
		
	SlotFrameRender = CreateComponent<GameEngineUIRenderer>();
	SlotFrameRender->SetTexture("Inventory_Deactivate.png");
	SlotFrameRender->GetTransform()->SetLocalScale(FrameSize);
	SlotFrameRender->GetTransform()->SetLocalPosition(float4::Zero);
	//SlotFrameRender->ColorOptionValue.MulColor = float4(1.34f, 1.34f, 1.34f, 1.0f);

	SlotImageRender = CreateComponent<GameEngineUIRenderer>();
	SlotImageRender->SetTexture("Empty.png");
	SlotImageRender->GetTransform()->SetLocalScale(FrameSize);
	SlotImageRender->GetTransform()->SetLocalPosition({ 0, 0, -1.0f });

	SlotSelectRender = CreateComponent<GameEngineUIRenderer>();
	SlotSelectRender->SetTexture("Inventory_Select.png");
	SlotSelectRender->GetTransform()->SetLocalScale(FrameSize + float4(3, 3));
	SlotSelectRender->Off();
}
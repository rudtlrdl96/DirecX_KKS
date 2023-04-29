#include "PrecompileHeader.h"
#include "InventorySlot.h"

InventorySlot::InventorySlot()
{
}

InventorySlot::~InventorySlot()
{
}

void InventorySlot::Start()
{
	float4 FrameSize = { 53, 53 };
		
	SlotFrameRender = CreateComponent<GameEngineSpriteRenderer>();
	SlotFrameRender->SetPipeLine("2DTexture_ColorLight");
	SlotFrameRender->GetShaderResHelper().SetConstantBufferLink("OutPixelColor", SlotFrameColor);
	SlotFrameRender->SetTexture("Inventory_Deactivate.png");
	SlotFrameRender->GetTransform()->SetLocalScale(FrameSize);
	SlotFrameRender->GetTransform()->SetLocalPosition(float4::Zero);
	SlotFrameColor.w = 1.34f;

	SlotImageRender = CreateComponent<GameEngineSpriteRenderer>();
	SlotImageRender->SetPipeLine("2DTexture_ColorLight");
	SlotImageRender->GetShaderResHelper().SetConstantBufferLink("OutPixelColor", SlotImageColor);
	SlotImageRender->SetTexture("Empty.png");
	SlotImageRender->GetTransform()->SetLocalScale(FrameSize);
	SlotImageRender->GetTransform()->SetLocalPosition({ 0, 0, -1.0f });
}
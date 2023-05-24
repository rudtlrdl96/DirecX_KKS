#include "PrecompileHeader.h"
#include "InventorySlot.h"
#include "ContentUIRender.h"

InventorySlot::InventorySlot()
{
}

InventorySlot::~InventorySlot()
{
}

void InventorySlot::Start()
{
	float4 FrameSize = { 53, 53 };
		
	SlotFrameRender = CreateComponent<ContentUIRender>();
	SlotFrameRender->PipeSetting("2DTexture_ColorLight");
	SlotFrameRender->GetShaderResHelper().SetConstantBufferLink("ColorBuffer", SlotFrameBuffer);
	SlotFrameRender->SetTexture("Inventory_Deactivate.png");
	SlotFrameRender->GetTransform()->SetLocalScale(FrameSize);
	SlotFrameRender->GetTransform()->SetLocalPosition(float4::Zero);
	SlotFrameBuffer.Color.w = 1.34f;

	SlotImageRender = CreateComponent<ContentUIRender>();
	SlotImageRender->PipeSetting("2DTexture_ColorLight");
	SlotImageRender->GetShaderResHelper().SetConstantBufferLink("ColorBuffer", SlotImageBuffer);
	SlotImageRender->SetTexture("Empty.png");
	SlotImageRender->GetTransform()->SetLocalScale(FrameSize);
	SlotImageRender->GetTransform()->SetLocalPosition({ 0, 0, -1.0f });
}
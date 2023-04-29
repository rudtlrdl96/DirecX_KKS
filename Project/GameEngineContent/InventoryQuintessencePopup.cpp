#include "PrecompileHeader.h"
#include "InventoryQuintessencePopup.h"

InventoryQuintessencePopup::InventoryQuintessencePopup()
{
}

InventoryQuintessencePopup::~InventoryQuintessencePopup()
{
}

void InventoryQuintessencePopup::Start()
{
	std::shared_ptr<GameEngineTexture> FindTex = GameEngineTexture::Find("Inventory_Quintessence_Frame.png");

	if (nullptr == FindTex)
	{
		MsgAssert_Rtti<InventoryQuintessencePopup>(" - �����Ϸ��� �ؽ��ĸ� ã�� ���߽��ϴ�.");
		return;
	}

	float4 TexSize = { static_cast<float>(FindTex->GetWidth()), static_cast<float>(FindTex->GetHeight()) };
	TexSize.x *= 2.0f;
	TexSize.y *= 1.975f;

	PopupFrameRender = CreateComponent<GameEngineSpriteRenderer>();
	PopupFrameRender->SetPipeLine("2DTexture_ColorLight");
	PopupFrameRender->GetShaderResHelper().SetConstantBufferLink("OutPixelColor", PopupFrameColor);
	PopupFrameRender->SetTexture("Inventory_Quintessence_Frame.png");
	PopupFrameRender->GetTransform()->SetWorldScale(TexSize);

	PopupFrameColor.w = 1.21f;
}

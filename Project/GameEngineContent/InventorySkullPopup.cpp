#include "PrecompileHeader.h"
#include "InventorySkullPopup.h"
#include "ContentUIRender.h"

InventorySkullPopup::InventorySkullPopup()
{
}

InventorySkullPopup::~InventorySkullPopup()
{
}

void InventorySkullPopup::Start()
{
	std::shared_ptr<GameEngineTexture> FindTex = GameEngineTexture::Find("Inventory_Skul_Single_Frame.png");

	if (nullptr == FindTex)
	{
		MsgAssert_Rtti<InventorySkullPopup>(" - 설정하려는 텍스쳐를 찾지 못했습니다.");
		return;
	}

	float4 TexSize = { static_cast<float>(FindTex->GetWidth()), static_cast<float>(FindTex->GetHeight()) };
	TexSize.x *= 2.0f;
	TexSize.y *= 2.0f;

	PopupFrameRender = CreateComponent<ContentUIRender>();
	PopupFrameRender->PipeSetting("2DTexture_ColorLight");
	PopupFrameRender->GetShaderResHelper().SetConstantBufferLink("ColorBuffer", Buffer);
	PopupFrameRender->SetTexture("Inventory_Skul_Single_Frame.png");
	PopupFrameRender->GetTransform()->SetLocalScale(TexSize);

	Buffer.Color.w = 1.21f;
}

#include "PrecompileHeader.h"
#include "InventoryItemPopup.h"
#include "ContentUIRender.h"

InventoryItemPopup::InventoryItemPopup()
{
}

InventoryItemPopup::~InventoryItemPopup()
{
}

void InventoryItemPopup::Start()
{
	std::shared_ptr<GameEngineTexture> FindTex = GameEngineTexture::Find("Inventory_Item_Frame.png");

	if (nullptr == FindTex)
	{
		MsgAssert_Rtti<InventoryItemPopup>(" - 설정하려는 텍스쳐를 찾지 못했습니다.");
		return;
	}

	float4 TexSize = { static_cast<float>(FindTex->GetWidth()), static_cast<float>(FindTex->GetHeight()) };
	TexSize.x *= 2.0f;
	TexSize.y *= 1.97f;

	PopupFrameRender = CreateComponent<GameEngineUIRenderer>();
	PopupFrameRender->SetTexture("Inventory_Item_Frame.png");
	PopupFrameRender->GetTransform()->SetLocalScale(TexSize);
	PopupFrameRender->ColorOptionValue.MulColor = float4(1.21f, 1.21f, 1.21f, 1.0f);
}
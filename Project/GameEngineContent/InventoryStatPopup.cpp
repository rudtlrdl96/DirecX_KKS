#include "PrecompileHeader.h"
#include "InventoryStatPopup.h"

InventoryStatPopup::InventoryStatPopup()
{
}

InventoryStatPopup::~InventoryStatPopup()
{
}

void InventoryStatPopup::Start()
{
	{
		std::shared_ptr<GameEngineTexture> FindTex = GameEngineTexture::Find("Inventory_Stat_Frame.png");

		if (nullptr == FindTex)
		{
			MsgAssert_Rtti<InventoryStatPopup>(" - 설정하려는 텍스쳐를 찾지 못했습니다.");
			return;
		}

		float4 TexSize = { static_cast<float>(FindTex->GetWidth()), static_cast<float>(FindTex->GetHeight()), 1.0f};
		TexSize.x *= 2.0f;
		TexSize.y *= 2.0f;

		PopupFrameRender = CreateComponent<GameEngineSpriteRenderer>();
		PopupFrameRender->SetPipeLine("2DTexture_ColorLight");
		PopupFrameRender->SetAtlasConstantBuffer();
		PopupFrameRender->GetShaderResHelper().SetConstantBufferLink("OutPixelColor", PopupFrameColor);
		PopupFrameRender->SetTexture("Inventory_Stat_Frame.png");
		PopupFrameRender->GetTransform()->SetLocalScale(TexSize);

		PopupFrameColor.w = 1.21f;
	}

	{
		std::shared_ptr<GameEngineTexture> FindTex = GameEngineTexture::Find("Inventory_Stat_Back.png");

		if (nullptr == FindTex)
		{
			MsgAssert_Rtti<InventoryStatPopup>(" - 설정하려는 텍스쳐를 찾지 못했습니다.");
			return;
		}

		float4 TexSize = { static_cast<float>(FindTex->GetWidth()), static_cast<float>(FindTex->GetHeight()), 1.0f};
		TexSize.x *= 2.1f;
		TexSize.y *= 2.0f;

		PopupBackRender = CreateComponent<GameEngineSpriteRenderer>();
		PopupBackRender->SetPipeLine("2DTexture_ColorLight");
		PopupBackRender->SetAtlasConstantBuffer();
		PopupBackRender->GetShaderResHelper().SetConstantBufferLink("OutPixelColor", PopupBackColor);
		PopupBackRender->SetTexture("Inventory_Stat_Back.png");
		PopupBackRender->GetTransform()->SetLocalPosition(float4(-465, 1, 0));
		PopupBackRender->GetTransform()->SetLocalScale(TexSize);

		PopupBackColor.w = 1.21f;
	}
}

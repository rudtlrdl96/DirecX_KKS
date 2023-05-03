#include "PrecompileHeader.h"
#include "InventoryUI.h"

#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineLevel.h>

#include "InventorySlot.h"
#include "InventoryItemPopup.h"
#include "InventoryQuintessencePopup.h"
#include "InventorySkullPopup.h"
#include "InventoryStatPopup.h"

InventoryUI::InventoryUI()
{
}

InventoryUI::~InventoryUI()
{
}

void InventoryUI::Start()
{
	InventoryBackRender = CreateComponent<GameEngineSpriteRenderer>();
	InventoryBackRender->SetPipeLine("2DTexture_ColorLight");
	InventoryBackRender->GetShaderResHelper().SetConstantBufferLink("ColorBuffer", BackFrameTex);
	InventoryBackRender->SetTexture("Inventory_Background.png");
	InventoryBackRender->GetTransform()->SetLocalScale(GameEngineWindow::GetScreenSize());
	InventoryBackRender->GetTransform()->SetLocalPosition(float4::Zero);
	BackFrameTex.Color.w = 0.5f;

	MainFrameRender = CreateComponent<GameEngineSpriteRenderer>();
	MainFrameRender->SetPipeLine("2DTexture_ColorLight");
	MainFrameRender->GetShaderResHelper().SetConstantBufferLink("ColorBuffer", MainFrameTex);
	MainFrameRender->SetTexture("Inventory_Main_Frame.png");
	MainFrameRender->GetTransform()->SetLocalScale(GameEngineWindow::GetScreenSize());
	MainFrameRender->GetTransform()->SetLocalPosition({0, 0, -1.0f});
	MainFrameTex.Color.w = 1.21f;

	GameEngineTransform* Trans = GetTransform();

	{	
		std::shared_ptr<InventorySlot> SkullSlot0 = GetLevel()->CreateActor<InventorySlot>();
		SkullSlot0->GetTransform()->SetParent(Trans);
		SkullSlot0->GetTransform()->SetLocalPosition(float4{-275, 218, -5});

		std::shared_ptr<InventorySlot> SkullSlot1 = GetLevel()->CreateActor<InventorySlot>();
		SkullSlot1->GetTransform()->SetParent(Trans);
		SkullSlot1->GetTransform()->SetLocalPosition(float4{-192, 218, -5});
	}

	//ItemPopup = GetLevel()->CreateActor<InventoryItemPopup>();
	//ItemPopup->GetTransform()->SetParent(Trans);
	//ItemPopup->GetTransform()->SetLocalPosition(float4{ 224, -80, -10 });

	//QuintessencePopup = GetLevel()->CreateActor<InventoryQuintessencePopup>();
	//QuintessencePopup->GetTransform()->SetParent(Trans);
	//QuintessencePopup->GetTransform()->SetLocalPosition(float4{ 224, -67, -10 });

	//SkullPopup = GetLevel()->CreateActor<InventorySkullPopup>();
	//SkullPopup->GetTransform()->SetParent(Trans);
	//SkullPopup->GetTransform()->SetLocalPosition(float4{ 224, -75, -10 });

	//StatPopup = GetLevel()->CreateActor<InventoryStatPopup>();
	//StatPopup->GetTransform()->SetParent(Trans);
	//StatPopup->GetTransform()->SetLocalPosition(float4{ 224, -3, -10 });

	if (false == GameEngineInput::IsKey("ShowInventoryStat"))
	{
		GameEngineInput::CreateKey("ShowInventoryStat", 'A');
	}
}

void InventoryUI::Update(float _DeltaTime)
{
	if (true == GameEngineInput::IsPress("ShowInventoryStat"))
	{

	}
	else
	{

	}
}

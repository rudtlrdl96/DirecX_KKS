#include "PrecompileHeader.h"
#include "ShopCollector_Reroll.h"
#include "FieldNoteActor.h"
#include "Inventory.h"

ShopCollector_Reroll::ShopCollector_Reroll()
{
}

ShopCollector_Reroll::~ShopCollector_Reroll()
{
}

void ShopCollector_Reroll::CallUseEvent()
{
	if (Inventory::GetGoodsCount_Gold() < RerollPrice)
	{
		return;
	}

	if (nullptr != RerollCallback)
	{
		GameEngineSound::Play("Reroll_Interact.wav");
		RerollCallback();
	}

	Inventory::AddGoods_Gold(-RerollPrice);
	RerollBox->ChangeAnimation("Interact");
}

void ShopCollector_Reroll::Start()
{
	RerollBox = CreateComponent<GameEngineSpriteRenderer>();
	RerollBox->SetScaleRatio(2.0f);
	RerollBox->CreateAnimation({ .AnimationName = "Idle", .SpriteName = "Reroll_Idle.png", .ScaleToTexture = true });
	RerollBox->CreateAnimation({ .AnimationName = "Interact", .SpriteName = "Reroll_Interact.png", .Loop = false, .ScaleToTexture = true });
	RerollBox->ChangeAnimation("Idle");

	RerollCol = CreateComponent<GameEngineCollision>((int)CollisionOrder::UseEvent);
	RerollCol->GetTransform()->SetLocalScale(float4(108, 132, 1));
	RerollCol->SetColType(ColType::AABBBOX2D);

	RerollNote = GetLevel()->CreateActor<FieldNoteActor>();
	RerollNote->GetTransform()->SetParent(GetTransform());
	RerollNote->GetTransform()->SetLocalPosition(float4(0, -77, 1));
	RerollNote->SetText("　 재입고(0)");
	RerollNote->AddKeyImage("KeyUI_F.png", float4(-55, 0, -1));
	RerollNote->Off();
}

void ShopCollector_Reroll::Update(float _DeltaTime)
{
	if (true == RerollBox->IsAnimationEnd())
	{
		RerollBox->ChangeAnimation("Idle", -1, false);
	}

	if (true == IsFocus())
	{
		RerollNote->SetText("　 재입고(" + std::to_string(RerollPrice) + ")");
		RerollNote->On();
	}
	else
	{
		RerollNote->Off();
	}
}

#include "PrecompileHeader.h"
#include "ItemGear.h"
#include "ResultInfo.h"
#include "Player.h"
#include "Inventory.h"
#include "AnimationPartParticle.h"
#include "ItemGearPopup.h"
#include "ItemSwapPopup.h"

ItemGear::ItemGear()
{
}

ItemGear::~ItemGear()
{
}

void ItemGear::Init(size_t _ItemIndex)
{
	if (false == ContentDatabase<ItemData, ItemGrade>::IsVaild(_ItemIndex))
	{
		MsgAssert_Rtti<ItemGear>(" - 존재하지 않는 아이템의 인덱스 입니다.");
		return;
	}

	Init(ContentDatabase<ItemData, ItemGrade>::GetData(_ItemIndex));
}

void ItemGear::Init(const ItemData& _Data)
{
	Data = _Data;
	Render->SetScaleToTexture(Data.ItemTexName);

	float4 RenderScale = Render->GetTransform()->GetLocalScale();
	Render->GetTransform()->SetLocalScale(RenderScale * 2.0f);

	GearBodyCol->GetTransform()->SetLocalScale(Render->GetTransform()->GetLocalScale());
}

void ItemGear::Start()
{
	BaseGear::Start();

	ColEnterCallback = [this]()
	{
		ItemGearPopup::SetItemData(Data);
		GetContentLevel()->CallEvent("ItemGearPopupOn");
	};

	ColUpdateCallback = [this]()
	{
		ItemGearPopup::SetItemData(Data);
		GetContentLevel()->CallEvent("ItemGearPopupCheck");
	};

	ColExitCallback = [this]()
	{
		GetContentLevel()->CallEvent("ItemGearPopupOff");
	};
}

void ItemGear::UseGear()
{
	if (GearState::Fixed != State && GearState::Wave != State)
	{
		return;
	}

	if (nullptr == ColPlayer)
	{
		return;
	}


	if (9 <= Inventory::GetItemCount())
	{
		ItemSwapPopup::SetData(Data);
		ItemSwapPopup::SetSpawnPos(GetTransform()->GetWorldPosition());
		ItemSwapPopup::SetSwapCallback([this]()
		{
			++ResultInfo::GetItemCount;
			GetContentLevel()->CallEvent("ItemGearPopupOff");
			Inventory::InsertItem(Data);
			Death();
		});		
		
		ItemSwapPopup::SetSwapCancel([this]()
		{
			IsUse = false;
		});

		GetContentLevel()->CallEvent("ItemSwapPopupOn");
	}
	else
	{
		++ResultInfo::GetItemCount;
		GetContentLevel()->CallEvent("ItemGearPopupOff");

		Inventory::InsertItem(Data);
		Death();
	}
}

void ItemGear::Destroy()
{
	BaseGear::Destroy();

	if (true == IsFocus())
	{
		GetContentLevel()->CallEvent("ItemGearPopupOff");
	}

	if (false == IsUse)
	{
		for (size_t i = 0; i < 6; i++)
		{
			std::shared_ptr<AnimationPartParticle> DeadPart = GetLevel()->CreateActor<AnimationPartParticle>();

			GameEngineTransform* PartTrans = DeadPart->GetTransform();

			GameEngineRandom& MainRand = GameEngineRandom::MainRandom;

			int RandLiveTime = MainRand.RandomInt(0, 2);

			float4 Dir = float4::Up;
			Dir.RotaitonZDeg(MainRand.RandomFloat(-15, 15));
			DeadPart->Init(
				{ .AnimationName = "Idle", .SpriteName = "Goods_Gold.png", .FrameInter = 0.1f, .Loop = true, .ScaleToTexture = true }, 2.0f, Dir, MainRand.RandomFloat(700.0f, 800.0f), 0.7f + (0.05f * RandLiveTime));

			DeadPart->RotOff();

			AnimationPartParticle* GetPtr = DeadPart.get();
			DeadPart->SetEndCallback([GetPtr]()
				{
					float4 DeathPos = GetPtr->GetTransform()->GetWorldPosition();

					EffectManager::PlayEffect({ .EffectName = "GoldGoodsEffect", .Position = DeathPos });

					SoundDoubleCheck::Play("Object_GainGold.wav");
				});

			PartTrans->SetWorldPosition(GetTransform()->GetWorldPosition() + float4(0, 40));
		}

		switch (Data.Grade)
		{
		case ItemGrade::Normal:
			Inventory::AddGoods_Gold(ContentConst::Goods_Item_Normal);
			ResultInfo::GetBone += ContentConst::Goods_Item_Normal;
			break;
		case ItemGrade::Rare:
			Inventory::AddGoods_Gold(ContentConst::Goods_Item_Rare);
			ResultInfo::GetBone += ContentConst::Goods_Item_Rare;
			break;
		case ItemGrade::Unique:
			Inventory::AddGoods_Gold(ContentConst::Goods_Item_Unique);
			ResultInfo::GetBone += ContentConst::Goods_Item_Unique;
			break;
		case ItemGrade::Legendary:
			Inventory::AddGoods_Gold(ContentConst::Goods_Item_Legendary);
			ResultInfo::GetBone += ContentConst::Goods_Item_Legendary;
			break;
		default:
			break;
		}
	}
}

void ItemGear::PlayDestroyEffect()
{
	if (false == IsUse)
	{
		EffectManager::PlayEffect({ .EffectName = "DestroyItem",
			.Position = GetTransform()->GetWorldPosition() + float4(0, 30)});
	}
}
#include "PrecompileHeader.h"
#include "ShopItemGear.h"
#include "ResultInfo.h"
#include "Player.h"
#include "Inventory.h"
#include "AnimationPartParticle.h"
#include "ShopItemPopup.h"
#include "ItemSwapPopup.h"

ShopItemGear::ShopItemGear()
{
}

ShopItemGear::~ShopItemGear()
{
}

void ShopItemGear::Init(size_t _ItemIndex)
{
	if (false == ContentDatabase<ItemData, ItemGrade>::IsVaild(_ItemIndex))
	{
		MsgAssert_Rtti<ShopItemGear>(" - 존재하지 않는 아이템의 인덱스 입니다.");
		return;
	}

	Init(ContentDatabase<ItemData, ItemGrade>::GetData(_ItemIndex));
}

void ShopItemGear::Init(const ItemData& _Data)
{
	Data = _Data;
	Render->SetScaleToTexture(Data.ItemTexName);

	float4 RenderScale = Render->GetTransform()->GetLocalScale();
	Render->GetTransform()->SetLocalScale(RenderScale * 2.0f);

	GearBodyCol->GetTransform()->AddLocalPosition(float4(0, -40));
	GearBodyCol->GetTransform()->SetLocalScale(Render->GetTransform()->GetLocalScale() + float4(0, 80));

	switch (Data.Grade)
	{
	case ItemGrade::Normal:
		Price = 50;
		break;
	case ItemGrade::Rare:
		Price = 100;
		break;
	case ItemGrade::Unique:
		Price = 150;
		break;
	case ItemGrade::Legendary:
		Price = 200;
		break;
	default:
		break;
	}

}


void ShopItemGear::CallUseEvent()
{
	if (State == GearState::Fixed || State == GearState::Wave)
	{
		UseGear();
		IsUse = true;
	}
}

int ShopItemGear::GetPrice()
{
	switch (Data.Grade)
	{
	case ItemGrade::Normal:
		return 50;
	case ItemGrade::Rare:
		return 100;
	case ItemGrade::Unique:
		return 150;
	case ItemGrade::Legendary:
		return 200;
	default:
		break;
	}
	return 0;
}


void ShopItemGear::Start()
{
	IsBrokenOn = false;

	BaseGear::Start();
	GetContentLevel()->RemoveEvent("MoveStage", GetActorCode());

	ColEnterCallback = [this]()
	{
		ShopItemPopup::SetItemData(Data);
		GetContentLevel()->CallEvent("ShopItemPopupOn");
	};

	ColUpdateCallback = [this]()
	{
		ShopItemPopup::SetItemData(Data);
		GetContentLevel()->CallEvent("ShopItemPopupCheck");
	};

	ColExitCallback = [this]()
	{
		GetContentLevel()->CallEvent("ShopItemPopupOff");
	};
}

void ShopItemGear::UseGear()
{
	if (GearState::Fixed != State && GearState::Wave != State)
	{
		return;
	}

	if (nullptr == ColPlayer)
	{
		return;
	}

	if (Price > Inventory::GetGoodsCount_Gold())
	{
		return;
	}

	GameEngineSound::Play("Object_GainItem.wav");

	if (9 <= Inventory::GetItemCount())
	{
		ItemSwapPopup::SetData(Data);
		ItemSwapPopup::SetSpawnPos(GetTransform()->GetWorldPosition());
		ItemSwapPopup::SetSwapCallback([this]()
		{
			ResultInfo::AddItemCount(Data.Index);
			GetContentLevel()->CallEvent("ShopItemPopupOff");
			Inventory::AddGoods_Gold(-Price);

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
		ResultInfo::AddItemCount(Data.Index);
		GetContentLevel()->CallEvent("ShopItemPopupOff");
		Inventory::AddGoods_Gold(-Price);

		Inventory::InsertItem(Data);
		Death();
	}
}

void ShopItemGear::Destroy()
{
	if (true == IsFocus())
	{
		GetContentLevel()->CallEvent("ShopItemPopupOff");
	}
}

void ShopItemGear::PlayDestroyEffect()
{
}
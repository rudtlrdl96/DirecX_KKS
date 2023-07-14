#include "PrecompileHeader.h"
#include "SkullGear.h"
#include "Inventory.h"
#include "Player.h"
#include "SkullGearPopup.h"
#include "ResultInfo.h"

SkullGear::SkullGear()
{
}

SkullGear::~SkullGear()
{

}

void SkullGear::Init(size_t _SkullIndex)
{
	if (false == ContentDatabase<SkullData, SkullGrade>::IsVaild(_SkullIndex))
	{
		MsgAssert_Rtti<SkullGear>(" - 존재하지 않는 스컬의 인덱스 입니다.");
		return;
	}

	Init(ContentDatabase<SkullData, SkullGrade>::GetData(_SkullIndex));
}

void SkullGear::Init(const SkullData& _Data)
{
	Data = _Data;

	Render->SetScaleToTexture(Data.HeadTexName);

	float4 RenderScale = Render->GetTransform()->GetLocalScale();
	Render->GetTransform()->SetLocalScale(RenderScale * 2.0f);

	GearBodyCol->GetTransform()->SetLocalScale(Render->GetTransform()->GetLocalScale());
}

void SkullGear::Start()
{
	BaseGear::Start();

	ColEnterCallback = [this]()
	{
		SkullGearPopup::SetSkullData(Data);
		GetContentLevel()->CallEvent("SkullGearPopupOn");
	};

	ColUpdateCallback = [this]()
	{
		SkullGearPopup::SetSkullData(Data);
		GetContentLevel()->CallEvent("SkullGearPopupCheck");
	};

	ColExitCallback = [this]()
	{
		GetContentLevel()->CallEvent("SkullGearPopupOff");
	};
}

void SkullGear::UseGear()
{
	if (GearState::Fixed != State && GearState::Wave != State)
	{
		return;
	}
	 
	if (nullptr == ColPlayer)
	{
		return;
	}

	++ResultInfo::GetSkullCount;
	GetContentLevel()->CallEvent("SkullGearPopupOff");
	ColPlayer->InsertNewSkull(Data.Index);
	Death();
}

void SkullGear::Destroy()
{
	BaseGear::Destroy();

	if (true == IsFocus())
	{
		GetContentLevel()->CallEvent("SkullGearPopupOff");
	}

	if (false == IsUse)
	{
		GetContentLevel()->CallEvent("PlayerGetSkullGoodsEffect");
		
		switch (Data.Grade)
		{
		case SkullGrade::Normal:
			Inventory::AddGoods_Bone(ContentConst::Goods_Bone_Normal);
			ResultInfo::GetBone += ContentConst::Goods_Bone_Normal;
			break;
		case SkullGrade::Rare:
			Inventory::AddGoods_Bone(ContentConst::Goods_Bone_Rare);
			ResultInfo::GetBone += ContentConst::Goods_Bone_Rare;
			break;
		case SkullGrade::Unique:
			Inventory::AddGoods_Bone(ContentConst::Goods_Bone_Unique);
			ResultInfo::GetBone += ContentConst::Goods_Bone_Unique;
			break;
		case SkullGrade::Legendary:
			Inventory::AddGoods_Bone(ContentConst::Goods_Bone_Legendary);
			ResultInfo::GetBone += ContentConst::Goods_Bone_Legendary;
			break;
		default:
			break;
		}

	}
}

void SkullGear::PlayDestroyEffect()
{
	if (false == IsUse)
	{
		EffectManager::PlayEffect({ .EffectName = "DestroySkull",
	.Position = GetTransform()->GetWorldPosition() });
	}

}

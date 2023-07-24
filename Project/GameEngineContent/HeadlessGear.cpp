#include "PrecompileHeader.h"
#include "HeadlessGear.h"
#include "Inventory.h"
#include "Player.h"
#include "SkullGearPopup.h"
#include "ResultInfo.h"

HeadlessGear::HeadlessGear()
{
}

HeadlessGear::~HeadlessGear()
{
}

void HeadlessGear::Init(size_t _SkullIndex)
{
	if (false == ContentDatabase<SkullData, SkullGrade>::IsVaild(_SkullIndex))
	{
		MsgAssert_Rtti<HeadlessGear>(" - 존재하지 않는 스컬의 인덱스 입니다.");
		return;
	}

	Init(ContentDatabase<SkullData, SkullGrade>::GetData(_SkullIndex));
}

void HeadlessGear::Init(const SkullData& _Data)
{
	Data = _Data;

	Render->SetScaleToTexture(Data.HeadTexName);

	float4 RenderScale = Render->GetTransform()->GetLocalScale();
	Render->GetTransform()->SetLocalScale(RenderScale * 2.0f);

	GearBodyCol->GetTransform()->SetLocalScale(Render->GetTransform()->GetLocalScale());
}

int HeadlessGear::GetPrice()
{
	switch (Data.Grade)
	{
	case SkullGrade::Normal:
		return 1;

	case SkullGrade::Rare:
		return 2;
	case SkullGrade::Unique:
		return 3;
	case SkullGrade::Legendary:
		return 4;
	default:
		break;
	}

	return 0;
}

void HeadlessGear::Start()
{
	IsBrokenOn = false;

	BaseGear::Start();
	GetContentLevel()->RemoveEvent("MoveStage", GetActorCode());

	ColEnterCallback = [this]()
	{
		SkullGearPopup::SetSkullData(Data);
		GetContentLevel()->CallEvent("SkullGearPopupOn_BrokenOff");
	};

	ColUpdateCallback = [this]()
	{
		SkullGearPopup::SetSkullData(Data);
		GetContentLevel()->CallEvent("SkullGearPopupCheck_BrokenOff");
	};

	ColExitCallback = [this]()
	{
		GetContentLevel()->CallEvent("SkullGearPopupOff");
	};
}

void HeadlessGear::UseGear()
{
	if (GearState::Fixed != State && GearState::Wave != State)
	{
		return;
	}

	if (nullptr == ColPlayer)
	{
		return;
	}

	if (nullptr != UseCallback)
	{
		UseCallback();
	}

	ResultInfo::AddSkullCount(Data.Index);
	GetContentLevel()->CallEvent("SkullGearPopupOff");
	ColPlayer->InsertNewSkull(Data.Index, false);
	Death();
}

void HeadlessGear::Destroy()
{
	GetContentLevel()->CallEvent("SkullPopupOff");
}

void HeadlessGear::PlayDestroyEffect()
{
}
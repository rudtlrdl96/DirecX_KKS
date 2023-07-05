#include "PrecompileHeader.h"
#include "SkullGear.h"
#include "Inventory.h"
#include "Player.h"
#include "SkullGearPopup.h"

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

	Data = ContentDatabase<SkullData, SkullGrade>::GetData(_SkullIndex);

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

	ColPlayer->InsertNewSkull(Data.Index);
	Death();
}
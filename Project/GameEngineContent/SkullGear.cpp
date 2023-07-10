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
		MsgAssert_Rtti<SkullGear>(" - �������� �ʴ� ������ �ε��� �Դϴ�.");
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
}

void SkullGear::PlayDestroyEffect()
{
	if (false == IsUse)
	{
		EffectManager::PlayEffect({ .EffectName = "DestroySkull",
	.Position = GetTransform()->GetWorldPosition() });
	}

}

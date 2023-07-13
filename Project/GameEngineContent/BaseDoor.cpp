#include "PrecompileHeader.h"
#include "BaseDoor.h"

#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineCollision.h>

#include "BattleLevel.h"
#include "FieldNoteActor.h"
#include "StageRewardObject.h"

BaseDoor::BaseDoor()
{
}

BaseDoor::~BaseDoor()
{
}

void BaseDoor::SetSprite(const std::string_view& _ActiveSprite, const std::string_view& _DisableSprite)
{
	ActiveSpriteName = _ActiveSprite;
	DisableSpriteName = _DisableSprite;

	if (nullptr == DoorRender->FindAnimation(ActiveSpriteName))
	{
		DoorRender->CreateAnimation({
		.AnimationName = ActiveSpriteName,
		.SpriteName = ActiveSpriteName,
		.FrameInter = 0.1f,
		.ScaleToTexture = true});
	}

	if (nullptr == DoorRender->FindAnimation(DisableSpriteName))
	{
		DoorRender->CreateAnimation({
			.AnimationName = DisableSpriteName,
			.SpriteName = DisableSpriteName,
			.FrameInter = 0.1f,
			.ScaleToTexture = true });
	}

	if (true == IsActiveDoor)
	{
		if (nullptr != DoorRender->FindAnimation(ActiveSpriteName))
		{
			DoorRender->ChangeAnimation(ActiveSpriteName);
		}
	}
	else
	{
		if (nullptr != DoorRender->FindAnimation(DisableSpriteName))
		{
			DoorRender->ChangeAnimation(DisableSpriteName);
		}
	}
}

void BaseDoor::SetDoorType(LevelArea _Area, DoorType _Type)
{
	Area = _Area;
	Type = _Type;

	switch (Area)
	{
	case LevelArea::Opening:
	case LevelArea::ForestOfHarmory:
	{	
		switch (Type)
		{
		case DoorType::Broken:
			SetSprite("ForestOfHarmony_BrokenDoor.png", "ForestOfHarmony_BrokenDoor.png");
			MinimapImageRender->Off();
			break;
		case DoorType::Normal:
			SetSprite("ForestOfHarmony_NormalDoor_Active.png", "ForestOfHarmony_NormalDoor_Disable.png");
			break;
		case DoorType::Equip:
			SetSprite("ForestOfHarmony_EquipDoor_Active.png", "ForestOfHarmony_EquipDoor_Disable.png");
			break;
		case DoorType::Skull:
			SetSprite("ForestOfHarmony_SkullDoor_Active.png", "ForestOfHarmony_SkullDoor_Disable.png");
			break;
		case DoorType::Shop:
			SetSprite("ForestOfHarmony_ShopDoor_Active.png", "ForestOfHarmony_ShopDoor_Disable.png");
			break;
		case DoorType::MiddleBoss:
			SetSprite("ForestOfHarmony_MiddleBossDoor_Active.png", "ForestOfHarmony_MiddleBossDoor_Disable.png");
			break;
		case DoorType::BossInter:
			SetSprite("ForestOfHarmony_BossIntroDoor_Active.png", "ForestOfHarmony_BossIntroDoor_Disable.png");
			break;
		case DoorType::MainBoss:
			SetSprite("ForestOfHarmony_MainBossDoor.png", "ForestOfHarmony_MainBossDoor.png");
			break;
		default:
			break;
		}
	}
		break;
	default:
		return;
	}

}

void BaseDoor::ActiveOn()
{
	if ("" == ActiveSpriteName)
	{
		return;
	}

	if (nullptr != DoorRender->FindAnimation(ActiveSpriteName))
	{
		DoorRender->ChangeAnimation(ActiveSpriteName, static_cast<size_t>(-1), false);
	}

	IsActiveDoor = true;
}

void BaseDoor::ActiveOff()
{
	if ("" == DisableSpriteName)
	{
		return;
	}

	if (nullptr != DoorRender->FindAnimation(DisableSpriteName))
	{
		DoorRender->ChangeAnimation(DisableSpriteName, static_cast<size_t>(-1), false);
	}

	IsActiveDoor = false;
}

void BaseDoor::CallUseEvent()
{
	if (nullptr == LevelPtr)
	{
		return;
	}

	if (false == IsActiveDoor)
	{
		return;
	}

	switch (Type)
	{
	case DoorType::Broken:
		return;
	case DoorType::Shop:
		LevelPtr->MoveLevel("Shop");
		break;
	default:
		LevelPtr->MoveNextStage();
		break;
	}

	switch (Type)
	{
	case DoorType::Broken:
		BattleStage::SetNextReward(RewardType::None);
		break;
	case DoorType::Normal:
		BattleStage::SetNextReward(RewardType::Normal);
		break;
	case DoorType::Equip:
		BattleStage::SetNextReward(RewardType::Item);
		break;
	case DoorType::Skull:
		BattleStage::SetNextReward(RewardType::Skull);
		break;
	case DoorType::Shop:
		BattleStage::SetNextReward(RewardType::None);
		break;
	case DoorType::MiddleBoss:
		BattleStage::SetNextReward(RewardType::MiddleBoss);
		break;
	case DoorType::BossInter:
		BattleStage::SetNextReward(RewardType::None);
		break;
	case DoorType::MainBoss:
		BattleStage::SetNextReward(RewardType::None);
		break;
	default:
		break;
	}
}

void BaseDoor::Start()
{
	DoorRender = CreateComponent<ContentSpriteRenderer>();
	DoorRender->PipeSetting("2DTexture_Color");
	DoorRender->GetShaderResHelper().SetConstantBufferLink("ColorBuffer", Buffer);
	DoorRender->SetTexture("Empty.png");
	DoorRender->GetTransform()->SetLocalPosition(float4(0, 10, 0));
	DoorRender->SetScaleRatio(2.0f);

	DoorCollision = CreateComponent<GameEngineCollision>((int)CollisionOrder::UseEvent);
	DoorCollision->GetTransform()->SetLocalPosition(float4(0, 0, 0));
	DoorCollision->GetTransform()->SetWorldScale(float4(150, 200, 0));
	DoorCollision->SetColType(ColType::AABBBOX2D);

	NoteActor = GetLevel()->CreateActor<FieldNoteActor>();
	NoteActor->GetTransform()->SetParent(GetTransform());
	NoteActor->GetTransform()->SetLocalPosition(float4(10, -140, -100.0f));
	NoteActor->SetText("ㅁ 들어가기");
	NoteActor->AddKeyImage("KeyUI_F.png", float4(-35, 0, -1));
	NoteActor->Off();

	if (nullptr != GetLevel()->GetCamera((int)CameraOrder::MiniMap))
	{
		MinimapImageRender = CreateComponent<ContentMinimapRender>();
		MinimapImageRender->SetTexture("MinimapImage.png");
		MinimapImageRender->ColorOptionValue.PlusColor = float4(0, 0.8f, 0, 0.0f);
		MinimapImageRender->GetTransform()->SetLocalPosition(float4(0, -60, 0));
		MinimapImageRender->GetTransform()->SetLocalScale(float4(85, 120, 1));
	}

}
//#include "GameEngineActorGUI.h"

void BaseDoor::Update(float _DeltaTime)
{
	NoteActor->Off();

	if (nullptr == LevelPtr)
	{
		return;
	}

	if (false == IsActiveDoor)
	{
		return;
	}

	if (false == IsFocus())
	{
		return;
	}

	switch (Type)
	{
	case DoorType::Broken:
		break;
		NoteActor->Off();
	default:
		NoteActor->On();
		break;
	}

}
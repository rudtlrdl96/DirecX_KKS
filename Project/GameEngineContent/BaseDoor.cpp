#include "PrecompileHeader.h"
#include "BaseDoor.h"

#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineCollision.h>

#include "BattleLevel.h"

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
		.FrameInter = 0.05f,
		.ScaleToTexture = true});
	}

	if (nullptr == DoorRender->FindAnimation(DisableSpriteName))
	{
		DoorRender->CreateAnimation({
			.AnimationName = DisableSpriteName,
			.SpriteName = DisableSpriteName,
			.FrameInter = 0.05f,
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
	case LevelArea::ForestOfHamory:
	{	
		switch (Type)
		{
		case DoorType::Broken:
			SetSprite("ForestOfHarmony_BrokenDoor.png", "ForestOfHarmony_BrokenDoor.png");
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
		DoorRender->ChangeAnimation(ActiveSpriteName);
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
		DoorRender->ChangeAnimation(DisableSpriteName);
	}

	IsActiveDoor = false;
}

void BaseDoor::Start()
{
	GetTransform()->SetLocalScale(float4(2, 2, 2, 1));

	DoorRender = CreateComponent<ContentSpriteRenderer>();
	DoorRender->PipeSetting("2DTexture_ColorLight");
	DoorRender->GetShaderResHelper().SetConstantBufferLink("ColorBuffer", Buffer);
	DoorRender->SetTexture("Empty.png");
	DoorRender->GetTransform()->SetLocalPosition(float4::Zero);

	DoorCollision = CreateComponent<GameEngineCollision>();
	DoorCollision->GetTransform()->SetLocalPosition(float4(0, 0, 0));
	DoorCollision->GetTransform()->SetWorldScale(float4(150, 200, 0));

	if (false == GameEngineInput::IsKey("UseKey"))
	{
		GameEngineInput::CreateKey("UseKey", 'F');
	}
}

void BaseDoor::Update(float _DeltaTime)
{
	if (nullptr == LevelPtr)
	{
		return;
	}

	if (false == IsActiveDoor)
	{
		return;
	}

	if (nullptr == DoorCollision->Collision((int)CollisionOrder::Player, ColType::AABBBOX2D, ColType::AABBBOX2D))
	{
		return;
	}

	if (true == GameEngineInput::IsDown("UseKey"))
	{
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
	}
}

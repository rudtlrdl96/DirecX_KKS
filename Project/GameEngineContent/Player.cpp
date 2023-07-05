#include "PrecompileHeader.h"
#include "Player.h"
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineCollision.h>
#include <GameEnginePlatform/GameEngineInput.h>

#include "BattleActorHealFont.h"
#include "CollisionDebugRender.h"

#include "PlayerHitFade.h"
#include "PlayerState.h"
#include "PlayerStateFrame.h"
#include "Inventory.h"
#include "BaseQuintessence.h"

#include "BoneSkull.h"
#include "ChiefGuard.h"
#include "WolfSkull_Normal.h"
#include "WolfSkull_Rare.h"
#include "WolfSkull_Unique.h"
#include "WolfSkull_Legandary.h"

#include "MinotaurusSkull_Rare.h"
#include "MinotaurusSkull_Unique.h"
#include "MinotaurusSkull_Legendary.h"

#include "BattleActorDamageFont.h"

#include "ContentLevel.h"
#include "SkullGear.h"

Player::Player()
{
}

Player::~Player()
{
	if (nullptr != StateFrame)
	{
		StateFrame->Death();
		StateFrame = nullptr;
	}

	if (nullptr != HitFade)
	{
		HitFade->Death();
		HitFade = nullptr;
	}
}

void Player::Destroy()
{
	ContentLevel* LevelPtr = GetContentLevel();
	LevelPtr->RemoveEvent("PlayerInputLock", GetActorCode());
	LevelPtr->RemoveEvent("PlayerInputUnlock", GetActorCode());
	LevelPtr->RemoveEvent("PlayerLookLeft", GetActorCode());
	LevelPtr->RemoveEvent("PlayerLookRight", GetActorCode());
}

void Player::SetInventoryData()
{
	const SkullData& MainData = Inventory::GetMainSkull();
	const SkullData& SubData = Inventory::GetSubSkull();

	MainSkull = CreateNewSkull(MainData.Index);

	if (static_cast<size_t>(-1) != SubData.Index)
	{
		SubSkull = CreateNewSkull(SubData.Index);
	}

	if (nullptr == MainSkull)
	{
		MsgAssert_Rtti<Player>(" - 메인 스컬 정보가 존재하지 않습니다");
		return;
	}

	MainSkull->On();
}

void Player::InsertNewSkull(size_t _SkullIndex)
{
	const SkullData& CreateData = ContentDatabase<SkullData, SkullGrade>::GetData(_SkullIndex);

	if (nullptr == SubSkull)
	{
		Inventory::SetSubSkull(CreateData);
		SubSkull = CreateNewSkull(_SkullIndex);
	}
	else
	{
		std::shared_ptr<SkullGear> Gear = GetLevel()->CreateActor<SkullGear>();

		Gear->DropGear(GetTransform()->GetWorldPosition() + float4(0, 20, -1));
		Gear->Init(MainSkull->Data.Index);

		MainSkull->Death();
		MainSkull = nullptr;
		Inventory::SetMainSkull(CreateData);
		MainSkull = CreateNewSkull(_SkullIndex);
		MainSkull->On();
	}
}

void Player::ForceSwapSkull()
{
	if (nullptr == SubSkull)
	{
		return;
	}

	Inventory::SwapSkull();

	std::shared_ptr<PlayerBaseSkull> TempSkull = SubSkull;
	SubSkull = MainSkull;
	MainSkull = TempSkull;

	MainSkull->On();
	SubSkull->Off();
}

void Player::HitPlayer(float _Damage, const float4& _HitForce)
{
	if (nullptr == MainSkull)
	{
		MsgAssert_Rtti<Player>(" - 스컬 데이터가 존재하지 않는데 플레이어를 공격하려 했습니다");
		return;
	}

	if (0.0f < HitWaitTime)
	{
		return;
	}

	if (true == MainSkull->DashAvoidance)
	{
		return;
	}

	if (SkullType::Power == MainSkull->GetSkullType())
	{
		_Damage *= 0.8f;
	}

	PlayerState::HP -= _Damage;

	if (true == Cheat_HP && 1.0f > PlayerState::HP)
	{
		PlayerState::HP = 1.0f;
	}

	std::shared_ptr<BattleActorDamageFont> NewDamageFont = GetLevel()->CreateActor<BattleActorDamageFont>();

	float4 FontColor;

	NewDamageFont->InitFont({
		.Damage = _Damage,
		.FontSize = 30,
		.FontColor = float4(1, 0.2509f, 0.1647f, 1),
		.Pos = GetTransform()->GetWorldPosition() + float4(0, 50, -100),
		.Dir = float4(0, 1000, 0),
		.MoveSpeed = 700,
		.RandX = 20.0f,
		.LiveTime = 0.8f,
		});

	HitWaitTime = 0.1f;
	HitFade->Active();
	MainSkull->BattleActorRigidbody.AddVelocity(_HitForce);
	MainSkull->IsHit = true;
	MainSkull->IsHitEffectOn = true;
	MainSkull->HitEffect(HitEffectType::Normal);
	MainSkull->HitPush();
}

void Player::HealPlayer(float _Heal, const float4& _HealForce)
{
	PlayerState::HP += _Heal;

	if (PlayerState::HP > PlayerState::MaxHP)
	{
		PlayerState::HP = PlayerState::MaxHP;
	}

	std::shared_ptr<BattleActorHealFont> NewDamageFont = GetLevel()->CreateActor<BattleActorHealFont>();

	float4 FontColor = float4(0.3607f, 0.9215f, 0.0784f, 1);

	NewDamageFont->InitFont({
		.Damage = _Heal,
		.FontSize = 34,
		.FontColor = FontColor,
		.Pos = GetTransform()->GetWorldPosition() + float4(GameEngineRandom::MainRandom.RandomFloat(-30, 30), 70, -100),
		.Dir = _HealForce,
		.MoveSpeed = 100,
		.RandX = 30.0f,
		.LiveTime = 0.55f,
		});
}

void Player::AddPushPlayer(const float4& _HitForce)
{
	if (nullptr == MainSkull)
	{
		MsgAssert_Rtti<Player>(" - 스컬 데이터가 존재하지 않는데 플레이어를 밀어내려 했습니다");
		return;
	}

	MainSkull->BattleActorRigidbody.AddVelocity(_HitForce);
}

void Player::SetPushPlayer(const float4& _HitForce)
{
	if (nullptr == MainSkull)
	{
		MsgAssert_Rtti<Player>(" - 스컬 데이터가 존재하지 않는데 플레이어를 밀어내려 했습니다");
		return;
	}

	MainSkull->BattleActorRigidbody.SetVelocity(_HitForce);
}

void Player::InputLock()
{
	IsInputLockValue = true;
}

void Player::InputUnlock()
{
	IsInputUnlockWait = true;
}

void Player::ActivePlayerFrame()
{
	StateFrame->On();
}

void Player::DisablePlayerFrame()
{
	StateFrame->Off();
}

void Player::PlayStoryMove(const float4& _StoryMovePos, std::function<void()> _EndCallback)
{
	MainSkull->PlayStoryMove(_StoryMovePos, _EndCallback);
}


#include "ContentUIRender.h"

void Player::Start()
{
	if (false == GameEngineInput::IsKey("Cheat_Attack"))
	{
		GameEngineInput::CreateKey("Cheat_Attack", '7');
		GameEngineInput::CreateKey("Cheat_HP", '8');
		GameEngineInput::CreateKey("Cheat_GearTest", '0');
	}

	CheatDebugComp_Attack = CreateComponent<GameEngineComponent>();
	CheatDebugComp_Attack->GetTransform()->SetLocalPosition(float4(-30, 60, 0));
	CheatDebugComp_Attack->GetTransform()->SetLocalScale(float4(10, 10, 1));

	CheatDebugComp_HP = CreateComponent<GameEngineComponent>();
	CheatDebugComp_HP->GetTransform()->SetLocalPosition(float4(30, 60, 0));
	CheatDebugComp_HP->GetTransform()->SetLocalScale(float4(10, 10, 1));

	PlayerBodyCol = CreateComponent<GameEngineCollision>((int)CollisionOrder::Player);
	PlayerBodyCol->GetTransform()->SetLocalPosition(float4(0.0f, 30.0f, 1.0f));
	PlayerBodyCol->GetTransform()->SetWorldScale(float4(30.0f, 60.0f, 1.0f));
	PlayerBodyCol->GetTransform()->SetWorldRotation(float4::Zero);
	PlayerBodyCol->SetColType(ColType::AABBBOX2D);

	StateFrame = GetLevel()->CreateActor<PlayerStateFrame>();
	StateFrame->SetParentPlayer(this);

	HitFade = GetLevel()->CreateActor<PlayerHitFade>();

	CheatRender_HP = CreateComponent<GameEngineFontRenderer>();
	CheatRender_HP->SetFont("Perfect DOS VGA 437");
	CheatRender_HP->GetTransform()->SetLocalPosition(float4(0, 120, -1));
	CheatRender_HP->SetText("체력 치트 ON");
	CheatRender_HP->SetScale(20);
	CheatRender_HP->SetColor(float4(0, 1, 0, 1));
	CheatRender_HP->SetFontFlag(FW1_TEXT_FLAG::FW1_CENTER);
	CheatRender_HP->Off();

	CheatRender_Attack = CreateComponent<GameEngineFontRenderer>();
	CheatRender_Attack->SetFont("Perfect DOS VGA 437");
	CheatRender_Attack->GetTransform()->SetLocalPosition(float4(0, 100, -1));
	CheatRender_Attack->SetText("공격력 치트 ON");
	CheatRender_Attack->SetScale(20);
	CheatRender_Attack->SetFontFlag(FW1_TEXT_FLAG::FW1_CENTER);
	CheatRender_Attack->SetColor(float4(1, 0, 0, 1));
	CheatRender_Attack->Off();

	GetContentLevel()->AddEvent("PlayerInputLock", GetActorCode(), [this]()
		{
			InputLock();
		});

	GetContentLevel()->AddEvent("PlayerInputUnlock", GetActorCode(), [this]()
		{
			InputUnlock();
		});

	GetContentLevel()->AddEvent("PlayerLookLeft", GetActorCode(), [this]()
		{
			MainSkull->SetViewDir(ActorViewDir::Left);
		});

	GetContentLevel()->AddEvent("PlayerLookRight", GetActorCode(), [this]()
		{
			MainSkull->SetViewDir(ActorViewDir::Right);
		});
}

void Player::Update(float _DeltaTime)
{
	if (true == IsInputUnlockWaitEnd)
	{
		IsInputUnlockWaitEnd = false;
		IsInputLockValue = false;
	}

	if (true == IsInputUnlockWait)
	{
		IsInputUnlockWait = false;
		IsInputUnlockWaitEnd = true;
	}

	HitWaitTime -= _DeltaTime;	
	SwitchCoolTime += _DeltaTime;

	if (true == GameEngineInput::IsDown("Cheat_Attack"))
	{
		Cheat_Attack = !Cheat_Attack;

		if (true == Cheat_Attack)
		{
			MeleeAttack = 100;
			MagicAttack = 100;

			CheatRender_Attack->On();
		}
		else
		{
			MeleeAttack = 10;
			MagicAttack = 10;

			CheatRender_Attack->Off();
		}
	}

	if (true == GameEngineInput::IsDown("Cheat_HP"))
	{
		Cheat_HP = !Cheat_HP;

		if (true == Cheat_HP)
		{
			CheatRender_HP->On();
		}
		else
		{
			CheatRender_HP->Off();
		}
	}

	if (true == GameEngineInput::IsDown("Cheat_GearTest"))
	{
		//std::shared_ptr<BaseGear> Gear = GetLevel()->CreateActor<BaseGear>();
		//Gear->DropGear(GetTransform()->GetWorldPosition());

		float4 PlayerPos = GetTransform()->GetWorldPosition() + float4(0, 40, -1); 

		{
			std::shared_ptr<SkullGear> Gear = GetLevel()->CreateActor<SkullGear>();
			Gear->Init(1);
			Gear->DropGear_Bezier(PlayerPos, PlayerPos);
			Gear->BlackAndWhiteColorOn();
			Gear->SetEndCallback([Gear]()
				{
					Gear->BlackAndWhiteEffectOn();
					Gear->ColWaveOn();
				});
		}

		{
			std::shared_ptr<SkullGear> Gear = GetLevel()->CreateActor<SkullGear>();
			Gear->Init(300);
			Gear->DropGear_Bezier(PlayerPos, PlayerPos + float4(-70, 0));
			Gear->BlackAndWhiteColorOn();
			Gear->SetEndCallback([Gear]()
				{
					Gear->BlackAndWhiteEffectOn();
					Gear->ColWaveOn();
				});
		}

		{
			std::shared_ptr<SkullGear> Gear = GetLevel()->CreateActor<SkullGear>();
			Gear->Init(301);
			Gear->DropGear_Bezier(PlayerPos, PlayerPos + float4(70, 0));
			Gear->BlackAndWhiteColorOn();
			Gear->SetEndCallback([Gear]()
				{
					Gear->BlackAndWhiteEffectOn();
					Gear->ColWaveOn();
				});
		}
	}

	if (PlayerState::HP <= 0.0f)
	{
		std::shared_ptr<ContentLevel> CastingLevel = GetLevel()->DynamicThis<ContentLevel>();

		if (nullptr == CastingLevel) 
		{ 
			return;
		}

		CameraController& CamCtrl = CastingLevel->GetCamCtrl();

		CamCtrl.EffectScaleRatio(1.0f, 0.7f, 1.5f);

		GameEngineTime::GlobalTime.SetAllUpdateOrderTimeScale(0.1f);
		GameEngineTime::GlobalTime.SetAllRenderOrderTimeScale(0.1f);

		std::shared_ptr<GameEngineActor> HeadPart = MainSkull->SkullDeath();
		
		if (nullptr != HeadPart)
		{
			CamCtrl.SetLookatTarget(HeadPart);
			CamCtrl.DisalbeForceLookAt();
		}
		
		StateFrame->Death();
		Death();
		return;
	}

	if (true == GameEngineInput::IsDown("PlayerCollisionDebugSwitch"))
	{
		if (true == IsDebug())
		{
			DebugOff();
		}
		else
		{
			DebugOn();
			CreateColDebugRender();
		}
	}

	if (nullptr == MainSkull)
	{
		MsgAssert_Rtti<Player>(" - 메인 스컬이 존재하지 않습니다.");
		return;
	}

	if (nullptr != SubSkull && true == MainSkull->IsSwitch() && SwitchCoolTime >= SwitchCoolEndTime)
	{
		SwitchCoolTime = 0.0f;
		DebugOff();

		ActorViewDir Dir = MainSkull->GetViewDir();

		EffectManager::PlayEffect({.EffectName = "SwitchEffect", 
			.Position = GetTransform()->GetWorldPosition() + float4(0, 40, 0),
			.FlipX = Dir == ActorViewDir::Left});

 		SubSkull->PlayerFSM.ChangeState("Switch");
		SubSkull->SetViewDir(Dir);
		SubSkull->ChangeSwitchStart();
		SubSkull->On();
		SubSkull->DebugOff();

		MainSkull->CaptureRenderTex(float4(0.85f, 0.2f, 0.92f, 1.0f), float4(0.85f, 0.2f, 0.92f, 0.0f), 1.5f);
		MainSkull->Off();
		MainSkull->ChangeSwitchEnd();
		MainSkull->DebugOff();
		MainSkull->IsSwitchValue = false;

		Inventory::SwapSkull();

		std::shared_ptr<PlayerBaseSkull> TempPtr = MainSkull;
		MainSkull = SubSkull;
		SubSkull = TempPtr;
	}

	if (nullptr != MainSkull)
	{
		MainSkull->CoolTimeCheck(_DeltaTime);
		MainSkull->IsSwitchValue = false;
	}

	if (nullptr != SubSkull)
	{
		SubSkull->CoolTimeCheck(_DeltaTime);
		SubSkull->IsSwitchValue = false;
	}
}

void Player::LevelChangeEnd()
{
	if (nullptr != StateFrame)
	{
		StateFrame->Death();
		StateFrame = nullptr;
	}

	if (nullptr != HitFade)
	{
		HitFade->Death();
		HitFade = nullptr;
	}
}

std::shared_ptr<PlayerBaseSkull> Player::CreateNewSkull(size_t _Index)
{
	std::shared_ptr<PlayerBaseSkull> NewSkull = nullptr;

	switch (_Index)
	{
	case 0: // 리틀본
		NewSkull = GetLevel()->CreateActor<BoneSkull>();
		break;
	case 1: // 웨어울프
		NewSkull = GetLevel()->CreateActor<WolfSkull_Normal>();
		break;
	case 100: // 나이 든 웨어울프
		NewSkull = GetLevel()->CreateActor<WolfSkull_Rare>();
		break;
	case 101: // 미노타우르스 1세 
		NewSkull = GetLevel()->CreateActor<MinotaurusSkull_Rare>();
		break;
	case 200: // 우두머리 웨어울프
		NewSkull = GetLevel()->CreateActor<WolfSkull_Unique>();
		break;	
	case 201: // 미노타우르스 2세
		NewSkull = GetLevel()->CreateActor<MinotaurusSkull_Unique>();
		break;
	case 203: // 경비대장
		NewSkull = GetLevel()->CreateActor<ChiefGuard>();
		break;
	case 300: // 영원의 웨어울프
		NewSkull = GetLevel()->CreateActor<WolfSkull_Legandary>();
		break;
	case 301: // 미노타우르스 3세
		NewSkull = GetLevel()->CreateActor<MinotaurusSkull_Legendary>();
		break;

	default:
		break;
	}

	if (nullptr != NewSkull)
	{
		NewSkull->GetTransform()->SetParent(GetTransform());
		NewSkull->SetPlayer(DynamicThis<Player>());
		NewSkull->Off();
	}

	NewSkull->GetTransform()->SetLocalPosition(float4(0, 0, 0));

	return NewSkull;
}

void Player::CreateColDebugRender()
{
	std::shared_ptr<CollisionDebugRender> BodyDebugRender = GetLevel()->CreateActor<CollisionDebugRender>();

	BodyDebugRender->SetColor(CollisionDebugRender::DebugColor::Magenta);
	BodyDebugRender->SetTargetCollision(PlayerBodyCol);
	BodyDebugRender->GetTransform()->SetParent(PlayerBodyCol->GetTransform(), false);
	BodyDebugRender->GetTransform()->AddLocalPosition(float4(0, 0, -10));
}

#include "PrecompileHeader.h"
#include "Player.h"
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineCollision.h>
#include <GameEnginePlatform/GameEngineInput.h>

#include "CollisionDebugRender.h"

#include "PlayerHitFade.h"
#include "PlayerState.h"
#include "PlayerStateFrame.h"
#include "Inventory.h"
#include "BaseQuintessence.h"

#include "BoneSkull.h"
#include "ChiefGuard.h"

#include "ContentLevel.h"

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
		MsgAssert_Rtti<Player>(" - ���� ���� ������ �������� �ʽ��ϴ�");
		return;
	}

	MainSkull->On();
}

void Player::HitPlayer(float _Damage, const float4& _HitForce)
{
	if (nullptr == MainSkull)
	{
		MsgAssert_Rtti<Player>(" - ���� �����Ͱ� �������� �ʴµ� �÷��̾ �����Ϸ� �߽��ϴ�");
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

	PlayerState::HP -= _Damage;

	HitWaitTime = 0.1f;
	HitFade->Active();
	MainSkull->HitRigidbody.AddVelocity(_HitForce);
	MainSkull->IsHit = true;
	MainSkull->IsHitEffectOn = true;
	MainSkull->HitEffect();
	MainSkull->HitPush();
}

void Player::PushPlayer(const float4& _HitForce)
{
	if (nullptr == MainSkull)
	{
		MsgAssert_Rtti<Player>(" - ���� �����Ͱ� �������� �ʴµ� �÷��̾ �о�� �߽��ϴ�");
		return;
	}

	MainSkull->JumpDir = _HitForce;
}

void Player::InputLock()
{
	IsInputLockValue = true;
}

void Player::InputUnlock()
{
	IsInputLockValue = false;
}

void Player::ActivePlayerFrame()
{
	StateFrame->On();
}

void Player::DisablePlayerFrame()
{
	StateFrame->Off();
}

void Player::Start()
{
	PlayerBodyCol = CreateComponent<GameEngineCollision>((int)CollisionOrder::Player);
	PlayerBodyCol->GetTransform()->SetLocalPosition(float4(0.0f, 30.0f, 1.0f));
	PlayerBodyCol->GetTransform()->SetWorldScale(float4(30.0f, 60.0f, 1.0f));
	PlayerBodyCol->GetTransform()->SetWorldRotation(float4::Zero);

	StateFrame = GetLevel()->CreateActor<PlayerStateFrame>();
	StateFrame->SetParentPlayer(this);

	HitFade = GetLevel()->CreateActor<PlayerHitFade>();

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
	HitWaitTime -= _DeltaTime;	
	SwitchCoolTime += _DeltaTime;

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
		MsgAssert_Rtti<Player>(" - ���� ������ �������� �ʽ��ϴ�.");
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
		SubSkull->SwitchEnter();
		SubSkull->On();
		SubSkull->DebugOff();

		MainSkull->CaptureRenderTex(float4(0.85f, 0.2f, 0.92f, 1.0f), float4(0.85f, 0.2f, 0.92f, 0.0f), 1.5f);
		MainSkull->Off();
		MainSkull->SwitchEnd();
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

	//LoadSkull({ .Name = "��Ʋ��", .Index = 0, .Grade = SkullGrade::Normal });
	//LoadSkull({ .Name = "�������", .Index = 1, .Grade = SkullGrade::Normal });
	//LoadSkull({ .Name = "���� �� �������", .Index = 100, .Grade = SkullGrade::Rare });
	//LoadSkull({ .Name = "�̳�Ÿ��ν�", .Index = 101, .Grade = SkullGrade::Rare });
	//LoadSkull({ .Name = "���ݼ���", .Index = 102, .Grade = SkullGrade::Rare });
	//LoadSkull({ .Name = "��θӸ� �������", .Index = 200, .Grade = SkullGrade::Unique });
	//LoadSkull({ .Name = "�̳�Ÿ��ν� 2��", .Index = 201, .Grade = SkullGrade::Unique });
	//LoadSkull({ .Name = "���� ���ݼ���", .Index = 202, .Grade = SkullGrade::Unique });
	//LoadSkull({ .Name = "������", .Index = 203, .Grade = SkullGrade::Unique });
	//LoadSkull({ .Name = "������ �������", .Index = 300, .Grade = SkullGrade::Legendary });
	//LoadSkull({ .Name = "�̳�Ÿ��ν� 3��", .Index = 301, .Grade = SkullGrade::Legendary });
	//LoadSkull({ .Name = "���� ���ݼ���", .Index = 302, .Grade = SkullGrade::Legendary });

	switch (_Index)
	{
	case 0: // ��Ʋ��
		NewSkull = GetLevel()->CreateActor<BoneSkull>();
		break;
	case 203: // ������
		NewSkull = GetLevel()->CreateActor<ChiefGuard>();
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

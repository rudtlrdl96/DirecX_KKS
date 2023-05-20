#include "PrecompileHeader.h"
#include "Player.h"
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineCollision.h>
#include <GameEnginePlatform/GameEngineInput.h>

#include "CollisionDebugRender.h"

#include "Inventory.h"
#include "BoneSkull.h"
#include "ChiefGuard.h"

Player::Player()
{
}

Player::~Player()
{
}

void Player::SetInventoryData()
{
	const SkullData& MainData = Inventory::GetMainSkull();
	const SkullData& SubData = Inventory::GetSubSkull();

	MainSkull = CreateNewSkull(MainData.Index);
	SubSkull = CreateNewSkull(SubData.Index);

	if (nullptr == MainSkull)
	{
		MsgAssert_Rtti<Player>(" - ���� ���� ������ �������� �ʽ��ϴ�");
		return;
	}

	MainSkull->On();
}

void Player::Start()
{
	PlayerBodyCol = CreateComponent<GameEngineCollision>((int)CollisionOrder::Player);
	PlayerBodyCol->GetTransform()->SetLocalPosition(float4(0.0f, 30.0f, 1.0f));
	PlayerBodyCol->GetTransform()->SetWorldScale(float4(30.0f, 60.0f, 1.0f));
	PlayerBodyCol->GetTransform()->SetWorldRotation(float4::Zero);
}

void Player::Update(float _DeltaTime)
{
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

	if (nullptr != SubSkull && true == MainSkull->IsSwitch())
	{
		DebugOff();

		ActorViewDir Dir = MainSkull->GetViewDir();

		EffectManager::PlayEffect({.EffectName = "SwitchEffect", 
			.Postion = GetTransform()->GetWorldPosition() + float4(0, 40, 0),
			.FlipX = Dir == ActorViewDir::Left});

 		SubSkull->PlayerFSM.ChangeState("Switch");
		SubSkull->SetViewDir(Dir);
		SubSkull->On();
		SubSkull->DebugOff();

		MainSkull->CaptureRenderTex(float4(0.85f, 0.2f, 0.92f, 1.0f), float4(0.85f, 0.2f, 0.92f, 0.0f), 1.5f);
		MainSkull->Off();
		MainSkull->DebugOff();
		MainSkull->IsSwitchValue = false;

		Inventory::SwapSkull();

		std::shared_ptr<PlayerBaseSkull> TempPtr = MainSkull;
		MainSkull = SubSkull;
		SubSkull = TempPtr;
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

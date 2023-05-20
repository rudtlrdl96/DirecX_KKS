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
		MsgAssert_Rtti<Player>(" - 메인 스컬 정보가 존재하지 않습니다");
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
		MsgAssert_Rtti<Player>(" - 메인 스컬이 존재하지 않습니다.");
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

	//LoadSkull({ .Name = "리틀본", .Index = 0, .Grade = SkullGrade::Normal });
	//LoadSkull({ .Name = "웨어울프", .Index = 1, .Grade = SkullGrade::Normal });
	//LoadSkull({ .Name = "나이 든 웨어울프", .Index = 100, .Grade = SkullGrade::Rare });
	//LoadSkull({ .Name = "미노타우로스", .Index = 101, .Grade = SkullGrade::Rare });
	//LoadSkull({ .Name = "연금술사", .Index = 102, .Grade = SkullGrade::Rare });
	//LoadSkull({ .Name = "우두머리 웨어울프", .Index = 200, .Grade = SkullGrade::Unique });
	//LoadSkull({ .Name = "미노타우로스 2세", .Index = 201, .Grade = SkullGrade::Unique });
	//LoadSkull({ .Name = "고위 연금술사", .Index = 202, .Grade = SkullGrade::Unique });
	//LoadSkull({ .Name = "경비대장", .Index = 203, .Grade = SkullGrade::Unique });
	//LoadSkull({ .Name = "영원의 웨어울프", .Index = 300, .Grade = SkullGrade::Legendary });
	//LoadSkull({ .Name = "미노타우로스 3세", .Index = 301, .Grade = SkullGrade::Legendary });
	//LoadSkull({ .Name = "검은 연금술사", .Index = 302, .Grade = SkullGrade::Legendary });

	switch (_Index)
	{
	case 0: // 리틀본
		NewSkull = GetLevel()->CreateActor<BoneSkull>();
		break;
	case 203: // 경비대장
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

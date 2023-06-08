#include "PrecompileHeader.h"
#include "WitchOpening.h"
#include "GameEngineActorGUI.h"
#include "Player.h"

WitchOpening::WitchOpening()
{
}

WitchOpening::~WitchOpening()
{
}

void WitchOpening::On()
{
	BaseNPC::On();

	if (nullptr != CagePtr)
	{
		CagePtr->On();
	}
}

void WitchOpening::Off()
{
	BaseNPC::Off();

	if (nullptr != CagePtr)
	{
		CagePtr->Off();
	}
}

void WitchOpening::Death()
{
	BaseNPC::Death();

	GetContentLevel()->RemoveEvent("MonsterAllDeath", GetActorCode());

	CagePtr->Death();
	CagePtr = nullptr;
}

void WitchOpening::Start()
{
	BaseNPC::Start();

	MainRender->CreateAnimation({
		.AnimationName = "CageIdle", .SpriteName = "Witch_OpeningCage.png", .ScaleToTexture = true });

	MainRender->CreateAnimation({
		.AnimationName = "HumanIdle", .SpriteName = "Witch_OpeningIdle.png", .ScaleToTexture = true });

	MainRender->CreateAnimation({
		.AnimationName = "Polymorp", .SpriteName = "Witch_HumanPolymorp.png", .Loop = false, .ScaleToTexture = true });

	MainRender->CreateAnimation({
		.AnimationName = "CatIdle", .SpriteName = "Witch_Cat_Idle.png", .ScaleToTexture = true });

	MainRender->CreateAnimation({
		.AnimationName = "CatWalk", .SpriteName = "Witch_Cat_Walk.png", .ScaleToTexture = true });

	MainRender->ChangeAnimation("CageIdle");

	CagePtr = GetLevel()->CreateActor<WitchCage>();
	CagePtr->GetTransform()->SetWorldPosition(GetTransform()->GetWorldPosition());
	CagePtr->Off();

	CagePtr->SetBrokenCallback([this]()
		{
			GetContentLevel()->CallEvent("WitchCageOut");
			GetContentLevel()->CallEvent("DoorLockMinus");
			PlayAnimation("HumanIdle", true);
		});

	GetContentLevel()->AddEvent("OpeningWitch_Script00_End", GetActorCode(), [this]()
		{
			PlayAnimation("Polymorp", true);

			Callback = [this]()
			{
				GetTransform()->AddLocalPosition(float4(0, 0, -5.0f));

				PlayAnimation("CageIdle", true);
				GetContentLevel()->CallEvent("StoryFadeOut");
				GetContentLevel()->CallEvent("PlayerInputUnlock");
				GetContentLevel()->CallEvent("PlayerFrameActive");
				IsPolymorpEnd = true;
			};
		});

	PlayerFindCol = CreateComponent<GameEngineCollision>();
	PlayerFindCol->GetTransform()->SetLocalScale(float4(100000, 100000, 1));

	GroundCol = CreateComponent<GameEngineCollision>();
	GroundCol->SetColType(ColType::AABBBOX2D);

	GroundCol->GetTransform()->SetLocalPosition(float4(0, 2.5f, 0));
	GroundCol->GetTransform()->SetLocalScale(float4(40, 5, 1));
}

void WitchOpening::Update(float _DeltaTime)
{
	BaseNPC::Update(_DeltaTime);

	if (nullptr == PlayerPtr && true == IsPolymorpEnd)
	{
		std::shared_ptr<GameEngineCollision> Col = PlayerFindCol->Collision((int)CollisionOrder::Player, ColType::AABBBOX2D, ColType::AABBBOX2D);
	
		if (nullptr != Col)
		{
			PlayerPtr = Col->GetActor()->DynamicThis<Player>();

			if (nullptr == PlayerPtr)
			{
				MsgAssert_Rtti<WitchOpening>(" - 플레이어만 Player ColOrder를 가질 수 있습니다.");
				return;
			}
		}
	}


	if (nullptr == PlayerPtr)
	{
		return;
	}

	if (true == PlayerPtr->IsDeath())
	{
		PlayerPtr = nullptr;
		return;
	}

	GameEngineTransform* WitchTrans = GetTransform();

	float4 DestPos;

	ActorViewDir PlayerViewDir = PlayerPtr->GetViewDir();

	switch (PlayerViewDir)
	{
	case ActorViewDir::Left:
	{
		DestPos = PlayerPtr->GetTransform()->GetWorldPosition() + float4(100, 0, 0);
	}
	break;
	case ActorViewDir::Right:
	{
		DestPos = PlayerPtr->GetTransform()->GetWorldPosition() + float4(-100, 0, 0);
	}
	break;
	}

	float4 Dir = DestPos - WitchTrans->GetWorldPosition();
	Dir.z = 0;

	float Dis = Dir.Size();

	if (0 < Dir.x)
	{
		WitchTrans->SetLocalNegativeScaleX();
	}
	else
	{
		WitchTrans->SetLocalPositiveScaleX();
	}

	Fall += _DeltaTime * ContentConst::Gravity_f;

	WitchTrans->AddLocalPosition(float4(0, Fall * _DeltaTime));

	std::shared_ptr<GameEngineCollision> ColCheck = ContentFunc::PlatformColCheck(GroundCol, true);

	if (nullptr != ColCheck)
	{
		float4 CurPos = WitchTrans->GetWorldPosition();
		CurPos.y = ColCheck->GetTransform()->GetWorldPosition().y + ColCheck->GetTransform()->GetWorldScale().hy();
		WitchTrans->SetLocalPosition(CurPos);

		Fall = 0.0f;
	}

	if (5.0f >= Dis)
	{
		PlayAnimation("CatIdle", false);

		switch (PlayerViewDir)
		{
		case ActorViewDir::Left:
		{
			WitchTrans->SetLocalPositiveScaleX();
		}
		break;
		case ActorViewDir::Right:
		{
			WitchTrans->SetLocalNegativeScaleX();
		}
		break;
		}
	}
	else
	{
		if (0 < Dir.x)
		{
			WitchTrans->AddLocalPosition(float4::Right * _DeltaTime * WalkSpeed);
		}
		else
		{
			WitchTrans->AddLocalPosition(float4::Left * _DeltaTime * WalkSpeed);
		}

		PlayAnimation("CatWalk", false);
	}

}

void WitchOpening::ResetBehavior()
{
	IsPolymorpEnd = false;
	PlayerPtr = nullptr;
	CagePtr->Off();
	CagePtr->Reset();
}

void WitchOpening::PlayBehavior()
{
	IsPolymorpEnd = false;
	PlayerPtr = nullptr;
	CagePtr->GetTransform()->SetWorldPosition(GetTransform()->GetWorldPosition());
	CagePtr->On();
	CagePtr->Reset();
	GetContentLevel()->CallEvent("DoorLockPlus");
}

void WitchOpening::SpriteLoad()
{
	if (nullptr == GameEngineSprite::Find("Witch_OpeningCage.png"))
	{
		GameEngineDirectory Path;

		Path.MoveParentToDirectory("Resources");
		Path.Move("Resources");
		Path.Move("Texture");
		Path.Move("1_Opening");
		Path.Move("Npc");
		Path.Move("Witch");
		Path.Move("Sheet");

		GameEngineSprite::LoadSheet(Path.GetPlusFileName("Witch_OpeningCage.png").GetFullPath(), 1, 1);
		GameEngineSprite::LoadSheet(Path.GetPlusFileName("Witch_OpeningIdle.png").GetFullPath(), 6, 1);
		GameEngineSprite::LoadSheet(Path.GetPlusFileName("Witch_HumanPolymorp.png").GetFullPath(), 21, 1);
		GameEngineSprite::LoadSheet(Path.GetPlusFileName("Witch_Cat_Idle.png").GetFullPath(), 6, 1);
		GameEngineSprite::LoadSheet(Path.GetPlusFileName("Witch_Cat_Walk.png").GetFullPath(), 6, 1);
	}
}
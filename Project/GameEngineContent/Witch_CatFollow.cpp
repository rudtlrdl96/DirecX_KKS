#include "PrecompileHeader.h"
#include "Witch_CatFollow.h"
#include "Player.h"

Witch_CatFollow::Witch_CatFollow()
{
}

Witch_CatFollow::~Witch_CatFollow()
{
}

void Witch_CatFollow::SpriteLoad()
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

void Witch_CatFollow::Start()
{
	BaseNPC::Start();

	MainRender->CreateAnimation({
		.AnimationName = "CatIdle", .SpriteName = "Witch_Cat_Idle.png", .ScaleToTexture = true });

	MainRender->CreateAnimation({
		.AnimationName = "CatWalk", .SpriteName = "Witch_Cat_Walk.png", .ScaleToTexture = true });

	PlayerFindCol = CreateComponent<GameEngineCollision>();
	PlayerFindCol->GetTransform()->SetLocalScale(float4(100000, 100000, 1));

	GroundCol = CreateComponent<GameEngineCollision>();
	GroundCol->SetColType(ColType::AABBBOX2D);

	GroundCol->GetTransform()->SetLocalPosition(float4(0, 2.5f, 0));
	GroundCol->GetTransform()->SetLocalScale(float4(40, 5, 1));

	PlayAnimation("CatIdle", true);
}

void Witch_CatFollow::Update(float _DeltaTime)
{
	BaseNPC::Update(_DeltaTime);

	if (nullptr == PlayerPtr)
	{
		std::shared_ptr<GameEngineCollision> Col = PlayerFindCol->Collision((int)CollisionOrder::Player, ColType::AABBBOX2D, ColType::AABBBOX2D);

		if (nullptr != Col)
		{
			PlayerPtr = Col->GetActor()->DynamicThis<Player>();

			if (nullptr == PlayerPtr)
			{
				MsgAssert_Rtti<Witch_CatFollow>(" - 플레이어만 Player ColOrder를 가질 수 있습니다.");
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

	float Dis = fabsf(DestPos.x - WitchTrans->GetWorldPosition().x);

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

void Witch_CatFollow::ResetBehavior()
{
	PlayerPtr = nullptr;
	PlayAnimation("CatIdle", false);
}

void Witch_CatFollow::PlayBehavior()
{
	PlayerPtr = nullptr;
	PlayAnimation("CatIdle", false);
}

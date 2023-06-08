#include "PrecompileHeader.h"
#include "CarleonManAtArms.h"
#include <GameEngineCore/GameEngineCollision.h>
#include "ContentLevel.h"

CarleonManAtArms::CarleonManAtArms()
{
}

CarleonManAtArms::~CarleonManAtArms()
{
}

void CarleonManAtArms::Start()
{
	HealthBarScale = float4(1.5f, 1.5f, 1.5f, 1.0f);
	NormalMonster::Start();
}

void CarleonManAtArms::DataLoad()
{
	Data = ContentDatabase<MonsterData, LevelArea>::GetData(106); // 106 = 칼레온 중보병

	IsSuperArmor = true;
	AttackWaitEndTime = 2.0f;
	TacklePauseTimes[0] = 0.5f;
	TacklePauseTimes[1] = 0.6f;
	TacklePauseTimes[2] = 0.4f;
}

void CarleonManAtArms::TextureLoad()
{
	if (nullptr == GameEngineSprite::Find("ManAtArms_StempEffect.png"))
	{
		GameEngineDirectory Path;

		Path.MoveParentToDirectory("Resources");
		Path.Move("Resources");
		Path.Move("Texture");
		Path.Move("3_ForestOfHarmony");
		Path.Move("Monster");

		{
			Path.Move("CarleonManAtArms");
			Path.Move("Effect");

			GameEngineSprite::LoadSheet(Path.GetPlusFileName("ManAtArms_StempEffect.png").GetFullPath(), 3, 4);
			GameEngineSprite::LoadSheet(Path.GetPlusFileName("ManAtArms_TackleFlash.png").GetFullPath(), 7, 2);
			GameEngineSprite::LoadSheet(Path.GetPlusFileName("ManAtArms_TackleSmoke.png").GetFullPath(), 4, 5);

			Path.MoveParent();
			Path.MoveParent();
		}

		EffectManager::CreateMetaData("ManAtArms_StempEffect", {
			.SpriteName = "ManAtArms_StempEffect.png",
			.AnimStart = 0,
			.AnimEnd = 11,
			.AnimIter = 0.025f,
			.ScaleRatio = 2.0f,
			});

		EffectManager::CreateMetaData("ManAtArms_TackleFlash", {
			.SpriteName = "ManAtArms_TackleFlash.png",
			.AnimStart = 0,
			.AnimEnd = 13,
			.AnimIter = 0.07f,
			.ScaleRatio = 3.0f,
			});

		EffectManager::CreateMetaData("ManAtArms_TackleSmoke", {
			.SpriteName = "ManAtArms_TackleSmoke.png",
			.AnimStart = 0,
			.AnimEnd = 16,
			.AnimIter = 0.05f,
			.ScaleRatio = 2.0f,
			});
	}
}

void CarleonManAtArms::LoadAnimation()
{
	Render->CreateAnimation({ .AnimationName = "Idle",  .SpriteName = "CarleonManAtArms_Idle.png", .Start = 0, .End = 4, .ScaleToTexture = true });
	Render->CreateAnimation({ .AnimationName = "Walk",  .SpriteName = "CarleonManAtArms_Walk.png", .Start = 0, .End = 7, .ScaleToTexture = true });
	Render->CreateAnimation({ .AnimationName = "Hit1",  .SpriteName = "CarleonManAtArms_Idle.png", .Start = 0, .End = 0, .ScaleToTexture = true });
	Render->CreateAnimation({ .AnimationName = "Hit2",  .SpriteName = "CarleonManAtArms_Idle.png", .Start = 0, .End = 0, .ScaleToTexture = true });
	Render->CreateAnimation({ .AnimationName = "Death", .SpriteName = "CarleonManAtArms_Dead.png", .Start = 0, .End = 0, .ScaleToTexture = true });
}

void CarleonManAtArms::AnimationAttackMetaDataLoad()
{
	AnimPauseTimes[2] = 0.5f;
	AnimPauseTimes[5] = 0.75f;

	AttackRigidbody.SetMaxSpeed(1000.0f);
	AttackRigidbody.SetFricCoeff(2000.0f);

	{
		GameEngineDirectory Path;

		Path.MoveParentToDirectory("Resources");
		Path.Move("Resources");
		Path.Move("Data");
		Path.Move("3_ForestOfHarmony");
		Path.Move("Monster");

		AnimColMeta_Attack = ContentFunc::LoadAnimAttackMetaData(Path.GetPlusFileName("CarleonManAtArms_Attack").GetFullPath());

		Render->CreateAnimation({
			.AnimationName = AnimColMeta_Attack.GetAnimationName().data(),
			.SpriteName = AnimColMeta_Attack.GetSpriteName().data(),
			.Start = AnimColMeta_Attack.GetStartFrame(),
			.End = AnimColMeta_Attack.GetEndFrame(),
			.Loop = false,
			.ScaleToTexture = true });

		AnimColMeta_Tackle = ContentFunc::LoadAnimAttackMetaData(Path.GetPlusFileName("CarleonManAtArms_Tackle").GetFullPath());

		Render->CreateAnimation({
			.AnimationName = AnimColMeta_Tackle.GetAnimationName().data(),
			.SpriteName = AnimColMeta_Tackle.GetSpriteName().data(),
			.Start = AnimColMeta_Tackle.GetStartFrame(),
			.End = AnimColMeta_Tackle.GetEndFrame(),
			.Loop = false,
			.ScaleToTexture = true });
	}
}

void CarleonManAtArms::SetColData()
{
	DeathEffectLocalPos = float4(0, 80, -0.1f);

	{
		GameEngineTransform* ColTrans = GroundCol->GetTransform();

		ColTrans->SetLocalPosition(float4(0, -3, 0));
		ColTrans->SetWorldScale(float4(70, 6, 1));
	}

	{
		GameEngineTransform* ColTrans = BodyCol->GetTransform();

		ColTrans->SetLocalPosition(float4(0, 70, 0));
		ColTrans->SetWorldScale(float4(80, 140, 1));
	}

	{
		GameEngineTransform* ColTrans = WalkCol->GetTransform();

		LocalWalkColPos = float4(45, 72, 0);

		ColTrans->SetLocalPosition(LocalWalkColPos);
		ColTrans->SetWorldScale(float4(10, 140, 1));
	}
	{
		GameEngineTransform* ColTrans = BackCol->GetTransform();

		LocalBackColPos = float4(-45, 72, 0);

		ColTrans->SetLocalPosition(LocalBackColPos);
		ColTrans->SetWorldScale(float4(10, 140, 1));
	}
	{
		GameEngineTransform* ColTrans = WalkFallCol->GetTransform();

		LocalWalkFallColPos = float4(45, 55, 0);

		ColTrans->SetLocalPosition(LocalWalkFallColPos);
		ColTrans->SetWorldScale(float4(10, 170, 1));
	}

	{
		GameEngineTransform* ColTrans = FindCol->GetTransform();

		LocalFindColPos = float4(200, 50, 0);

		ColTrans->SetLocalPosition(LocalFindColPos);
		ColTrans->SetWorldScale(float4(400, 100, 1));
	}

	{
		GameEngineTransform* ColTrans = ChasingCol->GetTransform();

		LocalChasingColPos = float4(50, 50, 0);

		ColTrans->SetLocalPosition(LocalChasingColPos);
		ColTrans->SetWorldScale(float4(100, 100, 1));
	}

	LoadFindEffectPos = float4(0, 150, 0);
}

void CarleonManAtArms::DeathPartLoad()
{
	DeathPartScale = 2.0f;

	DeadPartNames.reserve(8);
	DeadPartNames.push_back("Parts_CaerleonManAtArms01.png");
	DeadPartNames.push_back("Parts_CaerleonManAtArms02.png");
	DeadPartNames.push_back("Parts_CaerleonManAtArms03.png");
	DeadPartNames.push_back("Parts_CaerleonManAtArms04.png");
	DeadPartNames.push_back("Parts_CaerleonManAtArms05.png");
	DeadPartNames.push_back("Parts_CaerleonManAtArms06.png");
	DeadPartNames.push_back("Parts_CaerleonManAtArms07.png");
	DeadPartNames.push_back("Parts_CaerleonManAtArms08.png");

	if (nullptr == GameEngineTexture::Find("Parts_CaerleonManAtArms01.png"))
	{
		GameEngineDirectory Path;
		Path.MoveParentToDirectory("Resources");
		Path.Move("Resources");
		Path.Move("Texture");
		Path.Move("3_ForestOfHarmony");
		Path.Move("Monster");
		Path.Move("CarleonManAtArms");
		Path.Move("DeadPart");

		std::vector<GameEngineFile> Files = Path.GetAllFile({ ".png" });

		for (size_t i = 0; i < Files.size(); i++)
		{
			std::shared_ptr<GameEngineTexture> LoadTex = GameEngineTexture::Load(Files[i].GetFullPath());

			if (nullptr == LoadTex)
			{
				MsgAssert_Rtti<CarleonManAtArms>(" - 알 수 없는 이유로 DeadPart 텍스쳐 로드를 실패했습니다");
			}
		}
	}
}

void CarleonManAtArms::Attack_Enter()
{
	IsUnPushArmor = true;
	IsTackleAttack = false;
	IsAttackStempEffect = false;
	
	if (0 == GameEngineRandom::MainRandom.RandomInt(0, 1))
	{
		IsTackleAttack = true;
		IsTackleEffect = false;

		if ("" == AnimColMeta_Tackle.GetAnimationName())
		{
			MsgAssert_Rtti<CarleonManAtArms>(" - 칼레온중보병의 태클 공격 정보가 존재하지 않습니다");
		}

		Render->ChangeAnimation(AnimColMeta_Tackle.GetAnimationName());
		AttackRigidbody.SetVelocity(float4::Zero);

		AttackCheckFrame = 0;
		CurPauseTime = 0.0f;
		AttackCheck.SetColData(AnimColMeta_Tackle);

		AttakPushRatio = 2.0f;
	}
	else
	{
		NormalMonster::Attack_Enter();	
		AttackCheck.SetColData(AnimColMeta_Attack);
		AttakPushRatio = 1.0f;
	}
}

void CarleonManAtArms::Attack_Update(float _DeltaTime)
{
	if (true == IsTackleAttack)
	{
		if (true == HitCheck())
		{
			return;
		}
			
		if (1 == Render->GetCurrentFrame())
		{
			if (false == IsTackleEffect)
			{
				IsTackleEffect = true;

				// ManAtArms_TackleFlash

				float4 SmokeEffectPos = GetTransform()->GetWorldPosition();

				switch (Dir)
				{
				case ActorViewDir::Left:
					SmokeEffectPos += float4(150, 0, -0.1f);
					break;
				case ActorViewDir::Right:
					SmokeEffectPos += float4(-150, 0, -0.1f);
					break;
				default:
					break;
				}

				std::shared_ptr<EffectActor> SmokeEffect = EffectManager::PlayEffect({
					.EffectName = "ManAtArms_TackleSmoke",
					.Position = SmokeEffectPos,
					.FlipX = Dir == ActorViewDir::Left,
					});

				SmokeEffect->GetTransform()->SetParent(GetTransform());

				float4 FlashEffectPos = GetTransform()->GetWorldPosition();

				switch (Dir)
				{
				case ActorViewDir::Left:
					FlashEffectPos += float4(60, 80, -0.1f);
					break;
				case ActorViewDir::Right:
					FlashEffectPos += float4(-60, 80, -0.1f);
					break;
				default:
					break;
				}

				std::shared_ptr<EffectActor> FlashEffect = EffectManager::PlayEffect({
					.EffectName = "ManAtArms_TackleFlash",
					.Position = FlashEffectPos,
					.FlipX = Dir == ActorViewDir::Left,
					});

				FlashEffect->GetTransform()->SetParent(GetTransform());
			}

			switch (Dir)
			{
			case ActorViewDir::Left:
				AttackRigidbody.SetVelocity(float4::Left * 600.0f);
				break;
			case ActorViewDir::Right:
				AttackRigidbody.SetVelocity(float4::Right * 600.0f);
				break;
			default:
				break;
			}
		}

		Fall(_DeltaTime);
		AttackRigidbody.UpdateForce(_DeltaTime);

		size_t CurFrame = Render->GetCurrentFrame();

		if (AttackCheckFrame != CurFrame)
		{
			AttackCheckFrame = CurFrame;
			CurPauseTime = 0.0f;
		}

		CurPauseTime += _DeltaTime;

		if (TacklePauseTimes[AttackCheckFrame] > CurPauseTime)
		{
			Render->SetAnimPauseOn();
		}
		else
		{
			Render->SetAnimPauseOff();
		}

		if (nullptr == ContentFunc::PlatformColCheck(WalkCol))
		{
			float4 Velocity = AttackRigidbody.GetVelocity() * _DeltaTime;
			GetTransform()->AddLocalPosition(Velocity);
		}

		if (true == Render->IsAnimationEnd())
		{
			MonsterFsm.ChangeState("Idle");
			return;
		}

		AttackCheck.Update();
	}
	else
	{
		NormalMonster::Attack_Update(_DeltaTime);


		if (false == IsAttackStempEffect && 3 == Render->GetCurrentFrame())
		{
			IsAttackStempEffect = true;

			float4 EffectPos = GetTransform()->GetWorldPosition();

			switch (Dir)
			{
			case ActorViewDir::Left:
				EffectPos += float4(-40, 0, -0.1f);
				break;
			case ActorViewDir::Right:
				EffectPos += float4(40, 0, -0.1f);
				break;
			default:
				break;
			}

			EffectManager::PlayEffect({
				.EffectName = "ManAtArms_StempEffect",
				.Position = EffectPos });

			// CameraShake

			std::shared_ptr<ContentLevel> ContentLevelPtr = GetLevel()->DynamicThis<ContentLevel>();

			if (nullptr != ContentLevelPtr)
			{
				ContentLevelPtr->GetCamCtrl().CameraShake(20, 20.0f, 4);
			}
		}
	}
}

void CarleonManAtArms::Attack_End()
{
	NormalMonster::Attack_End();
	IsUnPushArmor = false;
}
